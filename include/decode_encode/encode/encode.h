#ifndef ENCODE_H
#define ENCODE_H

#include "enc_wm.h"
#include "enc_sos.h"
#include "../dec_enc_common.h"
#include "../../model/md1global.h"

void bitUnpackingEncoding(char* unpackedIntegers, const char* packedPassword, int bytesToUnpack);
void lookupTableEncodingSOS(char* password54Chars, const char* password54Integers);
void realocateBytesEncodingSOS(char* allocatedPassword, const char* unallocatedPassword);

#endif /* ENCODE_H */
