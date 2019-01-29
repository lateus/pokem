#include "../include/application.h"

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
    printSOSData(&sosInfo); /* Finally, print the wonder mail info */

    fflush(stdout);
    return 0;
}


int encodeSOSMail(int argc, const char *argv[])
{
    if (argc != 7) {
        return showHelpEncodingSOS(argv[0]);
    }

    struct SOSMAIL sos = { 0, 0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0 };
    if (!setMailData(argv, &sos, SOS)) {
        return INPUT_ERROR;
    }

    char packed34BytesPassword[34] = {0}; /* the first byte is merely a checksum */
    char *packed33BytesPassword = packed34BytesPassword + 1; /* be aware about pointer's arithmetic if you don't want an unexpectly behavior at runtime */
    bitPackingEncodingSOS(packed33BytesPassword, &sos); /* bit packing while decoding are equivalent to bit unpacking while encoding */

    packed34BytesPassword[0] = (char)computeChecksum(packed34BytesPassword, 34);

    char password54Integers[54] = {0};
    bitUnpackingEncoding(password54Integers, packed34BytesPassword, 34);

    char password54Chars[54] = {0};
    lookupTableEncodingSOS(password54Chars, password54Integers);

    char finalPassword[55] = {0}; /* 55 because we need one more char with a NULL value (if not fprintf() will maybe print garbage and cause a segmentation fault) */
    realocateBytesEncodingSOS(finalPassword, password54Chars);

    /* Preparing to print the mail... */
    struct SOS_INFO sosInfo  = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, 0, {0}, {0}, {0}, {0} }; /* The 8th element is a char */
    setSOSInfo(&sosInfo, &sos);
    sprintf(sosInfo.SOSMail, "%s\n          %s", strncat(sosInfo.SOSMail, finalPassword, 27), finalPassword + 27);
    printSOSData(&sosInfo); /* Finally, print the wonder mail info */

    fflush(stdout);
    return 0;
}


int convertSOSMail(int argc, const char *argv[])
{
    if (argc == 1) {
        return showHelpConverting(argv[0]);   /* No arguments specified. The value of the macro HELP is returned. */
    }

    char password54Integers[54] = {0};
    if (SOSMailIsInvalidForConverting(argv[1], password54Integers)) {
        return INPUT_ERROR;
    }

    int mailType = ((password54Integers[1] >> 3) & 0x03) | (password54Integers[2] & 0x03) << 2;
    if (mailType != 1) { /* 1 is SOS Mail */
        fputs("ERROR: The mail entered not belongs to a SOS Mail.\n", stderr);
        if (mailType == 4 || mailType == 5) {
            fprintf(stderr, "        Apparently it belongs to a %s.\n", mailType == 4 ? "A-OK Mail" : "Thank-You Mail");
        }
        fputs("THE PASSWORD CAN'T BE DECODED.\n\n", stderr);
        return INPUT_ERROR;
    }

    /* TODO: RANDOMIZE */

    /* FIRST: A-OK MAIL */
    convertSOSToAOKMail(password54Integers);

    /* Bit packing */
    char packed34Bytes[34] = {0}; /* The packed password */
    bitPackingDecoding(packed34Bytes, password54Integers, sizeof (password54Integers)); /* Pack the password */

    packed34Bytes[0] = (char)computeChecksum(packed34Bytes, sizeof(packed34Bytes));

    /* back again */
    int i;
    for (i = 0; i < 54; ++i) {
        password54Integers[i] = 0;
    }
    bitUnpackingEncoding(password54Integers, packed34Bytes, sizeof(packed34Bytes));
    char passwordAllocated[54] = {0};
    lookupTableEncodingSOS(passwordAllocated, password54Integers);
    char AOKPassword[55] = {0};
    realocateBytesEncodingSOS(AOKPassword, passwordAllocated);

    char finalAOKPassword[100] = {0};
    fprintf(stdout, "\nA-OK Password:      %27s\n                    %s\n", strncat(finalAOKPassword, AOKPassword, 27), AOKPassword + 27);

    /* SECOND: THANK-YOU MAIL */
    int item = 0;
    if (argc < 3) {
        fputs("Reward item not specified. Default to nothing.\n", stdout);
    } else {
        item = atoi(argv[2]);
        if (item <= 0 || item > 239) {
            fputs("The specified item is invalid. Default to nothing.\n", stderr);
            item = 0;
        } else {
            fprintf(stdout, "\nReward item:        %d [%s]\n", item, itemsStr[item]);
        }
    }

    convertAOKToThankYouMail(password54Integers, item);

    /* Bit packing */
    /* reseting variables */
    for (i = 0; i < 34; ++i) {
        packed34Bytes[i] = 0;
    }
    bitPackingDecoding(packed34Bytes, password54Integers, sizeof (password54Integers)); /* Pack the password */

    packed34Bytes[0] = (char)computeChecksum(packed34Bytes, sizeof(packed34Bytes));

    /* back again */
    for (i = 0; i < 54; ++i) {
        password54Integers[i] = 0;
        passwordAllocated[i] = 0;
    }
    bitUnpackingEncoding(password54Integers, packed34Bytes, sizeof(packed34Bytes));
    lookupTableEncodingSOS(passwordAllocated, password54Integers);
    char ThankYouPassword[55] = {0};
    realocateBytesEncodingSOS(ThankYouPassword, passwordAllocated);

    char finalThankYouPassword[100] = {0};
    fprintf(stdout, "Thank-You Password: %27s\n                    %s\n", strncat(finalThankYouPassword, ThankYouPassword, 27), ThankYouPassword + 27);

    fflush(stdout);
    return 0;
}

int SOSMailIsInvalidForConverting(const char *password, char password54Integers[])
{
    size_t pswLenght = strlen(password);
    if (pswLenght != 54) {
        fprintf(stderr, "ERROR: You password lenght is %u characters, and it must have exactly 54 characters.\n\n"
                        "THE PASSWORD CAN'T BE DECODED.\n\n", (unsigned int)pswLenght);
        return INPUT_ERROR;
    }

    char pswAllocated[54] = {0}; /* Please, initialize all data */
    reallocateBytesDecodingSOS(password, pswAllocated);

    /* The password that will be converted to integers representation using the lookup table bellow */
    if (lookupTableDecodingSOS(pswAllocated, password54Integers) == INPUT_ERROR) {
        return INPUT_ERROR;
    }

    return 0;
}
