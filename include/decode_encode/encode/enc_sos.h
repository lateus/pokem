#ifndef ENC_SOS_H
#define ENC_SOS_H

#include "../../model/md1global.h"

int encodeSOSMail(struct SOSMAIL *sos, char *finalPassword);
int foundErrorsEntriesSOS(const struct SOSMAIL *sos);
void bitPackingEncodingSOS(char* packed33BytesPassword, const struct SOSMAIL* mail);
void lookupTableEncodingSOS(char* password54Chars, const char* password54Integers);
void realocateBytesEncodingSOS(char* allocatedPassword, const char* unallocatedPassword);

#endif /* ENC_SOS_H */
