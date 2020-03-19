#ifndef ENCODESOS_H
#define ENCODESOS_H

#include "../../../data/md1global/md1global.h"

/* ENCODING SOS MAIL FUNCTIONS */
int encodeSosMail(struct SosMail *sos, char *finalPassword);
void bitPackingEncodingSos(const struct SosMail* mail, char* packed33BytesPassword);

#endif /* ENCODESOS_H */
