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

int requestWonderMailPassword(char *password);
int requestAndParseWonderMailData(struct WonderMail *wm);
int requestSOSMailPassword(char *password);
int requestAndParseSosMailData(struct SosMail *sos);

void printWonderMailData(const struct WonderMailInfo *mailInfo);
void printSOSData(const struct SosMailInfo *mailInfo);

int checkPkmnInWonderMail(int index, int printErrorMessages);
int checkDungeonInWonderMail(int index, int printErrorMessages);
int checkFloorForDungeon(int floor, int dungeonIndex, int printErrorMessages);
int checkItemToFindDeliverRangeInWonderMail(int index, int printErrorMessages);
int checkItemToFindDeliverByDungeonInWonderMail(int itemIndex, int dungeonIndex, int printErrorMessages);
int checkItemRange(int index, int printErrorMessages);

void clearStdinBuffer();

#endif /* VIEW_H */
