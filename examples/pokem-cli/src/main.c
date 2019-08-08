#include "application/application.h"
#include "view/view.h"

#include <stdio.h>

int autodetect(int argc, const char *argv[]);

int main(int argc, const char *argv[])
{
    /* Copyright notice */
    fputs("PokeM v0.1   Copyright 2018-2019 Carlos Enrique Perez Sanchez.\n"
          "Based on the tools written by Peter O.\n"
          ".................................................................\n", stdout);

    if (argc == 1) { /* no input */
        showGeneralHelp(argv[0]);
        fflush(stdout);
        return 0;
    }

    int selection;
    int autodetectResult = autodetect(argc, argv);
    if (autodetectResult == -1) {
        selection = showSelectionScreen();
        switch (selection) {
        case 1:
            return decodeWM(argc, argv);
        case 2:
            return encodeWM(argc, argv);
        case 3:
            return decodeSOSM(argc, argv);
        case 4:
            return encodeSOSM(argc, argv);
        case 5:
            return convertSOS(argc, argv);
        default:
            fputs("Exiting...\n", stdout);
        }
    } else {
        return autodetectResult;
    }

    fflush(stdout);
    return 0;
}


int autodetect(int argc, const char *argv[])
{
    /* this should never happen. Check to avoid segmentation fault while acceding argv */
    if (argc == 1) {
        return -1;
    }

    size_t lenghtArg1 = strlen(argv[1]);
    if (argc == 2 && lenghtArg1 >= 20 && lenghtArg1 <= 28) {
        return decodeWM(argc, argv);
    } else if (argc == 2 && lenghtArg1 >= 48 && lenghtArg1 <= 56) {
        return -1; /* what do you want? decode or convert? */
    } else if (argc == 10) {
        return encodeWM(argc, argv);
    } else if (argc == 7) {
        return encodeSOSM(argc, argv);
    } else {
        return -1; /* failed to autodetect */
    }
}
