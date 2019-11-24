#ifndef DECODEWONDERMAIL_H
#define DECODEWONDERMAIL_H

#include "../../../data/md1global/md1global.h"

/* DECODING WONDER MAIL FUNCTIONS */
int decodeWonderMail(const char *password, struct WM_INFO *wonderMailInfoResult);
int wonderMailIsInvalid(const char *password, char *packed15BytesPassword);
void reallocateBytesDecodingWM(char *allocatePassword, const char *unallocatedPassword);
int lookupTableDecodingWM(char *passwordIntegers, const char *allocatedPassword);
void bitUnpackingDecodingWM(const char *packed14BytesPassword, struct WONDERMAIL* mail);
int* flavorText(const struct WONDERMAIL *wm, int pairsIndex, int loversIndex, int parentsIndex);
void flavorTextHead(const struct WONDERMAIL *wm, int headIndicator, int pairsIndex, int loversIndex, int parentsIndex, struct WM_INFO *mailInfo);
void flavorTextBody(const struct WONDERMAIL *wm, int bodyIndicator, int pairsIndex, int loversIndex, int parentsIndex, struct WM_INFO *mailInfo);
void setWMInfo(struct WM_INFO *mailInfo, const struct WONDERMAIL *mail);

#endif /* DECODEWONDERMAIL_H */
