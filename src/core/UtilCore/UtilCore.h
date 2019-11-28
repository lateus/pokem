#ifndef UTILCORE_H
#define UTILCORE_H

#include "../../data/md1global/md1global.h"

/* DECODING/ENCODING COMMON FUNCTIONS */
int areParents(int pkmnClient, int pkmnTarget);
int arePairs(int pkmnClient, int pkmnTarget);
int areLovers(int pkmnClient, int pkmnTarget);
unsigned int getSpecialJobIndicator(int pkmnClient, int pkmnTarget, int missionType);
int findItemByDungeon(int item, int dungeon);
int computeDifficulty(int dungeon, int dungeonFloor, int missionType);
int computeMoneyReward(int difficulty, int rewardType);
int computeChecksum(const char* packedPassword, int bytes);
int entryErrorsWonderMail(const struct WonderMail *wm);
int entryErrorsSosMail(const struct SosMail *sos);

#endif /* UTILCORE_H */
