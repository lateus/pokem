#include "application/application.h"
#include "view/view.h"
#include "utils/colors.h"
#include "utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROGRAM_STRING "PokeM"
#define VERSION_STRING "0.1"

extern int printMessages;

int autodetect(int argc, const char *argv[]);
void printDatabaseMenu();
int requestItem();
int requestDungeon();
int requestGame();

int main(int argc, const char *argv[])
{
    printMessages = 1; /* enable messages */

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    system("title " PROGRAM_STRING " v" VERSION_STRING);
#endif

    /* Copyright notice */
    fputs(LIGHT PROGRAM_STRING RESET DRED " v" VERSION_STRING DGREEN "   Copyright 2018-2020 Carlos Enrique Perez Sanchez.\n"
          RESET "Based on the tools written by Peter O.\n"
          "..............................................................\n", stdout);
    fflush(stdout);

    int i; /* iterations */

    /* Basics command line options */
    const char* databaseTypesStr[] = { "pokemon", "items", "dungeons", "areas", "missions", "rewards", "mails" };
    if (argc > 1 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
        showHelp(argv[0]);
        return 0;
    } else if (argc > 1 && (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version"))) {
        fputs(VERSION_STRING "\n", stdout);
        return 0;
    } else if (argc > 1 && (!strcmp(argv[1], "-d") || !strcmp(argv[1], "--database"))) {
        if (argc <= 2) {
            fprintf(stderr, LRED "ERROR:" RESET LIGHT " Missing argument.\n" RESET \
                       "       Expected type [pokemon|items|dungeons|areas|missions|rewards|mails]\n" \
                       "       Example: " LGREEN "%s --database pokemon\n" RESET, argv[0]);
            return InputError;
        } else {
            for (i = 0; i < 7; ++i) {
                if (!strcmp(argv[2], databaseTypesStr[i])) {
                    showDatabase(i);
                    return 0;
                }
            }
            fprintf(stderr, LRED "ERROR:" RESET LIGHT " Unknown database type " LGREEN "%s" RESET LIGHT ".\n" RESET \
                                 "       Available types: [pokemon|items|dungeons|areas|missions|rewards|mails]\n", argv[2]);
            return InputError;
        }
    }

    /* A seed to generate random numbers */
    srand((unsigned int)time(NULL));

    int selection, result = 0, item = 0, dungeon = 0, game = 0;
    int autodetectResult = autodetect(argc, argv);
    if (autodetectResult == -1) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        (void)result;
        for (;;) {
#endif
            selection = showSelectionScreen();
            switch (selection) {
            case 1:
                result = decodeWM(0, NULL);
                break;
            case 2:
                result = encodeWM(0, NULL);
                break;
            case 3:
                result = decodeSOSM(0, NULL);
                break;
            case 4:
                result = encodeSOSM(0, NULL);
                break;
            case 5:
                result = convertSOS(0, NULL);
                break;
            case 6:
                item = requestItem();
                generateMassiveItemMissions(2, item, 8);
                break;
            case 7:
                dungeon = requestDungeon();
                item = requestItem();
                generateMassiveHighRankMissions(dungeon, item, 8);
                break;
            case 8:
                game = requestGame();
                unlockExclusivePokemon(game);
                break;
            case 9:
                unlockDungeons(game);
                break;
            case 10:
                printDatabaseMenu();
                if (requestAndValidateIntegerInput((unsigned int*)&selection, 0, 0, "") != NoError) {
                    break;
                }
                showDatabase(selection - 1);
                break;
            case 11:
                showHelp(argv[0]);
                break;
            default:
                fputs("Exiting...\n", stdout);
                return 0;
            }
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
            fputc('\n', stdout);
        }
#else
        return result;
#endif
    } else {
        return autodetectResult;
    }

    fflush(stdout);
    return 0;
}


int autodetect(int argc, const char *argv[])
{
    /* no input */
    if (argc <= 1) {
        return -1;
    }

    size_t lenghtArg1 = strlen(argv[1]);
    size_t lenghtArg2 = argc >= 3 ? strlen(argv[2]) : 0;
    fprintf(stdout, "Autodetected: ");
    if (lenghtArg1 >= 20 && lenghtArg1 <= 28) {
        fprintf(stdout, "Decode WM\n\n");
        return decodeWM(argc, argv);
    } else if (lenghtArg1 >= 48 && lenghtArg1 <= 56 && lenghtArg2 > 0 && lenghtArg2 <= 16) {
        fprintf(stdout, "Convert SOS\n\n");
        return convertSOS(argc, argv);
    } else if (lenghtArg1 >= 48 && lenghtArg1 <= 56) {
        fprintf(stdout, "Decode SOS\n\n");
        return decodeSOSM(argc, argv);
    } else if (argc == 10) {
        fprintf(stdout, "Encode WM\n\n");
        return encodeWM(argc, argv);
    } else if (argc == 8) {
        fprintf(stdout, "Encode SOS\n\n");
        return encodeSOSM(argc, argv);
    } else {
        fprintf(stdout, "Nothing.\n\n");
        return -1; /* failed to autodetect */
    }
}

void printDatabaseMenu()
{
    fputs(LIGHT "What kind of database?\n" \
          LGREEN  "1" RESET " - Pokemon\n" \
          LGREEN  "2" RESET " - Items\n" \
          LGREEN  "3" RESET " - Dungeons\n" \
          LGREEN  "4" RESET " - Friend areas\n" \
          LGREEN  "5" RESET " - Mission types\n"
          LGREEN  "6" RESET " - Reward types\n"
          LGREEN  "7" RESET " - SOS Mail types\n"
          LGREEN  "[Other]:" LRED " Cancel\n" RESET, stdout);
    fflush(stdout);
}

int requestItem()
{
    unsigned int i = 0;
    unsigned int selection = -1; /* holds integers values */
    char stringInput[101]; /* holds strings values */
    char *stringEnd;
    int randomHolder;
    int mostSimilarIndex = 0;

    for (;;) {
        randomHolder = 1 + rand() % (itemsCount - 1);
        if (requestAndValidateStringInput(stringInput, 100, 1, itemsStr[randomHolder], LIGHT "Enter the name or room index of the " LGREEN "reward item" RESET LIGHT " (leave it blank for random).\n" RESET) != NoError) {
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
                mostSimilarIndex = findMostSimilarStringInArray(stringInput, itemsStr, itemsCount);
                if (mostSimilarIndex == -1) {
                    fprintf(stderr, LRED "ERROR:" RESET LIGHT " Cannot find item " LGREEN "\"%s\"" RESET LIGHT " in the database.\n", stringInput);
                    fputs("Re-check your spelling.\n" RESET, stderr);
                    continue;
                } else {
                    selection = mostSimilarIndex;
                    fprintf(stderr, LGREEN "%s" RESET LIGHT " has been assumed.\n" RESET, itemsStr[mostSimilarIndex]);
                }
            }
        } else {
            fprintf(stdout, RESET "(%s" "%d" RESET ") %s\n", selection < itemsCount ? LGREEN : LRED, selection, selection < itemsCount ? itemsStr[selection] : LRED "[INVALID]" RESET);
        }

        if (checkItemRange(selection, 1) == NoError) {
            break; /* input is ok */
        }
    } /* for (;;) */
    return selection;
}

int requestDungeon()
{
    unsigned int i = 0;
    unsigned int selection = -1; /* holds integers values */
    char stringInput[101]; /* holds strings values */
    char *stringEnd;
    int randomHolder;
    int mostSimilarIndex = 0;

    for (;;) {
        do {
            randomHolder = rand() % dungeonsCount;
        } while (checkDungeonInWonderMail(randomHolder, 0) != NoError);
        if (requestAndValidateStringInput(stringInput, 100, 1, dungeonsStr[randomHolder], LIGHT "Enter the name or room index of the " LGREEN "dungeon" RESET LIGHT " (leave it blank for random).\n" RESET) != NoError) {
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
                mostSimilarIndex = findMostSimilarStringInArray(stringInput, dungeonsStr, dungeonsCount);
                if (mostSimilarIndex == -1) {
                    fprintf(stderr, LRED "ERROR:" RESET LIGHT " Cannot find dungeon " LGREEN "\"%s\"" RESET LIGHT " in the database.\n", stringInput);
                    fputs("Re-check your spelling.\n" RESET, stderr);
                    continue;
                } else {
                    selection = mostSimilarIndex;
                    fprintf(stderr, LGREEN "%s" RESET LIGHT " has been assumed.\n" RESET, dungeonsStr[mostSimilarIndex]);
                }
            }
        } else {
            fprintf(stdout, RESET "(%s" "%d" RESET ") %s\n", selection < dungeonsCount ? LGREEN : LRED, selection, selection < dungeonsCount ? dungeonsStr[selection] : LRED "[INVALID]" RESET);
        }

        if (checkDungeonInWonderMail(selection, 1) == NoError) {
            break; /* input is ok */
        }
    } /* for (;;) */
    return selection;
}

int requestGame()
{
    int selection;
    const char* gamesTypesStr[] = { "Red Rescue Team", "Blue Rescue Team" };
    int i;
    for (;;) {
        fputs(LIGHT "Select the " LGREEN "game type" RESET LIGHT ".\n" RESET, stdout);
        for (i = 0; i < 2; ++i) {
            fprintf(stdout, LGREEN "%u" RESET " - %s\n", i + 1, gamesTypesStr[i]);
        }
        if (requestAndValidateIntegerInput((unsigned int*)&selection, 0, 0, "") != NoError) {
            continue;
        }
        --selection;
        if (selection < 5) { /* `selection` is unsigned so it's always >= 0 */
            break; /* input is ok */
        }
        fprintf(stderr, LRED "INPUT ERROR\n" RESET);
    } /* forever */
    return selection;
}