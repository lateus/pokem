#include "../../../include/decode_encode/encode/enc_wm.h"
#include "../../../include/decode_encode/encode/encode.h"
#include "../../../include/model/md1database.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int setWMData(const char *argv[], struct WONDERMAIL *wm)
{
    srand((unsigned int)time(NULL));

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

    int pairsIndex   = arePairs(wm->pkmnClient, wm->pkmnTarget);
    int loversIndex  = areLovers(wm->pkmnClient, wm->pkmnTarget);
    int parentsIndex = areParents(wm->pkmnClient, wm->pkmnTarget);

    wm->specialJobIndicator = getSpecialJobIndicator(pairsIndex, loversIndex, parentsIndex);
    wm->flavorText = (15 - (wm->dungeon % 15)) % 15; /* obtained empirically */
    wm->random = rand() & 0xFF; /* same as % 256 */
    wm->idk_always0xFF = 0xFF; /* as his name suggest */

    int errors = foundErrorsEntriesWM(wm, argv);
    if (errors) {
        fprintf(stderr, " :: %d ERRORS FOUND. DECODING IS NOT POSSIBLE\a\n\n", errors);
        return 0;
    } else {
        /* now adjust the friend area reward values if necessary */
        if (wm->friendAreaReward) {
            switch (wm->friendAreaReward) {
                case 0:
                    wm->friendAreaReward = 9;
                    break;
                case 1:
                    wm->friendAreaReward = 10;
                    break;
                case 2:
                    wm->friendAreaReward = 15;
                    break;
                case 3:
                    wm->friendAreaReward = 37;
                    break;
            }
        }
        return 1;
    }

}



int foundErrorsEntriesWM(const struct WONDERMAIL *wm, const char *argv[])
{
    int errorsFound = 0;

    /* mission type check */
    if (wm->missionType > 4) {
        fprintf(stderr, "ERROR No. %d in argument 1 (Mission type): \"%s\"\n"
                        "      The mission type must be a number between 0 and 4.\n\n", ++errorsFound, argv[1]);
    }

    /* pkmn client check (limits) */
    if (wm->pkmnClient == 0 || wm->pkmnClient > 404) {
        fprintf(stderr, "ERROR No. %d in argument 2 (Pkmn client): \"%s\"\n"
                        "      Pkmns must be numbers between 1 and 404 (not necessarily match pkdex numbers).\n\n", ++errorsFound, argv[2]);
    }

    /* pkmn client check (legendaries) */
    if ( (wm->pkmnClient >= 144 && wm->pkmnClient <= 146) /* birds */ || (wm->pkmnClient >= 150 && wm->pkmnClient <= 151) /* mewtwo and mew */ ||
         (wm->pkmnClient >= 201 && wm->pkmnClient <= 226) /* unown */ || (wm->pkmnClient >= 268 && wm->pkmnClient <= 270) /* dogs */ ||
         (wm->pkmnClient >= 274 && wm->pkmnClient <= 276) /* lugia and ho-oh */ ) {
        fprintf(stderr, "ERROR No. %d in argument 2 (Pkmn client): \"%s\"\n"
                        "      Legendaries are not valid values.\n\n", ++errorsFound, argv[2]);
    }

    if (wm->missionType == FIND || wm->missionType == ESCORT) {
        /* pkmn target check (limits) */
        if (wm->pkmnTarget == 0 || wm->pkmnTarget > 404) {
            fprintf(stderr, "ERROR No. %d in argument 3 (Pkmn target): \"%s\"\n"
                            "      Pkmns must be numbers between 1 and 404 (not necessarily match pkdex numbers).\n\n", ++errorsFound, argv[3]);
        }

        /* pkmn target check (legendaries) */
        if ( (wm->pkmnTarget >= 144 && wm->pkmnTarget <= 146) /* birds */ || (wm->pkmnTarget >= 150 && wm->pkmnTarget <= 151) /* mewtwo and mew */ ||
             (wm->pkmnTarget >= 201 && wm->pkmnTarget <= 226) /* unown */ || (wm->pkmnTarget >= 268 && wm->pkmnTarget <= 270) /* dogs */ ||
             (wm->pkmnTarget >= 274 && wm->pkmnTarget <= 276) /* lugia and ho-oh */ ) {
            fprintf(stderr, "ERROR No. %d in argument 3 (Pkmn target): \"%s\"\n"
                            "      Legendaries are not valid values.\n\n", ++errorsFound, argv[3]);
        }
    }


    /* item to deliver/find check (limits) */
    if (wm->missionType == FINDITEM || wm->missionType == DELIVERITEM) {
        if (wm->itemDeliverFind > 232) {
            fprintf(stderr, "ERROR No. %d in argument 4 (item to find/deliver): \"%s\"\n"
                            "      Items to find or deliver must be numbers between 1 and 232.\n\n", ++errorsFound, argv[4]);
        }

        /* item to deliver/find check (existence) */
        if (wm->missionType == FINDITEM) {
            if (!findItemByDungeon(wm->itemDeliverFind, wm->dungeon)) {
                fprintf(stderr, "ERROR No. %d in argument 4 (item to find/deliver): \"%s\"\n"
                                "      The item %s (index %d) can't be found in the dungeon %s (index %d).\n"
                                "      To accept a job about find an item inside a dungeon, the item must exist on it.\n"
                                "      The items that can be found in that dungeon are listed bellow:\n",
                                            ++errorsFound, argv[4], itemsStr[wm->itemDeliverFind], wm->itemDeliverFind, dungeonsStr[wm->dungeon], wm->dungeon);
                unsigned short i;
                for (i = 1; i < itemsInDungeons[wm->dungeon][0]; ++i) {
                    fprintf(stderr, "[%d] ", itemsInDungeons[wm->dungeon][i]);
                }
                fprintf(stderr, "\n\n");
            }
        }
    }


    /* dungeon check */
    if (wm->dungeon > 63) {
        fprintf(stderr, "ERROR No. %d in argument 5 (Dungeon): \"%s\"\n"
                        "      The dungeon must be a number between 0 and 63.\n\n", ++errorsFound, argv[5]);
    } else if (!strcmp(dungeonsStr[wm->dungeon], "[INVALID]")) {
        fprintf(stderr, "ERROR No. %d in argument 5 (Dungeon): \"%s\"\n"
                        "      The dungeon with index %u isn't a valid dungeon.\n\n", ++errorsFound, argv[5], wm->dungeon);
    }


    /* floor check */
    if (wm->floor > difficulties[wm->dungeon][0]) {
        fprintf(stderr, "ERROR No. %d in argument 6 (Floor): \"%s\"\n"
                        "      The dungeon %s (index %u) only has %d floors. Your entry exceed that value.\n\n",
                                    ++errorsFound, argv[6], dungeonsStr[wm->dungeon], wm->dungeon, difficulties[wm->dungeon][0]);
    }


    /* reward type check */
    if (wm->rewardType > 9) {
        fprintf(stderr, "ERROR No. %d in argument 7 (Reward type): \"%s\"\n"
                        "      The reward type must be a number between 0 and 9.\n\n", ++errorsFound, argv[7]);
        if (!computeDifficulty(wm->dungeon, wm->floor, wm->missionType)) { /* 0 means 'E' difficulty */
            fprintf(stderr, "ERROR No. %d in argument 7 (Reward type): \"%s\"\n"
                            "      To receive a friend area reward, the mission must have at least 'D' difficulty.\n\n", ++errorsFound, argv[7]);
        }
    }


    /* reward item check */
    if ( (wm->rewardType >= 1 && wm->rewardType <= 3) || (wm->rewardType >= 6 && wm->rewardType <= 8) ) {
        if (wm->itemReward > 239) {
            fprintf(stderr, "ERROR No. %d in argument 8 (Reward item): \"%s\"\n"
                            "      Reward item must be a number between 0 and 239.\n\n", ++errorsFound, argv[8]);
        }
    }


    /* friend area reward check */
    if (wm->rewardType == 9) {
        if (wm->friendAreaReward > 3) {
            fprintf(stderr, "ERROR No. %d in argument 9 (Friend area reward): \"%s\"\n"
                            "      The friend area must be a number between 0 and 3.\n\n", ++errorsFound, argv[9]);
        }
    }

    return errorsFound;
}



void bitPackingEncodingWM(char* packed14BytesPassword, const struct WONDERMAIL* mail)
{
    /* I wrote the bits that a field must store, assign more will cause an overflow. I'm using standard C Bit Fields. */
    /* As final observation, I only will read the bits in the array, without destroying bits, instead I'll shift bits: non-destructive read is faster and safer than destructive read */

    packed14BytesPassword[0]   = (mail->mailType & 0x0F);   /* Get the 4 bits of the field. */
    packed14BytesPassword[0]  |= (mail->missionType & 0x07) << 4;   /* get other 3 bits and leftshift bits before assignment. */
    packed14BytesPassword[0]  |= (mail->specialJobIndicator & 0x01) << 7;   /* get another bit and leftshift bits before assignment. Bits remaining: 3 */

    packed14BytesPassword[1]   = ((mail->specialJobIndicator >> 1) & 0x07); /* we already got a bit from this field, so we rightshift a bit and then get the remaining 3 bits */
    packed14BytesPassword[1]  |= (mail->pkmnClient & 0x1F) << 3;    /* get bits from this field until empty the field or fill the current element (in this case until fill the element). Bits remaining: 5 bits */

    /* No more detailed comments, now you should know what to do... unless you are stu&@$... upppss! :) */
    packed14BytesPassword[2]   = ((mail->pkmnClient >> 5) & 0x0F);  /* get 4 bits */
    packed14BytesPassword[2]  |= (mail->pkmnTarget & 0x0F) << 4;    /* get 4 bits, remaining: 5 bits */

    packed14BytesPassword[3]   = ((mail->pkmnTarget >> 4) & 0x1F);  /* get 5 bits */
    packed14BytesPassword[3]  |= (mail->itemDeliverFind & 0x07) << 5;   /* get 3 bits, remaining: 5 bits */

    packed14BytesPassword[4]   = ((mail->itemDeliverFind >> 3) & 0x1F); /* get 5 bits */
    packed14BytesPassword[4]  |= (mail->rewardType & 0x07) << 5;    /* get 3 bits, remaining: 1 bit */

    packed14BytesPassword[5]   = ((mail->rewardType >> 3) & 0x01);  /* get 1 bit */
    packed14BytesPassword[5]  |= (mail->itemReward & 0x7F) << 1;    /* get 7 bits, remaining: 1 bit */

    packed14BytesPassword[6]   = ((mail->itemReward >> 7) & 0x01);  /* get 1 bit */
    packed14BytesPassword[6]  |= (mail->friendAreaReward & 0x3F) << 1;  /* get 6 bits */
    packed14BytesPassword[6]  |= (mail->flavorText & 0x01) << 7;    /* get 1 bit, remaining: 7 bits */

    packed14BytesPassword[7]   = ((mail->flavorText >> 1) & 0x7F);  /* get 7 bits */
    packed14BytesPassword[7]  |= (mail->random & 0x01) << 7;    /* get 1 bit, remaining: 7 bits */

    packed14BytesPassword[8]   = ((mail->random >> 1) & 0x7F);  /* get 7 bits */
    packed14BytesPassword[8]  |= (mail->idk_always0xFF & 0x01) << 7;    /* get 1 bit, remaining: 7 bits */

    packed14BytesPassword[9]   = ((mail->idk_always0xFF >> 1) & 0x7F);  /* get 7 bits */
    packed14BytesPassword[9]  |= (mail->dungeon & 0x01) << 7;   /* get 1 bit, remaining: 6 bits */

    packed14BytesPassword[10]  = ((mail->dungeon >> 1) & 0x3F); /* get 6 bits */
    packed14BytesPassword[10] |= (mail->floor & 0x03) << 6; /* get 2 bits, remaining: 5 bits */

    packed14BytesPassword[11]  = ((mail->floor >> 2) & 0x3F);   /* get the last 5 bits and... finish! */

    /* The elements beyong index 11 were filled with 0 during array initialization, so there is no need to do it now */
}



void lookupTableEncodingWM(const char* password24Integers, char* password24Chars)
{
    char table[] = "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W";
    int i;
    for (i = 0; i < 24; ++i) {
        password24Chars[i] = table[(int)password24Integers[i]];
    }
}



void reallocateBytesEncodingWM(const char* unallocatedPassword, char* allocatedPassword)
{
    const int newPos[24] = { 12, 20, 9, 17, 4, 15, 1, 23, 3, 7, 19, 14, 0, 5, 21, 6, 8, 18, 11, 2, 10, 13, 22, 16 };
    int i;
    for (i = 0; i < 24; ++i) {
        allocatedPassword[i] = unallocatedPassword[newPos[i]];
    }
}
