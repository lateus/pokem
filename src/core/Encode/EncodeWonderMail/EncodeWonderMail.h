#ifndef ENCODEWONDERMAIL_H
#define ENCODEWONDERMAIL_H

#include "../../../data/md1global/md1global.h"

/* ENCODING WONDER MAIL FUNCTIONS */
int encodeWonderMail(struct WonderMail *wm, char *finalPassword, int trySpecialWonderMail);
void bitPackingEncodingWonderMail(const struct WonderMail* mail, char* packed14BytesPassword);

#endif /* ENCODEWONDERMAIL_H */
