#include "application/application.h"
#include "view/view.h"
#include "utils/colors.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int autodetect(int argc, const char *argv[]);

int main(int argc, const char *argv[])
{
    /* Copyright notice */
    fputs(LIGHT "PokeM " RESET DRED "v0.1" DGREEN "   Copyright 2018-2019 Carlos Enrique Perez Sanchez.\n"
          RESET "Based on the tools written by Peter O.\n"
          ".................................................................\n", stdout);
    fflush(stdout);

    /* A seed to generate random numbers */
    srand((unsigned int)time(NULL));

    int selection;
    int autodetectResult = autodetect(argc, argv);
    if (autodetectResult == -1) {
        selection = showSelectionScreen();
        switch (selection) {
        case 1:
            return decodeWM(0, NULL);
        case 2:
            return encodeWM(0, NULL);
        case 3:
            return decodeSOSM(0, NULL);
        case 4:
            return encodeSOSM(0, NULL);
        case 5:
            return convertSOS(0, NULL);
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
    } else if (lenghtArg1 >= 48 && lenghtArg1 <= 56 && lenghtArg2 <= 16) {
        fprintf(stdout, "Convert SOS\n\n");
        return convertSOS(argc, argv);
    } else if (lenghtArg1 >= 48 && lenghtArg1 <= 56) {
        fprintf(stdout, "Decode SOS\n\n");
        return decodeSOSM(argc, argv);
    } else if (argc == 10) {
        fprintf(stdout, "Encode WM\n\n");
        return encodeWM(argc, argv);
    } else if (argc == 7) {
        fprintf(stdout, "Encode SOS\n\n");
        return encodeSOSM(argc, argv);
    } else {
        fprintf(stdout, "Nothing.\n\n");
        return -1; /* failed to autodetect */
    }
}