#include "application/application.h"
#include "view/view.h"
#include "utils/colors.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROGRAM_STRING "PokeM"
#define VERSION_STRING "0.1"

extern int printMessages;

int autodetect(int argc, const char *argv[]);

int main(int argc, const char *argv[])
{
    printMessages = 1; /* enable messages */

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    system("title " PROGRAM_STRING " v" VERSION_STRING);
#endif

    /* Copyright notice */
    fputs(LIGHT PROGRAM_STRING RESET DRED " v" VERSION_STRING DGREEN "   Copyright 2018-2020 Carlos Enrique Perez Sanchez.\n"
          RESET "Based on the tools written by Peter O.\n"
          ".................................................................\n", stdout);
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

    int selection, result = 0;
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
                fputs(LIGHT "What kind of database?\n" \
                      LGREEN  "1" RESET " - Pokemon\n" \
                      LGREEN  "2" RESET " - Items\n" \
                      LGREEN  "3" RESET " - Dungeons\n" \
                      LGREEN  "4" RESET " - Friend areas\n" \
                      LGREEN  "5" RESET " - Mission types\n"
                      LGREEN  "6" RESET " - Reward types\n"
                      LGREEN  "7" RESET " - SOS Mail types\n"
                      LGREEN  "[Other]:" LRED " Cancel\n" RESET, stdout);
                if (requestAndValidateIntegerInput((unsigned int*)&selection, 0, 0, "") != NoError) {
                    break;
                }
                showDatabase(selection - 1);
                break;
            case 7:
                showHelp(argv[0]);
                break;
            default:
                fputs("Exiting...\n", stdout);
                return 0;
            }
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
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