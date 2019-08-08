#ifndef ENC_WM_H
#define ENC_WM_H

#include "../../model/md1global.h"

int encodeWonderMail(struct WONDERMAIL *wm, char *finalPassword);
int foundErrorsEntriesWM(const struct WONDERMAIL *wm);
void bitPackingEncodingWM(char* packed14BytesPassword, const struct WONDERMAIL* mail);
void lookupTableEncodingWM(const char* password24Integers, char* password24Chars);
void reallocateBytesEncodingWM(const char* unallocatedPassword, char* allocatePassword);

#endif /* ENC_WM_H */
