<p align="center"><img src=res/images/png/pokem_128.png></p>  

# PokéM - Pokémon Mystery Dungeon Mail Generator

*Copyright 2018-2019 Carlos Enrique Pérez Sánchez.*  
*Based on the tools written by Peter O.*

**Pokémon Mystery Dungeon Mail Generator, *PokéM* for short is a tool to make your own Wonder Mail and SOS Mail, also allowing you to convert a SOS Mail into a A-OK Mail and a Thank-You Mail.**

-----------------------------------------------------------------------------------------------------------------------------------

# API DOCUMENTATION

Official documentation of the library ***PokéM***. Here you will find an API containing a detailed description of each routine you can access, as well the database used (items, pokémon, dungeons, ...).

-----------------------------------------------------------------------------------------------------------------------------------

# Function documentation

## Decoding/Encoding commmon functions

```c
int areParents(int pkmnClient, int pkmnTarget)
```
Returns the index of the parent-son pair only if `pkmnClient` is parent of `pkmnTarget`. Otherwise, returns `-1`. Parents have a distinctive flavor text in mails.  


```c
int arePairs(int pkmnClient, int pkmnTarget)
```
Returns the index of the pair only if `pkmnClient` is a special pair with `pkmnTarget` (or viceversa). Otherwise, returns `-1`. Special pairs have a distinctive flavor text in mails.  


```c
int areLovers(int pkmnClient, int pkmnTarget)
```
Returns the index of the pair only if `pkmnClient` is inloved with `pkmnTarget` (or viceversa). Otherwise, returns `-1`. Lovers have a distinctive flavor text in mails.  


```c
unsigned int getSpecialJobIndicator(int pairsIndex, int loversIndex, int parentsIndex)
```
**Internal function, should not be used**  
Returns an indicator representing a number that indicates the type of special job. `pairsIndex`, `loversIndex` and `parentsIndex` are the return values of the functions `arePairs`, `areLovers` and `areParents` respectively. A special job is, for example, any mission that involves pairs of any kind (including lovers and parents). This function is an internal function and should not be used.  


```c
int findItemByDungeon(int item, int dungeon)
```
Returns `1` if `item` is found in `dungeon`. `0` otherwise. You cannot deliver an item that doesn't exists in the dungeon you are making a mission.  


```c
int computeDifficulty(int dungeon, int dungeonFloor, int missionType)
```
Returns the difficulty level of the mission with type `missionType` that takes place in `dungeon` at `dungeonFloor`. The returned value is in the range `[0:6]` (both inclusive), matching the corresponding difficulty category: `E`, `D`, `C`, `B`, `A`, `S`, `*`.


```c
int computeMoneyReward(int difficulty, int rewardType)
```
Returns the amount of money you will receive after success in a mission with reward type `rewardType`. The `difficulty` parameter is the same returned by the function `computeDifficulty`.  


```c
int computeChecksum(const char* packedPassword, int bytes)
```
**Internal function, should not be used**  
Returns the checksum of the first `bytes` bytes in the array `packedPassword`. The checksum is calculated by initializing a variable to `0` and, in each iteration, adding to it each byte plus it's index in the array and truncated it to 1-byte long.  