#ifndef VIEW_H
#define VIEW_H

#include "../../lib/pokem.h"

/* Colors */
#define COLOR_BORDER COLOR(96, 128, 248)
#define COLOR_BACKGROUND COLOR_BG(32, 72, 104)
#define COLOR_GREEN COLOR(88, 248, 88)
#define COLOR_YELLOW COLOR(248, 248, 0)
#define COLOR_CYAN COLOR(0, 248, 248)
#define COLOR_RED COLOR(248, 128, 88)

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

void printWonderMailData(const struct WonderMailInfo *mailInfo, const struct WonderMail *mail);
void printSOSData(const struct SosMailInfo *mailInfo);

int checkPkmnInWonderMail(int index, int printErrorMessages);
int checkDungeonInWonderMail(int index, int printErrorMessages);
int checkFloorForDungeon(int floor, int dungeonIndex, int printErrorMessages);
int checkItemToFindDeliverRangeInWonderMail(int index, int printErrorMessages);
int checkItemToFindDeliverByDungeonInWonderMail(int itemIndex, int dungeonIndex, int printErrorMessages);
int checkItemRange(int index, int printErrorMessages);

void clearStdinBuffer();
int requestAndValidateIntegerInput(unsigned int *n, int allowEmptyValue, int valueIfEmpty, const char* message);
int requestAndValidateStringInput(char* str, int maxLength, int allowEmptyValue, const char* valueIfEmpty, const char* message);

#endif /* VIEW_H */
