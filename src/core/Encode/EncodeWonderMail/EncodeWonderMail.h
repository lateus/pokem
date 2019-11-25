#ifndef ENCODEWonderMail_H
#define ENCODEWonderMail_H

#include "../../../data/md1global/md1global.h"

/* ENCODING WONDER MAIL FUNCTIONS */
int encodeWonderMail(struct WonderMail *wm, char *finalPassword);
int foundErrorsEntriesWonderMail(const struct WonderMail *wm);
void bitPackingEncodingWonderMail(char* packed14BytesPassword, const struct WonderMail* mail);
void lookupTableEncodingWonderMail(const char* password24Integers, char* password24Chars);
void reallocateBytesEncodingWonderMail(const char* unallocatedPassword, char* allocatePassword);

#endif /* ENCODEWonderMail_H */
