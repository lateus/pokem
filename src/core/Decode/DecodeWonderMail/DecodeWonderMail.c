#include "DecodeWonderMail.h"
#include "../UtilDecode/UtilDecode.h"
#include "../../UtilCore/UtilCore.h"
#include "../../../data/md1database/md1database.h"
#include "../../../data/md1global/md1global.h"
#include "../../../util/messages.h"
#include "../../../util/colors.h"

#include <stdio.h>
#include <string.h>

int decodeWonderMail(const char *password, struct WonderMail *wonderMailResult)
{
    size_t pswLenght = strlen(password);
    char allocatedPassword[24] = {0};
    const unsigned char newPositions[24] = { 12, 6, 19, 8, 4, 13, 15, 9, 16, 2, 20, 18, 0, 21, 11, 5, 23, 3, 17, 10, 1, 14, 22, 7 };
    char password24Integers[24] = {0};
    const char* lookupTable = "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W";
    int errorCode = NoError;
    char packed15BytesPassword[15] = {0};
    int checksum = 0;
    char* packed14BytesPassword = NULL;
    struct WonderMail wm = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; /* to store the decoded Wonder Mail */

    if (pswLenght != 24) {
        printMessage(stderr, ErrorMessage, "The password must have " LGREEN "24" RESET " characters. Current length: " LRED "%d" RESET ".\n", pswLenght);
        return IncorrectPasswordLengthError;
    }

    reallocateBytes(password, newPositions, 24, allocatedPassword);

    /* this password will be 'integerized' using the lookup table */
    errorCode = mapPasswordByPositionInLookupTable(allocatedPassword, lookupTable, 24, password24Integers);
    if (errorCode != NoError) {
        return errorCode;
    }

    /* Bit packing */
    bitPackingDecoding(packed15BytesPassword, password24Integers, 24); /* pack the password */

    /* checksum */
    checksum = computeChecksum(packed15BytesPassword + 1, 14);
    if (checksum != (packed15BytesPassword[0] & 0xFF)) {
        printMessage(stderr, ErrorMessage, "Checksum failed. Expected " LGREEN "%d" RESET ", but was " LRED "%d" RESET ".\n", packed15BytesPassword[0] & 0xFF, checksum);
        return ChecksumError;
    }

    /* the first byte in the 15 byte packed password was merely a checksum, so it's useless and I'll remove it */
    packed14BytesPassword = packed15BytesPassword + 1;

    /* bit unpacking */
    bitUnpackingDecodingWonderMail(packed14BytesPassword, &wm);
    
    /* checking errors */
    if (entryErrorsWonderMail(&wm) > 0) {
        return MultipleError;
    }

    *wonderMailResult = wm;

    return NoError;
}



void bitUnpackingDecodingWonderMail(const char* packed14BytesPassword, struct WonderMail* mail)
{
    /*
        As a final step, the password is converted into a Wonder Mail by
        unpacking the bits of the 14-bytes password.
        Bit unpacking is the reverse of bit packing.
        It starts with the rightmost bit of the first byte. That bit is
        retrieved and stored in the rightmost position of the result.
        Then the next bit is retrieved and stored, and so on until all bits
        are stored. If a bit cannot be retrieved and stored in the source or the result,
        then the next byte of the source or the result is used.
    */

    mail->mailType = (packed14BytesPassword[0] & 0x0F); /* get the 4 rightmost bits of the first byte. An AND operation with 0x0F=1111 turn (before assignment) zeros all bits except the first four bits */

    mail->missionType = ((packed14BytesPassword[0] >> 4) & 0x07); /* we need 3 more bits to fit the second field, but we already get bits from this byte, so before obtain the bits it's neccesary rightshift the bits used earlier (4 in this case). Then an AND with 0x07=111 give to us the remaining first three bits */

    mail->specialJobIndicator  = ((packed14BytesPassword[0] >> 7) & 0x01); /* in the first byte there is a unused bit yet, so rightshift 7 bits to destroy the first 7 bits and make an AND with 0x01=1 to obtain the first bit (originally the last bit). Now the first byte has been used, so the next byte will be used */
    mail->specialJobIndicator |= (packed14BytesPassword[1] & 0x07) << 1;   /* all bits of the first byte were used, so we use the next byte: get the first 3 bits with an AND with 0x07=111, then we need to insert the bits in the current field, but the first bit of the field is occupied with the last bit of the first byte, so we leftshift 1 bit the new bits before assignment. An OR assignment insert the bits */

    mail->pkmnClient  = ((packed14BytesPassword[1] >> 3) & 0x1F); /* rightshift the 3 bits used earlier, then get bits (five in this case, using an AND with 0x1F=11111) until fill the field or arrive to the last bit of the byte (that ocurr in this case). If you empty the current byte (the second one in this case), use the next byte (the third one) */
    mail->pkmnClient |= (packed14BytesPassword[2] & 0x0F) << 5;   /* get 4 bits with an AND with 0x0F=1111, and before assignment leftshift the newly bits to fit the field, then use an OR-assignment to insert the bits */

    /* No more detailed comments, now you should know what to do... unless you are stu&@$... upppss! ;) */
    mail->pkmnTarget  = ((packed14BytesPassword[2] >> 4) & 0x0F); /* get 4 bits, remaining bits in the current byte: 0 (the next byte will be used) */
    mail->pkmnTarget |= (packed14BytesPassword[3] & 0x1F) << 4;   /* get 5 bits, remaining bits in the current byte: 3 */

    mail->itemDeliverFind  = ((packed14BytesPassword[3] >> 5) & 0x07); /* get 3 bits, remaining bits in the current byte: 0 (the next byte will be used) */
    mail->itemDeliverFind |= (packed14BytesPassword[4] & 0x1F) << 3; /* get 5 bits, remaining bits in the current byte: 3 */

    mail->rewardType  = ((packed14BytesPassword[4] >> 5) & 0x07); /* get 3 bits, remaining: 0 bits */
    mail->rewardType |= (packed14BytesPassword[5] & 0x01) << 3;   /* get 1 bit, remaining: 7 bits */

    mail->itemReward  = ((packed14BytesPassword[5] >> 1) & 0x7F); /* get 7 bits, remaining: 0 bits */
    mail->itemReward |= (packed14BytesPassword[6] & 0x01) << 7;   /* get 1 bit, remaining: 7 bits */

    mail->friendAreaReward  = ((packed14BytesPassword[6] >> 1) & 0x3F); /* get 6 bits, remaining: 1 bits */

    mail->flavorText  = ((packed14BytesPassword[6] >> 7) & 0x01); /* get 1 bit, remaining: 0 bits */
    mail->flavorText |= (packed14BytesPassword[7] & 0x7F) << 1;   /* get 7 bits, remaining: 1 bit */

    mail->random  = ((packed14BytesPassword[7] >> 7) & 0x01); /* get 1 bit, remaining: 0 bits */
    mail->random |= (packed14BytesPassword[8] & 0x7F) << 1;   /* get 7 bits, remaining: 1 bit */

    mail->idk_always0xFF  = ((packed14BytesPassword[8] >> 7) & 0x01); /* get 1 bit, remaining: 0 bits */
    mail->idk_always0xFF |= (packed14BytesPassword[9] & 0x7F) << 1;   /* get 7 bits, remaining: 1 bit */

    mail->dungeon  = ((packed14BytesPassword[9] >> 7) & 0x01); /* get 1 bit, remaining: 0 bits */
    mail->dungeon |= (packed14BytesPassword[10] & 0x3F) << 1;  /* get 6 bits, remaining: 2 bits */

    mail->floor  = ((packed14BytesPassword[10] >> 6) & 0x03); /* get 2 bits, remaining: 0 bits */
    mail->floor |= (packed14BytesPassword[11] & 0x1F) << 2;   /* get 5 bits and... finish! */
}



void setFlavorText(const struct WonderMail *wm, struct WonderMailInfo *mailInfo)
{
    int headIndicator =  8 + wm->missionType;
    int bodyIndicator = 12 + wm->missionType;

    int pairsIndex   = arePairs(wm->pkmnClient, wm->pkmnTarget);
    int loversIndex  = areLovers(wm->pkmnClient, wm->pkmnTarget);
    int parentsIndex = areParents(wm->pkmnClient, wm->pkmnTarget);

    switch (wm->specialJobIndicator) {
    case 0x01:
        break;
    case 0x02:
        break;
    case 0x03:
        break;
    case 0x04:
        break;
    case 0x05:
        headIndicator = wm->missionType == FindItem ? 11 : 12;
        bodyIndicator = 15;
        break;
    case 0x06:
        headIndicator = wm->missionType == FindItem ? 11 : 12;
        bodyIndicator = 16;
        break;
    case 0x09:
        if (pairsIndex >= 0) {
            headIndicator = 5;
            bodyIndicator = 7;
        }
        break;
    case 0x0A:
        if (loversIndex >= 0) {
            headIndicator = 6;
            bodyIndicator = 8;
        }
        break;
    case 0x0F:
        if (parentsIndex >= 0) {
            headIndicator = 4;
            bodyIndicator = 6;
        }
    }

    setFlavorTextHead(wm, headIndicator, pairsIndex, loversIndex, parentsIndex, mailInfo);
    setFlavorTextBody(wm, bodyIndicator, pairsIndex, loversIndex, parentsIndex, mailInfo);
}



void setFlavorTextHead(const struct WonderMail *wm, int headIndicator, int pairsIndex, int loversIndex, int parentsIndex, struct WonderMailInfo *mailInfo)
{
    int dungeonID = (wm->flavorText + wm->dungeon) & 0xFF;

    switch(headIndicator) {
    case 0: /* Should never happen, but we still support it */
        strcpy(mailInfo->head, mankeyTitle);
        break;
    case 1: /* Should never happen, but we still support it */
        strcpy(mailInfo->head, smeargleTitle);
        break;
    case 2: /* Should never happen, but we still support it */
        strcpy(mailInfo->head, medichamTitle);
        break;
    case 4:
        if (parentsIndex >= 0) {
            strcpy(mailInfo->head, parentsHead);
        } else {
            strcpy(mailInfo->head, "[UNKNOWN HEAD]"); /* This should never happen. Please fill a bug report if you encounter a case */
        }
        break;
    case 5:
        if(pairsIndex >= 0) {
            if (pairsIndex < 33) {
                strcpy(mailInfo->head, friendsHead);
            } else if (pairsIndex < 40) {
                strcpy(mailInfo->head, loversHead);
            } else if (pairsIndex < 44) {
                strcpy(mailInfo->head, rivalsHead);
            } else {
                strcpy(mailInfo->head, brothersHead);
            }
        } else {
            strcpy(mailInfo->head, "[UNKNOWN HEAD]"); /* This should never happen. Please fill a bug report if you encounter a case */
        }
        break;
    case 6:
        if (loversIndex >= 0) {
            strcpy(mailInfo->head, loversEscortHead);
        } else {
            strcpy(mailInfo->head, "[UNKNOWN HEAD]"); /* This should never happen. Please fill a bug report if you encounter a case */
        }
        break;
    case 7:
        sprintf(mailInfo->head, msgTitleStandard_DeliverItem, itemsStr[wm->itemDeliverFind]);
        break;
    case 8:
        strcpy(mailInfo->head, msgTitleStandard_HelpMe[dungeonID % 15]); /* Because the desired array has 15 elements */
        break;
    case 9:
        sprintf(mailInfo->head, msgTitleStandard_FindSomeone[dungeonID % 10], pkmnSpeciesStr[wm->pkmnTarget]); /* Because the desired array has 10 elements */
        break;
    case 10:
        sprintf(mailInfo->head, msgTitleStandard_Escort[dungeonID % 4], pkmnSpeciesStr[wm->pkmnTarget]); /* Because the desired array has 4 elements */
        break;
    case 11:
        sprintf(mailInfo->head, msgTitleStandard_FindItem, itemsStr[wm->itemDeliverFind]);
        break;
    case 12:
        sprintf(mailInfo->head, msgTitleStandard_DeliverItem, itemsStr[wm->itemDeliverFind]);
        break;
    default:  /* Should never happen, but we still support it */
        sprintf(mailInfo->head, "[UNKNOWN HEAD]");
    }

}



void setFlavorTextBody(const struct WonderMail *wm, int bodyIndicator, int pairsIndex, int loversIndex, int parentsIndex, struct WonderMailInfo *mailInfo)
{
    int dungeonID = (wm->flavorText + wm->dungeon) & 0xFF;
    int floorID = (wm->flavorText + wm->floor) & 0xFF;

    switch(bodyIndicator) {
    case 0:  /* Should never happen, but we still support it */
        strcpy(mailInfo->body1, mankeyBody1Of2);
        strcpy(mailInfo->body2, mankeyBody2Of2);
        break;
    case 1:  /* Should never happen, but we still support it */
        strcpy(mailInfo->body1, smeargleBody1Of2);
        strcpy(mailInfo->body2, smeargleBody2Of2);
        break;
    case 2:  /* Should never happen, but we still support it */
        strcpy(mailInfo->body1, medichamBody1Of2);
        strcpy(mailInfo->body2, medichamBody2Of2);
        break;
    case 6:
        if(parentsIndex >= 0) {
            strcpy(mailInfo->body1, parentsBody1Of2[parentsIndex]);
            strcpy(mailInfo->body2, parentsBody2Of2[parentsIndex]);
        } else {
            strcpy(mailInfo->body1, "[UNKNOWN BODY]");  /* This should never happen. Please fill a bug report if you encounter a case */
            strcpy(mailInfo->body2, "[UNKNOWN BODY]");
        }
        break;
    case 7:
        if(pairsIndex >= 0) {
            sprintf(mailInfo->body2, pairsBody2Of2[pairsIndex], pkmnSpeciesStr[wm->pkmnTarget]);
            sprintf(mailInfo->body1, pairsBody1Of2[pairsIndex], pkmnSpeciesStr[wm->pkmnTarget]);
        } else {
            strcpy(mailInfo->body1, "[UNKNOWN BODY]");  /* This should never happen. Please fill a bug report if you encounter a case */
            strcpy(mailInfo->body2, "[UNKNOWN BODY]");
        }
        break;
    case 8:
        if (loversIndex >= 0) {
            sprintf(mailInfo->body1, loversBody1Of2[dungeonID % 6], pkmnSpeciesStr[wm->pkmnTarget]);    /* Because the desired array has 6 elements */
            strcpy(mailInfo->body2, loversBody2Of2[floorID % 6]);   /* Because the desired array has 6 elements */
        } else {
            strcpy(mailInfo->body1, "[UNKNOWN BODY]");  /* This should never happen. Please fill a bug report if you encounter a case */
            strcpy(mailInfo->body2, "[UNKNOWN BODY]");
        }
        break;
    case 9: /* Should never happen, but we still support it */
        strcpy(mailInfo->body1, SOS_AskHelp1);
        strcpy(mailInfo->body2, SOS_AskHelp2);
        break;
    case 10: /* Should never happen, but we still support it */
        strcpy(mailInfo->body1, SOS_GoHelp1);
        strcpy(mailInfo->body2, SOS_GoHelp2);
        break;
    case 11: /* Should never happen, but we still support it */
        strcpy(mailInfo->body1, SOS_Thanks1);
        strcpy(mailInfo->body2, SOS_Thanks2);
        break;
    case 12:
        strcpy(mailInfo->body1, msgBodyStandard_1Of2_Help[dungeonID % 13]); /* Because the desired array has 13 elements */
        strcpy(mailInfo->body2, msgBodyStandard_2Of2_Help[floorID % 13]);   /* Because the desired array has 13 elements */
        break;
    case 13:
        sprintf(mailInfo->body1, msgBodyStandard_1Of2_FindSomeone[dungeonID % 45], pkmnSpeciesStr[wm->pkmnTarget]); /* Because the desired array has 45 elements */
        strcpy(mailInfo->body2, msgBodyStandard_2Of2_FindSomeone[floorID % 10]);    /* Because the desired array has 10 elements */
        break;
    case 14:
        sprintf(mailInfo->body2, msgBodyStandard_2Of2_Escort[floorID % 4], pkmnSpeciesStr[wm->pkmnTarget]);
        sprintf(mailInfo->body1, msgBodyStandard_1Of2_Escort[dungeonID % 20], pkmnSpeciesStr[wm->pkmnTarget]);  /* Because the desired array has 20 elements */
        break;
    case 15:
        if (wm->specialJobIndicator == 0x05) {
            sprintf(mailInfo->body1, evolutionBody1Of2, itemsStr[wm->itemDeliverFind]);
            strcpy(mailInfo->body2, evolutionBody2Of2);
        } else if (wm->specialJobIndicator == 0x06) {
            sprintf(mailInfo->body1, foodBody1Of2, itemsStr[wm->itemDeliverFind]);
            strcpy(mailInfo->body2, foodBody2Of2);
        } else {
            sprintf(mailInfo->body1, msgBodyStandard_1Of2_FindDeliverItem[dungeonID % 22], itemsStr[wm->itemDeliverFind]);  /* Because the desired array has 22 elements */
            strcpy(mailInfo->body2, msgBodyStandard_2Of2_FindDeliverItem[floorID % 22]);    /* Because the desired array has 22 elements */
        }
        break;
    case 16:
        if (wm->specialJobIndicator == 0x05) {
            sprintf(mailInfo->body1, evolutionBody1Of2, itemsStr[wm->itemDeliverFind]);
            strcpy(mailInfo->body2, evolutionBody2Of2);
        } else if (wm->specialJobIndicator == 0x06) {
            sprintf(mailInfo->body1, foodBody1Of2, itemsStr[wm->itemDeliverFind]);
            strcpy(mailInfo->body2, foodBody2Of2);
        } else {
            sprintf(mailInfo->body1, msgBodyStandard_1Of2_FindDeliverItem[dungeonID % 22], itemsStr[wm->itemDeliverFind]);  /* Because the desired array has 22 elements */
            strcpy(mailInfo->body2, msgBodyStandard_2Of2_FindDeliverItem[floorID % 22]);    /* Because the desired array has 22 elements */
        }
        break;
    default:
        strcpy(mailInfo->body1, "[UNKNOWN BODY]");  /* This should never happen. Please fill a bug report if you encounter a case */
        strcpy(mailInfo->body2, "[UNKNOWN BODY]");
    }
}

void setWonderMailInfo(const struct WonderMail *mail, struct WonderMailInfo *mailInfo)
{
    int diffValue = 0, money = 0;
    setFlavorText(mail, mailInfo);

    strcpy(mailInfo->client, mail->pkmnClient >= pkmnSpeciesCount ? "[INVALID]" : pkmnSpeciesStr[mail->pkmnClient]);

    switch (mail->missionType) {
    case Find:
        sprintf(mailInfo->objective, missionTypeObjectiveStr[mail->missionType], mail->pkmnTarget >= pkmnSpeciesCount ? "[INVALID]" : pkmnSpeciesStr[mail->pkmnTarget]);
        break;
    case Escort:
        sprintf(mailInfo->objective, missionTypeObjectiveStr[mail->missionType], pkmnSpeciesStr[mail->pkmnTarget]);
        break;
    case FindItem:
        sprintf(mailInfo->objective, missionTypeObjectiveStr[mail->missionType], itemsStr[mail->itemDeliverFind]);
        break;
    case DeliverItem:
        sprintf(mailInfo->objective, missionTypeObjectiveStr[mail->missionType], itemsStr[mail->itemDeliverFind]);
        break;
    default:
        strcpy(mailInfo->objective, mail->missionType >= missionTypeObjectiveCount ? "[INVALID]" : missionTypeObjectiveStr[mail->missionType]);
    }

    sprintf(mailInfo->place, "%s%s%s", mail->missionType == FindItem ? nearPlaceText : "", mail->missionType == FindItem ? " " : "", mail->dungeon >= dungeonsCount ? "[INVALID]" : dungeonsStr[mail->dungeon]);
    sprintf(mailInfo->floor, "%c%dF", mail->dungeon >= dungeonsCount ? '?' : dungeonUpOrDown[mail->dungeon], mail->floor);

    diffValue = computeDifficulty(mail->dungeon, mail->floor, mail->missionType);
    mailInfo->difficulty = diffValue >= difficultiesCharsCount ? '?' : difficultiesChars[diffValue];

    money = computeMoneyReward(diffValue, mail->rewardType);
    if (mail->rewardType == 9) {   /* Friend Area reward */
        sprintf(mailInfo->reward, "%s [%s]", friendZoneText, mail->friendAreaReward >= friendAreasCount ? "INVALID" : friendAreasStr[mail->friendAreaReward]);
    } else if (money != 0) {
        sprintf(mailInfo->reward, "%d poke", money);
        if (mail->rewardType == 1 || mail->rewardType == 6) {
            strcat(mailInfo->reward, " + ??? [");
            strcat(mailInfo->reward, mail->itemReward >= itemsCount ? "[INVALID]" : itemsStr[mail->itemReward]);
            strcat(mailInfo->reward, "]");
        }
    } else {
        sprintf(mailInfo->reward, "%s", mail->itemReward >= itemsCount ? "[INVALID]" : itemsStr[mail->itemReward]);
        if (mail->rewardType == 3 || mail->rewardType == 8) {
            strcat(mailInfo->reward, " + ???");
        }
    }
}
