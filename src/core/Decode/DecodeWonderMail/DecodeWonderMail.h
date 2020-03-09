#ifndef DECODEWonderMail_H
#define DECODEWonderMail_H

#include "../../../data/md1global/md1global.h"

/* DECODING WONDER MAIL FUNCTIONS */
int decodeWonderMail(const char *password, struct WonderMail *wonderMailResult);
void bitUnpackingDecodingWonderMail(const char *packed14BytesPassword, struct WonderMail* mail);
void setFlavorText(const struct WonderMail *wm, struct WonderMailInfo *mailInfo);
void setFlavorTextHead(const struct WonderMail *wm, int headIndicator, int pairsIndex, int loversIndex, int parentsIndex, struct WonderMailInfo *mailInfo);
void setFlavorTextBody(const struct WonderMail *wm, int bodyIndicator, int pairsIndex, int loversIndex, int parentsIndex, struct WonderMailInfo *mailInfo);
void setWonderMailInfo(const struct WonderMail *mail, struct WonderMailInfo *mailInfo);

#endif /* DECODEWonderMail_H */
