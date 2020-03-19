#include "DecodeSos.h"
#include "../UtilDecode/UtilDecode.h"
#include "../../UtilCore/UtilCore.h"
#include "../../../data/md1database/md1database.h"

#include <stdio.h>
#include <string.h>

extern int printMessages;

int decodeSosMail(const char *password, struct SosMail *sosMailResult)
{
    size_t pswLenght = strlen(password);
    if (pswLenght != 54) {
        if (printMessages) {
            fprintf(stderr, "ERROR: You password lenght is %u characters, and it must have exactly 54 characters.\n\n"
                            "THE PASSWORD CAN'T BE DECODED.\n\n", (unsigned int)pswLenght);
        }
        return InputError;
    }

    char allocatedPassword[54] = {0};

    const unsigned char newPositions[] = { 13, 7, 25, 15, 4, 29, 42, 49, 8, 19, 45, 24, 14, 26, 27, 41, 1, 32, 33, 34, 17, 51, 38, 0, 53, 10, 43, 31, 18, 35, 44, 23, 39, 16, 28, 48, 11, 2, 36, 9, 50, 5, 40, 52, 46, 3, 30, 12, 37, 20, 47, 22, 6, 21 };
    reallocateBytes(password, newPositions, 54, allocatedPassword);

    /* The password that will be converted to integers representation using the lookup table bellow */
    char password54Integers[54] = {0};
    const char* lookupTable = "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W";
    int errorCode = mapPasswordByPositionInLookupTable(allocatedPassword, lookupTable, 54, password54Integers);
    if (errorCode != NoError) {
        return errorCode;
    }

    char packed34BytesPassword[34] = {0};
    /* Bit packing */
    bitPackingDecoding(packed34BytesPassword, password54Integers, 54); /* Pack the password */

    /* Checksum */
    int checksum = computeChecksum(packed34BytesPassword + 1, 33); /* the first byte is ignored in the calculation, cuz is merely for a checksum */
    if (checksum != (packed34BytesPassword[0] & 0xFF)) {
        if (printMessages) {
            fprintf(stderr, "ERROR: Checksum failed, so the password is INVALID.\n\n"
                            "THE PASSWORD CAN'T BE DECODED.\n\n");
            fflush(stderr);
        }
        return ChecksumError;
    }

    /* The first byte in the 35 byte packed password was merely a checksum, so it's useless and I'll remove it */
    char* packed33BytesPassword = packed34BytesPassword + 1; /* You must be firm in pointer's arithmetic to handle this */

    /* Bit unpacking */
    struct SosMail sosm = { 0, 0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0 }; /* To store the decoded SOS Mail */
    bitUnpackingDecodingSosMail(packed33BytesPassword, &sosm);
    int errors = entryErrorsSosMail(&sosm);
    if (errors) {
        if (printMessages) {
            fprintf(stderr, " :: %d ERRORS FOUND. DECODING IS NOT POSSIBLE.\a\n\n", errors);
            fflush(stderr);
        }
        return InputError; /* to use the NOT operator */
    }
    
    *sosMailResult = sosm;

    return NoError;
}


void bitUnpackingDecodingSosMail(const char *packed33BytesPassword, struct SosMail *mail)
{
    /*
        As a final step, the password is converted into a Wonder Mail by
        unpacking the bits of the 33-bytes password.
        Bit unpacking is the reverse of bit packing.
        It starts with the rightmost bit of the first byte. That bit is
        retrieved and stored in the rightmost position of the result.
        Then the next bit is retrieved and stored, and so on until all bits
        are stored. If a bit cannot be retrieved and stored in the source or the result,
        then the next byte of the source or the result is used.
    */

    /* As final observation, I only will read the bits in the array, without destroying bits, instead I'll shift bits: non-destructive read is faster and safer than destructive read */

    mail->mailType = (packed33BytesPassword[0] & 0x0F);  /* get the 4 rightmost bits of the first byte. An AND operation with 0x0F=1111 turn (before assignment) zeros all bits except the first four bits */

    mail->dungeon  = (packed33BytesPassword[0] >> 4) & 0x0F; /* in the first byte there is four unused bits, so rightshift 4 bits to destroy the first 4 bits and make an AND with 0x0F=1111 to obtain the bits. Now the first byte has been used, so the next byte will be used */
    mail->dungeon |= (packed33BytesPassword[1] & 0x07) << 4; /* we need 3 more bits to fit the second field. An AND with 0x07=111 give to us the value of the first three bits */

    mail->floor  = (packed33BytesPassword[1] >> 3) & 0x1F; /* we already get 3 bits from this byte, so before obtain the remaining 5 bits it's neccesary rightshift the bits used earlier. AND with 0x1F=11111 give five bits. Now the first byte has been used, so the next byte will be used */
    mail->floor |= (packed33BytesPassword[2] & 0x03) << 5; /* we need 2 more bits to fit the field, but we already get bits from this byte, so rightshift the bits used earlier (4 in this case). Then an AND with 0x03=11 give to us the two bits */

    /* No more detailed comments, now you should know what to do... unless you are stu&@$... upppss! ;) */
    mail->idk_random  = (packed33BytesPassword[2] >> 2) & 0x3F; /* get 6 bits, 0 remaining (next byte will be used) */
    mail->idk_random |= (packed33BytesPassword[3] & 0xFF) << 6; /* get the full byte */
    mail->idk_random |= (packed33BytesPassword[4] & 0xFF) << 14; /* get the full byte */
    mail->idk_random |= (packed33BytesPassword[5] & 0x03) << 22; /* get 2 bits, 6 remaining */

    mail->pkmnToRescue  = (packed33BytesPassword[5] >> 2) & 0x3F; /* get 6 bits, 0 remaining */
    mail->pkmnToRescue |= ((packed33BytesPassword[6]) & 0x07) << 6; /* get 3 bits, 5 remaining */

    mail->mailID  = (packed33BytesPassword[6] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->mailID |= (packed33BytesPassword[7] & 0xFF) << 5; /* get the full byte */
    mail->mailID |= (packed33BytesPassword[8] & 0x07) << 13; /* get 3 bits, 5 remaining */
    mail->mailID &= 0xFFFF; /** REVIEW THIS IF THERE ARE PROBLEMS WITH THE MAIL ID */

    mail->idk_random2 = (packed33BytesPassword[8] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->idk_random2 |= (packed33BytesPassword[9] & 0xFF) << 5; /* get the full byte */
    mail->idk_random2 |= (packed33BytesPassword[10] & 0x07) << 13; /* get 3 bits, 5 remaining */

    mail->pkmnNick[0]  = (packed33BytesPassword[10] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->pkmnNick[0] |= (packed33BytesPassword[11] & 0x07) << 5; /* get 3 bits, 5 remaining */
    mail->pkmnNick[1]  = (packed33BytesPassword[11] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->pkmnNick[1] |= (packed33BytesPassword[12] & 0x07) << 5; /* get 3 bits, 5 remaining */
    mail->pkmnNick[2]  = (packed33BytesPassword[12] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->pkmnNick[2] |= (packed33BytesPassword[13] & 0x07) << 5; /* get 3 bits, 5 remaining */
    mail->pkmnNick[3]  = (packed33BytesPassword[13] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->pkmnNick[3] |= (packed33BytesPassword[14] & 0x07) << 5; /* get 3 bits, 5 remaining */
    mail->pkmnNick[4]  = (packed33BytesPassword[14] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->pkmnNick[4] |= (packed33BytesPassword[15] & 0x07) << 5; /* get 3 bits, 5 remaining */
    mail->pkmnNick[5]  = (packed33BytesPassword[15] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->pkmnNick[5] |= (packed33BytesPassword[16] & 0x07) << 5; /* get 3 bits, 5 remaining */
    mail->pkmnNick[6]  = (packed33BytesPassword[16] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->pkmnNick[6] |= (packed33BytesPassword[17] & 0x07) << 5; /* get 3 bits, 5 remaining */
    mail->pkmnNick[7]  = (packed33BytesPassword[17] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->pkmnNick[7] |= (packed33BytesPassword[18] & 0x07) << 5; /* get 3 bits, 5 remaining */
    mail->pkmnNick[8]  = (packed33BytesPassword[18] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->pkmnNick[8] |= (packed33BytesPassword[19] & 0x07) << 5; /* get 3 bits, 5 remaining */
    mail->pkmnNick[9]  = (packed33BytesPassword[19] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->pkmnNick[9] |= (packed33BytesPassword[20] & 0x07) << 5; /* get 3 bits, 5 remaining */

    mail->idk_0Or1  = (packed33BytesPassword[21] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->idk_0Or1 |= (packed33BytesPassword[22] & 0x07) << 5; /* get 3, 5 remaining */

    mail->itemReward  = (packed33BytesPassword[22] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->itemReward |= (packed33BytesPassword[23] & 0x07) << 5; /* get 3, 5 remaining */

    mail->idk_0  = (packed33BytesPassword[22] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->idk_0 |= (packed33BytesPassword[23] & 0x07) << 5; /* get 3, 5 remaining */

    mail->teamSeekingHelpID  = (packed33BytesPassword[23] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->teamSeekingHelpID |= (unsigned int)(packed33BytesPassword[24] & 0xFF) << 5; /* get the full byte */
    mail->teamSeekingHelpID |= (unsigned int)(packed33BytesPassword[25] & 0xFF) << 13; /* get the full byte */
    mail->teamSeekingHelpID |= (unsigned int)(packed33BytesPassword[26] & 0xFF) << 21; /* get the full byte */
    mail->teamSeekingHelpID |= (unsigned int)(packed33BytesPassword[27] & 0x07) << 29; /* get 3 bits, 5 remaining */

    mail->teamGivingHelpID  = (packed33BytesPassword[27] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->teamGivingHelpID |= (unsigned int)(packed33BytesPassword[28] & 0xFF) << 5; /* get the full byte */
    mail->teamGivingHelpID |= (unsigned int)(packed33BytesPassword[29] & 0xFF) << 13; /* get the full byte */
    mail->teamGivingHelpID |= (unsigned int)(packed33BytesPassword[30] & 0xFF) << 21; /* get the full byte */
    mail->teamGivingHelpID |= (unsigned int)(packed33BytesPassword[31] & 0x07) << 29; /* get 3 bits, 5 remaining */

    mail->chancesLeft  = (packed33BytesPassword[31] >> 3) & 0x1F; /* get 5 bits, 0 remaining */
    mail->chancesLeft |= (packed33BytesPassword[32] & 0x1F) << 5; /* get 3 bits, 5 remaining */

    mail->idk_last3Bits = (packed33BytesPassword[32] >> 3) & 0x07; /* get 3 bits and... finish! */
}


void setSosInfo(const struct SosMail *mail, struct SosMailInfo *sosInfo)
{
    int mailType = mail->mailType;
    strcpy(sosInfo->head, mailType == AOkMailType ? SOS_GoHelp1 : mailType == ThankYouMailType ? SOS_Thanks1 : SOS_AskHelp1);
    strcpy(sosInfo->body, mailType == AOkMailType ? SOS_GoHelp2 : mailType == ThankYouMailType ? SOS_Thanks2 : SOS_AskHelp2);
    strncpy(sosInfo->nickname, mail->pkmnNick, 10);  /* ensure not buffer overflow */
    strcpy(sosInfo->client, mail->pkmnToRescue >= pkmnSpeciesCount ? "[INVALID]" : pkmnSpeciesStr[mail->pkmnToRescue]);
    strcpy(sosInfo->objective, missionTypeObjectiveStr[FriendRescue]);
    strcpy(sosInfo->place, mail->dungeon >= dungeonsCount ? "[INVALID]" : dungeonsStr[mail->dungeon]);
    sprintf(sosInfo->floor, "%c%dF", mail->dungeon >= dungeonsCount ? '?' : dungeonUpOrDown[mail->dungeon], mail->floor);
    int diffValue = computeDifficulty(mail->dungeon, mail->floor, FriendRescue);
    sosInfo->difficulty = diffValue >= difficultiesCharsCount ? '?' : difficultiesChars[diffValue];
    strcpy(sosInfo->reward, mailType != ThankYouMailType ? "???" : (mail->itemReward >= itemsCount ? "[INVALID]" : itemsStr[mail->itemReward]));
    sprintf(sosInfo->id, "%d", mail->mailID);
    sprintf(sosInfo->chancesLeft, "%d", mail->chancesLeft % 11); /* ensure not buffer overflow */
}
