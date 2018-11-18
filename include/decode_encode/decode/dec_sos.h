#ifndef DEC_SOS_H
#define DEC_SOS_H

#include "../../model/md1global.h"

void reallocateBytesDecodingSOS(const char *unallocatedPassword, char *allocatedPassword);
int lookupTableDecodingSOS(const char *allocatedPassword, char *passwordIntegers);
void bitUnpackingDecodingSOS(const char *packed14BytesPassword, struct SOSMAIL* mail);
void setSOSInfo(struct SOS_INFO *sosInfo, const struct SOSMAIL *mail);

#endif /* DEC_SOS_H */
