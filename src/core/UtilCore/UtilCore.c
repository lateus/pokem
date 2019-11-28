#include "UtilCore.h"
#include "../../data/md1database/md1database.h"
#include "../../data/md1global/md1global.h"

#include <stdio.h>
#include <string.h>

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



unsigned int getSpecialJobIndicator(int pkmnClient, int pkmnTarget, int missionType)
{
    int pairsIndex   = arePairs(pkmnClient, pkmnTarget);
    int loversIndex  = areLovers(pkmnClient, pkmnTarget);
    int parentsIndex = areParents(pkmnClient, pkmnTarget);

    if (loversIndex >= 0 && missionType == Escort) {
        return 0x0A;
    } else if (parentsIndex >= 0) {
        return 0x0F;
    } else if (pairsIndex >= 0) {
        return 0x09;
    } else {
        return NoError;
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
    return NoError;
}



int computeDifficulty(int dungeon, int dungeonFloor, int missionType)
{
    int difficulty = difficulties[dungeon][dungeonFloor];

    if (missionType == Escort) { /* Escort mission */
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
        return NoError;
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



int entryErrorsWonderMail(const struct WonderMail *wm)
{
    int errorsFound = 0;

    /* mission type check */
    if (wm->missionType > 4) {
        ++errorsFound;
#if DEBUG
        fprintf(stderr, "ERROR No. %d in argument 1 (Mission type).\n"
                        "      The mission type must be a number between 0 and 4.\n\n", errorsFound);
#endif
    }

    /* pkmn client check (limits) */
    if (wm->pkmnClient == 0 || wm->pkmnClient > 404) {
        ++errorsFound;
#if DEBUG
        fprintf(stderr, "ERROR No. %d in argument 2 (Pkmn client).\n"
                        "      Pkmns must be numbers between 1 and 404 (not necessarily match pkdex numbers).\n\n", errorsFound);
#endif
    }
    /* pkmn client check (legendaries) */
    else if ( (wm->pkmnClient >= 144 && wm->pkmnClient <= 146) /* birds */ || (wm->pkmnClient >= 150 && wm->pkmnClient <= 151) /* mewtwo and mew */ ||
              (wm->pkmnClient >= 201 && wm->pkmnClient <= 226) /* unown */ || (wm->pkmnClient >= 268 && wm->pkmnClient <= 270) /* dogs */ ||
              (wm->pkmnClient >= 274 && wm->pkmnClient <= 276) /* lugia and ho-oh */ ) {
        ++errorsFound;
#if DEBUG
        fprintf(stderr, "ERROR No. %d in argument 2 (Pkmn client).\n"
                        "      Legendaries are not valid values.\n\n", errorsFound);
#endif
    }

    if (wm->missionType == Find || wm->missionType == Escort) {
        /* pkmn target check (limits) */
        if (wm->pkmnTarget == 0 || wm->pkmnTarget > 404) {
            ++errorsFound;
#if DEBUG
            fprintf(stderr, "ERROR No. %d in argument 3 (Pkmn target).\n"
                            "      Pkmns must be numbers between 1 and 404 (not necessarily match pkdex numbers).\n\n", errorsFound);
#endif
        }

        /* pkmn target check (legendaries) */
        if ( (wm->pkmnTarget >= 144 && wm->pkmnTarget <= 146) /* birds */ || (wm->pkmnTarget >= 150 && wm->pkmnTarget <= 151) /* mewtwo and mew */ ||
             (wm->pkmnTarget >= 201 && wm->pkmnTarget <= 226) /* unown */ || (wm->pkmnTarget >= 268 && wm->pkmnTarget <= 270) /* dogs */ ||
             (wm->pkmnTarget >= 274 && wm->pkmnTarget <= 276) /* lugia and ho-oh */ ) {
            ++errorsFound;
#if DEBUG
            fprintf(stderr, "ERROR No. %d in argument 3 (Pkmn target).\n"
                            "      Legendaries are not valid values.\n\n", errorsFound);
#endif
        }
    }


    /* item to deliver/find check (limits) */
    if (wm->missionType == FindItem || wm->missionType == DeliverItem) {
        if (wm->itemDeliverFind < 1 || wm->itemDeliverFind > 232) {
            ++errorsFound;
#if DEBUG
            fprintf(stderr, "ERROR No. %d in argument 4 (item to find/deliver).\n"
                            "      Invalid item index %d. Items to find or deliver must be numbers between 1 and 232.\n\n", wm->itemDeliverFind, errorsFound);
#endif
        }

        /* item to deliver/find check (existence) */
        if (wm->missionType == FindItem) {
            if (!findItemByDungeon(wm->itemDeliverFind, wm->dungeon)) {
            ++errorsFound;
#if DEBUG
                fprintf(stderr, "ERROR No. %d in argument 4 (item to find/deliver).\n"
                                "      The item %s (index %d) can't be found in the dungeon %s (index %d).\n"
                                "      To accept a job about find an item inside a dungeon, the item must exist on it.\n"
                                "      The items that can be found in that dungeon are listed bellow:\n",
                        errorsFound, itemsStr[wm->itemDeliverFind], wm->itemDeliverFind, dungeonsStr[wm->dungeon], wm->dungeon);
                unsigned short i;
                for (i = 1; i < itemsInDungeons[wm->dungeon][0]; ++i) {
                    fprintf(stderr, "[%d] ", itemsInDungeons[wm->dungeon][i]);
                }
                fprintf(stderr, "\n\n");
#endif
            }
        }
    }


    /* dungeon check */
    if (wm->dungeon > 62) {
        ++errorsFound;
#if DEBUG
        fprintf(stderr, "ERROR No. %d in argument 5 (Dungeon).\n"
                        "      The dungeon must be a number between 0 and 62.\n\n", errorsFound);
#endif
    } else if (!strcmp(dungeonsStr[wm->dungeon], "[INVALID]")) {
        ++errorsFound;
#if DEBUG
        fprintf(stderr, "ERROR No. %d in argument 5 (Dungeon).\n"
                        "      The dungeon with index %u isn't a valid dungeon.\n\n", errorsFound, wm->dungeon);
#endif
    }


    /* floor check (floor 0) */
    if (wm->floor == 0) {
        ++errorsFound;
#if DEBUG
        fprintf(stderr, "ERROR No. %d in argument 6 (Floor).\n"
                        "      Floor 0 does not exists.\n\n", errorsFound);
#endif
    }
    /* floor check (limit) */
    if (wm->floor > difficulties[wm->dungeon][0]) {
        ++errorsFound;
#if DEBUG
        fprintf(stderr, "ERROR No. %d in argument 6 (Floor).\n"
                        "      The dungeon %s (index %u) only has %d floors. Your entry exceed that value.\n\n",
                        errorsFound, dungeonsStr[wm->dungeon], wm->dungeon, difficulties[wm->dungeon][0]);
#endif
    }


    /* reward type check */
    if (wm->rewardType > 9) {
        ++errorsFound;
#if DEBUG
        fprintf(stderr, "ERROR No. %d in argument 7 (Reward type).\n"
                        "      The reward type must be a number between 0 and 9.\n\n", errorsFound);
#endif
        if (!computeDifficulty(wm->dungeon, wm->floor, wm->missionType)) { /* 0 means 'E' difficulty */
            ++errorsFound;
#if DEBUG
            fprintf(stderr, "ERROR No. %d in argument 7 (Reward type).\n"
                            "      To receive a friend area reward, the mission must have at least 'D' difficulty.\n\n", errorsFound);
#endif
        }
    }


    /* reward item check */
    if ( (wm->rewardType >= 1 && wm->rewardType <= 3) || (wm->rewardType >= 6 && wm->rewardType <= 8) ) {
        if (wm->itemReward > 239) {
            ++errorsFound;
#if DEBUG
            fprintf(stderr, "ERROR No. %d in argument 8 (Reward item).\n"
                            "      Reward item must be a number between 0 and 239.\n"
                            "      Current value: %d\n\n", errorsFound, wm->itemReward);
#endif
        }
    }


    /* friend area reward check */
    if (wm->rewardType == 9) {
        if (wm->friendAreaReward != 9 && wm->friendAreaReward != 10 && wm->friendAreaReward != 15 && wm->friendAreaReward != 37) {
            ++errorsFound;
#if DEBUG
            fprintf(stderr, "ERROR No. %d in argument 9 (Friend area reward).\n"
                            "      Valid friend area values are: [9, 10, 15, 37].\n"
                            "      Current value: %d\n\n", errorsFound, wm->friendAreaReward);
#endif
        }
    }

    fflush(stderr);
    return errorsFound;
}



int entryErrorsSosMail(const struct SosMail *sos)
{
    int errorsFound = 0;

    /* pkmn to rescue check (limits) */
    if (sos->pkmnToRescue == 0 || sos->pkmnToRescue > 414) {
        ++errorsFound;
#ifdef DEBUG
        fprintf(stderr, "ERROR No. %d in argument 1 (Pkmn to rescue).\n"
                        "      Pkmns must be numbers between 1 and 404 (not necessarily match pkdex numbers).\n\n", errorsFound);
        fflush(stderr);
#endif
    }


    /* nickname check */
    if (!strlen(sos->pkmnNick)) {
        ++errorsFound;
#ifdef DEBUG
        fprintf(stderr, "ERROR No. %d in argument 2 (Pkmn nickname).\n"
                        "      The nickname cannot be empty.\n\n", errorsFound);
        fflush(stderr);
#endif
    }


    /* dungeon check */
    if (sos->dungeon > 62) {
        ++errorsFound;
#ifdef DEBUG
        fprintf(stderr, "ERROR No. %d in argument 3 (Dungeon).\n"
                        "      The dungeon must be a number between 0 and 62.\n\n", errorsFound);
        fflush(stderr);
#endif
    } else if (!strcmp(dungeonsStr[sos->dungeon], "[INVALID]")) {
        ++errorsFound;
#ifdef DEBUG
        fprintf(stderr, "ERROR No. %d in argument 3 (Dungeon).\n"
                        "      The dungeon with index %u isn't a valid dungeon.\n\n", errorsFound, sos->dungeon);
        fflush(stderr);
#endif
    } else if (sos->floor > difficulties[sos->dungeon][0]) { /* floor check */
        ++errorsFound;
#ifdef DEBUG
        fprintf(stderr, "ERROR No. %d in argument 4 (Floor).\n"
                        "      The dungeon %s (index %u) only has %d floors. Your entry exceed that value.\n\n",
                                    errorsFound, dungeonsStr[sos->dungeon], sos->dungeon, difficulties[sos->dungeon][0]);
        fflush(stderr);
#endif
    }


    /* rescue chances left check */
    if (sos->chancesLeft < 1 || sos->chancesLeft > 10) {
        ++errorsFound;
#ifdef DEBUG
        fprintf(stderr, "ERROR No. %d in argument 6 (Chances left).\n"
                        "      The chances left value must be between 1 and 10.\n\n", errorsFound);
        fflush(stderr);
#endif
    }

    return errorsFound;
}
