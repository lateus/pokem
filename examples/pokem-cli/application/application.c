#include "../include/application.h"
#include "../include/decode_encode/decode/dec_wm.h"
#include "../include/decode_encode/decode/dec_sos.h"
#include "../include/decode_encode/encode/enc_wm.h"
#include "../include/decode_encode/encode/enc_sos.h"

#include <stdlib.h>

int decodeWM(int argc, const char *argv[]) /* The passwords are received here: in argv */
{
    if (argc == 1) {
        return showHelpDecodingWM(argv[0]); /* No arguments specified. */
    }

    struct WM_INFO mailInfo  = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0} }; /* The 8th element is a char */
    /* This loop will allow to decode all entered wonder mails one by one. */
    int errorCode;
    errorCode = decodeWonderMail(argv[1], &mailInfo);
    if (errorCode) {
        return errorCode;
    }

    printWMData(&mailInfo);   /* Finally, print the wonder mail info */
    fflush(stdout);

    return 0;
}


int encodeWM(int argc, const char *argv[])
{
    if (argc != 10) {
        return showHelpEncodingWM(argv[0]);
    }

    struct WONDERMAIL wm;
    parseWMData(argv, &wm);
    char finalPassword[25] = {0};
    int errorCode = encodeWonderMail(&wm, finalPassword);
    if (errorCode) {
        return errorCode;
    }

    fprintf(stdout, "Password: %s\n", finalPassword);
    fflush(stdout);

    return 0;
}



void parseWMData(const char *argv[], struct WONDERMAIL *wm)
{
    wm->mailType         = 5; /* Wonder Mail */
    wm->missionType      = (unsigned int)atoi(argv[1]);
    wm->pkmnClient       = (unsigned int)atoi(argv[2]);
    wm->pkmnTarget       = (wm->missionType == FIND || wm->missionType == ESCORT) ? (unsigned int)atoi(argv[3]) : wm->pkmnClient;
    wm->itemDeliverFind  = (wm->missionType == FINDITEM || wm->missionType == DELIVERITEM) ? (unsigned int)atoi(argv[4]) : 9;
    wm->dungeon          = (unsigned int)atoi(argv[5]);
    wm->floor            = (unsigned int)atoi(argv[6]);
    wm->rewardType       = (unsigned int)atoi(argv[7]);
    wm->itemReward       = (unsigned int)atoi(argv[8]);
    wm->friendAreaReward = (wm->rewardType == 9) ? (unsigned int)atoi(argv[9]) : 0;
}



int decodeSOSM(int argc, const char *argv[])
{
    if (argc == 1) {
        return showHelpDecodingSOS(argv[0]);   /* No arguments specified. The value of the macro HELP is returned. */
    }
    struct SOS_INFO sosInfo  = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0}, {0}, {0} }; /* The 8th element is a char */
    int errorCode;
    errorCode = decodeSOSMail(argv[1], &sosInfo);
    if (errorCode) {
        return errorCode;
    }
    printSOSData(&sosInfo); /* Finally, print the sos mail info */

    fflush(stdout);
    return 0;
}


int encodeSOSM(int argc, const char *argv[])
{
    if (argc != 7) {
        return showHelpEncodingSOS(argv[0]);
    }

    struct SOSMAIL sos;
    parseSOSData(argv, &sos);
    char finalPassword[55] = {0}; /* 55 because we need one more char with a NULL value (if not fprintf() will maybe print garbage and cause a segmentation fault) */
    int errorCode = encodeSOSMail(&sos, finalPassword);
    if (errorCode) {
        return errorCode;
    }

    fprintf(stdout, "Password: %s\n", finalPassword);
    fflush(stdout);

    return 0;
}

void parseSOSData(const char *argv[], struct SOSMAIL *sos)
{
    sos->pkmnToRescue = (unsigned int)atoi(argv[1]);
    sos->dungeon = (unsigned int)atoi(argv[3]);
    sos->floor = (unsigned int)atoi(argv[4]);
    sos->mailID = (unsigned int)atoi(argv[5]);
    sos->chancesLeft = (unsigned int)atoi(argv[6]);
    strncpy(sos->pkmnNick, argv[2], 10);
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
        item = atoi(argv[2]);
    }

    char AOKPassword[55];
    char ThankYouPassword[55];
    convertSOSMail(argv[1], item, AOKPassword, ThankYouPassword);

    char finalAOKPassword[100] = {0};
    char finalThankYouPassword[100] = {0};
    fprintf(stdout, "\nA-OK Password:      %27s\n                    %s\n", strncat(finalAOKPassword, AOKPassword, 27), AOKPassword + 27);
    fprintf(stdout, "Thank-You Password: %27s\n                    %s\n", strncat(finalThankYouPassword, ThankYouPassword, 27), ThankYouPassword + 27);

    fflush(stdout);
    return 0;
}