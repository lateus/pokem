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

void printWonderMailData(const struct WonderMailInfo *mailInfo);
void printSOSData(const struct SosMailInfo *mailInfo);

int checkPkmnInWonderMail(int index);
int checkDungeonInWonderMail(int index);
int checkFloorForDungeon(int floor, int dungeonIndex);
int checkItemToFindDeliverRangeInWonderMail(int index);
int checkItemToFindDeliverByDungeonInWonderMail(int itemIndex, int dungeonIndex);
int checkItemRange(int index);

void clearStdinBuffer();

#endif /* VIEW_H */
