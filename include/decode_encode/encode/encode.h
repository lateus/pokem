#ifndef ENCODE_H
#define ENCODE_H

void bitUnpackingEncoding(char* unpackedIntegers, const char* packedPassword, int bytesToUnpack);
void lookupTableEncodingSOS(char* password54Chars, const char* password54Integers);
void realocateBytesEncodingSOS(char* allocatedPassword, const char* unallocatedPassword);

#endif /* ENCODE_H */
