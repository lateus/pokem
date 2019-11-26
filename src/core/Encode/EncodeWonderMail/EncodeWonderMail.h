#ifndef ENCODEWonderMail_H
#define ENCODEWonderMail_H

#include "../../../data/md1global/md1global.h"

/* ENCODING WONDER MAIL FUNCTIONS */
int encodeWonderMail(struct WonderMail *wm, char *finalPassword);
int foundErrorsEntriesWonderMail(const struct WonderMail *wm);
void bitPackingEncodingWonderMail(const struct WonderMail* mail, char* packed14BytesPassword);
void lookupTableEncodingWonderMail(const char* password24Integers, char* password24Chars);
void reallocateBytesEncodingWonderMail(const char* unallocatedPassword, char* allocatedPassword);

#endif /* ENCODEWonderMail_H */
