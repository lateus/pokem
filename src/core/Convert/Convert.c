#include "Convert.h"
#include "../Decode/DecodeSos/DecodeSos.h"
#include "../Encode/EncodeSos/EncodeSos.h"
#include "../Decode/UtilDecode/UtilDecode.h"
#include "../Encode/UtilEncode/UtilEncode.h"
#include "../UtilCore/UtilCore.h"
#include "../../data/md1global/md1global.h"
#include "../../data/md1database/md1database.h"
#include "../../util/messages.h"

#include <stdio.h>
#include <string.h>

int convertSosMail(const char *SOSPassword, int idTeamGivingHelp, int item, char *resultAOKMail, char *resultThankYouMail)
{
    struct SosMail mailTest = { 0, 0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0 };
    int errorCode = NoError;
    char allocatedPassword[54] = {0}; /* always initialize */
    const unsigned char newPositionsToDecode[] = { 13, 7, 25, 15, 4, 29, 42, 49, 8, 19, 45, 24, 14, 26, 27, 41, 1, 32, 33, 34, 17, 51, 38, 0, 53, 10, 43, 31, 18, 35, 44, 23, 39, 16, 28, 48, 11, 2, 36, 9, 50, 5, 40, 52, 46, 3, 30, 12, 37, 20, 47, 22, 6, 21 };
    char password54Integers[54] = {0};
    const char* lookupTable = "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W";
    char packed34Bytes[34] = {0}; /* The packed password */
    char passwordUnallocated[54] = {0};
    const unsigned char newPositionsToEncode[] = { 23, 16, 37, 45, 4, 41, 52, 1, 8, 39, 25, 36, 47, 0, 12, 3, 33, 20, 28, 9, 49, 53, 51, 31, 11, 2, 13, 14, 34, 5, 46, 27, 17, 18, 19, 29, 38, 48, 22, 32, 42, 15, 6, 26, 30, 10, 44, 50, 35, 7, 40, 21, 43, 24 };
    int mailType = getMailType(SOSPassword);
    int i;

    errorCode = decodeSosMail(SOSPassword, &mailTest);
    if (errorCode != NoError) {
        return errorCode;
    } else if (checkItem(item) == ItemOutOfRangeError) {
        printMessage(stderr, ErrorMessage, "Reward items must be between " LGREEN "%d" RESET " [" LGREEN "%s" RESET "] and " LGREEN "%d" RESET " [" LGREEN "%s" RESET "]. Current value: " LRED "%u" RESET " [" LRED "INVALID" RESET "]\n\n", itemsStr[1], itemsCount - 5, itemsStr[itemsCount - 5], item);
        return ItemOutOfRangeError;
    }

    reallocateBytes(SOSPassword, newPositionsToDecode, 54, allocatedPassword);

    errorCode = mapPasswordByPositionInLookupTable(allocatedPassword, lookupTable, 54, password54Integers);
    if (errorCode != NoError) { /* this cannot happen because we already decoded the mail */
        return errorCode;
    }

    /* FIRST: A-OK MAIL */
    if (mailType == SosMailType) {
        convertSosToAOkMail(password54Integers, idTeamGivingHelp);

        /* Bit packing */
        bitPackingDecoding(packed34Bytes, password54Integers, 54); /* Pack the password */

        packed34Bytes[0] = (char)computeChecksum(packed34Bytes + 1, 33); /* the first byte is ignored in the calculation, cuz is merely for a checksum */

        /* back again */
        for (i = 0; i < 54; ++i) {
            password54Integers[i] = 0;
        }
        bitUnpackingEncoding(packed34Bytes, password54Integers, 34);

        reallocateBytes(lookupTable, (unsigned char*)password54Integers, 54, passwordUnallocated); /* a tricky one, but we want this: passwordUnallocated[i] = lookupTable[(int)password54Integers[i]]; */
        reallocateBytes(passwordUnallocated, newPositionsToEncode, 54, resultAOKMail);

        /* Update the mail type */
        mailType = getMailType(resultAOKMail);
        if (mailType != AOkMailType) { /* Conversion error */
            printMessage(stderr, ErrorMessage, "The converted mail is not an " LGREEN "A-OK Mail" RESET ".\n");
            return ConversionError;
        }
    }

    /* SECOND: THANK-YOU MAIL */
    if (mailType == AOkMailType) {
        convertAOkToThankYouMail(password54Integers, item);

        /* Bit packing */
        /* reseting variables */
        for (i = 0; i < 34; ++i) {
            packed34Bytes[i] = 0;
        }
        bitPackingDecoding(packed34Bytes, password54Integers, sizeof(password54Integers)); /* Pack the password */
        packed34Bytes[0] = (char)computeChecksum(packed34Bytes + 1, 33); /* the first byte is ignored in the calculation, cuz is merely for a checksum */

        /* back again */
        for (i = 0; i < 54; ++i) {
            password54Integers[i] = 0;
            passwordUnallocated[i] = 0;
        }
        bitUnpackingEncoding(packed34Bytes, password54Integers, sizeof(packed34Bytes));

        reallocateBytes(lookupTable, (unsigned char*)password54Integers, 54, passwordUnallocated); /* a tricky one, but we want this: passwordUnallocated[i] = lookupTable[(int)password54Integers[i]]; */
        reallocateBytes(passwordUnallocated, newPositionsToEncode, 54, resultThankYouMail);
    } else if (mailType == ThankYouMailType) {
        /* just replace the item */
        password54Integers[37] |= (item & 0x07) << 2;
        password54Integers[38]  = (item >> 3) & 0x1F;

        /* Bit packing */
        /* reseting variables */
        for (i = 0; i < 34; ++i) {
            packed34Bytes[i] = 0;
        }
        bitPackingDecoding(packed34Bytes, password54Integers, sizeof(password54Integers)); /* Pack the password */
        packed34Bytes[0] = (char)computeChecksum(packed34Bytes + 1, 33); /* the first byte is ignored in the calculation, cuz is merely for a checksum */

        /* back again */
        for (i = 0; i < 54; ++i) {
            password54Integers[i] = 0;
            passwordUnallocated[i] = 0;
        }
        bitUnpackingEncoding(packed34Bytes, password54Integers, sizeof(packed34Bytes));

        reallocateBytes(lookupTable, (unsigned char*)password54Integers, 54, passwordUnallocated); /* a tricky one, but we want this: passwordUnallocated[i] = lookupTable[(int)password54Integers[i]]; */
        reallocateBytes(passwordUnallocated, newPositionsToEncode, 54, resultThankYouMail);
    }

    return NoError;
}

void convertSosToAOkMail(char *password54Integers, int idTeamGivingHelp)
{
    /*
     * One possible way to do this is decoding the mail, then change the mail type,
     * the chances left and the ID of the rescue team giving help, then encode it
     * again. But that is very inefficient, however, that's the idea. I'll directly
     * change the bytes of the password by tracking the location of the bits I must
     * change:
     * UPDATE: It's very hard to track bits before the password has been reallocated and
     *         converted back to integers and I do not have enough time to check it out,
     *         so I'll track the bits after that. If someone help me track the bits, I
     *         will be sincerely grateful.
     *
     * > The mail type are stored at the first 4 bits of the first byte,
     *   but then the checksum is pushed at index 0, so the mail type is
     *   now at index 1. After the bit-unpacking process, each byte is
     *   now 5 bits long, so the checksum occupies the first byte and
     *   the first 3 bits of the second byte. So, the mail type occupies
     *   the 4th and 5th bits of the second byte, and the first 2 bits
     *   of the third byte.
    */

    int rescueChances = 0;

    password54Integers[1] &= 0x07; /* unset the last two bits. The first two bits of 4 (0100) are zeros */
    password54Integers[2] &= 0xFC; /* unset the first two bits */
    password54Integers[2] |= 0x01; /* set the first one as 4 (DEC) == 0100 (BIN) */

    /*
     * The ID of the team giving help must equal the ID of the team seeking help.
     * So first, we need to get the ID of the team seeking help, which is stored
     * in the last 5 bits of byte 23 and the next full 3 bytes and the first 3
     * bits of byte 27. Then the checksum is pushed and so the desired ID begins
     * at index 24. After unpacking, it starts at index 39:
    */

    password54Integers[45] &= 0x03;
    password54Integers[45] |= (idTeamGivingHelp & 0x07) << 2;
    password54Integers[46]  = (idTeamGivingHelp >>  3) & 0x1F;
    password54Integers[47]  = (idTeamGivingHelp >>  8) & 0x1F;
    password54Integers[48]  = (idTeamGivingHelp >> 13) & 0x1F;
    password54Integers[49]  = (idTeamGivingHelp >> 18) & 0x1F;
    password54Integers[50]  = (idTeamGivingHelp >> 23) & 0x1F;
    password54Integers[51] &= (0x01 << 4);
    password54Integers[51]  = (idTeamGivingHelp >> 28) & 0x0F;

    /*
     * The chances left must be decremented, because we "rescued" the other team,
     * and of course we used a rescue chance. The chances are stored just next
     * to the ID of the team giving help. We must obtain the chances, decrement
     * it and then insert it again.
    */
    rescueChances  = (password54Integers[51] >> 4) & 0x01;
    rescueChances |= (password54Integers[52] & 0x07) << 1;
    --rescueChances; /* must be > 0 */
    password54Integers[51] &= 0x0F;
    password54Integers[51] |= (rescueChances & 0x01) << 4;
    password54Integers[52]  = (char)(0 | (rescueChances >> 1));
}

void convertAOkToThankYouMail(char *password54Integers, int item)
{
    /*
     * Similar to the procedure to convert a SOS into an A-OK Mail.
     * We need to set the Mail Type to 5, which is 101 in binary.
     * As the current value is 4, which is 100 in binary, we only
     * need to set the LSB. It's the first bit of the Mail Type,
     * which is located at the fourth bit of the second byte:
    */
    password54Integers[1] |= (0x01 << 3);

    /*
     * Another value to change is the first bit of the field 'idk_0Or1',
     * which is located at index 20, but when the checksum was pushed,
     * it was moved eight bits forward, so it's at index 21.
     * After unpacking, it is at index 35 (the MSB of that byte).
    */
    password54Integers[35] |= (0x01 << 4);

    /* The item, it's just next to the field previously modified */
    if (item) {
        password54Integers[37] |= (item & 0x07) << 2;
        password54Integers[38]  = (item >> 3) & 0x1F;
    }
}
