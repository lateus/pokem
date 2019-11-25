#ifndef ENCODEWonderMail_H
#define ENCODEWonderMail_H

#include "../../../data/md1global/md1global.h"

/* ENCODING WONDER MAIL FUNCTIONS */
int encodeWonderMail(struct WonderMail *wm, char *finalPassword);
int foundErrorsEntriesWM(const struct WonderMail *wm);
void bitPackingEncodingWM(char* packed14BytesPassword, const struct WonderMail* mail);
void lookupTableEncodingWM(const char* password24Integers, char* password24Chars);
void reallocateBytesEncodingWM(const char* unallocatedPassword, char* allocatePassword);

#endif /* ENCODEWonderMail_H */
