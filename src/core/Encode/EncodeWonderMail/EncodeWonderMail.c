#include "EncodeWonderMail.h"
#include "../UtilEncode/UtilEncode.h"
#include "../../UtilCore/UtilCore.h"
#include "../../../data/md1database/md1database.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int printMessages;

int encodeWonderMail(struct WonderMail *wm, char* finalPassword, int trySpecialWonderMail)
{
    int errors = entryErrorsWonderMail(wm);
    if (errors) {
        if (printMessages) {
            fprintf(stderr, " :: %d ERRORS FOUND. ENCODING IS NOT POSSIBLE\a\n\n", errors);
            fflush(stderr);
        }
        return InputError;
    }

    wm->specialJobIndicator = getSpecialJobIndicator(wm->pkmnClient, wm->pkmnTarget, wm->missionType, trySpecialWonderMail, wm->itemDeliverFind);
    wm->flavorText = (15 - (wm->dungeon % 15)) % 15; /* obtained empirically */
    if (wm->random == 0) {
        wm->random = rand() & 0xFF; /* same as % 256 */
    }
    wm->idk_always0xFF = 0xFF; /* as his name suggest */

    char packed15BytesPassword[15] = {0}; /* the first byte is merely a checksum */
    char *packed14BytesPassword = packed15BytesPassword + 1; /* be aware about pointer's arithmetic if you don't want an unexpectly behavior at runtime */
    bitPackingEncodingWonderMail(wm, packed14BytesPassword); /* bit packing while decoding are equivalent to bit unpacking while decoding */

    packed15BytesPassword[0] = (char)computeChecksum(packed14BytesPassword, 14);

    char password24Integers[24] = {0};
    bitUnpackingEncoding(packed15BytesPassword, password24Integers, 15);

    char password24Chars[24] = {0};
    const char* lookupTable = "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W";
    reallocateBytes(lookupTable, (unsigned char*)password24Integers, 24, password24Chars); /* a tricky one, but we want this: password24Chars[i] = lookupTable[(int)password24Integers[i]]; */
    
    const unsigned char newPositions[24] = { 12, 20, 9, 17, 4, 15, 1, 23, 3, 7, 19, 14, 0, 5, 21, 6, 8, 18, 11, 2, 10, 13, 22, 16 };
    reallocateBytes(password24Chars, newPositions, 24, finalPassword);

    return NoError;
}



void bitPackingEncodingWonderMail(const struct WonderMail* mail, char* packed14BytesPassword)
{
    /* I wrote the bits that a field must store, assign more will cause an overflow. I'm using standard C Bit Fields. */
    /* As final observation, I only will read the bits in the array, without destroying bits, instead I'll shift bits: non-destructive read is faster and safer than destructive read */

    packed14BytesPassword[0]   = (mail->mailType & 0x0F);   /* Get the 4 bits of the field. */
    packed14BytesPassword[0]  |= (mail->missionType & 0x07) << 4;   /* get other 3 bits and leftshift bits before assignment. */
    packed14BytesPassword[0]  |= (mail->specialJobIndicator & 0x01) << 7;   /* get another bit and leftshift bits before assignment. Bits remaining: 3 */

    packed14BytesPassword[1]   = ((mail->specialJobIndicator >> 1) & 0x07); /* we already got a bit from this field, so we rightshift a bit and then get the remaining 3 bits */
    packed14BytesPassword[1]  |= (mail->pkmnClient & 0x1F) << 3;    /* get bits from this field until empty the field or fill the current element (in this case until fill the element). Bits remaining: 5 bits */

    /* No more detailed comments, now you should know what to do... unless you are stu&@$... upppss! :) */
    packed14BytesPassword[2]   = ((mail->pkmnClient >> 5) & 0x0F);  /* get 4 bits */
    packed14BytesPassword[2]  |= (mail->pkmnTarget & 0x0F) << 4;    /* get 4 bits, remaining: 5 bits */

    packed14BytesPassword[3]   = ((mail->pkmnTarget >> 4) & 0x1F);  /* get 5 bits */
    packed14BytesPassword[3]  |= (mail->itemDeliverFind & 0x07) << 5;   /* get 3 bits, remaining: 5 bits */

    packed14BytesPassword[4]   = ((mail->itemDeliverFind >> 3) & 0x1F); /* get 5 bits */
    packed14BytesPassword[4]  |= (mail->rewardType & 0x07) << 5;    /* get 3 bits, remaining: 1 bit */

    packed14BytesPassword[5]   = ((mail->rewardType >> 3) & 0x01);  /* get 1 bit */
    packed14BytesPassword[5]  |= (mail->itemReward & 0x7F) << 1;    /* get 7 bits, remaining: 1 bit */

    packed14BytesPassword[6]   = ((mail->itemReward >> 7) & 0x01);  /* get 1 bit */
    packed14BytesPassword[6]  |= (mail->friendAreaReward & 0x3F) << 1;  /* get 6 bits */
    packed14BytesPassword[6]  |= (mail->flavorText & 0x01) << 7;    /* get 1 bit, remaining: 7 bits */

    packed14BytesPassword[7]   = ((mail->flavorText >> 1) & 0x7F);  /* get 7 bits */
    packed14BytesPassword[7]  |= (mail->random & 0x01) << 7;    /* get 1 bit, remaining: 7 bits */

    packed14BytesPassword[8]   = ((mail->random >> 1) & 0x7F);  /* get 7 bits */
    packed14BytesPassword[8]  |= (mail->idk_always0xFF & 0x01) << 7;    /* get 1 bit, remaining: 7 bits */

    packed14BytesPassword[9]   = ((mail->idk_always0xFF >> 1) & 0x7F);  /* get 7 bits */
    packed14BytesPassword[9]  |= (mail->dungeon & 0x01) << 7;   /* get 1 bit, remaining: 6 bits */

    packed14BytesPassword[10]  = ((mail->dungeon >> 1) & 0x3F); /* get 6 bits */
    packed14BytesPassword[10] |= (mail->floor & 0x03) << 6; /* get 2 bits, remaining: 5 bits */

    packed14BytesPassword[11]  = ((mail->floor >> 2) & 0x3F);   /* get the last 5 bits and... finish! */

    /* The elements beyond index 11 were filled with 0 during array initialization, so there is no need to do it now */
}