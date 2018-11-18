#include "../../../include/decode_encode/encode/encode.h"
#include "../../../include/model/md1global.h"
#include "../../../include/model/md1database.h"

#include <stdio.h>
#include <string.h>


int setMailData(const char *argv[], void *mail, enum MAIL_TYPE type)
{
    switch (type)
    {
        case WONDER:
            return setWMData(argv, (struct WONDERMAIL*)mail);
        default: /* SOS, obviously */
            return setSOSData(argv, (struct SOSMAIL*)mail);
    }
}


/* see the equivalent in "decode.c" if you are looking for details about how this function works */
void bitUnpackingEncoding(char* unpackedIntegers, const char *packedPassword, int bytesToUnpack)
{
    int cnt = 0, row, col, val;
    int i, j;

    for(i = 0; i < bytesToUnpack; ++i) {

        for(j = 0; j < 8; ++j) {

            row = cnt / 5;
            col = cnt % 5;

            val = (packedPassword[i] >> j) & 1;  /* Obtain the state of a particular bit */
            unpackedIntegers[row] |= (val << col);    /* Set that bit in the pack */

            ++cnt;

        }

    }

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
