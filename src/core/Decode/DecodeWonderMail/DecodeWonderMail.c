#include "DecodeWonderMail.h"
#include "../UtilDecode/UtilDecode.h"
#include "../../UtilCore/UtilCore.h"
#include "../../../data/md1database/md1database.h"

#include <stdio.h>
#include <string.h>


int decodeWonderMail(const char *password, struct WM_INFO *wonderMailInfoResult)
{
    char packed15Bytes[15] = {0};
    int errorCodeWM = wonderMailIsInvalid(password, packed15Bytes);
    if (errorCodeWM) {
        return errorCodeWM;
    }

    /* The first byte in the 15 byte packed password was merely a checksum, so it's useless and I'll remove it */
    char* psw14Bytes = packed15Bytes + 1; /* You must be firm in pointer's arithmetic to handle this effectively, so take care doing this things */

    /* Bit unpacking */
    struct WONDERMAIL wm = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; /* To store the decoded Wonder Mail */
    bitUnpackingDecodingWM(psw14Bytes, &wm);

    /* Flavor Texts */
    int pairsIndex   = arePairs(wm.pkmnClient, wm.pkmnTarget);
    int loversIndex  = areLovers(wm.pkmnClient, wm.pkmnTarget);
    int parentsIndex = areParents(wm.pkmnClient, wm.pkmnTarget);
    int *textIndicator = flavorText(&wm, pairsIndex, loversIndex, parentsIndex);
    flavorTextHead(&wm, textIndicator[FlavorTextHead], pairsIndex, loversIndex, parentsIndex, wonderMailInfoResult);
    flavorTextBody(&wm, textIndicator[FlavorTextBody], pairsIndex, loversIndex, parentsIndex, wonderMailInfoResult);

    /* Bulking the mail's data... */
    setWMInfo(wonderMailInfoResult, &wm);
    sprintf(wonderMailInfoResult->WMail, "%s\n          %s", strncat(wonderMailInfoResult->WMail, password, 12), password + 12);

    return 0; /* means ok */
}



int wonderMailIsInvalid(const char *password, char packed15BytesPassword[]) /* is up to you to avoid a segmentation fault (receiving a 15 bytes array) */
{
    size_t pswLenght = strlen(password);
    if (pswLenght != 24) {
#if DEBUG
        fprintf(stderr, "ERROR: You password lenght is %u characters, and it must have exactly 24 characters.\n\n"
                        "THE PASSWORD CAN'T BE DECODED.\n\n", (unsigned int)pswLenght);
#endif
        return InputError;
    }

    char pswAllocated[24] = {0}; /* Please, initialize all data. This is done at compile time, so there isn't runtime overload */
    reallocateBytesDecodingWM(pswAllocated, password);

    /* This password will be 'integerized' using the lookup table bellow */
    char passIntegers[24] = {0};
    if (lookupTableDecodingWM(passIntegers, pswAllocated) == InputError) {
        return InputError;
    }

    /* Bit packing */
    bitPackingDecoding(packed15BytesPassword, passIntegers, sizeof(passIntegers)); /* Pack the password */

    /* Checksum */
    int checksum = computeChecksum(packed15BytesPassword, 15);
    if ( checksum != (packed15BytesPassword[0] & 0xFF) ) {
#if DEBUG
        fprintf(stderr, "ERROR: Checksum failed, so the password is INVALID.\n\n"
                        "THE PASSWORD CAN'T BE DECODED.\n\n");
#endif
        return ChecksumError;
    }

    return NoError;
}



void reallocateBytesDecodingWM(char* allocatedPassword, const char* unallocatedPassword)
{
    const int newPos[24] = { 12, 6, 19, 8, 4, 13, 15, 9, 16, 2, 20, 18, 0, 21, 11, 5, 23, 3, 17, 10, 1, 14, 22, 7 };

    int i;
    for (i = 0; i < 24; ++i) {
        allocatedPassword[i] = unallocatedPassword[newPos[i]];
    }
}



int lookupTableDecodingWM(char* passwordIntegers, const char* allocatedPassword)
{
    /* I'm worry about the performance of this algorithm. The switch was faster (but looooonger) */
    const char table[] = "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W";
    int i, j;
    for (i = 0; i < 24; ++i) {
        for (j = 0; j < 32; ++j) {
            if (allocatedPassword[i] == table[j]) {
                passwordIntegers[i] = (char)j;
                break;
            }
        }
        if (j == 32) { /* If there is some way to avoid this comparison... (without using goto statement) */
#if DEBUG            
            fprintf(stderr, "ERROR: INVALID character: '%c' found in index [%d].\n"
                            "Valid characters are:\n"
                            "    > Numbers: '0' to '9'.\n"
                            "    > Letters (UPPERCASE only): 'C', 'F', 'H', 'J', 'K', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'W', 'X' AND 'Y'.\n"
                            "    > Symbols: '*' (FEMALE), '/' (MALE), '.' (...), '!', '?', '+', '-'\n\n"
                            "THE PASSWORD CAN'T BE DECODED.\n\n", allocatedPassword[i], i);
#endif
            return InputError;
        }

    }

    return NoError;
}



void bitUnpackingDecodingWM(const char* packed14BytesPassword, struct WONDERMAIL* mail)
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



int* flavorText(const struct WONDERMAIL *wm, int pairsIndex, int loversIndex, int parentsIndex)
{
    /* TODO: Call the HEAD/BODY functions directly from here instead of return the address of a static pointer. */
    static int textIndicator[2];   /* In the index [0] we store a indicator relative to the title (head), the index [1] holds a body's indicator */
    int special = wm->specialJobIndicator;

    if (special < 9) {
        special = 0;
    } else {
        switch (special) {
        case 0x09:
            if (pairsIndex >= 0) {
                textIndicator[FlavorTextHead] = 5;
                textIndicator[FlavorTextBody] = 7;
            }
            return textIndicator;
        case 0x0A:
            if (loversIndex >= 0) {
                textIndicator[FlavorTextHead] = 6;
                textIndicator[FlavorTextBody] = 8;
            }
            return textIndicator;
        case 0x0F:
            if (parentsIndex >= 0) {
                textIndicator[FlavorTextHead] = 4;
                textIndicator[FlavorTextBody] = 6;
            }
            return textIndicator;
        }
    }
    /* Most of the cases will go here directly */
    textIndicator[FlavorTextHead] =  8 + wm->missionType;
    textIndicator[FlavorTextBody] = 12 + wm->missionType;
    return textIndicator;
}



void flavorTextHead(const struct WONDERMAIL *wm, int headIndicator, int pairsIndex, int loversIndex, int parentsIndex, struct WM_INFO *mailInfo)
{
    int dungeonID = (wm->flavorText + wm->dungeon) & 0xFF;

    switch(headIndicator) {
        case 4:
            if (parentsIndex >= 0) {
                strcpy(mailInfo->head, parentsHead);
            } else {
                strcpy(mailInfo->head, "[UNKNOWN HEAD]");
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
                strcpy(mailInfo->head, "[UNKNOWN HEAD]");  /* This should never happen. Please report to me if you encounter a case */
            }
            break;
        case 6:
            if (loversIndex >= 0) {
                strcpy(mailInfo->head, loversEscortHead);
            } else {
                strcpy(mailInfo->head, "[UNKNOWN HEAD]");
            }
            break;
        case 7:
            sprintf(mailInfo->head, msgTitleStandard_DeliverItem, itemsStr[wm->itemDeliverFind]);
            break;
        case 8:
            strcpy(mailInfo->head, msgTitleStandard_HelpMe[dungeonID % 15]);   /* Because the desired array has 15 elements */
            break;
        case 9:
            sprintf(mailInfo->head, msgTitleStandard_FindSomeone[dungeonID % 10], pkmnSpeciesStr[wm->pkmnTarget]);  /* Because the desired array has 10 elements */
            break;
        case 10:
            sprintf(mailInfo->head, msgTitleStandard_Escort[dungeonID % 4], pkmnSpeciesStr[wm->pkmnTarget]);    /* Because the desired array has 4 elements */
            break;
        case 11:
            sprintf(mailInfo->head, msgTitleStandard_FindItem, itemsStr[wm->itemDeliverFind]);
            break;
        case 12:
            sprintf(mailInfo->head, msgTitleStandard_DeliverItem, itemsStr[wm->itemDeliverFind]);
            break;
        default:
            sprintf(mailInfo->head, "[UNKNOWN HEAD]");  /* This should never happen. Please report to me if you encounter a case */
    }

}



void flavorTextBody(const struct WONDERMAIL *wm, int bodyIndicator, int pairsIndex, int loversIndex, int parentsIndex, struct WM_INFO *mailInfo)
{
    int dungeonID = (wm->flavorText + wm->dungeon) & 0xFF;
    int floorID = (wm->flavorText + wm->floor) & 0xFF;

    switch(bodyIndicator) {
        case 6:
            if(parentsIndex >= 0) {
                strcpy(mailInfo->body1, parentsBody1Of2[parentsIndex]);
                strcpy(mailInfo->body2, parentsBody2Of2[parentsIndex]);
            } else {
                strcpy(mailInfo->body1, "[UNKNOWN BODY]");  /* This should never happen. Please report to me if you encounter a case */
                strcpy(mailInfo->body2, "[UNKNOWN BODY]");
            }
            break;
        case 7:
            if(pairsIndex >= 0) {
                sprintf(mailInfo->body2, pairsBody2Of2[pairsIndex], pkmnSpeciesStr[wm->pkmnTarget]);
                sprintf(mailInfo->body1, pairsBody1Of2[pairsIndex], pkmnSpeciesStr[wm->pkmnTarget]);
            } else {
                strcpy(mailInfo->body1, "[UNKNOWN BODY]");  /* This should never happen. Please report to me if you encounter a case */
                strcpy(mailInfo->body2, "[UNKNOWN BODY]");
            }
            break;
        case 8:
            if (loversIndex >= 0) {
                sprintf(mailInfo->body1, loversBody1Of2[dungeonID % 6], pkmnSpeciesStr[wm->pkmnTarget]);    /* Because the desired array has 6 elements */
                strcpy(mailInfo->body2, loversBody2Of2[floorID % 6]);   /* Because the desired array has 6 elements */
            } else {
                strcpy(mailInfo->body1, "[UNKNOWN BODY]");  /* This should never happen. Please report to me if you encounter a case */
                strcpy(mailInfo->body2, "[UNKNOWN BODY]");
            }
            break;
        case 9:
            strcpy(mailInfo->body1, SOS_AskHelp1);
            strcpy(mailInfo->body2, SOS_AskHelp2);
            break;
        case 10:
            strcpy(mailInfo->body1, SOS_GoHelp1);
            strcpy(mailInfo->body2, SOS_GoHelp2);
            break;
        case 11:
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
            sprintf(mailInfo->body1, msgBodyStandard_1Of2_FindDeliverItem[dungeonID % 22], itemsStr[wm->itemDeliverFind]);  /* Because the desired array has 22 elements */
            strcpy(mailInfo->body2, msgBodyStandard_2Of2_FindDeliverItem[floorID % 22]);    /* Because the desired array has 22 elements */
            break;
        case 16:
            sprintf(mailInfo->body1, msgBodyStandard_1Of2_FindDeliverItem[dungeonID % 22], itemsStr[wm->itemDeliverFind]);  /* Because the desired array has 22 elements */
            strcpy(mailInfo->body2, msgBodyStandard_2Of2_FindDeliverItem[floorID % 22]);    /* Because the desired array has 22 elements */
            break;
        default:
            strcpy(mailInfo->body1, "[UNKNOWN BODY]");  /* This should never happen. Please report to me if you encounter a case */
            strcpy(mailInfo->body2, "[UNKNOWN BODY]");
    }
}

void setWMInfo(struct WM_INFO *mailInfo, const struct WONDERMAIL *mail)
{
    strcpy(mailInfo->client, pkmnSpeciesStr[mail->pkmnClient]);

    switch (mail->missionType) {
    case Find:
        sprintf(mailInfo->objective, missionTypeObjectiveStr[mail->missionType], pkmnSpeciesStr[mail->pkmnTarget]);
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
        strcpy(mailInfo->objective, missionTypeObjectiveStr[mail->missionType]);
    }

    strcpy(mailInfo->place, dungeonsStr[mail->dungeon]);
    sprintf(mailInfo->floor, "%c%dF", dungeonUpOrDown[mail->dungeon], mail->floor);

    int diffValue = computeDifficulty(mail->dungeon, mail->floor, mail->missionType);
    mailInfo->difficulty = difficultiesChars[diffValue];

    int money = computeMoneyReward(diffValue, mail->rewardType);
    if (mail->rewardType == 9) {   /* Friend Area reward */
        int friendArea = mail->friendAreaReward;
        /* This section of code must be commented if you uncomment the full database of friend areas in the database header (not recommended). */
        if (mail->friendAreaReward == 15) { /* Sky Blue Plains (in database) */
            friendArea = 2;
        } else {
            friendArea /= 10; /* It's not so difficult to follow, just see the database */
        }
        /* End of the section */
        sprintf(mailInfo->reward, "Friend Zone [%s]", friendAreasStr[friendArea]);
    } else if (money != 0) {
        sprintf(mailInfo->reward, "%d poke", money);
        if (mail->rewardType == 1 || mail->rewardType == 6) {
            strcat(mailInfo->reward, " + ??? [");
            strcat(mailInfo->reward, itemsStr[mail->itemReward]);
            strcat(mailInfo->reward, "]");
        }
    } else {
        sprintf(mailInfo->reward, "%s", itemsStr[mail->itemReward]);
        if (mail->rewardType == 3 || mail->rewardType == 8) {
            strcat(mailInfo->reward, " + ???");
        }
    }
}
