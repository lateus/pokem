#include "EncodeSOS.h"
#include "../UtilEncode/UtilEncode.h"
#include "../../UtilCore/UtilCore.h"
#include "../../../data/md1database/md1database.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int encodeSOSMail(struct SOSMAIL *sos, char *finalPassword)
{
    srand((unsigned int)time(NULL));

    sos->idk_random2 = rand() & 0xFFFF;
    sos->mailType = 1;                                 /* must be 1 for SOS Mail */
    sos->idk_random = (unsigned int)rand() & 0xFFFFFF; /* same as % ‭16777216 */
    sos->idk_0Or1 = 0;                                 /* 1 if Thank-You Mail, otherwise 0 */
    sos->itemReward = 0;                               /* 0 if not Thank-You Mail */
    sos->idk_0 = 0;                                    /* as his name suggest */
    sos->teamSeekingHelpID = (unsigned int)rand() & 0xFFFFFFFF;
    sos->teamGivingHelpID = 0; /* For SOS Mail, this is 0 */
    sos->idk_last3Bits = 0;

    int errors = foundErrorsEntriesSOS(sos);
    if (errors) {
        fprintf(stderr, " :: %d ERRORS FOUND. DECODING IS NOT POSSIBLE.\a\n\n", errors);
        return INPUT_ERROR; /* to use the NOT operator */
    }

    char packed34BytesPassword[34] = {0}; /* the first byte is merely a checksum */
    char *packed33BytesPassword = packed34BytesPassword + 1; /* be aware about pointer's arithmetic if you don't want an unexpectly behavior at runtime */
    bitPackingEncodingSOS(packed33BytesPassword, sos); /* bit packing while decoding are equivalent to bit unpacking while encoding */

    packed34BytesPassword[0] = (char)computeChecksum(packed34BytesPassword, 34);

    char password54Integers[54] = {0};
    bitUnpackingEncoding(password54Integers, packed34BytesPassword, 34);

    char password54Chars[54] = {0};
    lookupTableEncodingSOS(password54Chars, password54Integers);

    realocateBytesEncodingSOS(finalPassword, password54Chars);

    return 0;
}

int foundErrorsEntriesSOS(const struct SOSMAIL *sos)
{
    int errorsFound = 0;

    /* pkmn to rescue check (limits) */
    if (sos->pkmnToRescue == 0 || sos->pkmnToRescue > 404) {
        fprintf(stderr, "ERROR No. %d in argument 1 (Pkmn to rescue).\n"
                        "      Pkmns must be numbers between 1 and 404 (not necessarily match pkdex numbers).\n\n", ++errorsFound);
    }

    /* dungeon check */
    if (sos->dungeon > 63) {
        fprintf(stderr, "ERROR No. %d in argument 3 (Dungeon).\n"
                        "      The dungeon must be a number between 0 and 63.\n\n", ++errorsFound);
    } else if (!strcmp(dungeonsStr[sos->dungeon], "[INVALID]")) {
        fprintf(stderr, "ERROR No. %d in argument 3 (Dungeon).\n"
                        "      The dungeon with index %u isn't a valid dungeon.\n\n", ++errorsFound, sos->dungeon);
    } else if (sos->floor > difficulties[sos->dungeon][0]) { /* floor check */
        fprintf(stderr, "ERROR No. %d in argument 4 (Floor).\n"
                        "      The dungeon %s (index %u) only has %d floors. Your entry exceed that value.\n\n",
                                    ++errorsFound, dungeonsStr[sos->dungeon], sos->dungeon, difficulties[sos->dungeon][0]);
    }

    /* rescue chances left */
    if (sos->chancesLeft < 1 || sos->chancesLeft > 10) {
        fprintf(stderr, "ERROR No. %d in argument 6 (Chances left).\n"
                        "      The chances left value must be between 1 and 10.\n\n", ++errorsFound);
    }

    return errorsFound;
}

void bitPackingEncodingSOS(char* packed33BytesPassword, const struct SOSMAIL* mail)
{
    /*
        The structure of the SOS Mail struct is the following (see md1global.h):
        unsigned int mailType:4; ----------------  4 bits: Must equal 1 for SOS Mail, 4 for A-OK Mail, and 5 for Thank-You Mail
        unsigned int dungeon:7; -----------------  7 bits: Dungeon
        unsigned int floor:7; -------------------  7 bits: Floor (e.g. set to 2 for 2nd floor). The game will turn the floor negative if necesary
        unsigned int idk_random:24; ------------- 24 bits: 3 bytes for unknown purpose
        unsigned int pkmnToRescue:9; ------------  9 bits: Pokemon to be rescued
        unsigned int mailID:16; ----------------- 16 bits: Mail ID
        unsigned int idk_random2:16; ------------ 16 bits: 2 bytes for unknown purpose
        char         pkmnNick[10]; -------------- 80 bits: Pokemon's nickname, 0 marks end of name if shorter than 10 bytes
        unsigned int idk_0Or1:8; ----------------  8 bits: Unknown purpose. Safe to set to 1 if Thank-You Mail, else set to 0
        unsigned int itemReward:8; --------------  8 bits: Item reward. Safe to set to 0 if not Thank-You Mail
        unsigned int idk_0:8; -------------------  8 bits: Unknown purpose. Safe to set to 0
        unsigned int teamSeekingHelpID:32; ------ 32 bits: ID of rescue team seeking help
        unsigned int teamGivingHelpID:32; ------- 32 bits: ID of rescue team giving help. For SOS Mail, this is 0; for A-OK Mail, safe to set to rescue team seeking help
        unsigned int chancesLeft:8; -------------  8 bits: Rescue chances left; when converting to A-OK Mail, subtract 1 from this
        unsigned int idk_last3Bits:3; -----------  3 bits: Unknown. Safe to set to 0
    */

    /* I wrote the bits that a field must store, assign more will cause an overflow. I'll use Standard C Bit Fields. */
    /* As final observation, I only will read the bits in the array, without destroying bits, instead I'll shift bits: non-destructive read is faster and safer than destructive read */

    packed33BytesPassword[0]   = (mail->mailType & 0x0F);   /* Get the 4 bits of the field. */
    packed33BytesPassword[0]  |= (mail->dungeon & 0x0F) << 4;   /* get other 4 bits and leftshift bits before assignment. */

    packed33BytesPassword[1]   = ((mail->dungeon >> 4) & 0x07); /* we already got 4 bits from this field, so we rightshift a bit and then get the remaining 3 bits */
    packed33BytesPassword[1]  |= (mail->floor & 0x1F) << 3;    /* get bits from this field until empty the field or fill the current element (in this case until fill the element). Bits remaining: 2 bits */

    /* No more detailed comments, now you should know what to do... unless you are stu&@$... upppss! :) */
    packed33BytesPassword[2]   = ((mail->floor >> 5) & 0x03);  /* get 2 bits */
    packed33BytesPassword[2]  |= (mail->idk_random & 0x3F) << 2;    /* get 6 bits, 18 remaining */

    packed33BytesPassword[3]   = (char)((mail->idk_random >> 6) & 0xFF);  /* get 8 bits, 10 remaining */

    packed33BytesPassword[4]   = (char)((mail->idk_random >> 14) & 0xFF); /* get 5 bits, 2 remaining */

    packed33BytesPassword[5]   = ((mail->idk_random >> 22) & 0x03);  /* get 2 bits */
    packed33BytesPassword[5]  |= (mail->pkmnToRescue & 0x3F) << 2;    /* get 6 bits, 3 remaining */

    packed33BytesPassword[6]   = ((mail->pkmnToRescue >> 6) & 0x07);  /* get 3 bits */
    packed33BytesPassword[6]  |= (mail->mailID & 0x1F) << 3;  /* get 5 bits, 27 remaining */

    packed33BytesPassword[7]   = (char)((mail->mailID >> 5) & 0xFF); /* get 8 bits, 19 remaining */

    packed33BytesPassword[8]   = ((mail->mailID >> 13) & 0x07); /* get 3 bits */
    packed33BytesPassword[8]  |= (mail->idk_random2 & 0x1F) << 3; /* get 5 bits, 11 remaining */

    packed33BytesPassword[9]   = (char)((mail->idk_random2 >> 5) & 0xFF); /* get 8 bits, 3 remaining */

    packed33BytesPassword[10]  = ((mail->idk_random2 >> 13) & 0x07); /* get 3 bits */
    packed33BytesPassword[10] |= ((mail->pkmnNick[0] & 0x1F) << 3); /* get 5 bits, 3 remaining */

    packed33BytesPassword[11]  = ((mail->pkmnNick[0] >> 5) & 0x07); /* get 3 bits */
    packed33BytesPassword[11] |= ((mail->pkmnNick[1] & 0x1F) << 3); /* get 5 bits, 3 remaining */

    packed33BytesPassword[12]  = ((mail->pkmnNick[1] >> 5) & 0x07); /* get 3 bits */
    packed33BytesPassword[12] |= ((mail->pkmnNick[2] & 0x1F) << 3); /* get 5 bits, 3 remaining */

    packed33BytesPassword[13]  = ((mail->pkmnNick[2] >> 5) & 0x07); /* get 3 bits */
    packed33BytesPassword[13] |= ((mail->pkmnNick[3] & 0x1F) << 3); /* get 5 bits, 3 remaining */

    packed33BytesPassword[14]  = ((mail->pkmnNick[3] >> 5) & 0x07); /* get 3 bits */
    packed33BytesPassword[14] |= ((mail->pkmnNick[4] & 0x1F) << 3); /* get 5 bits, 3 remaining */

    packed33BytesPassword[15]  = ((mail->pkmnNick[4] >> 5) & 0x07); /* get 3 bits */
    packed33BytesPassword[15] |= ((mail->pkmnNick[5] & 0x1F) << 3); /* get 5 bits, 3 remaining */

    packed33BytesPassword[16]  = ((mail->pkmnNick[5] >> 5) & 0x07); /* get 3 bits */
    packed33BytesPassword[16] |= ((mail->pkmnNick[6] & 0x1F) << 3); /* get 5 bits, 3 remaining */

    packed33BytesPassword[17]  = ((mail->pkmnNick[6] >> 5) & 0x07); /* get 3 bits */
    packed33BytesPassword[17] |= ((mail->pkmnNick[7] & 0x1F) << 3); /* get 5 bits, 3 remaining */

    packed33BytesPassword[18]  = ((mail->pkmnNick[7] >> 5) & 0x07); /* get 3 bits */
    packed33BytesPassword[18] |= ((mail->pkmnNick[8] & 0x1F) << 3); /* get 5 bits, 3 remaining */

    packed33BytesPassword[19]  = ((mail->pkmnNick[8] >> 5) & 0x07); /* get 3 bits */
    packed33BytesPassword[19] |= ((mail->pkmnNick[9] & 0x1F) << 3); /* get 5 bits, 3 remaining */

    packed33BytesPassword[20]  = ((mail->pkmnNick[9] >> 5) & 0x07); /* get 3 bits */
    packed33BytesPassword[20] |= ((mail->idk_0Or1 & 0x1F) << 3); /* get 5 bits, 3 remaining */

    packed33BytesPassword[21]  = ((mail->idk_0Or1 >> 5) & 0x07); /* get 3 bits */
    packed33BytesPassword[21] |= ((mail->itemReward & 0x1F) << 3); /* get 5 bits, 3 remaining */

    packed33BytesPassword[22]  = ((mail->itemReward >> 5) & 0x07); /* get 3 bits */
    packed33BytesPassword[22] |= ((mail->idk_0 & 0x1F) << 3); /* get 5 bits, 3 remaining */

    packed33BytesPassword[23]  = ((mail->idk_0 >> 5) & 0x07); /* get 3 bits */
    packed33BytesPassword[23] |= ((mail->teamSeekingHelpID & 0x1F) << 3); /* get 5 bits, 27 remaining */

    packed33BytesPassword[24]  = (char)((mail->teamSeekingHelpID >> 5) & 0xFF); /* get 8 bits, 19 remaining */

    packed33BytesPassword[25]  = (char)((mail->teamSeekingHelpID >> 13) & 0xFF); /* get 8 bits, 11 remaining */

    packed33BytesPassword[26]  = (char)((mail->teamSeekingHelpID >> 21) & 0xFF); /* get 8 bits, 3 remaining */

    packed33BytesPassword[27]  = ((mail->teamSeekingHelpID >> 29) & 0x07); /* get 3 bits */
    packed33BytesPassword[27] |= ((mail->teamGivingHelpID & 0x1F) << 3); /* get 5 bits, 27 remaining */

    packed33BytesPassword[28]  = (char)((mail->teamGivingHelpID >> 5) & 0xFF); /* get 8 bits, 19 remaining */

    packed33BytesPassword[29]  = (char)((mail->teamGivingHelpID >> 13) & 0xFF); /* get 8 bits, 11 remaining */

    packed33BytesPassword[30]  = (char)((mail->teamGivingHelpID >> 21) & 0xFF); /* get 8 bits, 3 remaining */

    packed33BytesPassword[31]  = ((mail->teamGivingHelpID >> 29) & 0x07); /* get 3 bits */
    packed33BytesPassword[31] |= ((mail->chancesLeft & 0x1F) << 3); /* get 5 bits, 3 remaining */

    packed33BytesPassword[32]  = ((mail->chancesLeft >> 29) & 0x07); /* get 3 bits */
    packed33BytesPassword[32] |= ((mail->idk_last3Bits & 0x07) << 3); /* get 2 bits. NOTE: Always 0 */

    /* The remaining bits in index 33 were filled with 0 during array initialization, so there is no need to do it now */
}


void lookupTableEncodingSOS(char* password54Chars, const char* password54Integers)
{
    const char table[] = "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W";
    int i;
    for (i = 0; i < 54; ++i) {
        password54Chars[i] = table[(int)password54Integers[i]];
    }
}


void realocateBytesEncodingSOS(char* allocatedPassword, const char* unallocatedPassword)
{
    const int newPos[] = { 23, 16, 37, 45, 4, 41, 52, 1, 8, 39, 25, 36, 47, 0, 12, 3, 33, 20, 28, 9, 49, 53, 51, 31, 11, 2, 13, 14, 34, 5, 46, 27, 17, 18, 19, 29, 38, 48, 22, 32, 42, 15, 6, 26, 30, 10, 44, 50, 35, 7, 40, 21, 43, 24 };

    int i;
    for (i = 0; i < 54; ++i) {
        allocatedPassword[i] = unallocatedPassword[ newPos[i] ];
    }
}
