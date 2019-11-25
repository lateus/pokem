#ifndef ENCODESOS_H
#define ENCODESOS_H

#include "../../../data/md1global/md1global.h"

/* ENCODING SOS MAIL FUNCTIONS */
int encodeSOSMail(struct SosMail *sos, char *finalPassword);
int foundErrorsEntriesSOS(const struct SosMail *sos);
void bitPackingEncodingSOS(char* packed33BytesPassword, const struct SosMail* mail);
void lookupTableEncodingSOS(char* password54Chars, const char* password54Integers);
void realocateBytesEncodingSOS(char* allocatedPassword, const char* unallocatedPassword);

#endif /* ENCODESOS_H */
