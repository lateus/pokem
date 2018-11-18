#ifndef DECODE_H
#define DECODE_H

#include "dec_wm.h"
#include "dec_sos.h"

void bitPackingDecoding(char* packedPassword, const char* unpackedPassword, int bytesToPack);

#endif/* DECODE_H */
