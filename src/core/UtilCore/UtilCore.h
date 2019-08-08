#ifndef DEC_ENC_COMMON_H
#define DEC_ENC_COMMON_H

int areParents(int pkmnClient, int pkmnTarget);
int arePairs(int pkmnClient, int pkmnTarget);
int areLovers(int pkmnClient, int pkmnTarget);
unsigned int getSpecialJobIndicator(int pairsIndex, int loversIndex, int parentsIndex);
int findItemByDungeon(int item, int dungeon);
int computeDifficulty(int dungeon, int dungeonFloor, int missionType);
int computeMoneyReward(int difficulty, int rewardType);
int computeChecksum(const char* packedPassword, int bytes);

#endif /* DEC_ENC_COMMON_H */
