#include "view.h"
#include "../utils/colors.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define forever for(;;)
#define DISCLAIMER \
    "This program comes with ABSOLUTELY NO WARRANTY.\n" \
    "This is free software, and you are welcome to modify and/or redistribute it under\n" \
    "the terms of the GNU GENERAL PUBLIC LICENSE v2. Please visit http://www.gnu.org/licenses/\n\n"

int showSelectionScreen()
{
    fputs(LIGHT "What do you want to do?\n"
          LGREEN  "1." RESET " Decode a Wonder Mail\n"
          LGREEN  "2." RESET " Encode a Wonder Mail\n"
          LGREEN  "3." RESET " Decode a SOS Mail\n"
          LGREEN  "4." RESET " Encode a SOS Mail\n"
          LGREEN  "5." RESET " Convert a SOS Mail -> A-OK Mail -> Thank-You Mail\n"
          LGREEN  "[Other]:" LRED " Exit\n"
          RESET ">>> " LGREEN, stdout);
    return getchar() - '0';
}


int showGeneralHelp(const char *programName)
{
    fputs(DISCLAIMER, stdout);

    fprintf(stdout, "Usage: %s [ARGUMENTS]...\n"
                    "[ARGUMENTS]:\n"
                    "This program will try to autodetect what do you want to do based\n"
                    "on your input. If you enter a Wonder Mail, this program will try\n"
                    "to decode it. If you enter exactly 9 or 6 arguments, this program\n"
                    "will try to encode a Wonder Mail or a SOS Mail respectively.\n"
                    "If your input is incorrect, a menu will appear to bring you help\n"
                    "about a specific topic.\n\n"
                    "Developed by Carlos Enrique Perez Sanchez.\n", programName);
    fflush(stdout);
    return NoError;
}


int showHelpDecodingWonderMail(const char* programName) /* argv[0] is the program path/name */
{
    fputs(DISCLAIMER, stdout);

    fprintf(stdout, "========= HELP DECODING WONDER MAIL =========\n"
                    "Usage: %s [PASSWORD_1] [PASSWORD_2]...\n"
                    "Enter the password in UPPERCASE.\n"
                    "Symbols conventions:\n"
                    "\t> \'FEMALE\' are \'*\'\n"
                    "\t> \'MALE\' are \'/\'\n"
                    "\t> \'...\' are \'.\'\n\n"
                    "Examples of valid entries:\n"
                    "\t%s 16J.8!0?1PS35-?06N?RP8?W\n"
                    "\t%s ??J9XJX?2P??8??F6H?0P??W\n"
                    "NOTE: On UNIX, you must quote (using simple quotes) the passwords.\n"
                    "      The first one will decode three Wonder Mails, and the second will decode just one.\n\n"
                    "Developed by Carlos Enrique Perez Sanchez.\n", programName, programName, programName);
    fflush(stdout);
    return NoError;
}


int showHelpEncodingWonderMail(const char* programName)
{
    fputs(DISCLAIMER, stdout);

    fprintf(stdout, "========= HELP ENCODING WONDER MAIL =========\n"
                    "Usage: %s [Mission type] [Pkmn client] [Pkmn target] [Item to find/deliver] [Dungeon] [Floor] [Reward type] [Item reward] [Friend area reward]\n"
                    "You must enter exactly 9 arguments.\n"
                    "You can use both numeric or text values for pokemon, items, dungeons and friend areas.\n"
                    "For the remaining fields, only numeric values are accepted.\n"
                    "Example of valid entries:\n"
                    "%s 0 375 1 0 46 2 6 54 0\n"
                    "NOTE: It's a Help-type mission from Milotic, the target pkmn and the item\n"
                    "      to find/deliver are ignored. The rescue is in Fantasy Strait at 2nd floor.\n"
                    "      The reward is a lot of money and a Wish Stone, and the Friend Area Reward is ignored.\n\n"
                    "Developed by Carlos Enrique Perez Sanchez.\n\n", programName, programName);
    showDatabase();

    fflush(stdout);
    return NoError;
}


int showHelpDecodingSos(const char* programName)
{
    fputs(DISCLAIMER, stdout);

    fprintf(stdout, "========== HELP DECODING SOS MAIL ==========\n"
                    "Usage: %s [PASSWORD_1] [PASSWORD_2]...\n"
                    "Enter the password in UPPERCASE.\n"
                    "Symbols conventions:\n"
                    "\t> 'FEMALE' are '*'\n"
                    "\t> 'MALE' are '/'\n"
                    "\t> '...' are '.'\n\n"
                    "Examples of valid entries:\n"
                    "\t%s ?M???.R066???2FC?!?R????3HCP?-??32H???Y?M4C??1J??NQ04? S6???.RF?6F??NWH*5KC???RH1!9?8?JK7P0??SNMJRPSKJ??7QJ4N\n"
                    "\t%s S2???.RYW6F\?\?!P5*5KW???RH3J-?3?JX7P0??SNM42PSKJ\?\?!QJ4N\n" /* Seek others passwords that not contains trigraphs */
            "NOTE: On UNIX, you must quote (using simple quotes) the passwords.\n"
            "      The first one will decode two SOS Mails, and the second will decode just one.\n\n"
            "Developed by Carlos Enrique Perez Sanchez.\n\n", programName, programName, programName);

    fflush(stdout);
    return NoError;
}


int showHelpEncodingSos(const char *programName)
{
    fputs(DISCLAIMER, stdout);

    fprintf(stdout, "========== HELP ENCODING SOS MAIL ==========\n"
                    "Usage: %s [Pkmn client] [Pkmn nickname] [Dungeon] [Floor] [Mail ID (default: 0)] [Rescue chances (default: 10)]\n"
                    "Enter only the numerical values.\nYou must enter exactly 6 arguments.\n\n"
                    "Example of valid entry:\n%s 113 Nurcy 58 50 1234 10\n"
                    "NOTE: Rescue a Chansey named \'Nurcy\' at 'Joyous Tower' floor 50.\n"
                    "      The Mail ID is 1234 and you can try 10 times.\n\n"
                    "Developed by Carlos Enrique Perez Sanchez.\n\n", programName, programName);
    showDatabase();

    return NoError;
}


int showHelpConverting(const char *programName)
{
    fputs(DISCLAIMER, stdout);

    fprintf(stdout, "========= HELP CONVERTING SOS MAIL =========\n"
                    "Usage: %s [PASSWORD_1] [PASSWORD_2]...\n"
                    "Enter the password in UPPERCASE.\n"
                    "Symbols conventions:\n"
                    "\t> 'FEMALE' are '*'\n"
                    "\t> 'MALE' are '/'\n"
                    "\t> '...' are '.'\n\n"
                    "Examples of valid entries:\n"
                    "\t%s ?M???.R066???2FC?!?R????3HCP?-??32H???Y?M4C??1J??NQ04? S6???.RF?6F??NWH*5KC???RH1!9?8?JK7P0??SNMJRPSKJ??7QJ4N\n"
                    "\t%s S2???.RYW6F\?\?!P5*5KW???RH3J-?3?JX7P0??SNM42PSKJ\?\?!QJ4N\n" /* Seek others passwords that not contains trigraphs */
            "NOTE: On UNIX, you must quote (using simple quotes) the passwords.\n"
            "      The first one will convert two SOS Mails, and the second will convert just one.\n"
            "      You will get a A-OK Mail that allows you to be rescued.\n"
            "      You will get also a Thank-You Mail, use it if you want.\n\n"
            "Developed by Carlos Enrique Perez Sanchez.\n\n", programName, programName, programName);

    fflush(stdout);
    return NoError;
}


void showDatabase()
{
    unsigned int i;
    forever { /* infinite loop */
        fputs("Enter one of the following values to see the desired database:\n"
              "1) Pkmn database\n"
              "2) Dungeons database\n"
              "3) Mission type\n"
              "4) Reward type\n"
              "5) Friend area reward\n"
              "OTHER KEY: [Exit]\n"
              "Your choice?: ", stdout);
        fflush(stdout);
        fflush(stdin);
        int choice;
        if (scanf("%d", &choice) <= 0) {
            choice = 0; /* exit */
        }
        if (choice < 1 || choice > 5) {
            fputs("Exiting...\n", stdout);
            return;
        } else {
            switch (choice) {
            case 1:
                fprintf(stdout, " :: Pkmn database: ---\n");
                for (i = 0; i < 405; ++i) {
                    fprintf(stdout, "    %d - %s\n", i, pkmnSpeciesStr[i]);
                }
                break;
            case 2:
                fprintf(stdout, " :: Dungeons database: ---\n");
                for (i = 0; i < 63; ++i) {
                    fprintf(stdout, "    %d - %s\n", i, dungeonsStr[i]);
                }
                break;
            case 3:
                fprintf(stdout, " :: Mission type: ---\n");
                for (i = 0; i < 6; ++i) {
                    fprintf(stdout, "    %d - %s\n", i, missionTypeObjectiveStr[i]);
                }
                break;
            case 4:
                fprintf(stdout, " :: Reward type: ---\n");
                fputs("    0 - Money\n"
                      "    1 - Money + ?\n"
                      "    2 - Item\n"
                      "    3 - Item + ?\n"
                      "    4 - Money\n"
                      "    5 - Money + ?\n"
                      "    6 - Item\n"
                      "    7 - Item + ?\n"
                      "    8 - Friend area\n", stdout);
                break;
            case 5:
                fprintf(stdout, " :: Friend area reward: ---\n"); /* update the range if you uncomment the full database */
                for (i = 0; i < 4; ++i) {
                    fprintf(stdout, "    %d - %s\n", i, friendAreasStr[i]);
                }
                break;
            default:
                fprintf(stderr, " :: Invalid key\n");   /* this should never happen */
                break;
            }
            putchar('\n');
        }
    }
}



int requestWonderMailPassword(char *password)
{
    fputs(LIGHT "Enter the Wonder Mail's password\n" RESET, stdout);
    fputs(RESET ">>> " LGREEN, stdout);
    fflush(stdout);
    (void)!fgets(password, 24, stdin);
    fputs(RESET, stdout);
    fflush(stdout);
    if (password[strlen(password) - 1] == '\n') {
        password[strlen(password) - 1] = '\0';
    }

    return NoError;
}



int requestAndParseWonderMailData(struct WonderMail *wm)
{
    unsigned int i = 0;
    unsigned int selection = -1;
    char stringInput[101];
    int mostSimilarIndex = 0;

    /* mission type */
    forever {
        fputs(LIGHT "Select the mission type.\n" RESET, stdout);
        for (i = 0; i < 6; ++i) {
            fprintf(stdout, LGREEN "%u" RESET " - ", i + 1);
            fprintf(stdout, missionTypeObjectiveStr[i], i == FindItem || i == DeliverItem ? "item" : "pokemon");
            fputc('\n', stdout);
        }
        fputs(RESET ">>> " LGREEN, stdout);
        fflush(stdout);
        selection = getchar() - '0' - 1;
        clearStdinBuffer();
        if (selection < 6) { /* `selection` is unsigned so it's always >= 0 */
            break; /* input is ok */
        }
        fprintf(stderr, LRED "INPUT ERROR\n" RESET);
    }
    wm->missionType = selection;

    /* pokemon client */
    forever {
        fputs(LIGHT "Enter the name (case sensitive) or room index of the client pokemon (leave it blank for random).\n" RESET, stdout);
        fputs(RESET ">>> " LGREEN, stdout);
        fflush(stdout);
        (void)!fgets(stringInput, 100, stdin);
        if (stringInput[strlen(stringInput) - 1] == '\n') {
            stringInput[strlen(stringInput) - 1] = '\0';
        }
        if (strlen(stringInput) == 0) {
            do {
                sprintf(stringInput, "%u", rand() % pkmnSpeciesCount);
            } while (checkPkmnInWonderMail(atoi(stringInput), 0) != NoError);
            selection = (unsigned int)atoi(stringInput);
        } else {
            for (i = 0; i < strlen(stringInput); ++i) {
                if (!isdigit(stringInput[i])) {
                    break;
                }
            }
            if (i != strlen(stringInput)) { /* non-digit found */
                selection = pkmnSpeciesCount; /* invalid name, invalid index */
                for (i = 0; i < pkmnSpeciesCount; ++i) {
                    if (strcmp(pkmnSpeciesStr[i], stringInput) == 0) {
                        selection = i;
                        break; /* item found */
                    }
                }

                if (selection == pkmnSpeciesCount) {
                    fprintf(stderr, LRED "ERROR:" RESET LIGHT " Cannot find pokemon " LGREEN "\"%s\"" RESET LIGHT " in the database.\n", stringInput);
                    mostSimilarIndex = findMostSimilarStringInArray(stringInput, pkmnSpeciesStr, pkmnSpeciesCount);
                    if (mostSimilarIndex == -1) {
                        fputs("Re-check your spelling.\n" RESET, stderr);
                    } else {
                        fprintf(stderr, RESET LIGHT "Do you mean " LGREEN "\"%s\"" RESET LIGHT "?\n" RESET, pkmnSpeciesStr[mostSimilarIndex]);
                    }
                    continue;
                }
            } else {
                selection = (unsigned int)atoi(stringInput);
            }
        } /* non-empty input */

        if (checkPkmnInWonderMail(selection, 1) == NoError) {
            break; /* input is ok */
        }
    } /* forever */
    wm->pkmnClient = selection;

    /* pokemon target */
    if (wm->missionType == Find || wm->missionType == Escort) {
        forever {
            fputs(LIGHT "Enter the name (case sensitive) or room index of the target pokemon (leave it blank for random).\n" RESET, stdout);
            fputs(RESET ">>> " LGREEN, stdout);
            fflush(stdout);
            (void)!fgets(stringInput, 100, stdin);
            if (stringInput[strlen(stringInput) - 1] == '\n') {
                stringInput[strlen(stringInput) - 1] = '\0';
            }
            if (strlen(stringInput) == 0) {
                do {
                    sprintf(stringInput, "%u", rand() % pkmnSpeciesCount);
                } while (checkPkmnInWonderMail(atoi(stringInput), 0) != NoError);
                selection = (unsigned int)atoi(stringInput);
            } else {
                for (i = 0; i < strlen(stringInput); ++i) {
                    if (!isdigit(stringInput[i])) {
                        break;
                    }
                }
                if (i != strlen(stringInput)) { /* non-digit found */
                    selection = pkmnSpeciesCount; /* invalid name, invalid index */
                    for (i = 0; i < pkmnSpeciesCount; ++i) {
                        if (strcmp(pkmnSpeciesStr[i], stringInput) == 0) {
                            selection = i;
                            break; /* item found */
                        }
                    }

                    if (selection == pkmnSpeciesCount) {
                        fprintf(stderr, LRED "ERROR:" RESET LIGHT " Cannot find pokemon " LGREEN "\"%s\"" RESET LIGHT " in the database.\n", stringInput);
                        mostSimilarIndex = findMostSimilarStringInArray(stringInput, pkmnSpeciesStr, pkmnSpeciesCount);
                        if (mostSimilarIndex == -1) {
                            fputs("Re-check your spelling.\n" RESET, stderr);
                        } else {
                            fprintf(stderr, RESET LIGHT "Do you mean " LGREEN "\"%s\"" RESET LIGHT "?\n" RESET, pkmnSpeciesStr[mostSimilarIndex]);
                        }
                        continue;
                    }
                } else {
                    selection = (unsigned int)atoi(stringInput);
                }
            } /* non-empty input */

            if (checkPkmnInWonderMail(selection, 1) == NoError) {
                break; /* input is ok */
            }
        } /* forever */
        wm->pkmnTarget = selection;
    } else {
        wm->pkmnTarget = 0;
    }

    /* dungeon */
    forever {
        fputs(LIGHT "Enter the name (case sensitive) or room index of the dungeon (leave it blank for random).\n" RESET, stdout);
        fputs(RESET ">>> " LGREEN, stdout);
        fflush(stdout);
        (void)!fgets(stringInput, 100, stdin);
        if (stringInput[strlen(stringInput) - 1] == '\n') {
            stringInput[strlen(stringInput) - 1] = '\0';
        }
        if (strlen(stringInput) == 0) {
            do {
                sprintf(stringInput, "%u", rand() % dungeonsCount);
            } while (checkDungeonInWonderMail(atoi(stringInput), 0) != NoError);
            selection = (unsigned int)atoi(stringInput);
        } else {
            for (i = 0; i < strlen(stringInput); ++i) {
                if (!isdigit(stringInput[i])) {
                    break;
                }
            }
            if (i != strlen(stringInput)) { /* non-digit found */
                selection = dungeonsCount; /* invalid name, invalid index */
                for (i = 0; i < dungeonsCount; ++i) {
                    if (strcmp(dungeonsStr[i], stringInput) == 0) {
                        selection = i;
                        break; /* item found */
                    }
                }

                if (selection == dungeonsCount) {
                    fprintf(stderr, LRED "ERROR:" RESET LIGHT " Cannot find pokemon " LGREEN "\"%s\"" RESET LIGHT " in the database.\n", stringInput);
                    mostSimilarIndex = findMostSimilarStringInArray(stringInput, dungeonsStr, dungeonsCount);
                    if (mostSimilarIndex == -1) {
                        fputs("Re-check your spelling.\n" RESET, stderr);
                    } else {
                        fprintf(stderr, RESET LIGHT "Do you mean " LGREEN "\"%s\"" RESET LIGHT "?\n" RESET, dungeonsStr[mostSimilarIndex]);
                    }
                    continue;
                }
            } else {
                selection = (unsigned int)atoi(stringInput);
            }
        } /* non-empty input */

        if (checkDungeonInWonderMail(selection, 1) == NoError) {
            break; /* input is ok */
        }
    } /* forever */
    wm->dungeon = selection;

    /* floor */
    forever {
        fputs(LIGHT "Enter the floor (leave it blank for random).\n" RESET, stdout);
        fputs(RESET ">>> " LGREEN, stdout);
        fflush(stdout);
        (void)!fgets(stringInput, 100, stdin);
        if (stringInput[strlen(stringInput) - 1] == '\n') {
            stringInput[strlen(stringInput) - 1] = '\0';
        }
        if (strlen(stringInput) == 0) {
            sprintf(stringInput, "%u", 1 + rand() % difficulties[wm->dungeon][0]);
        } else {
            for (i = 0; i < strlen(stringInput); ++i) {
                if (!isdigit(stringInput[i])) {
                    break;
                }
            }
            if (i != strlen(stringInput)) { /* non-digit found */
                fputs(LRED "ERROR:" RESET LIGHT " Invalid input. Only positive numbers are allowed.\n\n", stderr);
                continue;
            }
        } /* non-empty input */

        /* input is ok (only digits) */
        selection = (unsigned int)atoi(stringInput);
        if (checkFloorForDungeon(selection, wm->dungeon, 1) == NoError) {
            break; /* input is ok */
        }
    } /* forever */
    wm->floor = selection;

    /* item to find/deliver */
    if (wm->missionType == FindItem || wm->missionType == DeliverItem) {
        forever {
            fprintf(stdout, LIGHT "Enter the name (case sensitive) or room index of the " LGREEN "item to %s" RESET LIGHT " (leave it blank for random).\n" RESET, wm->missionType == FindItem ? "find" : "deliver");
            fputs(RESET ">>> " LGREEN, stdout);
            (void)!fgets(stringInput, 100, stdin);
            if (stringInput[strlen(stringInput) - 1] == '\n') {
                stringInput[strlen(stringInput) - 1] = '\0';
            }
            if (strlen(stringInput) == 0) {
                sprintf(stringInput, "%u", wm->missionType == FindItem ? (unsigned int)itemsInDungeons[wm->dungeon][1 + rand() % (itemsInDungeons[wm->dungeon][0] - 1)] : 1 + rand() % (itemsCount - 8));
                selection = (unsigned int)atoi(stringInput);
            } else {
                for (i = 0; i < strlen(stringInput); ++i) {
                    if (!isdigit(stringInput[i])) {
                        break;
                    }
                }
                if (i != strlen(stringInput)) { /* non-digit found */
                    selection = itemsCount; /* invalid name, invalid index */
                    for (i = 0; i < itemsCount; ++i) {
                        if (strcmp(itemsStr[i], stringInput) == 0) {
                            selection = i;
                            break; /* item found */
                        }
                    }

                    if (selection == itemsCount) {
                        fprintf(stderr, LRED "ERROR:" RESET LIGHT " Cannot find item " LGREEN "\"%s\"" RESET LIGHT " in the database.\n", stringInput);
                        mostSimilarIndex = findMostSimilarStringInArray(stringInput, itemsStr, itemsCount);
                        if (mostSimilarIndex == -1) {
                            fputs("Re-check your spelling.\n" RESET, stderr);
                        } else {
                            fprintf(stderr, RESET LIGHT "Do you mean " LGREEN "\"%s\"" RESET LIGHT "?\n" RESET, itemsStr[mostSimilarIndex]);
                        }
                        continue;
                    }
                } else {
                    selection = (unsigned int)atoi(stringInput);
                }
            } /* non-empty input */

            if (checkItemToFindDeliverRangeInWonderMail(selection, 1) == NoError) {
                if (wm->missionType == DeliverItem) {
                    break; /* input is ok */
                } else if (checkItemToFindDeliverByDungeonInWonderMail(selection, wm->dungeon, 1) == NoError) {
                    break; /* input is ok */
                }
            }
        } /* forever */
        wm->itemDeliverFind = selection;
    } else {
        wm->itemDeliverFind = 9; /* the default value must be 9 */
    }

    /* reward type */
    const enum RewardType rewardTypes[] = { MoneyMoney, Item2, MoneyMoneyItem, ItemItem2, FriendArea };
    const char* rewardTypesStr[] = { "Money", "Item", "Money + (?)", "Item + (?)", "Friend Area" };
    forever {
        fputs(LIGHT "Select the " LGREEN "reward type" RESET LIGHT ".\n" RESET, stdout);
        for (i = 0; i < 5; ++i) {
            fprintf(stdout, LGREEN "%u" RESET " - ", i + 1);
            fputs(rewardTypesStr[i], stdout);
            fputc('\n', stdout);
        }
        fputs(RESET ">>> " LGREEN, stdout);
        fflush(stdout);
        selection = getchar() - '0' - 1;
        clearStdinBuffer();
        if (selection < 5) { /* `selection` is unsigned so it's always >= 0 */
            break; /* input is ok */
        }
        fprintf(stderr, LRED "INPUT ERROR\n" RESET);
    } /* forever */
    wm->rewardType = rewardTypes[selection];

    /* reward item */
    if (wm->rewardType == Item || wm->rewardType == ItemItem || wm->rewardType == Item2 || wm->rewardType == ItemItem2 || wm->rewardType == MoneyItem || wm->rewardType == MoneyMoneyItem) {
        forever {
            fputs(LIGHT "Enter the name (case sensitive) or room index of the reward item (leave it blank for random).\n" RESET, stdout);
            fputs(RESET ">>> " LGREEN, stdout);
            (void)!fgets(stringInput, 100, stdin);
            if (stringInput[strlen(stringInput) - 1] == '\n') {
                stringInput[strlen(stringInput) - 1] = '\0';
            }
            if (strlen(stringInput) == 0) {
                sprintf(stringInput, "%u", 1 + rand() % (itemsCount - 1));
                selection = (unsigned int)atoi(stringInput);
            } else {
                for (i = 0; i < strlen(stringInput); ++i) {
                    if (!isdigit(stringInput[i])) {
                        break;
                    }
                }
                if (i != strlen(stringInput)) { /* non-digit found */
                    selection = itemsCount; /* invalid name, invalid index */
                    for (i = 0; i < itemsCount; ++i) {
                        if (strcmp(itemsStr[i], stringInput) == 0) {
                            selection = i;
                            break; /* item found */
                        }
                    }

                    if (selection == itemsCount) {
                        fprintf(stderr, LRED "ERROR:" RESET LIGHT " Cannot find item " LGREEN "\"%s\"" RESET LIGHT " in the database.\n", stringInput);
                        mostSimilarIndex = findMostSimilarStringInArray(stringInput, itemsStr, itemsCount);
                        if (mostSimilarIndex == -1) {
                            fputs("Re-check your spelling.\n" RESET, stderr);
                        } else {
                            fprintf(stderr, RESET LIGHT "Do you mean " LGREEN "\"%s\"" RESET LIGHT "?\n" RESET, itemsStr[mostSimilarIndex]);
                        }
                        continue;
                    }
                } else {
                    selection = (unsigned int)atoi(stringInput);
                }
            } /* non-empty input */

            if (checkItemRange(selection, 1) == NoError) {
                break; /* input is ok */
            }
        } /* forever */
        wm->itemReward = selection;
    } else { /* no item reward */
        wm->itemReward = 0;
    }

    /* friend area reward */
    const int availableFriendAreasIndexes[] = { 9, 10, 15, 37 };
    if (wm->rewardType == FriendArea) {
        forever {
            fputs(LIGHT "Select the friend area that you want as reward.\n" RESET, stdout);
            for (i = 0; i < 4; ++i) {
                fprintf(stdout, LGREEN "%u" RESET " - ", i + 1);
                fputs(friendAreasStr[availableFriendAreasIndexes[i]], stdout);
                fputc('\n', stdout);
            }
            fputs(RESET ">>> " LGREEN, stdout);
            fflush(stdout);
            selection = getchar() - '0' - 1;
            clearStdinBuffer();
            if (selection < 4) { /* `selection` is unsigned so it's always >= 0 */
                break; /* input is ok */
            }
            fprintf(stderr, LRED "INPUT ERROR\n" RESET);
        }
        wm->friendAreaReward = availableFriendAreasIndexes[selection];
    } else {
        wm->friendAreaReward = 0;
    }

    return NoError;
}



int requestSOSMailPassword(char *password)
{
    fputs(LIGHT "Enter the SOS Mail's password\n" RESET, stdout);
    fputs(RESET ">>> " LGREEN, stdout);
    fflush(stdout);
    (void)!fgets(password, 54, stdin);
    fputs(RESET, stdout);
    fflush(stdout);
    if (password[strlen(password) - 1] == '\n') {
        password[strlen(password) - 1] = '\0';
    }

    return NoError;
}



int requestAndParseSosMailData(struct SosMail *sos)
{
    unsigned int i = 0;
    unsigned int selection = -1;
    char stringInput[101];
    int mostSimilarIndex = 0;

    /* mail type */
    const enum MailType mailTypes[] = { SosMailType, AOkMailType, ThankYouMailType };
    const char* mailTypesStr[] = { "SOS Mail", "A-Ok Mail", "Thank-You Mail" };
    forever {
        fputs(LIGHT "Select the mail type.\n" RESET, stdout);
        for (i = 0; i < 3; ++i) {
            fprintf(stdout, LGREEN "%u" RESET " - ", i + 1);
            fputs(mailTypesStr[i], stdout);
            fputc('\n', stdout);
        }
        fputs(RESET ">>> " LGREEN, stdout);
        fflush(stdout);
        selection = getchar() - '0' - 1;
        clearStdinBuffer();
        if (selection < 3) { /* as `selection` is unsigned, it is always >= 0 */
            break; /* input is ok */
        }
        fprintf(stderr, LRED "INPUT ERROR\n" RESET);
    }
    sos->mailType = mailTypes[selection];

    /* dungeon */
    forever {
        fputs(LIGHT "Enter the name (case sensitive) or room index of the dungeon (leave it blank for random).\n" RESET, stdout);
        fputs(RESET ">>> " LGREEN, stdout);
        fflush(stdout);
        (void)!fgets(stringInput, 100, stdin);
        if (stringInput[strlen(stringInput) - 1] == '\n') {
            stringInput[strlen(stringInput) - 1] = '\0';
        }
        if (strlen(stringInput) == 0) {
            do {
                sprintf(stringInput, "%u", rand() % dungeonsCount);
            } while (checkDungeonInWonderMail(atoi(stringInput), 0) != NoError);
            selection = (unsigned int)atoi(stringInput);
            fputs(LYELLOW "WARNING:" RESET " You selected a random dungeon. This can be unacceptable for you friend.\n", stdout);
            fflush(stdout);
        } else {
            for (i = 0; i < strlen(stringInput); ++i) {
                if (!isdigit(stringInput[i])) {
                    break;
                }
            }
            if (i != strlen(stringInput)) { /* non-digit found */
                selection = dungeonsCount; /* invalid name, invalid index */
                for (i = 0; i < dungeonsCount; ++i) {
                    if (strcmp(dungeonsStr[i], stringInput) == 0) {
                        selection = i;
                        break; /* item found */
                    }
                }

                if (selection == dungeonsCount) {
                    fprintf(stderr, LRED "ERROR:" RESET LIGHT " Cannot find pokemon " LGREEN "\"%s\"" RESET LIGHT " in the database.\n", stringInput);
                    mostSimilarIndex = findMostSimilarStringInArray(stringInput, dungeonsStr, dungeonsCount);
                    if (mostSimilarIndex == -1) {
                        fputs("Re-check your spelling.\n" RESET, stderr);
                    } else {
                        fprintf(stderr, RESET LIGHT "Do you mean " LGREEN "\"%s\"" RESET LIGHT "?\n" RESET, dungeonsStr[mostSimilarIndex]);
                    }
                    continue;
                }
            } else {
                selection = (unsigned int)atoi(stringInput);
            }
        } /* non-empty input */

        if (checkDungeonInWonderMail(selection, 1) == NoError) {
            break; /* input is ok */
        }
    } /* forever */
    sos->dungeon = selection;

    /* floor */
    forever {
        fputs(LIGHT "Enter the floor (leave it blank for random).\n" RESET, stdout);
        fputs(RESET ">>> " LGREEN, stdout);
        fflush(stdout);
        (void)!fgets(stringInput, 100, stdin);
        if (stringInput[strlen(stringInput) - 1] == '\n') {
            stringInput[strlen(stringInput) - 1] = '\0';
        }
        if (strlen(stringInput) == 0) {
            sprintf(stringInput, "%u", 1 + rand() % (difficulties[sos->dungeon][0] + 1));
            fputs(LYELLOW "WARNING:" RESET " You selected a random floor. This can be unacceptable for you friend.\n", stdout);
            fflush(stdout);
        } else {
            for (i = 0; i < strlen(stringInput); ++i) {
                if (!isdigit(stringInput[i])) {
                    break;
                }
            }
            if (i != strlen(stringInput)) { /* non-digit found */
                fputs(LRED "ERROR:" RESET LIGHT " Invalid input. Only positive numbers are allowed.\n\n", stderr);
                continue;
            }

            if (checkFloorForDungeon(selection, sos->dungeon, 1) == NoError) {
                break; /* input is ok */
            }
        } /* non-empty input */

        /* input is ok (only digits) */
        selection = (unsigned int)atoi(stringInput);
    } /* forever */
    sos->floor = selection;

    /* pokemon to rescue */
    forever {
        fputs(LIGHT "Enter the name (case sensitive) or room index of the pokemon to rescue (leave it blank for random).\n" RESET, stdout);
        fputs(RESET ">>> " LGREEN, stdout);
        fflush(stdout);
        (void)!fgets(stringInput, 100, stdin);
        if (stringInput[strlen(stringInput) - 1] == '\n') {
            stringInput[strlen(stringInput) - 1] = '\0';
        }
        if (strlen(stringInput) == 0) {
            do {
                sprintf(stringInput, "%u", rand() % pkmnSpeciesCount);
            } while (checkPkmnInWonderMail(atoi(stringInput), 0) != NoError);
            selection = (unsigned int)atoi(stringInput);
            fputs(LYELLOW "WARNING:" RESET " You selected a random pokemon. This can be unacceptable for you friend.\n", stdout);
            fflush(stdout);
        } else {
            for (i = 0; i < strlen(stringInput); ++i) {
                if (!isdigit(stringInput[i])) {
                    break;
                }
            }
            if (i != strlen(stringInput)) { /* non-digit found */
                selection = pkmnSpeciesCount; /* invalid name, invalid index */
                for (i = 0; i < pkmnSpeciesCount; ++i) {
                    if (strcmp(pkmnSpeciesStr[i], stringInput) == 0) {
                        selection = i;
                        break; /* item found */
                    }
                }

                if (selection == pkmnSpeciesCount) {
                    fprintf(stderr, LRED "ERROR:" RESET LIGHT " Cannot find pokemon " LGREEN "\"%s\"" RESET LIGHT " in the database.\n", stringInput);
                    mostSimilarIndex = findMostSimilarStringInArray(stringInput, pkmnSpeciesStr, pkmnSpeciesCount);
                    if (mostSimilarIndex == -1) {
                        fputs("Re-check your spelling.\n" RESET, stderr);
                    } else {
                        fprintf(stderr, RESET LIGHT "Do you mean " LGREEN "\"%s\"" RESET LIGHT "?\n" RESET, pkmnSpeciesStr[mostSimilarIndex]);
                    }
                    continue;
                }
            } else {
                selection = (unsigned int)atoi(stringInput);
            }
        } /* non-empty input */

        if (checkPkmnInWonderMail(selection, 1) == NoError) {
            break; /* input is ok */
        }
    } /* forever */
    sos->pkmnToRescue = selection;

    /* reward item */
    forever {
        fputs(LIGHT "Enter the name (case sensitive) or room index of the reward item (type \"0\" or \"Nothing\" for no reward, or leave it blank for random).\n" RESET, stdout);
        fputs(RESET ">>> " LGREEN, stdout);
        (void)!fgets(stringInput, 100, stdin);
        if (stringInput[strlen(stringInput) - 1] == '\n') {
            stringInput[strlen(stringInput) - 1] = '\0';
        }
        if (strlen(stringInput) == 0) {
            sprintf(stringInput, "%u", 1 + rand() % (itemsCount - 1));
        } else {
            for (i = 0; i < strlen(stringInput); ++i) {
                if (!isdigit(stringInput[i])) {
                    break;
                }
            }
            if (i != strlen(stringInput)) { /* non-digit found */
                selection = itemsCount; /* invalid name, invalid index */
                for (i = 0; i < itemsCount; ++i) {
                    if (strcmp(itemsStr[i], stringInput) == 0) {
                        selection = i;
                        break; /* item found */
                    }
                }

                if (selection == itemsCount) {
                    fprintf(stderr, LRED "ERROR:" RESET LIGHT " Cannot find item " LGREEN "\"%s\"" RESET LIGHT " in the database.\n", stringInput);
                    mostSimilarIndex = findMostSimilarStringInArray(stringInput, itemsStr, itemsCount);
                    if (mostSimilarIndex == -1) {
                        fputs("Re-check your spelling.\n" RESET, stderr);
                    } else {
                        fprintf(stderr, RESET LIGHT "Do you mean " LGREEN "\"%s\"" RESET LIGHT "?\n" RESET, itemsStr[mostSimilarIndex]);
                    }
                    continue;
                }
            } else {
                selection = (unsigned int)atoi(stringInput);
            }
        } /* non-empty input */

        if (checkItemRange(selection, 1) == NoError) {
            break; /* input is ok */
        }
    } /* forever */
    sos->itemReward = selection;

    /* nickname */
    forever {
        fputs(LIGHT "Enter the nickname of the pokemon to the rescue.\n" RESET, stdout);
        fputs(RESET ">>> " LGREEN, stdout);
        fflush(stdout);
        (void)!fgets(stringInput, 100, stdin);
        if (stringInput[strlen(stringInput) - 1] == '\n') {
            stringInput[strlen(stringInput) - 1] = '\0';
        }
        if (strlen(stringInput) == 0) {
            fputs(LRED "ERROR:" RESET LIGHT " Invalid input. Please enter a name with no more than 10 characters.\n\n", stderr);
            fflush(stderr);
            continue;
        } else if (strlen(stringInput) > 10) {
            fputs(LYELLOW "WARNING:" RESET " The entered name (" LRED "%s" RESET ") is bigger than 10 characters, so it has been truncated to " LGREEN "%10s" RESET ".\n", stdout);
            fflush(stdout);
        }
        break;
    } /* forever */
    strncpy(sos->pkmnNick, stringInput, 10);

    /* mail ID */
    forever {
        fputs(LIGHT "Enter the Mail ID (leave blank for random).\n" RESET, stdout);
        fputs(RESET ">>> " LGREEN, stdout);
        fflush(stdout);
        (void)!fgets(stringInput, 100, stdin);
        if (stringInput[strlen(stringInput) - 1] == '\n') {
            stringInput[strlen(stringInput) - 1] = '\0';
        }
        if (strlen(stringInput) == 0) {
            sprintf(stringInput, "%u", rand() & 0xFFFF);
            fputs(LYELLOW "WARNING:" RESET " You selected a random Mail ID. You may be unable to receive an A-Ok/Thank-You Mail.\n", stdout);
            fflush(stdout);
        } else {
            for (i = 0; i < strlen(stringInput); ++i) {
                if (!isdigit(stringInput[i])) {
                    break;
                }
            }
        }
        if (i != strlen(stringInput)) { /* non-digit found */
            fputs(LRED "ERROR:" RESET LIGHT " Invalid input. Only positive numbers are allowed.\n\n", stderr);
            fflush(stderr);
            continue;
        }

        /* input is ok (only digits) */
        selection = (unsigned int)atoi(stringInput);
    }
    sos->mailID = selection;

    return NoError;
}



void printWonderMailData(const struct WonderMailInfo *mailInfo, const struct WonderMail *mail)
{
    char newHead[76] = {0};
    char newBody1[150] = {0};
    char newBody2[150] = {0};
    char newObjective[72] = {0};
    char newPlace[76] = {0};
    char newFloor[57] = {0};
    char newReward[85] = {0};
    strcpy(newHead, mailInfo->head);
    strcpy(newBody1, mailInfo->body1);
    strcpy(newBody2, mailInfo->body2);
    strcpy(newObjective, mailInfo->objective);
    strcpy(newPlace, mailInfo->place);
    strcpy(newFloor, mailInfo->floor);
    strcpy(newReward, mailInfo->reward);
    char* pkmnHead = strstr(newHead, pkmnSpeciesStr[mail->pkmnTarget]);
    char* pkmnBody1 = strstr(newBody1, pkmnSpeciesStr[mail->pkmnTarget]);
    char* pkmnBody2 = strstr(newBody2, pkmnSpeciesStr[mail->pkmnTarget]);
    char* pkmnObjective = strstr(newObjective, pkmnSpeciesStr[mail->pkmnTarget]);
    char* dungeonPlace = strstr(newPlace, dungeonsStr[mail->dungeon]);
    char floorStr[3];
    sprintf(floorStr, "%d", mail->floor % 100);
    char* dungeonFloor = strstr(newFloor, floorStr);
    char* itemHead = strstr(newHead, itemsStr[mail->itemDeliverFind]);
    char* itemBody1 = strstr(newBody1, itemsStr[mail->itemDeliverFind]);
    char* itemBody2 = strstr(newBody2, itemsStr[mail->itemDeliverFind]);
    char* itemObjective = strstr(newObjective, itemsStr[mail->itemDeliverFind]);
    char* itemReward = strstr(newReward, itemsStr[mail->itemReward]);

    char hold[200] = {0};

    if (pkmnHead) {
        strcpy(hold, pkmnHead);
        strcpy(pkmnHead, LYELLOW);
        strncat(newHead, hold, strlen(pkmnSpeciesStr[mail->pkmnTarget]));
        strcat(newHead, WHITE);
        strcat(newHead, hold + strlen(pkmnSpeciesStr[mail->pkmnTarget]));
    }

    if (pkmnBody1) {
        strcpy(hold, pkmnBody1);
        strcpy(pkmnBody1, COLOR_YELLOW);
        strncat(newBody1, hold, strlen(pkmnSpeciesStr[mail->pkmnTarget]));
        strcat(newBody1, RESET COLOR_BACKGROUND);
        strcat(newBody1, hold + strlen(pkmnSpeciesStr[mail->pkmnTarget]));
    }

    if (pkmnBody2) {
        strcpy(hold, pkmnBody2);
        strcpy(pkmnBody2, COLOR_YELLOW);
        strncat(newBody2, hold, strlen(pkmnSpeciesStr[mail->pkmnTarget]));
        strcat(newBody2, RESET COLOR_BACKGROUND);
        strcat(newBody2, hold + strlen(pkmnSpeciesStr[mail->pkmnTarget]));
    }

    if (pkmnObjective) {
        strcpy(hold, pkmnObjective);
        strcpy(pkmnObjective, COLOR_YELLOW);
        strncat(newObjective, hold, strlen(pkmnSpeciesStr[mail->pkmnTarget]));
        strcat(newObjective, RESET COLOR_BACKGROUND);
        strcat(newObjective, hold + strlen(pkmnSpeciesStr[mail->pkmnTarget]));
    }

    if (dungeonPlace) {
        strcpy(hold, dungeonPlace);
        strcpy(dungeonPlace, COLOR_YELLOW);
        strncat(newPlace, hold, strlen(dungeonsStr[mail->dungeon]));
        strcat(newPlace, RESET COLOR_BACKGROUND);
        strcat(newPlace, hold + strlen(dungeonsStr[mail->dungeon]));
    } else {
        strcat(newPlace, COLOR_YELLOW RESET COLOR_BACKGROUND);
    }

    if (dungeonFloor) {
        --dungeonFloor;
        strcpy(hold, dungeonFloor);
        strcpy(dungeonFloor, COLOR_CYAN);
        strncat(newFloor, hold, strlen(floorStr) + 1);
        strcat(newFloor, RESET COLOR_BACKGROUND);
        strcat(newFloor, hold + strlen(floorStr) + 1);
    } else {
        strcat(newFloor, COLOR_CYAN RESET COLOR_BACKGROUND);
    }

    if (itemHead) {
        strcpy(hold, itemHead);
        strcpy(itemHead, LGREEN);
        strncat(newHead, hold, strlen(itemsStr[mail->itemDeliverFind]));
        strcat(newHead, WHITE);
        strcat(newHead, hold + strlen(itemsStr[mail->itemDeliverFind]));
    }

    if (itemBody1) {
        strcpy(hold, itemBody1);
        strcpy(itemBody1, COLOR_GREEN);
        strncat(newBody1, hold, strlen(itemsStr[mail->itemDeliverFind]));
        strcat(newBody1, RESET COLOR_BACKGROUND);
        strcat(newBody1, hold + strlen(itemsStr[mail->itemDeliverFind]));
    }

    if (itemBody2) {
        strcpy(hold, itemBody2);
        strcpy(itemBody2, COLOR_GREEN);
        strncat(newBody2, hold, strlen(itemsStr[mail->itemDeliverFind]));
        strcat(newBody2, RESET COLOR_BACKGROUND);
        strcat(newBody2, hold + strlen(itemsStr[mail->itemDeliverFind]));
    }

    if (itemObjective) {
        strcpy(hold, itemObjective);
        strcpy(itemObjective, COLOR_GREEN);
        strncat(newObjective, hold, strlen(itemsStr[mail->itemDeliverFind]));
        strcat(newObjective, RESET COLOR_BACKGROUND);
        strcat(newObjective, hold + strlen(itemsStr[mail->itemDeliverFind]));
    }
    
    if (itemReward) {
        strcpy(hold, itemReward);
        strcpy(itemReward, COLOR_GREEN);
        strncat(newReward, hold, strlen(itemsStr[mail->itemReward]));
        strcat(newReward, RESET COLOR_BACKGROUND);
        strcat(newReward, hold + strlen(itemsStr[mail->itemReward]));
    } else {
        strcat(newReward, COLOR_GREEN RESET COLOR_BACKGROUND);
    }

    if (!pkmnHead && !itemHead) {
        strcat(newHead, LYELLOW WHITE);
    }
    if (!pkmnBody1 && !itemBody1) {
        strcat(newBody1, COLOR_YELLOW RESET COLOR_BACKGROUND);
    }
    if (!pkmnBody2 && !itemBody2) {
        strcat(newBody2, COLOR_YELLOW RESET COLOR_BACKGROUND);
    }
    if (!pkmnObjective && !itemObjective) {
        strcat(newObjective, COLOR_YELLOW RESET COLOR_BACKGROUND);        
    }

    char placeAndFloor[120] = {0};
    sprintf(placeAndFloor, "%s  %s", newPlace, newFloor);
    
    char diffColor[50] = {0};
    strcpy(diffColor, mailInfo->difficulty == 'E' ? RESET COLOR_BACKGROUND : mailInfo->difficulty == 'D' || mailInfo->difficulty == 'C' ? COLOR_GREEN : mailInfo->difficulty == 'B' || mailInfo->difficulty == 'A' ? COLOR_CYAN : mailInfo->difficulty == 'S' ? COLOR_RED : LYELLOW);
    
    int i, j;
    char temp[30] = {0};
    for (i = j = 0; i < 24; ++i) {
        if (i && i % 4 == 0) {
            temp[i + j++] = '\0';
        }
        temp[i + j] = mailInfo->password[i];
    }

    fprintf(stdout, "\n" COLOR_BORDER COLOR_BACKGROUND "**********************************************" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " RESET WHITE COLOR_BACKGROUND UNDERLINE "%-56s" RESET COLOR_BACKGROUND COLOR_BORDER " *" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " COLOR_BORDER "%-43s*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " RESET COLOR_BACKGROUND "%-81s" COLOR_BORDER COLOR_BACKGROUND "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " RESET COLOR_BACKGROUND "%-81s" COLOR_BORDER COLOR_BACKGROUND "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " COLOR_BORDER "%-43s*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Client:     " RESET COLOR_BACKGROUND "%-31s" COLOR_BORDER "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Objective:  " RESET COLOR_BACKGROUND "%-69s" COLOR_BORDER "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Place:      " RESET COLOR_BACKGROUND "%-107s" COLOR_BORDER "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Difficulty: " RESET COLOR_BACKGROUND "%s%c%-30s" COLOR_BORDER "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Reward:     " RESET COLOR_BACKGROUND "%-69s" COLOR_BORDER "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Password:   " RESET COLOR_BACKGROUND "%s" COLOR_YELLOW "%s" RESET COLOR_BACKGROUND "%-23s" COLOR_BORDER COLOR_BACKGROUND "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " RESET COLOR_BACKGROUND "            %s" COLOR_YELLOW "%s" RESET COLOR_BACKGROUND "%-23s" COLOR_BORDER COLOR_BACKGROUND "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "**********************************************" RESET "\n",
            newHead, "", newBody1, newBody2, "", mailInfo->client, newObjective, placeAndFloor, diffColor, mailInfo->difficulty, "", newReward, temp, temp + 5, temp + 10, temp + 15, temp + 20, temp + 25);
}


void printSOSData(const struct SosMailInfo *mailInfo)
{
    fprintf(stdout, "\n%s\n\n%s\n\n"
                    "Client: %s (%s)\n"
                    "Objective: %s\n"
                    "Place: %s  %s\n"
                    "Difficulty: %c\n"
                    "Reward: %s\n"
                    "ID: %s\n"
                    "Chances left: %s\n"
                    "Password: %s\n"
                    "_____________________________________________\n\n",
            mailInfo->head, mailInfo->body, mailInfo->nickname, mailInfo->client, mailInfo->objective, mailInfo->place, mailInfo->floor, mailInfo->difficulty, mailInfo->reward, mailInfo->id, mailInfo->chancesLeft, mailInfo->password);
}



int checkPkmnInWonderMail(int index, int printErrorMessages)
{
    /* pkmn check (limits) */
    if (index <= 0 || (unsigned int)index >= pkmnSpeciesCount) {
        if (printErrorMessages) {
            fprintf(stderr, LRED "ERROR:" RESET LIGHT " Pkmn must be numbers between 1 and %d (not necessarily match pkdex numbers).\n"
                            "      Current value: " LRED "%u" RESET LIGHT " [" LRED "INVALID" RESET LIGHT "]\n\n" RESET, pkmnSpeciesCount - 1, index);
        }
        return InputError;
    }
    /* pkmn check (legendaries) */
    else if ( (index >= 144 && index <= 146) /* birds */ || (index >= 150 && index <= 151) /* mewtwo and mew */ ||
              (index >= 201 && index <= 226) /* unown */ || (index >= 268 && index <= 270) /* dogs */ ||
              (index >= 274 && index <= 276) /* lugia and ho-oh */ ||
              (index >= 405 && index <= 414) /* regis, eons, kyogre, groudon, rayquaza, jirachi and deoxys */ ) {
        if (printErrorMessages) {
            fprintf(stderr, LRED "ERROR:" RESET LIGHT " Legendaries are not valid values.\n"
                            "      Current value: " LRED "%u" RESET LIGHT " [" LRED "%s" RESET LIGHT "]\n\n" RESET, index, pkmnSpeciesStr[index]);
        }
        return InputError;
    }

    return NoError;
}



int checkDungeonInWonderMail(int index, int printErrorMessages)
{
    /* dungeon check */
    if (index < 0 || (unsigned int)index >= dungeonsCount) {
        if (printErrorMessages) {
            fprintf(stderr, LRED "ERROR:" RESET LIGHT " Dungeons must be numbers between 1 and %d.\n"
                            "      Current value: " LRED "%u" RESET LIGHT " [" LRED "INVALID" RESET LIGHT "]\n\n" RESET, dungeonsCount - 1, index);
        }
        return InputError;
    } else if (strcmp(dungeonsStr[index], "[INVALID]") == 0) {
        if (printErrorMessages) {
            fprintf(stderr, LRED "ERROR:" RESET LIGHT " The dungeon with index " LRED "%u" RESET " isn't a valid dungeon.\n", index);
        }
        return InputError;
    }

    return NoError;
}



int checkFloorForDungeon(int floor, int dungeonIndex, int printErrorMessages)
{
    /* floor check (floor 0) */
    if (floor <= 0) {
        if (printErrorMessages) {
            fprintf(stderr, LIGHT "ERROR:" RESET LIGHT " Floor %d does not exists.\n", floor);
        }
        return InputError;
    }
    /* floor check (limit) */
    if (floor > difficulties[dungeonIndex][0]) {
        if (printErrorMessages) {
            fprintf(stderr, LIGHT "ERROR:" RESET LIGHT " The dungeon " LGREEN "%u" RESET LIGHT " [" LGREEN "%s" RESET LIGHT "] only has " LRED "%d" RESET LIGHT " floors. Your entry exceed that value.\n\n",
                            dungeonIndex, dungeonsStr[dungeonIndex], difficulties[dungeonIndex][0]);
        }
        return InputError;
    }

    return NoError;
}



int checkItemToFindDeliverRangeInWonderMail(int index, int printErrorMessages)
{
    /* item check (limits) */
    if (index < 1 || (unsigned int)index >= (itemsCount - 8)) { /* the last 8 are not valid */
        if (printErrorMessages) {
            fprintf(stderr, LRED "ERROR:" RESET LIGHT " Items must be numbers between 1 and %d.\n"
                            "      Current value: " LRED "%u" RESET LIGHT " [" LRED "INVALID" RESET LIGHT "]\n\n" RESET, (itemsCount - 9), index);
        }
        return InputError;
    }

    return NoError;
}



int checkItemToFindDeliverByDungeonInWonderMail(int itemIndex, int dungeonIndex, int printErrorMessages)
{
    /* item check (availability in dungeon) */
    if (!findItemByDungeon(itemIndex, dungeonIndex)) {
        if (printErrorMessages) {
            fprintf(stderr, LRED "ERROR:" RESET LIGHT " The item " LGREEN "%u" RESET LIGHT " [" LGREEN "%s" RESET LIGHT "] can't be found in the dungeon " LGREEN "%u" RESET LIGHT " [" LGREEN "%s" RESET LIGHT "].\n"
                            "      To accept a job about finding an item inside a dungeon, the item must exist on that dungeon.\n"
                            "      The items that can be found in that dungeon are listed bellow:\n",
                    itemIndex, (unsigned int)itemIndex < itemsCount ? itemsStr[itemIndex] : "[INVALID]", dungeonIndex, dungeonsStr[dungeonIndex]);
            unsigned short i;
            for (i = 1; i < itemsInDungeons[dungeonIndex][0]; ++i) {
                fprintf(stderr, LGREEN "%u" RESET LIGHT " [" LGREEN "%s" RESET LIGHT "]\n" RESET, itemsInDungeons[dungeonIndex][i], itemsStr[itemsInDungeons[dungeonIndex][i]]);
            }
            fputc('\n', stderr);
        }
        return InputError;
    }

    return NoError;
}



int checkItemRange(int index, int printErrorMessages)
{
    /* item check (limits) */
    if (index < 1 || (unsigned int)index >= itemsCount) {
        if (printErrorMessages) {
            fprintf(stderr, LRED "ERROR:" RESET LIGHT " Items must be numbers between 1 and %d.\n"
                            "      Current value: " LRED "%u" RESET LIGHT " [" LRED "INVALID" RESET LIGHT "]\n\n" RESET, itemsCount - 1, index);
        }
        return InputError;
    }

    return NoError;
}



void clearStdinBuffer()
{
    int c;
    while ( (c = getchar()) != '\n' && c != EOF );
}