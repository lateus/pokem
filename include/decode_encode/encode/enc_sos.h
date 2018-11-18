#ifndef ENC_SOS_H
#define ENC_SOS_H

#include "../../model/md1global.h"

int setSOSData(const char *argv[], struct SOSMAIL *wm);
int foundErrorsEntriesSOS(const struct SOSMAIL *wm, const char *argv[]);
void bitPackingEncodingSOS(char* packed33BytesPassword, const struct SOSMAIL* mail);

#endif /* ENC_SOS_H */
