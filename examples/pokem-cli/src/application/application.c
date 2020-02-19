#include "application.h"
#include "../view/view.h"
#include "../utils/utils.h"
#include "../utils/colors.h"

#include <stdlib.h>
#include <ctype.h>

int decodeWM(int argc, const char *argv[]) /* The passwords are received here: in argv */
{
    char psw[25] = {0};

    if (argc <= 1 || argv == NULL) {
        requestWonderMailPassword(psw);
    }

    struct WonderMailInfo mailInfo  = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0} }; /* The 8th element is a char */
    int i;
    int errorCode;
    
    if (argc > 1) {
        /* This loop will allow to decode all entered wonder mails one by one. */
        for (i = 1; i < argc; ++i) {
            errorCode = decodeWonderMail(argv[i], &mailInfo);
            if (errorCode) {
                return errorCode;
            }
            printWonderMailData(&mailInfo, NULL);   /* Finally, print the wonder mail info */
        }
    } else {
        errorCode = decodeWonderMail(psw, &mailInfo);
        if (errorCode) {
            return errorCode;
        }
        printWonderMailData(&mailInfo, NULL);   /* Finally, print the wonder mail info */
    }
    fflush(stdout);

    return NoError;
}


int encodeWM(int argc, const char *argv[])
{
    struct WonderMail wm;

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

    if (argc == 1) {
        requestSOSMailPassword(psw);
    }
    struct SosMailInfo sosInfo  = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0}, {0}, {0} }; /* The 8th element is a char */
    int i;
    int errorCode;

    if (argc > 1) {
        /* This loop will allow to decode all entered wonder mails one by one. */
        for (i = 1; i < argc; ++i) {
            errorCode = decodeSosMail(argv[i], &sosInfo);
            if (errorCode) {
                return errorCode;
            }
            printSOSData(&sosInfo, NULL);   /* Finally, print the wonder mail info */
        }
    } else {
        errorCode = decodeSosMail(psw, &sosInfo);
        if (errorCode) {
            return errorCode;
        }
        printSOSData(&sosInfo, NULL);   /* Finally, print the wonder mail info */
    }
    fflush(stdout);

    return NoError;
}


int encodeSOSM(int argc, const char *argv[])
{
    struct SosMail sos;

    if (argc != 7 || argv == NULL) {
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
    if (sos.dungeon == 10 || sos.dungeon == 12 || sos.dungeon == 14 || sos.dungeon == 16 || sos.dungeon == 18 || sos.dungeon == 22 || sos.dungeon == 47 || sos.dungeon == 48 || sos.dungeon == 52) {
        fputs(LYELLOW "WARNING:" RESET " Due to the choosen dungeon, you will not be able to accept the above mission.\n", stderr);
    }
    fflush(stdout);
    fflush(stderr);

    return NoError;
}

int parseSOSData(const char *argv[], struct SosMail *sos)
{
    sos->pkmnToRescue = (unsigned int)atoi(argv[1]);
    sos->dungeon = (unsigned int)atoi(argv[3]);
    sos->floor = (unsigned int)atoi(argv[4]);
    sos->mailID = (unsigned int)atoi(argv[5]);
    sos->chancesLeft = (unsigned int)atoi(argv[6]);
    if (strlen(argv[2])) {
        strncpy(sos->pkmnNick, argv[2], 10);
    } else {
        sos->pkmnNick[0] = '\0';
    }

    return NoError;
}

int convertSOS(int argc, const char *argv[])
{
    if (argc == 1) {
        return showHelpConverting(argv[0]);   /* No arguments specified. The value of the macro HELP is returned. */
    }

    int item = 0;
    if (argc < 3) {
        fputs("Reward item not specified. Default to nothing.\n", stderr);
    } else {
        item = atoi(argv[3]);
    }

    char AOKPassword[55];
    char ThankYouPassword[55];
    convertSosMail(argv[1], item, AOKPassword, ThankYouPassword);

    struct SosMailInfo AOKInfo  = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0}, {0}, {0} };
    struct SosMailInfo ThxInfo  = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0}, {0}, {0} };
    decodeSosMail(AOKPassword, &AOKInfo);
    decodeSosMail(ThankYouPassword, &ThxInfo);
    fprintf(stdout, "============== A-OK Mail ==============");
    printSOSData(&AOKInfo, NULL);
    fprintf(stdout, "============ Thank-You Mail ===========");
    printSOSData(&ThxInfo, NULL);
    fflush(stdout);
    return NoError;
}