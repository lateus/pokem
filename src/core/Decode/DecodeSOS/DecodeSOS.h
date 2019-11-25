#ifndef DECODESOS_H
#define DECODESOS_H

#include "../../../data/md1global/md1global.h"

/* DECODING SOS MAIL FUNCTIONS */
int decodeSOSMail(const char *sosPassword, struct SosMailInfo *sosMailInfoResult);
int SOSMailIsInvalid(const char *password, char *packed34BytesPassword);
void reallocateBytesDecodingSOS(const char *unallocatedPassword, char *allocatedPassword);
int lookupTableDecodingSOS(const char *allocatedPassword, char *passwordIntegers);
void bitUnpackingDecodingSOS(const char *packed14BytesPassword, struct SosMail* mail);
void setSOSInfo(struct SosMailInfo *sosInfo, const struct SosMail *mail);

#endif /* DECODESOS_H */
