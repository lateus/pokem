#ifndef MD1DEBUGGER_H
#define MD1DEBUGGER_H

#include <stdio.h>
#include <string.h>
#include "../data/md1global/md1global.h"

/* Functions prototypes */
void printBinary(long long int n, const int bitsToPrint);    /* Print the binary representation using bitsToPrint bits to stderr */
void printWonderMailBruteData(const struct WonderMail *wm);
void printSosMailBruteData(const struct SosMail *sosm);
void printWonderMailInfo(const struct WonderMailInfo *wm);
void printSosMailInfo(const struct SosMailInfo *sosm);
void printArray(const char* array, int size);

/** Functions implementations */

void printBinary(long long int n, const int bits)
{
    unsigned int mask = 1 << (bits - 1);
    int i;
    for (i = 1; i <= bits; ++i) {
        putchar(n & mask ? '1' : '0');
        n <<= 1;
    }
    putchar('\n');

    fflush(stderr);
}



void printWonderMailBruteData(const struct WonderMail *wm)
{
    fprintf(stderr, "======================== WONDER MAIL ========================\n"
                    "Mail Type ------------- %d\n"
                    "Mission Type ---------- %d\n"
                    "Special Job Indicator - %d\n"
                    "Pkmn Client ----------- %d\n"
                    "Pkmn Target ----------- %d\n"
                    "Item to Find/Deliver -- %d\n"
                    "Reward Type ----------- %d\n"
                    "Reward Item ----------- %d\n"
                    "Friend Area Reward ---- %d\n"
                    "Flavor Text ----------- %d\n"
                    "Random ---------------- %d\n"
                    "IDK (always 0xFF) ----- %d\n"
                    "Dungeon --------------- %d\n"
                    "Floor ----------------- %d\n"
                    "=========================================================\n",
                    wm->mailType,
                    wm->missionType,
                    wm->specialJobIndicator,
                    wm->pkmnClient,
                    wm->pkmnTarget,
                    wm->itemDeliverFind,
                    wm->rewardType,
                    wm->itemReward,
                    wm->friendAreaReward,
                    wm->flavorText,
                    wm->random,
                    wm->idk_always0xFF,
                    wm->dungeon,
                    wm->floor);
    fprintf(stderr, "\nHead indicator: %d"
                    "\nBody indicator: %d\n",
                    8 + wm->missionType,
                    12 + wm->missionType);
    fflush(stderr);
}



extern void printSosMailBruteData(const struct SosMail *sosm)
{
    char nick[11] = {0};
    strncpy(nick, sosm->pkmnNick, 10);
    fprintf(stderr, "======================== SOS MAIL ========================\n"
                    "Mail Type ------------ %d\n"
                    "Dungeon -------------- %d\n"
                    "Floor ---------------- %d\n"
                    "IDK random ----------- %d\n"
                    "Pkmn to rescue ------- %d\n"
                    "Mail ID -------------- %d\n"
                    "IDK random 2 --------- %d\n"
                    "Pkmn nick ------------ [%s] %d %d %d %d %d %d %d %d %d %d\n"
                    "IDK 01 --------------- %d\n"
                    "Item reward ---------- %d\n"
                    "IDK 0 ---------------- %d\n"
                    "ID Team Seeking Help - %d\n"
                    "ID Team Giving Help -- %d\n"
                    "Chances left --------- %d\n"
                    "IDK last 3 bits ------ %d\n"
                    "==========================================================\n",
                    sosm->mailType,
                    sosm->dungeon,
                    sosm->floor,
                    sosm->idk_random,
                    sosm->pkmnToRescue,
                    sosm->mailID,
                    sosm->idk_random2,
                    nick,
                    sosm->pkmnNick[0],
                    sosm->pkmnNick[1],
                    sosm->pkmnNick[2],
                    sosm->pkmnNick[3],
                    sosm->pkmnNick[4],
                    sosm->pkmnNick[5],
                    sosm->pkmnNick[7],
                    sosm->pkmnNick[7],
                    sosm->pkmnNick[8],
                    sosm->pkmnNick[9],
                    sosm->idk_0Or1,
                    sosm->itemReward,
                    sosm->idk_0,
                    sosm->teamSeekingHelpID,
                    sosm->teamGivingHelpID,
                    sosm->chancesLeft,
                    sosm->idk_last3Bits);
    fflush(stderr);
}



void printWonderMailInfo(const struct WonderMailInfo *wm)
{
    fprintf(stderr, "==================== WONDER MAIL INFO ====================\n"
                    "Head -------- %s\n"
                    "Body 1 ------ %s\n"
                    "Body 2 ------ %s\n"
                    "Pkmn Client - %s\n"
                    "Objective --- %s\n"
                    "Place ------- %s\n"
                    "Floor ------- %s\n"
                    "Difficulty -- %c\n"
                    "Reward ------ %s\n"
                    "Password ---- %s\n"
                    "==========================================================\n",
                    wm->head,
                    wm->body1,
                    wm->body2,
                    wm->client,
                    wm->objective,
                    wm->place,
                    wm->floor,
                    wm->difficulty,
                    wm->reward,
                    wm->password);
    fflush(stderr);
}



extern void printSosMailInfo(const struct SosMailInfo *sosm)
{
    char nick[11] = {0};
    strncpy(nick, sosm->nickname, 10);
    fprintf(stderr, "===================== SOS MAIL INFO =====================\n"
                    "Head --------- %s\n"
                    "Body --------- %s\n"
                    "Nickname ----- %s\n"
                    "Pkmn Client -- %s\n"
                    "Objective ---- %s\n"
                    "Place -------- %s\n"
                    "Floor -------- %s\n"
                    "Difficulty --- %c\n"
                    "Reward ------- %s\n"
                    "Mail ID ------ %s\n"
                    "Chances left - %s\n"
                    "Password ----- %s\n"
                    "==========================================================\n",
                    sosm->head,
                    sosm->body,
                    nick,
                    sosm->client,
                    sosm->objective,
                    sosm->place,
                    sosm->floor,
                    sosm->difficulty,
                    sosm->reward,
                    sosm->id,
                    sosm->chancesLeft,
                    sosm->password);
    fflush(stderr);
}

extern void printArray(const char* array, int size)
{
    int i;
    fprintf(stderr, "BRUTE ARRAY: ");
    for (i = 0; i < size; ++i) {
        fprintf(stderr, "%d ", (int)array[i]);
    }
    fprintf(stderr, "\n");
}

#endif /* MD1DEBUGGER_H */
