#include "UtilCore.h"
#include "../../data/md1database/md1database.h"
#include "../../data/md1global/md1global.h"

#include <stdio.h>
#include <string.h>

int printMessages = 0;

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



int canEvolveWithItem(int pkmn, int item)
{
    int i;
    switch(item) {
    case 108: /* Thunderstone */
        for (i = 1; i <= thunderStonePkmn[0]; ++i) { /* Start at [1] because [0] contains the size */
            if (pkmn == thunderStonePkmn[i]) {
                return 1;
            }
        }
        break;
    case 111: /* Sun Stone */
        for (i = 1; i <= sunStonePkmn[0]; ++i) { /* Start at [1] because [0] contains the size */
            if (pkmn == sunStonePkmn[i]) {
                return 1;
            }
        }
        break;
    case 112: /* Moon Stone */
        for (i = 1; i <= moonStonePkmn[0]; ++i) { /* Start at [1] because [0] contains the size */
            if (pkmn == moonStonePkmn[i]) {
                return 1;
            }
        }
        break;
    case 113: /* Fire Stone */
        for (i = 1; i <= fireStonePkmn[0]; ++i) { /* Start at [1] because [0] contains the size */
            if (pkmn == fireStonePkmn[i]) {
                return 1;
            }
        }
        break;
    case 114: /* Water Stone */
        for (i = 1; i <= waterStonePkmn[0]; ++i) { /* Start at [1] because [0] contains the size */
            if (pkmn == waterStonePkmn[i]) {
                return 1;
            }
        }
        break;
    case 116: /* Leaf Stone */
        for (i = 1; i <= leafStonePkmn[0]; ++i) { /* Start at [1] because [0] contains the size */
            if (pkmn == leafStonePkmn[i]) {
                return 1;
            }
        }
        break;
    case 118: /* Link Cable */
        for (i = 1; i <= linkCablePkmn[0]; ++i) { /* Start at [1] because [0] contains the size */
            if (pkmn == linkCablePkmn[i]) {
                return 1;
            }
        }
        break;
    case 109: /* Deepseascale */
        for (i = 1; i <= deepSeaScalePkmn[0]; ++i) { /* Start at [1] because [0] contains the size */
            if (pkmn == deepSeaScalePkmn[i]) {
                return 1;
            }
        }
        break;
    case 110: /* Deepseatooth */
        for (i = 1; i <= deepSeaToothPkmn[0]; ++i) { /* Start at [1] because [0] contains the size */
            if (pkmn == deepSeaToothPkmn[i]) {
                return 1;
            }
        }
        break;
    case 117: /* Dragon scale */
        for (i = 1; i <= dragonScalePkmn[0]; ++i) { /* Start at [1] because [0] contains the size */
            if (pkmn == dragonScalePkmn[i]) {
                return 1;
            }
        }
        break;
    case 107: /* King's Rock */
        for (i = 1; i <= kingsRockPkmn[0]; ++i) { /* Start at [1] because [0] contains the size */
            if (pkmn == kingsRockPkmn[i]) {
                return 1;
            }
        }
        break;
    case 115: /* Metal Coat */
        for (i = 1; i <= metalCoatPkmn[0]; ++i) { /* Start at [1] because [0] contains the size */
            if (pkmn == metalCoatPkmn[i]) {
                return 1;
            }
        }
        break;
    case 106: /* Upgrade */
        for (i = 1; i <= upgradePkmn[0]; ++i) { /* Start at [1] because [0] contains the size */
            if (pkmn == upgradePkmn[i]) {
                return 1;
            }
        }
        break;
    case 48: /* Sun Ribbon */
        for (i = 1; i <= sunRibbonPkmn[0]; ++i) { /* Start at [1] because [0] contains the size */
            if (pkmn == sunRibbonPkmn[i]) {
                return 1;
            }
        }
        break;
    case 49: /* Lunar Ribbon */
        for (i = 1; i <= lunarRibbonPkmn[0]; ++i) { /* Start at [1] because [0] contains the size */
            if (pkmn == lunarRibbonPkmn[i]) {
                return 1;
            }
        }
        break;
    case 47: /* Beauty Scarf */
        for (i = 1; i <= beautyScarfPkmn[0]; ++i) { /* Start at [1] because [0] contains the size */
            if (pkmn == beautyScarfPkmn[i]) {
                return 1;
            }
        }
    }

    return 0;
}



int isFood(int item)
{
    return item == 82  || /* Apple */
           item == 83  || /* Big Apple */
           item == 85  || /* Huge Apple */
           item == 103 || /* Banana */
           (item >= 86 && item <= 102); /* Gummis */
}



unsigned int getSpecialJobIndicator(int pkmnClient, int pkmnTarget, int missionType, int trySpecialJobIndicator, int itemToFindDeliver)
{
    int pairsIndex   = arePairs(pkmnClient, pkmnTarget);
    int loversIndex  = areLovers(pkmnClient, pkmnTarget);
    int parentsIndex = areParents(pkmnClient, pkmnTarget);

    if (trySpecialJobIndicator && (missionType == FindItem || missionType == DeliverItem)) {
        if (canEvolveWithItem(pkmnClient, itemToFindDeliver)) { /* Evolution special missions */
            return 0x05;
        } else if (isFood(itemToFindDeliver)) { /* Food special missions */
            return 0x06;
        }
    } else if (loversIndex >= 0 && missionType == Escort) { /* Lovers special missions */
        return 0x0A;
    } else if (parentsIndex >= 0 && missionType == Find) { /* Lovers special missions */
        return 0x0F;
    } else if (pairsIndex >= 0 && missionType == Find) { /* Pairs special missions */
        return 0x09;
    }

    return 0; /* No special */
}


/* TODO: This does not works in Wonder Mails */
int getMailType(const char* password)
{
    const size_t passwordLength = strlen(password);
    if (/*passwordLength != 24 && */passwordLength != 54) {
        return InvalidMailType;
    }
    // int mailType = ((password54Integers[1] >> 3) & 0x03) | (password54Integers[2] & 0x03) << 2;
    const char* lookupTable = "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W";
    const char firstChar  = password[passwordLength == 24 ? 20 :  7];
    const char secondChar = password[passwordLength == 24 ?  9 : 25];
    const char* firstCharPtr = strchr(lookupTable, firstChar);
    const char* secondCharPtr = strchr(lookupTable, secondChar);
    return (!firstCharPtr || !secondCharPtr) ? InvalidMailType : (((firstCharPtr - lookupTable) >> 3) & 0x03) | ((secondCharPtr - lookupTable) & 0x03) << 2;
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

    if (rewardType == Money || rewardType == MoneyItem) {
        return money;
    } else if (rewardType == MoneyMoney || rewardType == MoneyMoneyItem) {
        return money << 1;  /* same as money*2 */
    } else {
        return 0;
    }
}



int computeChecksum(const char* packedPassword, int bytes)
{
    int i, checksum = 0;
    for (i = 0; i < bytes; ++i) {
        checksum += (packedPassword[i]) + i + 1;
        checksum &= 0xFF; /* make the checksum variable a single byte long */
    }

    return checksum;
}



int entryErrorsWonderMail(const struct WonderMail *wm)
{
    int errorsFound = 0;

    /* mail type check */
    if (wm->mailType != WonderMailType) {
        ++errorsFound;
        if (printMessages) {
            fprintf(stderr, "ERROR No. %d (Mail type).\n"
                            "      The mail type must be a Wonder Mail.\n"
                            "      Current value: %u [%s]\n\n", errorsFound, wm->mailType,
                            wm->mailType == SosMailType ? "SOS Mail" :
                            wm->mailType == AOkMailType ? "AOK Mail" : "INVALID");
        }
    } 

    /* mission type check */
    if (wm->missionType > 4) {
        ++errorsFound;
        if (printMessages) {
            fprintf(stderr, "ERROR No. %d in argument 1 (Mission type).\n"
                            "      The mission type must be a number between 0 and 4.\n"
                            "      Current value: %u [%s]\n\n", errorsFound, wm->missionType, wm->missionType == FriendRescue ? "Friend rescue" : "INVALID");
        }
    }

    /* pkmn client check (limits) */
    if (wm->pkmnClient == 0 || wm->pkmnClient >= pkmnSpeciesCount) {
        ++errorsFound;
        if (printMessages) {
            fprintf(stderr, "ERROR No. %d in argument 2 (Pkmn client).\n"
                            "      Pkmns must be numbers between 1 and %d (not necessarily match pkdex numbers).\n"
                            "      Current value: %u [INVALID]\n\n", errorsFound, pkmnSpeciesCount - 1, wm->pkmnClient);
        }
    }
    /* pkmn client check (legendaries) */
    else if ( (wm->pkmnClient >= 144 && wm->pkmnClient <= 146) /* birds */ || (wm->pkmnClient >= 150 && wm->pkmnClient <= 151) /* mewtwo and mew */ ||
              (wm->pkmnClient >= 201 && wm->pkmnClient <= 226) /* unown */ || (wm->pkmnClient >= 268 && wm->pkmnClient <= 270) /* dogs */ ||
              (wm->pkmnClient >= 274 && wm->pkmnClient <= 276) /* lugia and ho-oh */ ||
              (wm->pkmnClient >= 405 && wm->pkmnClient <= 414) /* regis, eons, kyogre, groudon, rayquaza, jirachi and deoxys */ ) {
        ++errorsFound;
        if (printMessages) {
            fprintf(stderr, "ERROR No. %d in argument 2 (Pkmn client).\n"
                            "      Legendaries are not valid values.\n"
                            "      Current value: %u [%s]\n\n", errorsFound, wm->pkmnClient, pkmnSpeciesStr[wm->pkmnClient]);
        }
    }

    if (wm->missionType == Find || wm->missionType == Escort) {
        /* pkmn target check (limits) */
        if (wm->pkmnTarget == 0 || wm->pkmnTarget >= pkmnSpeciesCount) {
            ++errorsFound;
            if (printMessages) {
                fprintf(stderr, "ERROR No. %d in argument 3 (Pkmn target).\n"
                                "      Pkmns must be numbers between 1 and %d (not necessarily match pkdex numbers).\n"
                                "      Current value: %u [INVALID]\n\n", errorsFound, pkmnSpeciesCount - 1, wm->pkmnTarget);
            }
        }

        /* pkmn target check (legendaries) */
        if ( (wm->pkmnTarget >= 144 && wm->pkmnTarget <= 146) /* birds */ || (wm->pkmnTarget >= 150 && wm->pkmnTarget <= 151) /* mewtwo and mew */ ||
             (wm->pkmnTarget >= 201 && wm->pkmnTarget <= 226) /* unown */ || (wm->pkmnTarget >= 268 && wm->pkmnTarget <= 270) /* dogs */ ||
             (wm->pkmnTarget >= 274 && wm->pkmnTarget <= 276) /* lugia and ho-oh */ ||
             (wm->pkmnTarget >= 405 && wm->pkmnTarget <= 414) /* regis, eons, kyogre, groudon, rayquaza, jirachi and deoxys */ ) {
            ++errorsFound;
            if (printMessages) {
                fprintf(stderr, "ERROR No. %d in argument 3 (Pkmn target).\n"
                                "      Legendaries are not valid values.\n"
                                "      Current value: %u [%s]\n\n", errorsFound, wm->pkmnTarget, pkmnSpeciesStr[wm->pkmnTarget]);
            }
        }
    }


    /* item to deliver/find check (limits) */
    if (wm->missionType == FindItem || wm->missionType == DeliverItem) {
        if (wm->itemDeliverFind < 1 || wm->itemDeliverFind > (itemsCount - 8)) { /* the last 7 are not valid */
            ++errorsFound;
            if (printMessages) {
                fprintf(stderr, "ERROR No. %d in argument 4 (item to find/deliver).\n"
                                "      Invalid item index %d. Items to find or deliver must be numbers between 1 and %d.\n"
                                "      Current value: %u [INVALID]\n\n", errorsFound, wm->itemDeliverFind, (itemsCount - 8), wm->itemDeliverFind);
            }
        }

        /* item to deliver/find check (existence) */
        if (wm->missionType == FindItem) {
            if (!findItemByDungeon(wm->itemDeliverFind, wm->dungeon)) {
                ++errorsFound;
                if (printMessages) {
                    fprintf(stderr, "ERROR No. %d in argument 4 (item to find/deliver).\n"
                                    "      The item %u [%s] can't be found in the dungeon %u [%s].\n"
                                    "      To accept a job about finding an item inside a dungeon, the item must exist on that dungeon.\n"
                                    "      The items that can be found in that dungeon are listed bellow:\n",
                            errorsFound, wm->itemDeliverFind, itemsStr[wm->itemDeliverFind], wm->dungeon, dungeonsStr[wm->dungeon]);
                    unsigned short i;
                    for (i = 1; i < itemsInDungeons[wm->dungeon][0]; ++i) {
                        fprintf(stderr, "%u [%s]\n", itemsInDungeons[wm->dungeon][i], itemsStr[itemsInDungeons[wm->dungeon][i]]);
                    }
                    fprintf(stderr, "\n\n");
                }
            }
        }
    }


    /* dungeon check */
    if (wm->dungeon >= dungeonsCount) {
        ++errorsFound;
        if (printMessages) {
        fprintf(stderr, "ERROR No. %d in argument 5 (Dungeon).\n"
                        "      The dungeon must be a number between 0 and %d.\n"
                        "      Current value: %u [INVALID]\n\n", errorsFound, dungeonsCount - 1, wm->dungeon);
        }
    } else if (strcmp(dungeonsStr[wm->dungeon], "[INVALID]") == 0) {
        ++errorsFound;
        if (printMessages) {
            fprintf(stderr, "ERROR No. %d in argument 5 (Dungeon).\n"
                            "      The dungeon with index %u isn't a valid dungeon.\n", errorsFound, wm->dungeon);
        }
    } else { /* Check the floor only if the dungeon is valid */
        if (wm->floor == 0) { /* floor check (floor 0) */
            ++errorsFound;
            if (printMessages) {
                fprintf(stderr, "ERROR No. %d in argument 6 (Floor).\n"
                                "      Floor 0 does not exists.\n\n", errorsFound);
            }
        } else if (wm->floor > difficulties[wm->dungeon][0]) { /* floor check (limit) */
            ++errorsFound;
            if (printMessages) {
                fprintf(stderr, "ERROR No. %d in argument 6 (Floor).\n"
                                "      The dungeon %u [%s] only has %d floors. Your entry exceed that value.\n\n",
                                errorsFound, wm->dungeon, wm->dungeon < dungeonsCount ? dungeonsStr[wm->dungeon] : "INVALID", difficulties[wm->dungeon][0]);
            }
        } else if (wm->floor == forbiddenFloorsInDungeons[wm->dungeon][1] || wm->floor == forbiddenFloorsInDungeons[wm->dungeon][2]) {
            ++errorsFound;
            if (printMessages) {
                fprintf(stderr, "ERROR No. %d in argument 6 (Floor).\n"
                                "      A mission cannot be made in floor %d of dungeon %u [%s].\n\n",
                                errorsFound, wm->floor, wm->dungeon, wm->dungeon < dungeonsCount ? dungeonsStr[wm->dungeon] : "INVALID");
            }
        }
    }

    /* reward type check (range) */
    if (wm->rewardType > 9) {
        ++errorsFound;
        if (printMessages) {
            fprintf(stderr, "ERROR No. %d in argument 7 (Reward type).\n"
                            "      The reward type must be a number between 0 and 9.\n\n"
                            "      Current value: %u [INVALID]\n\n", errorsFound, wm->rewardType);
        }
    }
    /* reward type check (enable friend area reward) */
    if (wm->rewardType == FriendArea && computeDifficulty(wm->dungeon, wm->floor, wm->missionType) == 0) { /* 0 means 'E' difficulty */
        ++errorsFound;
        if (printMessages) {
            fprintf(stderr, "ERROR No. %d in argument 7 (Reward type).\n"
                            "      To receive a friend area reward, the mission must have at least \"D\" difficulty.\n\n", errorsFound);
        }
    }


    /* reward item check */
    if ( (wm->rewardType >= 1 && wm->rewardType <= 3) || (wm->rewardType >= 6 && wm->rewardType <= 8) ) {
        if (wm->itemReward == 0 || wm->itemReward >= itemsCount) {
            ++errorsFound;
            if (printMessages) {
                fprintf(stderr, "ERROR No. %d in argument 8 (Reward item).\n"
                                "      Reward item must be a number between 0 and %d.\n"
                                "      Current value: %u [INVALID]\n\n", errorsFound, itemsCount - 1, wm->itemReward);
            }
        }
    }


    /* friend area reward check */
    if (wm->rewardType == 9) {
        if (wm->friendAreaReward != 9 && wm->friendAreaReward != 10 && wm->friendAreaReward != 15 && wm->friendAreaReward != 37) {
            ++errorsFound;
            if (printMessages) {
                fprintf(stderr, "ERROR No. %d in argument 9 (Friend area reward).\n"
                                "      Valid friend area values are: [%d (%s), %d (%s), %d (%s), %d (%s)].\n"
                                "      Current value: %u [%s]\n\n", errorsFound, 9, friendAreasStr[9], 10, friendAreasStr[10], 15, friendAreasStr[15], 37, friendAreasStr[37], wm->friendAreaReward, wm->friendAreaReward < friendAreasCount ? friendAreasStr[wm->friendAreaReward] : "INVALID");
            }
        }
    }

    fflush(stderr);
    return errorsFound;
}



int entryErrorsSosMail(const struct SosMail *sos)
{
    int errorsFound = 0;

    /* mail type check */
    if (sos->mailType != SosMailType && sos->mailType != AOkMailType && sos->mailType != ThankYouMailType) {
        ++errorsFound;
        if (printMessages) {
            fprintf(stderr, "ERROR No. %d (Mail type).\n"
                            "      The mail type must be a SOS Mail, A-OK Mail or Thank-You Mail.\n"
                            "      Current value: %u [INVALID]\n\n", errorsFound, sos->mailType);
        }
    } 

    /* pkmn to rescue check (limits) */
    if (sos->pkmnToRescue == 0 || sos->pkmnToRescue >= pkmnSpeciesCount) {
        ++errorsFound;
        if (printMessages) {
            fprintf(stderr, "ERROR No. %d in argument 1 (Pkmn to rescue).\n"
                            "      Pkmns must be numbers between 1 and 404 (not necessarily match pkdex numbers).\n\n", errorsFound);
            fflush(stderr);
        }
    }


    /* nickname check */
    if (!strlen(sos->pkmnNick)) {
        ++errorsFound;
        if (printMessages) {
            fprintf(stderr, "ERROR No. %d in argument 2 (Pkmn nickname).\n"
                            "      The nickname cannot be empty.\n\n", errorsFound);
            fflush(stderr);
        }
    }


    /* dungeon check */
    if (sos->dungeon >= dungeonsCount) {
        ++errorsFound;
        if (printMessages) {
            fprintf(stderr, "ERROR No. %d in argument 3 (Dungeon).\n"
                            "      The dungeon must be a number between 0 and 62.\n\n", errorsFound);
            fflush(stderr);
        }
    } else if (!strcmp(dungeonsStr[sos->dungeon], "[INVALID]")) {
        ++errorsFound;
        if (printMessages) {
            fprintf(stderr, "ERROR No. %d in argument 3 (Dungeon).\n"
                            "      The dungeon with index %u isn't a valid dungeon.\n\n", errorsFound, sos->dungeon);
            fflush(stderr);
        }
    } else {
        if (sos->floor == 0) { /* floor check (floor 0) */
            ++errorsFound;
            if (printMessages) {
                fprintf(stderr, "ERROR No. %d in argument 4 (Floor).\n"
                                "      Floor 0 does not exists.\n\n", errorsFound);
            }
        } else if (sos->floor > difficulties[sos->dungeon][0]) { /* floor check (limit) */
            ++errorsFound;
            if (printMessages) {
                fprintf(stderr, "ERROR No. %d in argument 4 (Floor).\n"
                                "      The dungeon %s (index %u) only has %d floors. Your entry exceed that value.\n\n",
                                            errorsFound, dungeonsStr[sos->dungeon], sos->dungeon, difficulties[sos->dungeon][0]);
                fflush(stderr);
            }
        }
    }


    /* mail ID check */
    if (sos->mailID > 9999) {
        ++errorsFound;
        if (printMessages) {
            fprintf(stderr, "ERROR No. %d in argument 5 (Mail ID).\n"
                            "      The mail ID must be a non-negative number with no more than 4 digits.\n\n", errorsFound);
            fflush(stderr);
        }
    }


    /* rescue chances left check */
    int minChancesLeft = sos->mailType == SosMailType ? 1  : 0;
    int maxChancesLeft = sos->mailType == SosMailType ? 10 : 9;
    if (sos->mailType >= SosMailType && sos->mailType <= ThankYouMailType && (sos->chancesLeft < minChancesLeft || sos->chancesLeft > maxChancesLeft)) {
        ++errorsFound;
        if (printMessages) {
            fprintf(stderr, "ERROR No. %d in argument 6 (Chances left).\n"
                            "      The chances left for %s value must be between %d and %d.\n\n", errorsFound, sos->mailType == SosMailType ? "SOS mails" : "AOK and Thank-You mails", minChancesLeft, maxChancesLeft);
            fflush(stderr);
        }
    }

    return errorsFound;
}



void reallocateBytes(const char* unallocatedBytes, const unsigned char newPositions[], int n, char* allocatedBytes)
{
    int i;
    for (i = 0; i < n; ++i) {
        allocatedBytes[i] = unallocatedBytes[ newPositions[i] ];
    }
}



int mapPasswordByPositionInLookupTable(const char* password, const char* lookupTable, int n, char* newPassword)
{
    char *characterLocation = NULL;
    int i;
    for (i = 0; i < n; ++i) {
        characterLocation = strchr(lookupTable, password[i]);
        if (characterLocation) {
            newPassword[i] = characterLocation - lookupTable;
        } else {
            if (printMessages) {
                fprintf(stderr, "ERROR: INVALID character: '%c' found at index [%d].\n"
                                "Valid characters are:\n"
                                "    > Numbers: '0' to '9'.\n"
                                "    > Letters (UPPERCASE only): 'C', 'F', 'H', 'J', 'K', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'W', 'X' AND 'Y'.\n"
                                "    > Symbols: '*' (FEMALE), '/' (MALE), '.' (...), '!', '?', '+', '-'\n\n"
                                "THE PASSWORD CAN'T BE DECODED.\n\n", password[i], i);
                fflush(stderr);
            }
            return InputError;
        }
    }

    return NoError;
}