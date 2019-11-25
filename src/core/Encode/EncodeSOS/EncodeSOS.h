#ifndef ENCODESOS_H
#define ENCODESOS_H

#include "../../../data/md1global/md1global.h"

/* ENCODING SOS MAIL FUNCTIONS */
int encodeSosMail(struct SosMail *sos, char *finalPassword);
int foundErrorsEntriesSos(const struct SosMail *sos);
void bitPackingEncodingSos(char* packed33BytesPassword, const struct SosMail* mail);
void lookupTableEncodingSos(char* password54Chars, const char* password54Integers);
void realocateBytesEncodingSos(char* allocatedPassword, const char* unallocatedPassword);

#endif /* ENCODESOS_H */
