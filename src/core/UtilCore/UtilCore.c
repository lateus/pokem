#include "UtilCore.h"
#include "../../data/md1database/md1database.h"
#include "../../data/md1global/md1global.h"

int areParents(int pkmnClient, int pkmnTarget)
{
    int i;
    for (i = 0; i < 42; i+=2) {
        if ( (parents[i] == pkmnClient) && (parents[i + 1] == pkmnTarget) ) {
            return (i >> 1); /* same as i/2 */
        }
    }

    return -1;
}



int arePairs(int pkmnClient, int pkmnTarget)
{
    int i;
    for (i = 0; i < 90; i+=2) {
        if ( ( (pairs[i] == pkmnClient) && (pairs[i + 1] == pkmnTarget) ) || ( (pairs[i] == pkmnTarget) && (pairs[i + 1] == pkmnClient) ) ) {
            return (i >> 1); /* same as i/2 */
        }
    }

    return -1;
}



int areLovers(int pkmnClient, int pkmnTarget)
{
    int i;
    for (i = 0; i < 12; i+=2) {
        if ( ( (lovers[i] == pkmnClient) && (lovers[i + 1] == pkmnTarget) ) || ( (lovers[i] == pkmnTarget) && (lovers[i + 1] == pkmnClient) ) ) {
            return (i >> 1); /* same as i/2 */
        }
    }

    return -1;
}



unsigned int getSpecialJobIndicator(int pairsIndex, int loversIndex, int parentsIndex)
{
    if (pairsIndex >= 0) {
        return 0x09;
    } else if (loversIndex >= 0) {
        return 0x0A;
    } else if (parentsIndex >= 0) {
        return 0x0F;
    } else {
        return 0;
    }
}



int findItemByDungeon(int item, int dungeon)
{
    int i;
    for (i = 1; i <= itemsInDungeons[dungeon][0]; ++i) {
        if (item == itemsInDungeons[dungeon][i]) {
            return 1;
        }
    }
    return 0;
}



int computeDifficulty(int dungeon, int dungeonFloor, int missionType)
{
    int difficulty = difficulties[dungeon][dungeonFloor];

    if (missionType == ESCORT) { /* Escort mission */
        difficulty += 2;
    }

    difficulty >>= 1;   /* same as an integer division by 2. This operation truncate the byte. It's equivalent to use the function 'floor(double)' of <math.h> */

    if (difficulty > 6) {
        difficulty = 6;
    }

    return difficulty;
}



int computeMoneyReward(int difficulty, int rewardType)
{
    int money = (difficulty + 1) * 100;

    if (rewardType < 2) {
        return money;
    } else if (rewardType == 5 || rewardType == 6) {
        return money << 1;  /* same as money*2 */
    } else {
        return 0;
    }
}



int computeChecksum(const char* packedPassword, int bytes)
{
    int i, checksum = 0;
    for (i = 1; i < bytes; ++i) { /* the first byte is ignored in the calculation, cuz is merely for a checksum */
        checksum += (packedPassword[i]) + i;
        checksum &= 0xFF; /* make the checksum variable a single byte long */
    }

    return checksum;
}
