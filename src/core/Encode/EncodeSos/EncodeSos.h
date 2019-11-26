#ifndef ENCODESOS_H
#define ENCODESOS_H

#include "../../../data/md1global/md1global.h"

/* ENCODING SOS MAIL FUNCTIONS */
int encodeSosMail(struct SosMail *sos, char *finalPassword);
int foundErrorsEntriesSos(const struct SosMail *sos);
void bitPackingEncodingSos(const struct SosMail* mail, char* packed33BytesPassword);
void lookupTableEncodingSos(const char* password54Integers, char* password54Chars);
void realocateBytesEncodingSos(const char* unallocatedPassword, char* allocatedPassword);

#endif /* ENCODESOS_H */
