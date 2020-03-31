#include "UtilCore.h"
#include "../../data/md1database/md1database.h"
#include "../../data/md1global/md1global.h"
#include "../../util/messages.h"
#include "../../util/colors.h"

#include <stdio.h>
#include <string.h>

extern int printMessages;

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


int getMailType(const char* password)
{
    const size_t passwordLength = strlen(password);
    const char* lookupTable = "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W";
    const char firstChar  = password[passwordLength < 54 ? 1 :  7];
    const char secondChar = password[passwordLength < 54 ? 2 : 25];
    const char* firstCharPtr = strchr(lookupTable, firstChar);
    const char* secondCharPtr = strchr(lookupTable, secondChar);
    if (passwordLength != 24 && passwordLength != 54) {
        return InvalidMailType;
    }
    return (!firstCharPtr || !secondCharPtr) ? InvalidMailType : (((firstCharPtr - lookupTable) >> 3) & 0x03) | ((secondCharPtr - lookupTable) & 0x03) << 2;
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
    unsigned short i;

    /* mail type check */
    if (wm->mailType != WonderMailType) {
        ++errorsFound;
        printMessage(stderr, ErrorMessage, "The mail type must be a " LGREEN "Wonder Mail" RESET ". Current value: " LRED "%u" RESET " [" LRED "%s" LRED "]\n\n", wm->mailType,
                        wm->mailType == SosMailType ? "SOS Mail" : wm->mailType == AOkMailType ? "AOK Mail" : "INVALID");
    } 

    /* mission type check */
    if (wm->missionType < 0 || wm->missionType > 4) {
        ++errorsFound;
        printMessage(stderr, ErrorMessage, "The mission type must be a number between " LGREEN "0" RESET " [" LGREEN "%s" RESET "] and " LGREEN "%d" RESET " [" LGREEN "%s" RESET "]. Current value: " LRED "%u" RESET " [" LRED "%s" RESET "]\n\n", missionTypeObjectiveStr[0], missionTypeObjectiveCount - 1, missionTypeObjectiveStr[missionTypeObjectiveCount - 1], wm->missionType, wm->missionType == FriendRescue ? "Friend rescue" : "INVALID");
    }

    /* pkmn client check (limits) */
    switch (checkPokemon(wm->pkmnClient, WonderMailType))
    {
    case NoError:
        break;
    case PokemonOutOfRangeError:
        ++errorsFound;
        printMessage(stderr, ErrorMessage, "Pokemon must be between " LGREEN "1" RESET " [" LGREEN "%s" RESET "] and " LGREEN "%d" RESET " [" LGREEN "%s" RESET "]. Current value: " LRED "%u" RESET " [" LRED "INVALID" RESET "]\n\n", pkmnSpeciesStr[1], pkmnSpeciesCount - 1, pkmnSpeciesStr[pkmnSpeciesCount - 1], wm->pkmnClient);
        break;
    case PokemonNotAllowedError:
        ++errorsFound;
        printMessage(stderr, ErrorMessage, LIGHT "Legendaries" RESET " are not allowed in Wonder Mails. Current value: " LRED "%u" RESET " [" LRED "%s" RESET "]\n\n", wm->pkmnClient, pkmnSpeciesStr[wm->pkmnClient]);
        break;
    }

    if (wm->missionType == Find || wm->missionType == Escort) {
        switch (checkPokemon(wm->pkmnTarget, WonderMailType))
        {
        case NoError:
            break;
        case PokemonOutOfRangeError:
            ++errorsFound;
            printMessage(stderr, ErrorMessage, "Pokemon must be between " LGREEN "1" RESET " [" LGREEN "%s" RESET "] and " LGREEN "%d" RESET " [" LGREEN "%s" RESET "]. Current value: " LRED "%u" RESET " [" LRED "INVALID" RESET "]\n\n", pkmnSpeciesStr[1], pkmnSpeciesCount - 1, pkmnSpeciesStr[pkmnSpeciesCount - 1], wm->pkmnClient);
            break;
        case PokemonNotAllowedError:
            ++errorsFound;
            printMessage(stderr, ErrorMessage, LIGHT "Legendaries" RESET " are not allowed in Wonder Mails. Current value: " LRED "%u" RESET " [" LRED "%s" RESET "]\n\n", wm->pkmnClient, pkmnSpeciesStr[wm->pkmnClient]);
            break;
        }
    }

    /* item to deliver/find check (limits) */
    if (wm->missionType == FindItem || wm->missionType == DeliverItem) {
        switch (checkItem(wm->itemDeliverFind))
        {
        case NoError:
            break;
        case NoItemError:
            ++errorsFound;
            printMessage(stderr, ErrorMessage, "Item " LRED "0" RESET " [" LRED "%s" RESET "] is not allowed as item to find or deliver.\n\n", itemsStr[0]);
            break;
        case ItemCannotBeObtainedError:
            ++errorsFound;
            printMessage(stderr, ErrorMessage, "Item " LRED "%d" RESET " [" LRED "%s" RESET "] cannot be obtained as reward.\n\n", wm->itemDeliverFind, itemsStr[wm->itemDeliverFind]);
            break;
        case ItemOutOfRangeError:
            ++errorsFound;
            printMessage(stderr, ErrorMessage, "Items to find or deliver must be numbers between " LGREEN "1" RESET " [" LGREEN "%s" RESET "] and " LGREEN "%d" RESET " [" LGREEN "%s" RESET "]. Current value: %u [INVALID]\n\n", itemsStr[1], itemsCount - 5, itemsStr[itemsCount - 5], wm->itemDeliverFind);
            break;
        }

        /* item to deliver/find check (existence) */
        if (wm->missionType == FindItem) {
            if (checkItemExistenceInDungeon(wm->itemDeliverFind, wm->dungeon) != NoError) {
                ++errorsFound;
                printMessage(stderr, ErrorMessage, "The item " LRED "%u" RESET " [" LRED "%s" RESET "] can't be found in the dungeon " LIGHT "%u" RESET " [" LIGHT "%s" RESET "] To accept a job about finding an item inside a dungeon, the item must exist on that dungeon. The items that can be found in that dungeon are listed bellow:\n",
                        wm->itemDeliverFind, itemsStr[wm->itemDeliverFind], wm->dungeon, dungeonsStr[wm->dungeon]);
                if (printMessages) {
                    for (i = 1; i <= itemsInDungeons[wm->dungeon][0]; ++i) {
                        fprintf(stderr, RESET "(" LGREEN "%u" RESET ") %s\n", itemsInDungeons[wm->dungeon][i], itemsStr[itemsInDungeons[wm->dungeon][i]]);
                    }
                    fprintf(stderr, "\n\n");
                }
            }
        }
    }

    /* dungeon check */
    switch (checkDungeon(wm->dungeon, WonderMailType))
    {
    case MissionCannotBeAcceptedInDungeonError:
        /* since the mail can be generated, just ignore this error (don't increment the errors counter) */
        printMessage(stderr, WarningMessage, "A mission in dungeon " LYELLOW "%u" RESET " [" LYELLOW "%s" RESET "] can be generated, but cannot be done.\n\n", wm->dungeon, wm->dungeon < dungeonsCount ? dungeonsStr[wm->dungeon] : "INVALID");
        /* fall through */
    case NoError:
        /* floor check */
        switch (checkFloor(wm->floor, wm->dungeon))
        {
        case NoError:
            break;
        case FloorOutOfRangeError:
            ++errorsFound;
            printMessage(stderr, ErrorMessage, "The dungeon " LIGHT "%u" LIGHT " [" LIGHT "%s" LIGHT "] has floors in the range " LGREEN "1" RESET "-" LGREEN "%d" RESET " floors. Current value: " LRED "%u" RESET "\n\n", wm->dungeon, wm->dungeon < dungeonsCount ? dungeonsStr[wm->dungeon] : "INVALID", difficulties[wm->dungeon][0], wm->floor);
            break;
        case FloorInvalidInDungeonError:
            ++errorsFound;
            printMessage(stderr, ErrorMessage, "A mission cannot be made in floor " LRED "%d" RESET " of dungeon " LIGHT "%u" RESET " [" LIGHT "%s" RESET "].\n\n",
                            wm->floor, wm->dungeon, wm->dungeon < dungeonsCount ? dungeonsStr[wm->dungeon] : "INVALID");
            break;
        }
        break;
    case DungeonOutOfRangeError:
        ++errorsFound;
        printMessage(stderr, ErrorMessage, "The dungeon must be between " LGREEN "0" RESET " [" LGREEN "%s" RESET "] and " LGREEN "%d" RESET " [" LGREEN "%s" RESET "]. Current value: " LRED "%u" RESET " [" LGREEN "INVALID" RESET "]\n\n", dungeonsStr[0], dungeonsCount - 1, dungeonsStr[dungeonsCount - 1], wm->dungeon);
        break;
    case DungeonIsInvalidError:
        ++errorsFound;
        printMessage(stderr, ErrorMessage, "The dungeon " LRED "%u" RESET " [" LRED "INVALID" RESET "] is not a valid dungeon.\n\n", wm->dungeon);
        break;
    }

    /* reward type check (range) */
    if (wm->rewardType > FriendArea) {
        ++errorsFound;
        printMessage(stderr, ErrorMessage, "The reward type must be between " LGREEN "0" RESET " [" LGREEN "Money + (?)" RESET "] and " LGREEN "%d" RESET " [" LGREEN "Friend Area" RESET "]. Current value: " LRED "%u [" LRED "INVALID" RESET "]\n\n", FriendArea, wm->rewardType);
    }

    /* reward type check (enable friend area reward) */
    if (wm->rewardType == FriendArea && computeDifficulty(wm->dungeon, wm->floor, wm->missionType) == 0) { /* 0 means 'E' difficulty */
        ++errorsFound;
        printMessage(stderr, ErrorMessage, "To receive a friend area reward, the mission must have at least " COLOR(88, 248, 88) "D" RESET " difficulty.\n\n");
    }

    /* reward item check */
    if ( (wm->rewardType >= MoneyItem && wm->rewardType <= ItemItem) || (wm->rewardType >= MoneyMoneyItem && wm->rewardType <= ItemItem2) ) {
        switch (checkItem(wm->itemReward))
        {
        case NoError:
            break;
        case NoItemError:
            ++errorsFound;
            printMessage(stderr, ErrorMessage, "Item " LRED "0" RESET " [" LRED "%s" RESET "] is not allowed as reward.\n\n", itemsStr[0]);
            break;
        case ItemCannotBeObtainedError:
            ++errorsFound;
            printMessage(stderr, ErrorMessage, "Item " LRED "%d" RESET " [" LRED "%s" RESET "] cannot be obtained as reward.\n\n", wm->itemReward, itemsStr[wm->itemReward]);
            break;
        case ItemOutOfRangeError:
            ++errorsFound;
            printMessage(stderr, ErrorMessage, "Reward items must be between " LGREEN "%d" RESET " [" LGREEN "%s" RESET "] and " LGREEN "%d" RESET " [" LGREEN "%s" RESET "]. Current value: " LRED "%u" RESET " [" LRED "INVALID" RESET "]\n\n", itemsStr[1], itemsCount - 5, itemsStr[itemsCount - 5], wm->itemReward);
            break;
        }
    }

    /* friend area reward check */
    if (wm->rewardType == FriendArea) {
        switch (checkFriendArea(wm->friendAreaReward))
        {
        case NoError:
            break;
        case FriendAreaIsInvalidAsRewardError:
            ++errorsFound;
            printMessage(stderr, ErrorMessage, "The friend area " LRED "%d" RESET " [" LRED "%s" RESET "] cannot be set as reward.\n" \
                                               "Must be one of:\n" \
                                               RESET "(" LGREEN "%u" RESET ") %s\n" \
                                               RESET "(" LGREEN "%u" RESET ") %s\n" \
                                               RESET "(" LGREEN "%u" RESET ") %s\n" \
                                               RESET "(" LGREEN "%u" RESET ") %s\n", wm->friendAreaReward, wm->friendAreaReward < friendAreasCount ? friendAreasStr[wm->friendAreaReward] : "INVALID", 9, friendAreasStr[9], 10, friendAreasStr[10], 15, friendAreasStr[15], 37, friendAreasStr[37]);
            break;
        case FriendAreaOutOfRangeError:
            ++errorsFound;
            printMessage(stderr, ErrorMessage, "Friend area must be between " LGREEN "%d" RESET " [" LGREEN "%s" RESET "] and " LGREEN "%d" RESET " [" LGREEN "%s" RESET "]. Current value: " LRED "%u" RESET " [" LRED "INVALID" RESET "]\n\n", friendAreasStr[1], friendAreasCount - 1, friendAreasStr[friendAreasCount - 1], wm->friendAreaReward);
            break;
        }
    }

    fflush(stderr);
    return errorsFound;
}



int entryErrorsSosMail(const struct SosMail *sos)
{
    int errorsFound = 0;
    int minChancesLeft = sos->mailType == SosMailType ?   1 :  0;
    int maxChancesLeft = sos->mailType == SosMailType ? 100 : 99;

    /* mail type check */
    if (sos->mailType != SosMailType && sos->mailType != AOkMailType && sos->mailType != ThankYouMailType) {
        ++errorsFound;
        printMessage(stderr, ErrorMessage, "The mail type must be a " LGREEN "SOS Mail" RESET ", " LGREEN "A-OK Mail" RESET " or " LGREEN "Thank-You" RESET ". Current value: " LRED "%u" RESET " [" LRED "%s" LRED "]\n\n", sos->mailType);
    } 

    /* pkmn to rescue check (limits) */
    switch (checkPokemon(sos->pkmnToRescue, SosMailType))
    {
    case NoError:
        break;
    case PokemonOutOfRangeError:
        ++errorsFound;
        printMessage(stderr, ErrorMessage, "Pokemon must be between " LGREEN "1" RESET " [" LGREEN "%s" RESET "] and " LGREEN "%d" RESET " [" LGREEN "%s" RESET "]. Current value: " LRED "%u" RESET " [" LRED "INVALID" RESET "]\n\n", pkmnSpeciesStr[1], pkmnSpeciesCount - 1, pkmnSpeciesStr[pkmnSpeciesCount - 1], sos->pkmnToRescue);
        break;
    case PokemonNotAllowedError: /* this cannot happen in SOS Mails */
        ++errorsFound;
        printMessage(stderr, ErrorMessage, LIGHT "Legendaries" RESET " are not allowed. Current value: " LRED "%u" RESET " [" LRED "%s" RESET "]\n\n", sos->pkmnToRescue, pkmnSpeciesStr[sos->pkmnToRescue]);
        break;
    }

    /* nickname check */
    if (strlen(sos->pkmnNick) == 0) {
        ++errorsFound;
        printMessage(stderr, ErrorMessage, "The nickname cannot be empty.\n\n");
    }

    /* dungeon check */
    switch (checkDungeon(sos->dungeon, SosMailType))
    {
    case NoError:
        /* floor check */
        switch (checkFloor(sos->floor, sos->dungeon))
        {
        case NoError:
            break;
        case FloorOutOfRangeError:
            ++errorsFound;
            printMessage(stderr, ErrorMessage, "The dungeon " LIGHT "%u" LIGHT " [" LIGHT "%s" LIGHT "] has floors in the range " LGREEN "1" RESET "-" LGREEN "%d" RESET " floors. Current value: " LRED "%u" RESET "\n\n", sos->dungeon, sos->dungeon < dungeonsCount ? dungeonsStr[sos->dungeon] : "INVALID", difficulties[sos->dungeon][0], sos->floor);
            break;
        case FloorInvalidInDungeonError:
            /* floor-specific restriction do not apply in non Wonder Mail requests */
            break;
        }
        break;
    case DungeonOutOfRangeError:
        ++errorsFound;
        printMessage(stderr, ErrorMessage, "The dungeon must be between " LGREEN "0" RESET " [" LGREEN "%s" RESET "] and " LGREEN "%d" RESET " [" LGREEN "%s" RESET "]. Current value: " LRED "%u" RESET " [" LGREEN "INVALID" RESET "]\n\n", dungeonsStr[0], dungeonsCount - 1, dungeonsStr[dungeonsCount - 1], sos->dungeon);
        break;
    case DungeonIsInvalidError:
        ++errorsFound;
        printMessage(stderr, ErrorMessage, "The dungeon " LRED "%u" RESET " [" LRED "INVALID" RESET "] is not a valid dungeon.\n\n", sos->dungeon);
        break;
    case MissionCannotBeAcceptedInDungeonError: /* this cannot happen in SOS Mails */
        break;
    }
    
    if (sos->mailType == ThankYouMailType) {
        /* reward item check */
        switch (checkItem(sos->itemReward))
        {
        case NoError:
            break;
        case ItemOutOfRangeError:
            ++errorsFound;
            printMessage(stderr, ErrorMessage, "Reward items must be between " LGREEN "%d" RESET " [" LGREEN "%s" RESET "] and " LGREEN "%d" RESET " [" LGREEN "%s" RESET "]. Current value: " LRED "%u" RESET " [" LRED "INVALID" RESET "]\n\n", itemsStr[1], itemsCount - 5, itemsStr[itemsCount - 5], sos->itemReward);
            break;
        }
    }

    /* mail ID check */
    switch (checkMailID(sos->mailID))
    {
    case NoError:
        break;
    case MailIDOutOfRangeError:
        ++errorsFound;
        printMessage(stderr, ErrorMessage, "The mail ID must be beetwen " LGREEN "0" RESET " and " LGREEN "9999" RESET ". Current value: " LRED "%u\n\n", sos->mailID);
        break;
    }

    /* rescue chances left check */
    if (sos->mailType >= SosMailType && sos->mailType <= ThankYouMailType && (sos->chancesLeft < minChancesLeft || sos->chancesLeft > maxChancesLeft)) {
        ++errorsFound;
        printMessage(stderr, ErrorMessage, "The chances left for " LIGHT "%s" RESET " must be between " LGREEN "%d" RESET " and " LGREEN "%d" RESET ". Current value: " LRED "%u" RESET "\n\n", sos->mailType == SosMailType ? "SOS mails" : "AOK and Thank-You mails", minChancesLeft, maxChancesLeft, sos->chancesLeft);
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
            printMessage(stderr, ErrorMessage, "Invalid character " LRED "%c" RESET " found at index " LIGHT "%d" RESET ". Remember that [male, female, ...] -> [/, *, .]\n", password[i], i);
            return InvalidCharacterError;
        }
    }

    return NoError;
}



int checkPokemon(int pokemon, enum MailType mailType)
{
    /* pkmn check (limits) */
    if (pokemon <= 0 || (unsigned int)pokemon >= pkmnSpeciesCount) {
        return PokemonOutOfRangeError;
    } else if (mailType == WonderMailType && 
              ((pokemon >= 144 && pokemon <= 146) /* birds */ ||
               (pokemon >= 150 && pokemon <= 151) /* mewtwo and mew */ ||
               (pokemon >= 201 && pokemon <= 226) /* unown a-z */ ||
               (pokemon >= 268 && pokemon <= 270) /* dogs */ ||
               (pokemon >= 274 && pokemon <= 276) /* lugia and ho-oh */ ||
               (pokemon >= 405 && pokemon <= 423) /* regis, eons, kyogre, groudon, rayquaza, jirachi, deoxys, unown!, unown?, deoxys A, deoxys D, deoxys S, munchlax, decoy, statue and rayquaza (unused copy) */ ||
               (pokemon >= 376 && pokemon <= 379) /* castform */ ||
               (pokemon == 291 || pokemon == 293) /* cascoon and silcoon */ ||
               (pokemon ==  11 || pokemon ==  14) /* kakuna and metapod */ ||
               (pokemon ==  81 || pokemon ==  82) /* magnemite and magneton */ ||
               (pokemon ==  94 || pokemon == 307) /* gengar and gardevoir */ ||
               (pokemon == 380)) /* kecleon */ ) {
        return PokemonNotAllowedError;
    }

    return NoError;
}



int checkDungeon(int dungeon, enum MailType mailType)
{
    if (dungeon < 0 || (unsigned int)dungeon >= dungeonsCount) {
        return DungeonOutOfRangeError;
    } else if (strcmp(dungeonsStr[dungeon], "[INVALID]") == 0) {
        return DungeonIsInvalidError;
    } else if (mailType == WonderMailType && (dungeon == 6 || dungeon == 10 || dungeon == 12 || dungeon == 14 || dungeon == 16 || dungeon == 18 || dungeon == 22 || dungeon == 47 || dungeon == 48 || dungeon == 52)) {
        return MissionCannotBeAcceptedInDungeonError;
    }

    return NoError;
}



int checkFloor(int floor, int dungeon)
{
    if (floor <= 0 || floor > difficulties[dungeon][0]) {
        return FloorOutOfRangeError;
    } else if (floor == forbiddenFloorsInDungeons[dungeon][1] || floor == forbiddenFloorsInDungeons[dungeon][2]) {
        return FloorInvalidInDungeonError;
    }

    return NoError;
}



int checkItem(int item)
{
    if (item == 0) {
        return NoItemError;
    } else if (item < 0 || (unsigned int)item >= itemsCount) {
        return ItemOutOfRangeError;
    } else if ((unsigned int)item >= (itemsCount - 4)) {
        return ItemCannotBeObtainedError;
    }

    return NoError;
}



int checkItemExistenceInDungeon(int item, int dungeon)
{
    int i;
    for (i = 1; i <= itemsInDungeons[dungeon][0]; ++i) {
        if (item == itemsInDungeons[dungeon][i]) {
            return NoError;
        }
    }
    return ItemNotExistsInDungeonError;
}



int checkFriendArea(int friendArea)
{
    /* pkmn check (limits) */
    if (friendArea <= 0 || (unsigned int)friendArea >= friendAreasCount) {
        return FriendAreaOutOfRangeError;
    } else if (friendArea != 9 && friendArea != 10 && friendArea != 15 && friendArea != 37) {
        return FriendAreaIsInvalidAsRewardError;
    }

    return NoError;
}



int checkMailID(int mailID)
{
    if (mailID < 0 || mailID > 9999) {
        return MailIDOutOfRangeError;
    }

    return NoError;
}