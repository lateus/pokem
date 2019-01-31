#ifndef ENC_SOS_H
#define ENC_SOS_H

#include "../../model/md1global.h"

int encodeSOSMail(struct SOSMAIL *sos, char *finalPassword);
int foundErrorsEntriesSOS(const struct SOSMAIL *sos);
void bitPackingEncodingSOS(char* packed33BytesPassword, const struct SOSMAIL* mail);

#endif /* ENC_SOS_H */
