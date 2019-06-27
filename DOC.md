<p align="center"><img src=res/images/png/pokem_128.png></p>  

# PokéM - Pokémon Mystery Dungeon Mail Generator

*Copyright 2018-2019 Carlos Enrique Pérez Sánchez.*  
*Based on the tools written by Peter O.*

**Pokémon Mystery Dungeon Mail Generator, *PokéM* for short is a tool to make your own Wonder Mail and SOS Mail, also allowing you to convert a SOS Mail into a A-OK Mail and a Thank-You Mail.**  

Currently, only *Red & Blue Rescue Teams* are supported.

-----------------------------------------------------------------------------------------------------------------------------------

# API DOCUMENTATION

Official documentation of the library ***PokéM***. Here you will find an API containing a detailed description of each routine you can access, as well the database used (items, pokémon, dungeons, ...).

-----------------------------------------------------------------------------------------------------------------------------------

# Function documentation

## Decoding/Encoding common functions  
Functions used for both encode and decode all kinds of mails.

----------  

```c
int areParents(int pkmnClient, int pkmnTarget)
```  
Returns the index of the parent-son pair only if `pkmnClient` is parent of `pkmnTarget`. Otherwise, returns `-1`. Parents have a distinctive flavor text in mails.  

----------  


```c
int arePairs(int pkmnClient, int pkmnTarget)
```  
Returns the index of the pair only if `pkmnClient` is a special pair with `pkmnTarget` (or viceversa). Otherwise, returns `-1`. Special pairs have a distinctive flavor text in mails.  

----------  


```c
int areLovers(int pkmnClient, int pkmnTarget)
```  
Returns the index of the pair only if `pkmnClient` is inloved with `pkmnTarget` (or viceversa). Otherwise, returns `-1`. Lovers have a distinctive flavor text in mails.  

----------  


```c
unsigned int getSpecialJobIndicator(int pairsIndex, int loversIndex, int parentsIndex)
```  
**Internal function, should not be used**  
Returns an indicator representing a number that indicates the type of special job. `pairsIndex`, `loversIndex` and `parentsIndex` are the return values of the functions `arePairs`, `areLovers` and `areParents` respectively. A special job is, for example, any mission that involves pairs of any kind (including lovers and parents). This is an internal function and should not be used.  

----------  


```c
int findItemByDungeon(int item, int dungeon)
```  
Returns `1` if `item` is found in `dungeon`. `0` otherwise. You cannot deliver an item that doesn't exists in the dungeon you are making a mission.  

----------  


```c
int computeDifficulty(int dungeon, int dungeonFloor, int missionType)
```  
Returns the difficulty level of the mission with type `missionType` that takes place in `dungeon` at `dungeonFloor`. The returned value is in the range `[0:6]` (both inclusive), matching the corresponding difficulty category: `E`, `D`, `C`, `B`, `A`, `S`, `*`.  

----------  


```c
int computeMoneyReward(int difficulty, int rewardType)
```  
Returns the amount of money you will receive after success in a mission with reward type `rewardType`. The `difficulty` parameter is the same returned by the function `computeDifficulty`.  

----------  


```c
int computeChecksum(const char* packedPassword, int bytes)
```  
**Internal function, should not be used**  
Returns the checksum of the first `bytes` bytes in the array `packedPassword`. The checksum is calculated by initializing a variable to `0`. Then, in each iteration, adds to itself each byte plus it's index in the array, while truncating it to 1-byte long. This is an internal function and should not be used.  

----------  


## Decoding

### General decoding functions  
This functions are used for both decoding Wonder Mails and SOS Mails.

----------  

```c
void bitPackingDecoding(char* packedPassword, const char* unpackedPassword, int bytesToPack)
```  
**Internal function, should not be used**  
In a process called *bit packing*, `bytesToPack` bytes are read from `unpackedPassword` and packed in `packedPassword`. This optimization is done because only the first 5 bits of each octet are used. This is an internal function and should not be used.  

----------  

### Wonder Mail Decoding functions  
This functions are used to decode Wonder Mails.

----------  

```c
int decodeWonderMail(const char *password, struct WM_INFO *wonderMailInfoResult)
```  
Decodes the Wonder Mail with password `password` and puts the result in `wonderMailInfoResult`. Returns the error code (check the `ERROR_TYPE` enum type). This function must be used in order to get a decoded Wonder Mail info, it's the best approach.  

----------  

```c
int WonderMailIsInvalid(const char *password, char *packed15BytesPassword)
```  
Check whatever `password` belongs to a invalid Wonder Mail. Returns `0` if the Wonder Mail is valid. In such case `packed15BytesPassword` contains the packed password in 15 bytes. Otherwise returns the error code (check the `ERROR_TYPE` enum type).  

----------  

```c
void reallocateBytesDecodingWM(char *allocatePassword, const char *unallocatedPassword)
```  
**Internal function, should not be used**  
Returns in `allocatePassword` a reallocated version of `unallocatedPassword`. This is an internal function and should not be used.  

----------  

