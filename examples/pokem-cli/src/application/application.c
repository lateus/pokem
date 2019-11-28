#include "application.h"
#include "../view/view.h"

#include <stdlib.h>

int decodeWM(int argc, const char *argv[]) /* The passwords are received here: in argv */
{
    if (argc == 1) {
        return showHelpDecodingWonderMail(argv[0]); /* No arguments specified. */
    }

    struct WonderMailInfo mailInfo  = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0} }; /* The 8th element is a char */
    /* This loop will allow to decode all entered wonder mails one by one. */
    int errorCode;
    errorCode = decodeWonderMail(argv[1], &mailInfo);
    if (errorCode) {
        return errorCode;
    }

    printWonderMailData(&mailInfo);   /* Finally, print the wonder mail info */
    fflush(stdout);

    return NoError;
}


int encodeWM(int argc, const char *argv[])
{
    if (argc != 10) {
        return showHelpEncodingWonderMail(argv[0]);
    }

    struct WonderMail wm;
    parseWMData(argv, &wm);
    char finalPassword[25] = {0};
    int errorCode = encodeWonderMail(&wm, finalPassword);
    if (errorCode) {
        return errorCode;
    }

    /* Get the full Wonder Mail info */
    struct WonderMailInfo wmInfo = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0} };
    setWonderMailInfo(&wm, &wmInfo);
    sprintf(wmInfo.WMail, "%s\n          %s", strncat(wmInfo.WMail, finalPassword, 12), finalPassword + 12);
    printWonderMailData(&wmInfo);
    if (wm.dungeon == 10 || wm.dungeon == 12 || wm.dungeon == 14 || wm.dungeon == 16 || wm.dungeon == 18 || wm.dungeon == 22 || wm.dungeon == 47 || wm.dungeon == 48 || wm.dungeon == 52) {
        fputs("* Warning: You will not be able to accept the above mission.\n", stderr);
    }
    fflush(stdout);

    return NoError;
}



void parseWMData(const char *argv[], struct WonderMail *wm)
{
    wm->mailType         = 5; /* Wonder Mail */
    wm->missionType      = (unsigned int)atoi(argv[1]);
    wm->pkmnClient       = (unsigned int)atoi(argv[2]);
    wm->pkmnTarget       = (wm->missionType == Find || wm->missionType == Escort) ? (unsigned int)atoi(argv[3]) : wm->pkmnClient;
    wm->itemDeliverFind  = (wm->missionType == FindItem || wm->missionType == DeliverItem) ? (unsigned int)atoi(argv[4]) : 9;
    wm->dungeon          = (unsigned int)atoi(argv[5]);
    wm->floor            = (unsigned int)atoi(argv[6]);
    wm->rewardType       = (unsigned int)atoi(argv[7]);
    wm->itemReward       = (unsigned int)atoi(argv[8]);
    wm->friendAreaReward = (wm->rewardType == 9) ? (unsigned int)atoi(argv[9]) : 0;
}



int decodeSOSM(int argc, const char *argv[])
{
    if (argc == 1) {
        return showHelpDecodingSos(argv[0]);   /* No arguments specified. The value of the macro HELP is returned. */
    }
    struct SosMailInfo sosInfo  = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0}, {0}, {0} }; /* The 8th element is a char */
    int errorCode;
    errorCode = decodeSosMail(argv[1], &sosInfo);
    if (errorCode) {
        return errorCode;
    }
    printSOSData(&sosInfo); /* Finally, print the sos mail info */

    fflush(stdout);
    return NoError;
}


int encodeSOSM(int argc, const char *argv[])
{
    if (argc != 7) {
        return showHelpEncodingSos(argv[0]);
    }

    struct SosMail sos;
    parseSOSData(argv, &sos);
    char finalPassword[55] = {0}; /* 55 because we need one more char with a NULL value (if not fprintf() will maybe print garbage and cause a segmentation fault) */
    int errorCode = encodeSosMail(&sos, finalPassword);
    if (errorCode) {
        return errorCode;
    }

    struct SosMailInfo sosInfo  = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0}, {0}, {0} };
    setSosInfo(&sos, &sosInfo);
    sprintf(sosInfo.SOSMail, "%s\n          %s", strncat(sosInfo.SOSMail, finalPassword, 27), finalPassword + 27);
    printSOSData(&sosInfo);
    fflush(stdout);

    return NoError;
}

void parseSOSData(const char *argv[], struct SosMail *sos)
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
    convertSosMail(argv[1], item, AOKPassword, ThankYouPassword);

    struct SosMailInfo AOKInfo  = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0}, {0}, {0} };
    struct SosMailInfo ThxInfo  = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0}, {0}, {0} };
    decodeSosMail(AOKPassword, &AOKInfo);
    decodeSosMail(ThankYouPassword, &ThxInfo);
    fprintf(stdout, "============== A-OK Mail ==============");
    printSOSData(&AOKInfo);
    fprintf(stdout, "============ Thank-You Mail ===========");
    printSOSData(&ThxInfo);
    fflush(stdout);
    return NoError;
}