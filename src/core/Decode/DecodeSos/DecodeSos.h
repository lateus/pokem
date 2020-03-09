#ifndef DECODESOS_H
#define DECODESOS_H

#include "../../../data/md1global/md1global.h"

/* DECODING SOS MAIL FUNCTIONS */
int decodeSosMail(const char *password, struct SosMail *sosMailResult);
void bitUnpackingDecodingSosMail(const char *packed14BytesPassword, struct SosMail* mail);
void setSosInfo(const struct SosMail *mail, struct SosMailInfo *sosInfo);

#endif /* DECODESOS_H */
