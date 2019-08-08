#ifndef ENCODESOS_H
#define ENCODESOS_H

#include "../../../data/md1global/md1global.h"

int encodeSOSMail(struct SOSMAIL *sos, char *finalPassword);
int foundErrorsEntriesSOS(const struct SOSMAIL *sos);
void bitPackingEncodingSOS(char* packed33BytesPassword, const struct SOSMAIL* mail);
void lookupTableEncodingSOS(char* password54Chars, const char* password54Integers);
void realocateBytesEncodingSOS(char* allocatedPassword, const char* unallocatedPassword);

#endif /* ENCODESOS_H */
