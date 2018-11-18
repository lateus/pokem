#include "../../../include/decode_encode/convert/convert.h"

void convertSOSToAOKMail(char *password54Integers)
{
    /*
     * One possible way to do this is decoding the mail, then change the mail type,
     * the chances left and the ID of the rescue team giving help, then encode it
     * again. But that is very inefficient, however, that's the idea. I'll directly
     * change the bytes of the password by tracking the location of the bits I must
     * change:
     * UPDATE: It's very hard to track bits before the password has been relocated and
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

    password54Integers[1] &= 0x07; /* unset the last two bits. The first two bits of 4 (0100) are zeros */
    password54Integers[2] &= 0xFC; /* unset the first two bits */
    password54Integers[2] |= 0x01; /* set the first one as 4 (DEC) == 0100 (BIN) */

    /*
     * > The ID of the team giving help must equal the ID of the team seeking help.
     *   So first, we need to get the ID of the team seeking help, which is stored
     *   in the last 5 bits of byte 23 and the next full 3 bytes and the first 3
     *   bits of byte 27. Then the checksum is pushed and so the desired ID begins
     *   at index 24. After unpacking, it starts at index 39:
    */

    int teamSeekingHelpID  =  password54Integers[39] & 0x1F;
    teamSeekingHelpID     |= (password54Integers[40] & 0x1F) <<  5;
    teamSeekingHelpID     |= (password54Integers[41] & 0x1F) << 10;
    teamSeekingHelpID     |= (password54Integers[42] & 0x1F) << 15;
    teamSeekingHelpID     |= (password54Integers[43] & 0x1F) << 20;
    teamSeekingHelpID     |= (password54Integers[44] & 0x1F) << 25;
    teamSeekingHelpID     |= (password54Integers[45] & 0x03) << 30;

    password54Integers[45] &= 0x03;
    password54Integers[45] |= (teamSeekingHelpID & 0x07) << 2;
    password54Integers[46]  = (teamSeekingHelpID >>  3) & 0x1F;
    password54Integers[47]  = (teamSeekingHelpID >>  8) & 0x1F;
    password54Integers[48]  = (teamSeekingHelpID >> 13) & 0x1F;
    password54Integers[49]  = (teamSeekingHelpID >> 18) & 0x1F;
    password54Integers[50]  = (teamSeekingHelpID >> 23) & 0x1F;
    password54Integers[51] &= (0x01 << 4);
    password54Integers[51]  = (teamSeekingHelpID >> 28) & 0x0F;

    /*
     * > The chances left must be decremented, because we "rescue" the other team,
     *   and of course we used a rescue chance. The chances are stored just next
     *   to the ID of the team giving help. We must obtain the chances, decrement
     *   it and then insert it again.
    */
    int rescueChances = (password54Integers[51] >> 4) & 0x01;
    rescueChances |= (password54Integers[52] & 0x07) << 1;
    --rescueChances; /* must be > 0 */
    password54Integers[51] &= 0x0F;
    password54Integers[51] |= (rescueChances & 0x01) << 4;
    password54Integers[52]  = (char)(0 | (rescueChances >> 1));
}

void convertAOKToThankYouMail(char *password54Integers, int item)
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
