#include "application.h"
#include "../view/view.h"
#include "../utils/utils.h"
#include "../utils/colors.h"

#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

int decodeWM(int argc, const char *argv[]) /* The passwords are received here: in argv */
{
    char psw[25] = {0};

    if (argc <= 1 || argv == NULL) {
        requestWonderMailPassword(psw);
    }

    struct WonderMail mail = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    struct WonderMailInfo mailInfo  = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0} }; /* The 8th element is a char */
    int i;
    int errorCode;
    
    for (i = 1; i < argc || i == 1; ++i) {
        if (argc > 1) {
            fprintf(stdout, LIGHT "%d.\n" RESET, i);
            strncpy(psw, argv[i], 24);
        }
        errorCode = decodeWonderMail(psw, &mail);
        if (errorCode) {
            continue;
        }

        /* Bulking the mail's data... */
        setWonderMailInfo(&mail, &mailInfo);
        strncpy(mailInfo.password, psw, 24);
        printWonderMailData(&mailInfo, &mail);
        fputc('\n', stdout);
    }
    fflush(stdout);

    return NoError;
}


int encodeWM(int argc, const char *argv[])
{
    struct WonderMail wm;
    wm.mailType = WonderMailType;

    if (argc != 10 || argv == NULL) {
        requestAndParseWonderMailData(&wm);
    } else if (parseWMData(argv, &wm) != NoError) {
        fputs("Aborting...\n", stderr);
        return InputError;
    }

    char finalPassword[25] = {0};
    int errorCode = encodeWonderMail(&wm, finalPassword, 1); /* "1": Try special missions */
    if (errorCode != NoError) {
        return errorCode;
    }

    /* Get the full Wonder Mail info */
    struct WonderMailInfo wmInfo = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0} };
    setWonderMailInfo(&wm, &wmInfo);
    strncpy(wmInfo.password, finalPassword, 24);
    printWonderMailData(&wmInfo, &wm);
    if (wm.dungeon == 10 || wm.dungeon == 12 || wm.dungeon == 14 || wm.dungeon == 16 || wm.dungeon == 18 || wm.dungeon == 22 || wm.dungeon == 47 || wm.dungeon == 48 || wm.dungeon == 52) {
        fputs(LYELLOW "WARNING:" RESET " Due to the choosen dungeon, you will not be able to accept the above mission.\n\n", stderr);
    }
    fflush(stdout);
    fflush(stderr);

    return NoError;
}



int parseWMData(const char *argv[], struct WonderMail *wm)
{
    unsigned int i;
    int mostSimilarIndex = 0;

    wm->mailType         = 5; /* Wonder Mail */
    wm->missionType      = (unsigned int)atoi(argv[1]);

    /* user can input the pkmns, items, dungeons and friend zones by using its name or its index */
    
    if (isdigit(argv[2][0])) {
        wm->pkmnClient   = (unsigned int)atoi(argv[2]);
    } else {
        wm->pkmnClient   = pkmnSpeciesCount; /* invalid name, invalid index */
        for (i = 0; i < pkmnSpeciesCount; ++i) {
            if (strcmp(pkmnSpeciesStr[i], argv[2]) == 0) {
                wm->pkmnClient = i;
                break;
            }
        }
        if (wm->pkmnClient == pkmnSpeciesCount) {
            fprintf(stderr, "ERROR: Cannot find client pokemon \"%s\" in the database.\n", argv[2]);
            mostSimilarIndex = findMostSimilarStringInArray(argv[2], pkmnSpeciesStr, pkmnSpeciesCount);
            if (mostSimilarIndex == -1) {
                fputs("Re-check your spelling.\n", stderr);
            } else {
                fprintf(stderr, "Do you mean \"%s\"?\n", pkmnSpeciesStr[mostSimilarIndex]);
            }
            return InputError;
        }
    }

    if (wm->missionType == Find || wm->missionType == Escort) {
        if (isdigit(argv[3][0])) {
            wm->pkmnTarget   = (unsigned int)atoi(argv[3]);
        } else {
            wm->pkmnTarget   = pkmnSpeciesCount; /* invalid name, invalid index */
            for (i = 0; i < pkmnSpeciesCount; ++i) {
                if (strcmp(pkmnSpeciesStr[i], argv[3]) == 0) {
                    wm->pkmnTarget = i;
                    break;
                }
            }
        }
        if (wm->pkmnTarget == pkmnSpeciesCount) {
            fprintf(stderr, "ERROR: Cannot find target pokemon \"%s\" in the database.\n", argv[3]);
            mostSimilarIndex = findMostSimilarStringInArray(argv[3], pkmnSpeciesStr, pkmnSpeciesCount);
            if (mostSimilarIndex == -1) {
                fputs("Re-check your spelling.\n", stderr);
            } else {
                fprintf(stderr, "Do you mean \"%s\"?\n", pkmnSpeciesStr[mostSimilarIndex]);
            }
            return InputError;
        }
    } else {
        wm->pkmnTarget   = wm->pkmnClient;
    }

    if (wm->missionType == FindItem || wm->missionType == DeliverItem) {
        if (isdigit(argv[4][0])) {
            wm->itemDeliverFind   = (unsigned int)atoi(argv[4]);
        } else {
            wm->itemDeliverFind   = itemsCount; /* invalid name, invalid index */
            for (i = 0; i < itemsCount; ++i) {
                if (strcmp(itemsStr[i], argv[4]) == 0) {
                    wm->itemDeliverFind = i;
                    break;
                }
            }
            if (wm->itemDeliverFind == itemsCount) {
                fprintf(stderr, "ERROR: Cannot find item to %s \"%s\" in the database.\n", wm->missionType == FindItem ? "find" : "deliver", argv[4]);
                mostSimilarIndex = findMostSimilarStringInArray(argv[4], itemsStr, itemsCount);
                if (mostSimilarIndex == -1) {
                    fputs("Re-check your spelling.\n", stderr);
                } else {
                    fprintf(stderr, "Do you mean \"%s\"?\n", itemsStr[mostSimilarIndex]);
                }
                return InputError;
            }
        }
    } else {
        wm->itemDeliverFind = 9;
    }

    if (isdigit(argv[5][0])) {
        wm->dungeon   = (unsigned int)atoi(argv[5]);
    } else {
        wm->dungeon   = dungeonsCount; /* invalid name, invalid index */
        for (i = 0; i < dungeonsCount; ++i) {
            if (strcmp(dungeonsStr[i], argv[5]) == 0) {
                wm->dungeon = i;
                break;
            }
        }
        if (wm->dungeon == dungeonsCount) {
            fprintf(stderr, "ERROR: Cannot find dungeon \"%s\" in the database.\n", argv[5]);
            mostSimilarIndex = findMostSimilarStringInArray(argv[5], dungeonsStr, dungeonsCount);
            if (mostSimilarIndex == -1) {
                fputs("Re-check your spelling.\n", stderr);
            } else {
                fprintf(stderr, "Do you mean \"%s\"?\n", dungeonsStr[mostSimilarIndex]);
            }
            return InputError;
        }
    }

    wm->floor            = (unsigned int)atoi(argv[6]);
    wm->rewardType       = (unsigned int)atoi(argv[7]);

    if (isdigit(argv[8][0])) {
        wm->itemReward   = (unsigned int)atoi(argv[8]);
    } else {
        wm->itemReward   = itemsCount; /* invalid name, invalid index */
        for (i = 0; i < itemsCount; ++i) {
            if (strcmp(itemsStr[i], argv[8]) == 0) {
                wm->itemReward = i;
                break;
            }
        }
        if (wm->itemReward == itemsCount) {
            fprintf(stderr, "ERROR: Cannot find reward item \"%s\" in the database.\n", argv[8]);
            mostSimilarIndex = findMostSimilarStringInArray(argv[8], itemsStr, itemsCount);
            if (mostSimilarIndex == -1) {
                fputs("Re-check your spelling.\n", stderr);
            } else {
                fprintf(stderr, "Do you mean \"%s\"?\n", itemsStr[mostSimilarIndex]);
            }
            return InputError;
        }
    }

    if (wm->rewardType == 9) {
        if (isdigit(argv[9][0])) {
            wm->friendAreaReward   = (unsigned int)atoi(argv[9]);
        } else {
            wm->friendAreaReward   = friendAreasCount; /* invalid name, invalid index */
            for (i = 0; i < friendAreasCount; ++i) {
                if (strcmp(friendAreasStr[i], argv[9]) == 0) {
                    wm->friendAreaReward = i;
                    break;
                }
            }
            if (wm->friendAreaReward == friendAreasCount) {
                fprintf(stderr, "ERROR: Cannot find friend area \"%s\" in the database.\n", argv[9]);
                mostSimilarIndex = findMostSimilarStringInArray(argv[9], friendAreasStr, friendAreasCount);
                if (mostSimilarIndex == -1) {
                    fputs("Re-check your spelling.\n", stderr);
                } else {
                    fprintf(stderr, "Do you mean \"%s\"?\n", friendAreasStr[mostSimilarIndex]);
                }
                    return InputError;
                }
        }
    } else {
        wm->friendAreaReward = 0;
    }

    return NoError;
}



int decodeSOSM(int argc, const char *argv[])
{
    char psw[55] = {0};

    if (argc <= 1) {
        requestSOSMailPassword(psw);
    }

    struct SosMail mail = { 0, 0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0 };
    struct SosMailInfo mailInfo  = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0}, {0}, {0} }; /* The 8th element is a char */
    int i;
    int errorCode;

    for (i = 1; i < argc || i == 1; ++i) {
        if (argc > 1) {
            fprintf(stdout, LIGHT "%d.\n" RESET, i);
            strncpy(psw, argv[i], 54);
        }
        errorCode = decodeSosMail(psw, &mail);
        if (errorCode != NoError) {
            continue;
        }

        /* Bulking the mail's data... */
        setSosInfo(&mail, &mailInfo);
        strncpy(mailInfo.password, psw, 54);
        printSOSData(&mailInfo, &mail);
        fputc('\n', stdout);
    }
    fflush(stdout);

    return NoError;
}


int encodeSOSM(int argc, const char *argv[])
{
    struct SosMail sos;

    if (argc != 8 || argv == NULL) {
        requestAndParseSosMailData(&sos);
    } else if (parseSOSData(argv, &sos) != NoError) {
        fputs("Aborting...\n", stderr);
        return InputError;
    }

    char finalPassword[55] = {0};
    int errorCode = encodeSosMail(&sos, finalPassword);
    if (errorCode) {
        return errorCode;
    }

    /* Get the full SOS Mail info */
    struct SosMailInfo sosInfo  = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0}, {0}, {0} };
    setSosInfo(&sos, &sosInfo);
    strncpy(sosInfo.password, finalPassword, 54);
    printSOSData(&sosInfo, &sos);
    fflush(stdout);
    fflush(stderr);

    return NoError;
}

int parseSOSData(const char *argv[], struct SosMail *sos)
{
    int hold = (unsigned int)atoi(argv[1]);
    sos->mailType = hold == 0 ? SosMailType : (hold == 1) ? AOkMailType : (hold == 2) ? ThankYouMailType : InvalidMailType;
    sos->pkmnToRescue = (unsigned int)atoi(argv[2]);
    sos->dungeon = (unsigned int)atoi(argv[4]);
    sos->floor = (unsigned int)atoi(argv[5]);
    sos->mailID = (unsigned int)atoi(argv[6]);
    sos->chancesLeft = (unsigned int)atoi(argv[7]);
    if (strlen(argv[3])) {
        strncpy(sos->pkmnNick, argv[3], 10);
    } else {
        sos->pkmnNick[0] = '\0';
    }

    return NoError;
}

int convertSOS(int argc, const char *argv[])
{
    char SOSPassword[55];
    char AOKPassword[55];
    char ThankYouPassword[55];
    int itemReward;
    char *stringEnd; /* strtol() */

    struct SosMail SOSMail = { 0, 0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0 };
    struct SosMail AOKMail = { 0, 0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0 };
    struct SosMail ThxMail = { 0, 0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0 };
    struct SosMailInfo SOSInfo = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0}, {0}, {0} };
    struct SosMailInfo AOKInfo = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0}, {0}, {0} };
    struct SosMailInfo ThxInfo = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0}, {0}, {0} };

    int i, j, count;
    int mostSimilarIndex = 0;
    int errorCode;
    int mailType = SosMailType; /* default type */

    if (argc <= 1) {
        requestAndParseSOSMailConvertion(SOSPassword, &itemReward);
        mailType = getMailType(SOSPassword);
        if (mailType == AOkMailType) {
            strncpy(AOKPassword, SOSPassword, 54);
        } else if (mailType == ThankYouMailType) {
            strncpy(ThankYouPassword, SOSPassword, 54);
        }
    }

    for (i = 1, count = 1; i < argc || i == 1; i += 2, ++count) {
        if (argc > 1) {
            fprintf(stdout, LIGHT "%d.\n" RESET, count);
            mailType = getMailType(argv[i]);
            strncpy(SOSPassword, argv[i], 54);
            if (mailType == AOkMailType) {
                strncpy(AOKPassword, argv[i], 54);
            } else if (mailType == ThankYouMailType) {
                strncpy(ThankYouPassword, argv[i], 54);
            } else if (mailType == InvalidMailType) {
                continue;
            }
        }

        if (argc > 1 && i + 1 >= argc) {
            itemReward = 0;
            fprintf(stdout, LIGHT "Reward item not specified. Default to " LGREEN "\"%s\"" RESET LIGHT ".\n", itemsStr[itemReward]);
        } else if (argc > 1) {
            itemReward = strtol(argv[i + 1], &stringEnd, 10);
            if (*stringEnd) { /* non-digit found */
                itemReward = itemsCount; /* invalid name, invalid index */
                for (j = 0; j < (int)itemsCount; ++j) {
                    if (strcmp(itemsStr[j], argv[i + 1]) == 0) {
                        itemReward = j;
                        break; /* item found */
                    }
                }

                if ((unsigned int)itemReward == itemsCount) {
                    fprintf(stderr, LRED "ERROR:" RESET LIGHT " Cannot find item " LGREEN "\"%s\"" RESET LIGHT " in the database.\n" RESET, argv[i + 1]);
                    mostSimilarIndex = findMostSimilarStringInArray(argv[i + 1], itemsStr, itemsCount);
                    itemReward = mostSimilarIndex == -1 ? 0 : mostSimilarIndex;
                    fprintf(stderr, LGREEN "\"%s\"" RESET LIGHT " has been assumed.\n" RESET, itemsStr[itemReward]);
                }
            } else if (itemReward != 0 && checkItemRange(itemReward, 1) != NoError) {
                continue;
            }
        }

        errorCode = convertSosMail(SOSPassword, itemReward, AOKPassword, ThankYouPassword);
        if (errorCode) {
            fprintf(stderr, RESET "Convertion error %d\n", errorCode);
            continue;
        }

        /* Bulking the mail's data... */
        if (mailType != SosMailType) {
            SOSPassword[0] = '\0';
        }
        if (strlen(SOSPassword) == 54) {
            fputs(RESET "=================== SOS Mail =====================\n", stdout);
            if (decodeSosMail(SOSPassword, &SOSMail) != NoError) {
                fprintf(stderr, "Cannot show SOS Mail. Errors ocurr.\n");
                continue;
            }
            setSosInfo(&SOSMail, &SOSInfo);
            strncpy(SOSInfo.password, SOSPassword, 54);
            printSOSData(&SOSInfo, &SOSMail);
            fputc('\n', stdout);
        }
        if (strlen(AOKPassword) == 54) {
            if (decodeSosMail(AOKPassword, &AOKMail) != NoError) {
                continue;
            }
            fputs(RESET "=================== A-OK Mail ====================\n", stdout);
            setSosInfo(&AOKMail, &AOKInfo);
            strncpy(AOKInfo.password, AOKPassword, 54);
            printSOSData(&AOKInfo, &AOKMail);
            fputc('\n', stdout);
        }
        if (strlen(ThankYouPassword) == 54) {
            if (decodeSosMail(ThankYouPassword, &ThxMail) != NoError) {
                continue;
            }
            fputs(RESET "================= Thank-You Mail =================\n", stdout);
            setSosInfo(&ThxMail, &ThxInfo);
            strncpy(ThxInfo.password, ThankYouPassword, 54);
            printSOSData(&ThxInfo, &ThxMail);
        }
        fflush(stdout);
    } /* for loop */
    fflush(stdout);

    return NoError;
}

int generateMassiveItemMissions(int dungeon, int item, int amount)
{
    int errorCode = checkDungeonInWonderMail(dungeon, 1);
    if (errorCode != NoError) {
        return NoError;
    } else if (amount > (difficulties[dungeon][0] - forbiddenFloorsInDungeons[dungeon][0])) {
        fprintf(stderr, LYELLOW "WARNING:" RESET LIGHT " No enough floors. Truncated to %d.\n", difficulties[dungeon][0] - forbiddenFloorsInDungeons[dungeon][0]);
        amount = difficulties[dungeon][0] - forbiddenFloorsInDungeons[dungeon][0];
    }

    struct WonderMail wm = { WonderMailType, HelpMe, 0, 0, 0, 0, MoneyMoneyItem, item, 0, 0, 0, 0xFF, dungeon, 0 };
    struct WonderMailInfo wmInfo = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0} };
    char password[25] = {0};
    int i;
    for (i = 0; i < amount; ++i) {
        wm.floor = i + 1;
        while (checkFloorForDungeon(wm.floor, wm.dungeon, 0) != NoError) {
            wm.floor++;
        }
        while (checkPkmnInWonderMail(wm.pkmnClient, 0)) {
            wm.pkmnClient = rand() % pkmnSpeciesCount;
        }
        wm.pkmnTarget = wm.pkmnClient;
        encodeWonderMail(&wm, password, 1);
        setWonderMailInfo(&wm, &wmInfo);
        strncpy(wmInfo.password, password, 24);
        printWonderMailData(&wmInfo, &wm);
        if (i < amount - 1) {
            fputc('\n', stdout);
        }
    }
    return NoError;
}

int generateMassiveHighRankMissions(int dungeon, int item, int amount)
{
    int errorCode = checkDungeonInWonderMail(dungeon, 1);
    if (errorCode != NoError) {
        return NoError;
    } else if (amount > (difficulties[dungeon][0] - forbiddenFloorsInDungeons[dungeon][0])) {
        fprintf(stderr, LYELLOW "WARNING:" RESET LIGHT " No enough floors. Truncated to %d.\n", difficulties[dungeon][0] - forbiddenFloorsInDungeons[dungeon][0]);
        amount = difficulties[dungeon][0] - forbiddenFloorsInDungeons[dungeon][0];
    }

    struct WonderMail wm = { WonderMailType, HelpMe, 0, 0, 0, 0, MoneyMoneyItem, item, 0, 0, 0, 0xFF, dungeon, 0 };
    struct WonderMailInfo wmInfo = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0} };
    char password[25] = {0};

    char calculatedDiffChar = 'E';
    char diffColor[50] = {0};
    int targetRank = 12;
    int i;
    /* locate the first appareance of a high rank floor */
    for (i = 1; i <= difficulties[dungeon][0]; ++i) {
        if (difficulties[dungeon][i] >= targetRank) {
            break;
        } else if (i == difficulties[dungeon][0] && targetRank > 1) {
            calculatedDiffChar = difficultiesChars[(targetRank >> 1) > 6 ? 6 : (targetRank >> 1)];
            strcpy(diffColor, calculatedDiffChar == 'E' ? RESET : calculatedDiffChar == 'D' || calculatedDiffChar == 'C' ? COLOR_GREEN : calculatedDiffChar == 'B' || calculatedDiffChar == 'A' ? COLOR_CYAN : calculatedDiffChar == 'S' ? COLOR_RED : LYELLOW);
            fprintf(stderr, LYELLOW "WARNING:" RESET LIGHT " The dungeon " LGREEN "%u" RESET LIGHT " [" LGREEN "%s" RESET LIGHT "] cannot provide %s%c" RESET LIGHT " rank missions.\n", dungeon, ((unsigned int)dungeon >= dungeonsCount) ? "INVALID" : dungeonsStr[dungeon], diffColor, calculatedDiffChar);
            while (calculatedDiffChar == difficultiesChars[(targetRank >> 1) > 6 ? 6 : (targetRank >> 1)]) {
                targetRank--; /* try again with a lower rank */
            }
            i = 0; /* it is increased to 1 for the next iterations */
        }
    }
    /* if `i` is too close to the end of the dungeon, assign an appropriate value to `i` */
    if ((i + amount + forbiddenFloorsInDungeons[dungeon][0] - 1) > (difficulties[dungeon][0])) {
        i = difficulties[dungeon][0] - forbiddenFloorsInDungeons[dungeon][0] - amount + 1;
    }
    /* now generate the mails */
    int top = i + amount;
    for (; i < top; ++i) {
        wm.floor = i;
        while (checkFloorForDungeon(wm.floor, wm.dungeon, 0) != NoError) {
            wm.floor++;
        }
        while (checkPkmnInWonderMail(wm.pkmnClient, 0)) {
            wm.pkmnClient = rand() % pkmnSpeciesCount;
        }
        wm.pkmnTarget = wm.pkmnClient;
        encodeWonderMail(&wm, password, 1);
        setWonderMailInfo(&wm, &wmInfo);
        strncpy(wmInfo.password, password, 24);
        printWonderMailData(&wmInfo, &wm);
        if (i < top - 1) {
            fputc('\n', stdout);
        }
    }
    return NoError;
}

int unlockExclusivePokemon(enum GameType gameType)
{
    if (gameType != RedRescueTeam && gameType != BlueRescueTeam) {
        fprintf(stderr, LRED "ERROR:" RESET LIGHT " Unrecognized game type.\n");
        return InputError;
    }
    int pokemonRedRescueTeam[]  = { 137, 251, 336, 340, 374 }; /* Porygon, Mantine, Plusle, Roselia and Feebas */
    int pokemonBlueRescueTeam[] = { 129, 131, 190, 337 }; /* Magikarp, Lapras, Aipom and Minum */

    struct WonderMail wm = { WonderMailType, HelpMe, 0, 0, 0, 0, MoneyMoney, 0x09, 0, 0, 0, 0xFF, 0, 1 };
    struct WonderMailInfo wmInfo = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0} };
    char password[25] = {0};

    int i;
    int top = gameType == RedRescueTeam ? 5 : 4;
    for (i = 0; i < top; ++i) {
        wm.pkmnClient = gameType == RedRescueTeam ? pokemonRedRescueTeam[i] : pokemonBlueRescueTeam[i];
        wm.pkmnTarget = wm.pkmnClient;
        encodeWonderMail(&wm, password, 1);
        setWonderMailInfo(&wm, &wmInfo);
        strncpy(wmInfo.password, password, 24);
        printWonderMailData(&wmInfo, &wm);
        if (i < top - 1) {
            fputc('\n', stdout);
        }
    }
    return NoError;
}

int unlockDungeons()
{
    int dungeonsToUnlock[] = { 44, 45, 46 }; /* Remains Island, Marvelous Sea and Fantasy Strait */
    struct WonderMail wm = { WonderMailType, HelpMe, 0, 0, 0, 0, MoneyMoney, 0x09, 0, 0, 0, 0xFF, 0, 1 };
    struct WonderMailInfo wmInfo = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0} };
    char password[25] = {0};

    int i;
    for (i = 0; i < 3; ++i) {
        wm.dungeon = dungeonsToUnlock[i];
        while (checkPkmnInWonderMail(wm.pkmnClient, 0)) {
            wm.pkmnClient = rand() % pkmnSpeciesCount;
        }
        wm.pkmnTarget = wm.pkmnClient;
        encodeWonderMail(&wm, password, 1);
        setWonderMailInfo(&wm, &wmInfo);
        strncpy(wmInfo.password, password, 24);
        printWonderMailData(&wmInfo, &wm);
        if (i < 2) {
            fputc('\n', stdout);
        }
    }
    return NoError;
}