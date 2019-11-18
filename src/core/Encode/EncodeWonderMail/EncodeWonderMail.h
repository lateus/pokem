#ifndef ENCODEWONDERMAIL_H
#define ENCODEWONDERMAIL_H

#include "../../../data/md1global/md1global.h"

/* ENCODING WONDER MAIL FUNCTIONS */
int encodeWonderMail(struct WONDERMAIL *wm, char *finalPassword);
int foundErrorsEntriesWM(const struct WONDERMAIL *wm);
void bitPackingEncodingWM(char* packed14BytesPassword, const struct WONDERMAIL* mail);
void lookupTableEncodingWM(const char* password24Integers, char* password24Chars);
void reallocateBytesEncodingWM(const char* unallocatedPassword, char* allocatePassword);

#endif /* ENCODEWONDERMAIL_H */
