#ifndef DECODESOS_H
#define DECODESOS_H

#include "../../../data/md1global/md1global.h"

int decodeSOSMail(const char *sosPassword, struct SOS_INFO *sosMailInfoResult);
int SOSMailIsInvalid(const char *password, char *packed34BytesPassword);
void reallocateBytesDecodingSOS(const char *unallocatedPassword, char *allocatedPassword);
int lookupTableDecodingSOS(const char *allocatedPassword, char *passwordIntegers);
void bitUnpackingDecodingSOS(const char *packed14BytesPassword, struct SOSMAIL* mail);
void setSOSInfo(struct SOS_INFO *sosInfo, const struct SOSMAIL *mail);

#endif /* DECODESOS_H */
