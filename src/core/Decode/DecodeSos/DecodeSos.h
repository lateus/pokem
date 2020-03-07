#ifndef DECODESOS_H
#define DECODESOS_H

#include "../../../data/md1global/md1global.h"

/* DECODING SOS MAIL FUNCTIONS */
int decodeSosMail(const char *sosPassword, struct SosMail *sosMailResult);
int sosMailIsInvalid(const char *password, char *packed34BytesPassword);
void reallocateBytesDecodingSos(const char *unallocatedPassword, char *allocatedPassword);
int lookupTableDecodingSos(const char *allocatedPassword, char *passwordIntegers);
void bitUnpackingDecodingSos(const char *packed14BytesPassword, struct SosMail* mail);
void setSosInfo(const struct SosMail *mail, struct SosMailInfo *sosInfo);

#endif /* DECODESOS_H */
