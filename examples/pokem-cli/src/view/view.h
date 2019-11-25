#ifndef VIEW_H
#define VIEW_H

#include "../../lib/pokem.h"

int showSelectionScreen(void);

int showGeneralHelp(const char *programName);
int showHelpDecodingWonderMail(const char *programName);
int showHelpEncodingWonderMail(const char *programName);
int showHelpDecodingSos(const char *programName);
int showHelpEncodingSos(const char *programName);
int showHelpConverting(const char *programName);

void showDatabase(void);

void printWonderMailData(const struct WonderMailInfo *mailInfo);
void printSOSData(const struct SosMailInfo *mailInfo);

#endif /* VIEW_H */
