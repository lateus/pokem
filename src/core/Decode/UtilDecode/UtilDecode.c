#include "UtilDecode.h"

void bitPackingDecoding(char* packedPassword, const char* unpackedPassword, int bytesToPack)
{
    /*
        In a process called bit packing, where bits are packed into 8-bit bytes without
        waste of space, the 24-bytes password is converted into 15 binary bytes, and
        the 54-bytes password is converted into 34 binary bytes. In the latter case,
        the 54 characters make up 54*8=270 bits, and the 34 bytes make up 272 bits,
        so the last 2 unused bits are filled with zeros.

        Each number is packed by starting with the rightmost bit of the number, and
        storing that bit in the rightmost position of the result. Then the rightmost
        bit is retrieved and stored, and so on until all bits are stored.
        If there is no room to retrieve and store more bits, the next byte of the result is used.
    */

    int cnt = 0, row, col, val; /*
                                    row: stores the index of the current element of the array ...
                                    col: stores the index of the current bit of the current row (i.e. the column) ...
                                    val: stores the value of the current bit of the current row ...
                                    cnt: used to get the row (row) and column (col) by dividing by 8.
                                */
    int i, j;
    for (i = 0; i < bytesToPack; ++i) {

        for (j = 0; j < 5; ++j, ++cnt) { /* ++cnt pass to the next column (i.e. the next bit) */

            row = cnt >> 3;  /* It's equivalent to (cnt / 8), and give me the row (the element in the array) */
            col = cnt & 0x7; /* It's equivalent to (cnt % 8), and give me the column (the bit in the desired row) */
    	
            val = (unpackedPassword[i] >> j) & 1;   /* Obtains the state of a particular bit */
            packedPassword[row] |= (val << col); /* Set that bit in the pack */

        }

    }

}
