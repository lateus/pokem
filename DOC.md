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

```c
int lookupTableDecodingWM(char *passwordIntegers, const char *allocatedPassword)
```  
**Internal function, should not be used**  
Since mails only works with alphanumeric characters plus some others, and not with the whole ASCCI collection, the value of each character can be reasigned in order to save storage space. New values are 5 bit long, instead of 8. The reassignment is done by using a lookup table. This function takes `allocatedPassword` which must be previously allocated with `reallocateBytesDecodingWM` and returns the reassigned values in `passwordIntegers`. This is an internal function and should not be used.  

----------  

```c
void bitUnpackingDecodingWM(const char *packed14BytesPassword, struct WONDERMAIL* mail)
```  
**Internal function, should not be used**  
This function takes the packed 14 bytes stored in `packed15BytesPassword`, decodes them and writes the obtained information into `mail`. This is an internal function and should not be used.  

----------  

```c
int* flavorText(const struct WONDERMAIL *wm, int pairsIndex, int loversIndex, int parentsIndex)
```  
**Internal function, should not be used**  
This function takes the decoded Wonder Mail `wm` as returned the function `bitUnpackingDecodingWM`, and also the index of pairs, lovers and parents stored in `pairsIndex`, `loversIndex` and `parentsIndex` respectively. Only one of the last 3 arguments are relevant. The function returns a two-byte. The first one contains an integer code relative to the HEAD of the flavor text, and the second contains an integer code relative to the BODY of the flavor text. Then you can call `flavorTextHead` and `flavorTextBody` to get the flavor text. This is an internal function and should not be used.  

----------  

```c
void flavorTextHead(const struct WONDERMAIL *wm, int headIndicator, int pairsIndex, int loversIndex, int parentsIndex, struct WM_INFO *mailInfo)
```  
**Internal function, should not be used**  
This function takes the decoded Wonder Mail `wm` as returned the function `bitUnpackingDecodingWM`, the HEAD code returned by `flavorText` and stored in `headIndicator`, the index of pairs, lovers and parents stored in `pairsIndex`, `loversIndex` and `parentsIndex` respectively, and a structure `WM_INFO` named `mailInfo` in order to save the flavor text. Only one of the last 3 index arguments are relevant. Once this function returns, `mailInfo` contains the head of the flavor text. This is an internal function and should not be used.  

----------  

```c
void flavorTextBody(const struct WONDERMAIL *wm, int bodyIndicator, int pairsIndex, int loversIndex, int parentsIndex, struct WM_INFO *mailInfo)
```  
**Internal function, should not be used**  
This function takes the decoded Wonder Mail `wm` as returned the function `bitUnpackingDecodingWM`, the BODY code returned by `flavorText` and stored in `bodyIndicator`, the index of pairs, lovers and parents stored in `pairsIndex`, `loversIndex` and `parentsIndex` respectively, and a structure `WM_INFO` named `mailInfo` in order to save the flavor text. Only one of the last 3 index arguments are relevant. Once this function returns, `mailInfo` contains the body of the flavor text. This is an internal function and should not be used.  

----------  

```c
void setWMInfo(struct WM_INFO *mailInfo, const struct WONDERMAIL *mail)
```  
This function extract the information contained in `mail` and write it to `mailInfo` in a mail-style layout. The flavor text is not filled here, you must call `flavorText` and related functions to do so.  

----------  
