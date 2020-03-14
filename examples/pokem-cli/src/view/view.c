#include "view.h"
#include "../utils/colors.h"
#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define forever for(;;)
#define DISCLAIMER \
    "This program comes with ABSOLUTELY NO WARRANTY.\n" \
    "This is free software, and you are welcome to modify and/or redistribute it under the\n" \
    "terms of the GNU GENERAL PUBLIC LICENSE v2. Please visit http://www.gnu.org/licenses/\n\n"


void showHelp(const char *programName)
{
    fputs(DISCLAIMER, stdout);

    fprintf(stdout, LIGHT "Usage: " LGREEN "%s [ARGUMENTS]...\n" \
                    LYELLOW "-h, --help              " RESET "display this help and exit\n" \
                    LYELLOW "-v, --version           " RESET "display version information and exit\n" \
                    LYELLOW "-d, --database <type>   " RESET "display the database of the selected type,\n" \
                    "                        which can be one of [pokemon|items|dungeons|areas|missions|rewards]\n\n" \
                    LIGHT "Generic:\n" RESET \
                    "This program will try to autodetect what do you want to do based\n" \
                    "on your input. If you enter a Wonder Mail or SOS Mail, this program\n" \
                    "will try to decode it. If you enter an SOS Mail and an item, this\n" \
                    "program will try to convert it in a A-OK Mail and then in a Thank-You\n" \
                    "Mail. If you enter exactly 9 or 6 arguments, this program will try\n" \
                    "to encode a Wonder Mail or a SOS Mail respectively.\n" \
                    "\n" \
                    LIGHT "Conventions:\n" RESET \
                    LIGHT "1. " RESET "Enter the password in UPPERCASE.\n" \
                    LIGHT "2. " RESET "Enter the names of pokemon, items, dungeons, etc. " LIGHT "C" RESET "apitalized.\n" \
                    LIGHT "3. " RESET "Symbols conventions:\n" \
                    "    \'Female\' -> \'" LGREEN "*" RESET "\'\n" \
                    "    \'Male\'   -> \'" LGREEN "/" RESET "\'\n" \
                    "    \'...\'    -> \'" LGREEN "." RESET "\'\n" \
                    LIGHT "4. " RESET "It's recommended that you quote passwords arguments and arguments that\n" \
                    "   contains spaces by using \"double quotes\" on Windows and \'single quotes\' on\n" \
                    "   UNIX systems.\n" \
                    "\n", programName);
    fprintf(stdout, LIGHT "Decode Wonder Mail:\n" RESET \
                    LIGHT "Usage: " LGREEN "%s [password1] [password2]...\n" RESET \
                    "Decode all entered passwords. Invalid ones are skipped.\n" \
                    "Examples of valid entries:\n" \
                    LGREEN "%s \'4?6F7M+?4JNRJ*??K??0+9??\' \'16J.8!0?1PS35-?06N?RP8?W\' \'F?N.?QY?8RNYYN?4.J75N+?W\'\n" \
                    LGREEN "%s \'??J9XJX?2P??8??F6H?0P??W\'\n" \
                    "\n" \
                    LIGHT "Encode Wonder Mail:\n" RESET \
                    LIGHT "Usage: " LGREEN "%s [Mission type] [Pkmn client] [Pkmn target] [Item to find/deliver] [Dungeon] [Floor] [Reward type] [Item reward] [Friend area reward]\n" RESET \
                    "Encode a Wonder Mail using the entered arguments.\n" \
                    "You must enter exactly 9 arguments.\n" \
                    "You can use both numeric or text values for pokemon, items, dungeons and friend areas.\n" \
                    "For the remaining fields, only numeric values are accepted.\n" \
                    "Check the database to know the available mission types, pokemon, items, dungeons, etc.\n" \
                    "Example of valid entries:\n" \
                    LGREEN "%s 0 Milotic 1 0 \"Fantasy Strait\" 2 6 \"Wish Stone\" 0\n" RESET \
                    LIGHT "NOTE: " RESET "It's a Help-type mission from Milotic, the target pkmn and the item\n" \
                    "      to find/deliver are ignored. The rescue is in Fantasy Strait at 2nd floor.\n" \
                    "      The reward is a lot of money and a Wish Stone, and the Friend Area reward is ignored.\n" \
                    "--This is very useful, as wou can get any item, including hard to find ones like Beauty Scarf.\n" \
                    "--You can also unlock game-exclusive pokemon like Porygon, Mantine, Plusle, Roselia and Feebas in\n"
                    "  Red Rescue Team (GBA), and Lapras, Minum, Aipom and Magikarp in Blue Rescue Team (DS).\n" \
                    "--And, of course, you can also create high rescue points rewarding missions to improve your rank.\n" \
                    "\n" \
                    LIGHT "Decode SOS Mail:\n" RESET \
                    LIGHT "Usage: " LGREEN "%s [password1] [password2]...\n" RESET \
                    "Decode all entered passwords. Invalid ones are skipped.\n" \
                    "Examples of valid entries:\n" \
                    LGREEN "%s \'?M???.R066???2FC?!?R????3HCP?-??32H???Y?M4C??1J??NQ04?\' \'S6???.RF?6F??NWH*5KC???RH1!9?8?JK7P0??SNMJRPSKJ??7QJ4N\'\n" RESET \
                    LGREEN "%s \'????6+7SHX???1?4???H??4?NP???4???TR?????X25??PJ??07?C?\'\n" RESET \
                    "\n" \
                    LIGHT "Encode SOS Mail:\n" RESET \
                    LIGHT "Usage: " LGREEN "%s [Pkmn client] [Pkmn nickname] [Dungeon] [Floor] [Mail ID] [Rescue chances]\n" RESET \
                    "Encode a SOS Mail using the entered arguments.\n" \
                    "You must enter exactly 6 arguments.\n" \
                    "You can use both numeric or text values for pokemon, items and dungeons.\n" \
                    "For the remaining fields, only numeric values are accepted.\n" \
                    "Check the database to know the available pokemon, items, dungeons, etc.\n" \
                    "Example of valid entries:\n" \
                    LGREEN "%s Chansey Nurcy \'Joyous Tower\' 50 1234 10\n" RESET \
                    LIGHT "NOTE: " RESET "Rescue a Chansey named Nurcy at Joyous Tower floor 50.\n" \
                    "      The Mail ID is 1234 and you can try 10 times.\n" \
                    "--It is very unlikely that you ever need to encode a SOS Mail, but, still, I want to support it.\n" \
                    "\n"
                    LIGHT "Convert SOS Mail in A-OK and Thank-You Mail:\n" RESET \
                    LIGHT "Usage: " LGREEN "%s [password1] [item1] [password2] [item2]...\n" RESET \
                    "Convert all entered SOS passwords in A-OK and Thank-You Mail passwords. Invalid ones are skipped.\n" \
                    "The input is not restricted to an SOS Mail. If you enter an A-OK Mail, it will be converted to Thank-You Mail,\n" \
                    "and if you enter a Thank-You Mail, its reward item will be replaced with the received one.\n" \
                    "The item specified is set as reward in the Thank-You Mail password.\n" \
                    "If the item specified does not exists, the most similar in terms of writing is assumed.\n" \
                    "Check the database to know the available items.\n" \
                    "Examples of valid entries:\n" \
                    LGREEN "%s \'?M???.R066???2FC?!?R????3HCP?-??32H???Y?M4C??1J??NQ04?\' \"Joy Seed\" \'S6???.RF?6F??NWH*5KC???RH1!9?8?JK7P0??SNMJRPSKJ??7QJ4N\' Ginseng\n" RESET \
                    LGREEN "%s \'????6+7SHX???1?4???H??4?NP???4???TR?????X25??PJ??07?C?\' Nothing\n" RESET \
                    "--This is very useful, as wou can rescue yourself by converting your own SOS Mail.\n", programName, programName, programName, programName, programName, programName, programName, programName, programName, programName, programName, programName, programName);
    fflush(stdout);
}



void showDatabase(enum DatabaseType type)
{
    unsigned int i;
    switch (type) {
    case PokemonDB:
        fprintf(stdout, LIGHT "Pokemon database\n" RESET);
        for (i = 0; i < pkmnSpeciesCount; ++i) {
            fprintf(stdout, "(" LGREEN "%d" RESET ") %s\n", i, pkmnSpeciesStr[i]);
        }
        break;
    case ItemsDB:
        fprintf(stdout, LIGHT "Items database\n" RESET);
        for (i = 0; i < itemsCount; ++i) {
            fprintf(stdout, "(" LGREEN "%d" RESET ") %s\n", i, itemsStr[i]);
        }
        break;
    case DungeonDB:
        fprintf(stdout, LIGHT "Dungeons database\n" RESET);
        for (i = 0; i < dungeonsCount; ++i) {
            fprintf(stdout, "(" LGREEN "%d" RESET ") %s\n", i, dungeonsStr[i]);
        }
        break;
    case FriendAreaDB:
        fprintf(stdout, LIGHT "Friend areas database\n" RESET);
        for (i = 0; i < friendAreasCount; ++i) {
            fprintf(stdout, "(" LGREEN "%d" RESET ") %s\n", i, friendAreasStr[i]);
        }
        break;
    case MissionDB:
        fprintf(stdout, LIGHT "Mission types database\n" RESET);
        for (i = 0; i < missionTypeObjectiveCount; ++i) {
            fprintf(stdout, "(" LGREEN "%d" RESET ") %s\n", i, missionTypeObjectiveStr[i]);
        }
        break;
    case RewardTypeDB:
        fputs(LIGHT "Reward types database\n" RESET \
              "(" LGREEN "0" RESET ") Money\n" \
              "(" LGREEN "1" RESET ") Money + ?\n" \
              "(" LGREEN "2" RESET ") Item\n" \
              "(" LGREEN "3" RESET ") Item + ?\n" \
              "(" LGREEN "4" RESET ") Money\n" \
              "(" LGREEN "5" RESET ") Money + ?\n" \
              "(" LGREEN "6" RESET ") Item\n" \
              "(" LGREEN "7" RESET ") Item + ?\n" \
              "(" LGREEN "8" RESET ") Friend area\n", stdout);
        break;
    default:
        fprintf(stderr, LRED "ERROR:" RESET LIGHT " Invalid request\n" RESET);   /* this should never happen */
        break;
    }
}



int showSelectionScreen()
{
    fputs(LIGHT "What do you want to do?\n" \
          LGREEN  "1" RESET " - Decode a Wonder Mail\n" \
          LGREEN  "2" RESET " - Encode a Wonder Mail\n" \
          LGREEN  "3" RESET " - Decode a SOS Mail\n" \
          LGREEN  "4" RESET " - Encode a SOS Mail\n" \
          LGREEN  "5" RESET " - Convert a SOS Mail -> A-OK Mail -> Thank-You Mail\n"
          LGREEN  "6" RESET " - Show Help\n"
          LGREEN  "[Other]:" LRED " Exit\n" RESET, stdout);
    unsigned int selection;
    if (requestAndValidateIntegerInput(&selection, 0, 0, "") != NoError) {
        return 7; /* exit */
    } else {
        return selection;
    }
}



int requestWonderMailPassword(char *password)
{
    return requestAndValidateStringInput(password, 24, 0, NULL, LIGHT "Enter the Wonder Mail's password\n" RESET);
}



int requestAndParseWonderMailData(struct WonderMail *wm)
{
    unsigned int i = 0;
    unsigned int selection = -1; /* holds integers values */
    char stringInput[101]; /* holds strings values */
    char *stringEnd;
    int randomHolder;
    int mostSimilarIndex = 0;

    /* mission type */
    forever {
        fputs(LIGHT "Select the " LGREEN "type of mission" RESET LIGHT " (leave it blank for random).\n" RESET, stdout);
        for (i = 0; i < 5; ++i) {
            fprintf(stdout, LGREEN "%u" RESET " - ", i + 1);
            fprintf(stdout, missionTypeObjectiveStr[i], i == FindItem || i == DeliverItem ? "item" : "pokemon");
            fputc('\n', stdout);
        }
        if (requestAndValidateIntegerInput(&selection, 1, 1 + rand() % 5, "") != NoError) {
            continue;
        }
        --selection;
        if (selection < 5) { /* `selection` is unsigned so it's always >= 0 */
            break; /* input is ok */
        }
        fprintf(stderr, LRED "INPUT ERROR\n" RESET);
    }
    wm->missionType = selection;

    /* pokemon client */
    forever {
        do {
            randomHolder = rand() % pkmnSpeciesCount;
        } while (checkPkmnInWonderMail(randomHolder, 0) != NoError);
        if (requestAndValidateStringInput(stringInput, 100, 1, pkmnSpeciesStr[randomHolder], LIGHT "Enter the name (case sensitive) or room index of the " LGREEN "client pokemon" RESET LIGHT " (leave it blank for random).\n" RESET) != NoError) {
            continue;
        }
        selection = (unsigned int)strtol(stringInput, &stringEnd, 10);
        if (*stringEnd) { /* non-digit found */
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
        }

        if (checkPkmnInWonderMail(selection, 1) == NoError) {
            break; /* input is ok */
        }
    } /* forever */
    wm->pkmnClient = selection;

    /* pokemon target */
    if (wm->missionType == Find || wm->missionType == Escort) {
        forever {
            do {
                randomHolder = rand() % pkmnSpeciesCount;
            } while (checkPkmnInWonderMail(randomHolder, 0) != NoError);
            if (requestAndValidateStringInput(stringInput, 100, 1, pkmnSpeciesStr[randomHolder], LIGHT "Enter the name (case sensitive) or room index of the " LGREEN "target pokemon" RESET LIGHT " (leave it blank for random).\n" RESET) != NoError) {
                continue;
            }
            selection = (unsigned int)strtol(stringInput, &stringEnd, 10);
            if (*stringEnd) { /* non-digit found */
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
            }

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
        do {
            randomHolder = rand() % dungeonsCount;
        } while (checkDungeonInWonderMail(randomHolder, 0) != NoError);
        if (requestAndValidateStringInput(stringInput, 100, 1, dungeonsStr[randomHolder], LIGHT "Enter the name (case sensitive) or room index of the " LGREEN "dungeon" RESET LIGHT " (leave it blank for random).\n" RESET) != NoError) {
            continue;
        }
        selection = (unsigned int)strtol(stringInput, &stringEnd, 10);
        if (*stringEnd) { /* non-digit found */
            selection = dungeonsCount; /* invalid name, invalid index */
            for (i = 0; i < dungeonsCount; ++i) {
                if (strcmp(dungeonsStr[i], stringInput) == 0) {
                    selection = i;
                    break; /* item found */
                }
            }

            if (selection == dungeonsCount) {
                fprintf(stderr, LRED "ERROR:" RESET LIGHT " Cannot find dungeon " LGREEN "\"%s\"" RESET LIGHT " in the database.\n", stringInput);
                mostSimilarIndex = findMostSimilarStringInArray(stringInput, dungeonsStr, dungeonsCount);
                if (mostSimilarIndex == -1) {
                    fputs("Re-check your spelling.\n" RESET, stderr);
                } else {
                    fprintf(stderr, RESET LIGHT "Do you mean " LGREEN "\"%s\"" RESET LIGHT "?\n" RESET, dungeonsStr[mostSimilarIndex]);
                }
                continue;
            }
        }

        if (checkDungeonInWonderMail(selection, 1) == NoError) {
            break; /* input is ok */
        }
    } /* forever */
    wm->dungeon = selection;

    /* floor */
    forever {
        if (requestAndValidateIntegerInput(&selection, 1, 1 + rand() % difficulties[wm->dungeon][0], LIGHT "Enter the " LGREEN "floor" RESET LIGHT " (leave it blank for random).\n" RESET) == NoError && checkFloorForDungeon(selection, wm->dungeon, 1) == NoError) {
            break; /* input is ok */
        }
    } /* forever */
    wm->floor = selection;

    /* item to find/deliver */
    if (wm->missionType == FindItem || wm->missionType == DeliverItem) {
        forever {
            randomHolder = wm->missionType == FindItem ? (unsigned int)itemsInDungeons[wm->dungeon][1 + rand() % (itemsInDungeons[wm->dungeon][0] - 1)] : 1 + rand() % (itemsCount - 8);
            fprintf(stdout, LIGHT "Enter the name (case sensitive) or room index of the " LGREEN "item to %s" RESET LIGHT " (leave it blank for random).\n" RESET, wm->missionType == FindItem ? "find" : "deliver");
            if (requestAndValidateStringInput(stringInput, 100, 1, itemsStr[randomHolder], "") != NoError) {
                continue;
            }
            selection = (unsigned int)strtol(stringInput, &stringEnd, 10);
            if (*stringEnd) { /* non-digit found */
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
            }

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
        fputs(LIGHT "Select the " LGREEN "reward type" RESET LIGHT " (leave it blank for random).\n" RESET, stdout);
        for (i = 0; i < 5; ++i) {
            fprintf(stdout, LGREEN "%u" RESET " - ", i + 1);
            fputs(rewardTypesStr[i], stdout);
            fputc('\n', stdout);
        }
        if (requestAndValidateIntegerInput(&selection, 1, 1 + rand() % 5, "") != NoError) {
            continue;
        }
        --selection;
        if (selection < 5) { /* `selection` is unsigned so it's always >= 0 */
            break; /* input is ok */
        }
        fprintf(stderr, LRED "INPUT ERROR\n" RESET);
    } /* forever */
    wm->rewardType = rewardTypes[selection];

    /* reward item */
    if (wm->rewardType == Item || wm->rewardType == ItemItem || wm->rewardType == Item2 || wm->rewardType == ItemItem2 || wm->rewardType == MoneyItem || wm->rewardType == MoneyMoneyItem) {
        forever {
            randomHolder = 1 + rand() % (itemsCount - 1);
            if (requestAndValidateStringInput(stringInput, 100, 1, itemsStr[randomHolder], LIGHT "Enter the name (case sensitive) or room index of the " LGREEN "reward item" RESET LIGHT " (leave it blank for random).\n" RESET) != NoError) {
                continue;
            }
            selection = (unsigned int)strtol(stringInput, &stringEnd, 10);
            if (*stringEnd) { /* non-digit found */
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
            }

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
            fputs(LIGHT "Select the " LGREEN "friend area" RESET LIGHT " reward (leave it blank for random).\n" RESET, stdout);
            for (i = 0; i < 4; ++i) {
                fprintf(stdout, LGREEN "%u" RESET " - ", i + 1);
                fputs(friendAreasStr[availableFriendAreasIndexes[i]], stdout);
                fputc('\n', stdout);
            }
            if (requestAndValidateIntegerInput(&selection, 1, 1 + rand() % 4, "") != NoError) {
                continue;
            }
            --selection;
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
    return requestAndValidateStringInput(password, 54, 0, NULL, LIGHT "Enter the SOS Mail's password\n" RESET);
}



int requestAndParseSosMailData(struct SosMail *sos)
{
    unsigned int i = 0;
    unsigned int selection = -1;
    char stringInput[101];
    int randomHolder;
    char *stringEnd;
    int mostSimilarIndex = 0;

    /* mail type */
    const enum MailType mailTypes[] = { SosMailType, AOkMailType, ThankYouMailType };
    const char* mailTypesStr[] = { "SOS Mail", "A-Ok Mail", "Thank-You Mail" };
    forever {
        fputs(LIGHT "Select the " LGREEN "type of mail" RESET LIGHT ".\n" RESET, stdout);
        for (i = 0; i < 3; ++i) {
            fprintf(stdout, LGREEN "%u" RESET " - ", i + 1);
            fputs(mailTypesStr[i], stdout);
            fputc('\n', stdout);
        }
        if (requestAndValidateIntegerInput(&selection, 0, 0, "") == NoError) {
            --selection;
            if (selection < 3) { /* as `selection` is unsigned, it is always >= 0 */
                break; /* input is ok */
            }
        }
        fprintf(stderr, LRED "INPUT ERROR\n" RESET);
    }
    sos->mailType = mailTypes[selection];

    /* pokemon to rescue */
    forever {
        if (requestAndValidateStringInput(stringInput, 100, 1, pkmnSpeciesStr[rand() % pkmnSpeciesCount], LIGHT "Enter the name (case sensitive) or room index of the " LGREEN "pokemon to rescue" RESET LIGHT " (leave it blank for random).\n" RESET) != NoError) {
            continue;
        }
        selection = (unsigned int)strtol(stringInput, &stringEnd, 10);
        if (*stringEnd) { /* non-digit found */
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
        }

        if (checkPkmnInSosMail(selection, 1) == NoError) {
            break; /* input is ok */
        }
    } /* forever */
    sos->pkmnToRescue = selection;

    /* nickname */
    forever {
        if (requestAndValidateStringInput(stringInput, 10, 1, pkmnSpeciesStr[sos->pkmnToRescue], LIGHT "Enter the " LGREEN "nickname" RESET LIGHT " of that pokemon (leave it blank for none).\n" RESET) == NoError) {
            break;
        }        
    } /* forever */
    strncpy(sos->pkmnNick, stringInput, 10);

    /* dungeon */
    forever {
        do {
            randomHolder = rand() % dungeonsCount;
        } while (checkDungeonInSosMail(randomHolder, 0) != NoError);
        if (requestAndValidateStringInput(stringInput, 100, 1, dungeonsStr[randomHolder], LIGHT "Enter the name (case sensitive) or room index of the " LGREEN "dungeon" RESET LIGHT " (leave it blank for random).\n" RESET) != NoError) {
            continue;
        }
        selection = (unsigned int)strtol(stringInput, &stringEnd, 10);
        if (*stringEnd) { /* non-digit found */
            selection = dungeonsCount; /* invalid name, invalid index */
            for (i = 0; i < dungeonsCount; ++i) {
                if (strcmp(dungeonsStr[i], stringInput) == 0) {
                    selection = i;
                    break; /* item found */
                }
            }

            if (selection == dungeonsCount) {
                fprintf(stderr, LRED "ERROR:" RESET LIGHT " Cannot find dungeon " LGREEN "\"%s\"" RESET LIGHT " in the database.\n", stringInput);
                mostSimilarIndex = findMostSimilarStringInArray(stringInput, dungeonsStr, dungeonsCount);
                if (mostSimilarIndex == -1) {
                    fputs("Re-check your spelling.\n" RESET, stderr);
                } else {
                    fprintf(stderr, RESET LIGHT "Do you mean " LGREEN "\"%s\"" RESET LIGHT "?\n" RESET, dungeonsStr[mostSimilarIndex]);
                }
                continue;
            }
        }

        if (checkDungeonInWonderMail(selection, 1) == NoError) {
            break; /* input is ok */
        }
    } /* forever */
    sos->dungeon = selection;

    /* floor */
    forever {
        if (requestAndValidateIntegerInput(&selection, 1, 1 + rand() % difficulties[sos->dungeon][0], LIGHT "Enter the " LGREEN "floor" RESET LIGHT " (leave it blank for random).\n" RESET) == NoError && checkFloorForDungeon(selection, sos->dungeon, 1) == NoError) {
            break; /* input is ok */
        }
    }
    sos->floor = selection;

    /* reward item */
    if (sos->mailType == ThankYouMailType) {
        forever {
            randomHolder = 1 + rand() % (itemsCount - 1);
            if (requestAndValidateStringInput(stringInput, 100, 1, itemsStr[randomHolder], LIGHT "Enter the name (case sensitive) or room index of the " LGREEN "reward item" RESET LIGHT " (type \"" LGREEN "0" RESET LIGHT "\" or \"" LGREEN "Nothing" RESET LIGHT "\" for no reward, or leave it blank for random).\n" RESET) != NoError) {
                continue;
            }
            selection = (unsigned int)strtol(stringInput, &stringEnd, 10);
            if (*stringEnd) { /* non-digit found */
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
            }

            if (selection == 0 || checkItemRange(selection, 1) == NoError) {
                break; /* input is ok */
            }
        } /* forever */
        sos->itemReward = selection;
    } else {
        sos->itemReward = rand() % itemsCount; /* ignored if not thank-u mail */
    }

    /* mail ID */
    forever {
        if (requestAndValidateIntegerInput(&selection, 1, rand() % 10000, LIGHT "Enter the " LGREEN "Mail ID" RESET LIGHT " (0 to 9999, leave blank for random).\n" RESET) == NoError && checkMailID(selection, 0) == NoError) {
            break; /* input is ok */
        }
    }
    sos->mailID = selection;

    /* Chances left */
    unsigned int minChancesLeft = sos->mailType == SosMailType ? 1  : 0;
    unsigned int maxChancesLeft = sos->mailType == SosMailType ? 10 : 9;
    forever {
        fprintf(stdout, LIGHT "Enter the number of " LGREEN "chances left" RESET LIGHT " (%d to %d, leave blank for %d).\n" RESET, minChancesLeft, maxChancesLeft, maxChancesLeft);
        if (requestAndValidateIntegerInput(&selection, 1, maxChancesLeft, "") == NoError && selection >= minChancesLeft && selection <= maxChancesLeft) {
            break; /* input is ok */
        }
    }
    sos->chancesLeft = selection;

    return NoError;
}



int requestAndParseSOSMailConvertion(char *password, int *item)
{
    if (requestAndValidateStringInput(password, 54, 0, NULL, LIGHT "Enter the SOS, A-OK or Thank-You Mail's " LGREEN "password" RESET LIGHT " (54 characters)\n" RESET) != NoError) {
        return InputError;
    }

    unsigned int i = 0;
    unsigned int selection = -1;
    char stringInput[101];
    int randomHolder;
    char *stringEnd;
    int mostSimilarIndex = 0;

    forever {
        randomHolder = 1 + rand() % (itemsCount - 1);
        if (requestAndValidateStringInput(stringInput, 100, 1, itemsStr[randomHolder], LIGHT "Enter the name (case sensitive) or room index of the " LGREEN "reward item for the Thank-You mail" RESET LIGHT " (type \"" LGREEN "0" RESET LIGHT "\" or \"" LGREEN "Nothing" RESET LIGHT "\" for no reward, or leave it blank for random).\n" RESET) != NoError) {
            continue;
        }
        selection = (unsigned int)strtol(stringInput, &stringEnd, 10);
        if (*stringEnd) { /* non-digit found */
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
        }

        if (selection == 0 || checkItemRange(selection, 1) == NoError) {
            break; /* input is ok */
        }
    } /* forever */
    *item = selection;
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
    char newReward[106] = {0};
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
    char* friendAreaReward = strstr(newReward, friendAreasStr[mail->friendAreaReward]);

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
    
    if (friendAreaReward) {
        strcpy(hold, friendAreaReward);
        strcpy(friendAreaReward, COLOR_GREEN);
        strncat(newReward, hold, strlen(friendAreasStr[mail->friendAreaReward]));
        strcat(newReward, RESET COLOR_BACKGROUND);
        strcat(newReward, hold + strlen(friendAreasStr[mail->friendAreaReward]));
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

    fprintf(stdout, COLOR_BORDER COLOR_BACKGROUND "**********************************************" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " RESET WHITE COLOR_BACKGROUND UNDERLINE "%-56s" RESET COLOR_BACKGROUND COLOR_BORDER " *" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " COLOR_BORDER "%-43s*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " RESET COLOR_BACKGROUND "%-81s" COLOR_BORDER COLOR_BACKGROUND "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " RESET COLOR_BACKGROUND "%-81s" COLOR_BORDER COLOR_BACKGROUND "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " COLOR_BORDER "%-43s*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Client:     " RESET COLOR_BACKGROUND "%-31s" COLOR_BORDER "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Objective:  " RESET COLOR_BACKGROUND "%-69s" COLOR_BORDER "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Place:      " RESET COLOR_BACKGROUND "%-107s" COLOR_BORDER "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Difficulty: " RESET COLOR_BACKGROUND "%s%c%-30s" COLOR_BORDER "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Reward:     " RESET COLOR_BACKGROUND "%-107s" COLOR_BORDER "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Password:   " RESET COLOR_BACKGROUND "%s" COLOR_YELLOW "%s" RESET COLOR_BACKGROUND "%-23s" COLOR_BORDER COLOR_BACKGROUND "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " RESET COLOR_BACKGROUND "            %s" COLOR_YELLOW "%s" RESET COLOR_BACKGROUND "%-23s" COLOR_BORDER COLOR_BACKGROUND "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "**********************************************" RESET "\n",
            newHead, "", newBody1, newBody2, "", mailInfo->client, newObjective, placeAndFloor, diffColor, mailInfo->difficulty, "", newReward, temp, temp + 5, temp + 10, temp + 15, temp + 20, temp + 25);
}


void printSOSData(const struct SosMailInfo *mailInfo, const struct SosMail *mail)
{
    char newClient[70]  = {0};
    char newPlace[76]   = {0};
    char newFloor[57]   = {0};
    char newReward[106] = {0};
    sprintf(newClient, "%s " COLOR_GREEN "(%s)" RESET COLOR_BACKGROUND, mailInfo->nickname, mailInfo->client);
    strcpy(newPlace, mailInfo->place);
    strcpy(newFloor, mailInfo->floor);
    strcpy(newReward, mailInfo->reward);
    char* dungeonPlace = strstr(newPlace, dungeonsStr[mail->dungeon]);
    char floorStr[3];
    sprintf(floorStr, "%d", mail->floor % 100);
    char* dungeonFloor = strstr(newFloor, floorStr);
    char* itemReward = strstr(newReward, itemsStr[mail->itemReward]);

    char hold[200] = {0};

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
    
    if (itemReward) {
        strcpy(hold, itemReward);
        strcpy(itemReward, COLOR_GREEN);
        strncat(newReward, hold, strlen(itemsStr[mail->itemReward]));
        strcat(newReward, RESET COLOR_BACKGROUND);
        strcat(newReward, hold + strlen(itemsStr[mail->itemReward]));
    } else {
        strcat(newReward, COLOR_GREEN RESET COLOR_BACKGROUND);
    }

    char placeAndFloor[120] = {0};
    sprintf(placeAndFloor, "%s  %s", newPlace, newFloor);

    char diffColor[50] = {0};
    strcpy(diffColor, mailInfo->difficulty == 'E' ? RESET COLOR_BACKGROUND : mailInfo->difficulty == 'D' || mailInfo->difficulty == 'C' ? COLOR_GREEN : mailInfo->difficulty == 'B' || mailInfo->difficulty == 'A' ? COLOR_CYAN : mailInfo->difficulty == 'S' ? COLOR_RED : LYELLOW);

    int i, j;
    char temp[70] = {0};
    for (i = j = 0; i < 54; ++i) {
        if (i ==  5 || i == 13 || i == 18 ||
            i == 23 || i == 31 || i == 36 ||
            i == 41 || i == 49) {
            temp[i + j++] = '\0';
        }
        temp[i + j] = mailInfo->password[i];
    }

    fprintf(stdout, COLOR_BORDER COLOR_BACKGROUND "************************************************" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " RESET WHITE COLOR_BACKGROUND UNDERLINE "%-44s" RESET COLOR_BACKGROUND COLOR_BORDER " *" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " COLOR_BORDER "%-45s*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " RESET COLOR_BACKGROUND "%-45s" COLOR_BORDER COLOR_BACKGROUND "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " COLOR_BORDER "%-45s*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Client:       " RESET COLOR_BACKGROUND "%-69s" COLOR_BORDER COLOR_BACKGROUND "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Objective:    " RESET COLOR_BACKGROUND "%-31s" COLOR_BORDER "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Place:        " RESET COLOR_BACKGROUND "%-107s" COLOR_BORDER "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Difficulty:   " RESET COLOR_BACKGROUND "%s%c%-30s" COLOR_BORDER "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Reward:       " RESET COLOR_BACKGROUND "%-69s" COLOR_BORDER "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "ID:           " RESET COLOR_BACKGROUND "%-31s" COLOR_BORDER "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "%s" WHITE COLOR_BACKGROUND "%s"             RESET COLOR_BACKGROUND "%-31s" COLOR_BORDER "%s" RESET "%s"
                    COLOR_BORDER COLOR_BACKGROUND "* " WHITE COLOR_BACKGROUND "Password:     " RESET COLOR_BACKGROUND "%s" COLOR_YELLOW "%s" RESET COLOR_BACKGROUND "%-18s" COLOR_BORDER COLOR_BACKGROUND "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " RESET COLOR_BACKGROUND "              %s" COLOR_YELLOW "%s" RESET COLOR_BACKGROUND "%-18s" COLOR_BORDER COLOR_BACKGROUND "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "* " RESET COLOR_BACKGROUND "              %s" COLOR_YELLOW "%s" RESET COLOR_BACKGROUND "%-18s" COLOR_BORDER COLOR_BACKGROUND "*" RESET "\n"
                    COLOR_BORDER COLOR_BACKGROUND "************************************************" RESET "\n",
            mailInfo->head, "", mailInfo->body, "", newClient, mailInfo->objective, placeAndFloor, diffColor, mailInfo->difficulty, "", newReward, mailInfo->id, mail->mailType == SosMailType ? "* " : "\r", mail->mailType == SosMailType ? "Chances left: " : "\r", mail->mailType == SosMailType ? mailInfo->chancesLeft : "\r", mail->mailType == SosMailType ? "*" : "\r", mail->mailType == SosMailType ? "\n" : "\r", temp, temp + 6, temp + 15, temp + 21, temp + 27, temp + 36, temp + 42, temp + 48, temp + 57);
}



int checkPkmnInWonderMail(int index, int printErrorMessages)
{
    /* pkmn check (limits) */
    if (index <= 0 || (unsigned int)index >= pkmnSpeciesCount) {
        if (printErrorMessages) {
            fprintf(stderr, LRED "ERROR:" RESET LIGHT " Pkmn must be numbers between 1 and %d (not necessarily match pkdex numbers).\n"
                            "       Current value: " LRED "%u" RESET LIGHT " [" LRED "INVALID" RESET LIGHT "]\n\n" RESET, pkmnSpeciesCount - 1, index);
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
                            "       Current value: " LRED "%u" RESET LIGHT " [" LRED "%s" RESET LIGHT "]\n\n" RESET, index, pkmnSpeciesStr[index]);
        }
        return InputError;
    }

    return NoError;
}



int checkPkmnInSosMail(int index, int printErrorMessages)
{
    /* pkmn check (limits) */
    if (index <= 0 || (unsigned int)index >= pkmnSpeciesCount) {
        if (printErrorMessages) {
            fprintf(stderr, LRED "ERROR:" RESET LIGHT " Pkmn must be numbers between 1 and %d (not necessarily match pkdex numbers).\n"
                            "       Current value: " LRED "%u" RESET LIGHT " [" LRED "INVALID" RESET LIGHT "]\n\n" RESET, pkmnSpeciesCount - 1, index);
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
                            "       Current value: " LRED "%u" RESET LIGHT " [" LRED "INVALID" RESET LIGHT "]\n\n" RESET, dungeonsCount - 1, index);
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



int checkDungeonInSosMail(int index, int printErrorMessages)
{
    /* it's actually the same checking for all kinds of mails */
    return checkDungeonInWonderMail(index, printErrorMessages);
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
                            "       Current value: " LRED "%u" RESET LIGHT " [" LRED "INVALID" RESET LIGHT "]\n\n" RESET, (itemsCount - 9), index);
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
                            "       Current value: " LRED "%u" RESET LIGHT " [" LRED "INVALID" RESET LIGHT "]\n\n" RESET, itemsCount - 1, index);
        }
        return InputError;
    }

    return NoError;
}



int checkMailID(int mailID, int printErrorMessages)
{
    /* item check (limits) */
    if (mailID < 0 || mailID > 10000) {
        if (printErrorMessages) {
            fprintf(stderr, LRED "ERROR:" RESET LIGHT " The mail ID must be a non-negative number with no more than 4 digits (0 to 9999).\n"
                            "       Current value: " LRED "%u" RESET "\n\n", mailID);
        }
        return InputError;
    }

    return NoError;
}



int requestAndValidateIntegerInput(unsigned int *n, int allowEmptyValue, int valueIfEmpty, const char* message)
{
#define MAX_LENGTH_INPUT 20
    char *stringEnd;
    fputs(message, stdout);
    fputs(">>> " LGREEN, stdout);
    fflush(stdout);
    char stringInput[MAX_LENGTH_INPUT + 1];
    (void)!fgets(stringInput, MAX_LENGTH_INPUT, stdin);
    if (stringInput[strlen(stringInput) - 1] == '\n') {
        stringInput[strlen(stringInput) - 1] = '\0';
    }
    if (strlen(stringInput) == 0) {
        if (allowEmptyValue) {
            *n = valueIfEmpty;
            fprintf(stdout, "%u\n", valueIfEmpty);
            return NoError;
        } else {
            return InputError;
        }
    } else {
        errno = 0; /* strtol modifies `errno` if the input is too big to be stored in a `long int` */
        *n = (unsigned int)strtol(stringInput, &stringEnd, 10);
        if (*stringEnd || errno) {
            fprintf(stderr, LRED "ERROR:" RESET LIGHT " Invalid input. %s.\n\n" RESET, errno ? strerror(errno) : "Only positive numbers are allowed");
            return InputError;
        }
        return NoError;
    }
#undef MAX_LENGTH_INPUT
}

int requestAndValidateStringInput(char* str, unsigned int maxLength, int allowEmptyValue, const char* valueIfEmpty, const char* message)
{
#define MAX_LENGTH_INPUT 100 /* if `maxLength` is bigger the behavior is undefined */
    fputs(message, stdout);
    fputs(">>> " LGREEN, stdout);
    fflush(stdout);
    char stringInput[MAX_LENGTH_INPUT + 1];
    (void)!fgets(stringInput, MAX_LENGTH_INPUT, stdin);
    if (stringInput[strlen(stringInput) - 1] == '\n') {
        stringInput[strlen(stringInput) - 1] = '\0';
    }
    strncpy(str, stringInput, maxLength);
    if (strlen(stringInput) > maxLength) {
        fprintf(stderr, LYELLOW "WARNING:" RESET " The input (" LRED "%s" RESET ") is bigger than %d characters, so it has been truncated to " LGREEN "%s" RESET ".\n" LGREEN, stringInput, maxLength, str);
    }
    
    if (strlen(stringInput) == 0 && !allowEmptyValue) {
        return InputError;
    } else if (strlen(stringInput) == 0) {
        strncpy(str, valueIfEmpty, maxLength);
        fprintf(stdout, "%s\n", str);
    }

    return NoError;
#undef MAX_LENGTH_INPUT
}

#undef forever
#undef DISCLAIMER
