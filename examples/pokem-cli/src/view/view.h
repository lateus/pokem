#ifndef VIEW_H
#define VIEW_H

#include "../../lib/pokem.h"

int showSelectionScreen(void);

int showGeneralHelp(const char *programName);
int showHelpDecodingWM(const char *programName);
int showHelpEncodingWM(const char *programName);
int showHelpDecodingSOS(const char *programName);
int showHelpEncodingSOS(const char *programName);
int showHelpConverting(const char *programName);

void showDatabase(void);

void printWMData(const struct WonderMailInfo *mailInfo);
void printSOSData(const struct SosMailInfo *mailInfo);

#endif /* VIEW_H */
