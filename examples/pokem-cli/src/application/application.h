#ifndef APPLICATION_H
#define APPLICATION_H

#include "../../lib/pokem.h"

#include <stdio.h>
#include <string.h>

enum GameType { RedRescueTeam, BlueRescueTeam };

int decodeWM(int argc, const char *argv[]);
int encodeWM(int argc, const char *argv[]);
int parseWMData(const char *argv[], struct WonderMail *wm);
int decodeSOSM(int argc, const char *argv[]);
int parseSOSData(const char *argv[], struct SosMail *sos);
int encodeSOSM(int argc, const char *argv[]);
int convertSOS(int argc, const char *argv[]);

int generateMassiveItemMissions(int dungeon, int item, int amount);
int generateMassiveHighRankMissions(int dungeon, int item, int amount);

int unlockExclusivePokemon(enum GameType gameType);
int unlockDungeons();

#endif /* APPLICATION_H */
