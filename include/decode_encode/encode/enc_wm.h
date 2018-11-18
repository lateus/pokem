#ifndef ENC_WM_H
#define ENC_WM_H

#include "../../model/md1global.h"

int setWMData(const char *argv[], struct WONDERMAIL *wm);
int foundErrorsEntriesWM(const struct WONDERMAIL *wm, const char *argv[]);

void bitPackingEncodingWM(char* packed14BytesPassword, const struct WONDERMAIL* mail);
void lookupTableEncodingWM(const char* password24Integers, char* password24Chars);
void reallocateBytesEncodingWM(const char* unallocatedPassword, char* allocatePassword);

#endif /* ENC_WM_H */
