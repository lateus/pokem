<p align="center"><img width=256 height=256 src=resources/logo/pokem.png></p>  

# PokéM - Pokémon Mystery Dungeon Mail Generator  

*Copyright 2018-2020 Carlos Enrique Pérez Sánchez.*  

**Pokémon Mystery Dungeon Mail Generator, *PokéM* for short is a tool to make your own Wonder Mail and SOS Mail, also allowing you to convert a SOS Mail into a A-OK Mail and a Thank-You Mail.**  

Currently, only *Red & Blue Rescue Teams* are supported.

-----------------------------------------------------------------------------------------------------------------------------------

# API DOCUMENTATION  

Official documentation of the library ***PokéM***. Here you will find an API containing a detailed description of each routine you can access, as well the database used (items, pokémon, dungeons, ...).

-----------------------------------------------------------------------------------------------------------------------------------


# Global switches

```c
int printMessages;
```

This switch enables the verbosity of message-related functions. This includes all the error checking functions. Its default value is `1`, which means that messages are enabled. You may want to disable messages in GUI applications. To do so, set it to `0`, which is also recommended when you want to make quick checks without bottering the user, or to print error custom messages:  

```c
int pkmn;
/* ... (do something with that variable) */

printMessages = 0; /* disable messages */
if (checkPokemon(pkmn, WonderMailType) != NoError) {
    /* handle the error */
}
printMessages = 1; /* enable messages again if you want */
```

-----------------------------------------------------------------------------------------------------------------------------------

```c
#define NO_USE_COLORS
```

If this directive is defined, the library will be built without color support. It is recommended that you define it only in console applications if you are streming to `stdout` or `stderr`. Also remember that *Windows* versions prior to *Windows 10 RS2* has no color support in consoles.  

Since this must be defined in this library prior to compilation, it's recommended that you compile this by passing that definition to the compiler (for example passing `-DNO_USE_COLORS` to `gcc`) which is done automatically by compiling this library without color support (check the `README.md` file to learn how to do it).

Note that for some reason the default *Windows*'s shell in which programs are executed, prints buggy characters instead of colors even on *Windows 10* with color support. A possible workaround is calling C `system()` function (which is defined in `stdlib.h`, or `cstdlib` if C++) with some command (can be an empty string) at the begining of the program:

```c
int main(int argc, const char* argv[])
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    system("title My program v1.0");
#endif

    /* ... */
}
```

-----------------------------------------------------------------------------------------------------------------------------------  


# Data types

## Structures

This structures are handled internally and you will not need to modify them. But, since you must instantiate them in one place or another, it is better that you know about them.

### `struct WonderMail`

This structure contains the information of a **Wonder Mail**. It uses bit fields, so take care of not overflow them. It's defined as follows:

Field                              | Size   | Description
---------------------------------- | ------ | -----------
`unsigned int mailType`            | 4 bits | The type of mail. Must equal `5` for **Wonder Mail**. See `MailType` enumeration.
`unsigned int missionType`         | 3 bits | The type of mission. See `MissionType` enumeration.
`unsigned int specialJobIndicator` | 4 bits | Indicates if the mission is a special job. Usually `0`. This value is handled internally and shouldn't be modified.
`unsigned int pkmnClient`          | 9 bits | Client pokémon.
`unsigned int pkmnTarget`          | 9 bits | Target pokémon.
`unsigned int itemDeliverFind`     | 8 bits | Item to find/deliver. Safe to set to `0x9` if the mission is not of type `FindItem` or `DeliverItem`. See `MissionType` enumeration.
`unsigned int rewardType`          | 4 bits | The type of reward. See `RewardType` enumeration.
`unsigned int itemReward`          | 8 bits | The reward item.
`unsigned int friendAreaReward`    | 6 bits | The friend zone reward if the `rewardType` field is set to `FriendArea`.
`unsigned int flavorText`          | 8 bits | A byte that holds information about the head and body of the mail message.
`unsigned int random`              | 8 bits | A random byte.
`unsigned int idk_always0xFF`      | 8 bits | A byte for unknown purpose, but almost always with the value `0xFF`.
`unsigned int dungeon`             | 7 bits | The dungeon.
`unsigned int floor`               | 7 bits | The floor in absolute value. The game will turn it negative if neccessary.

-----------------------------------------------------------------------------------------------------------------------------------


### `struct SosMail`

This structure contains the information of a **SOS Mail**. It uses bit fields, so take care of not overflow them. It's defined as follows:

Field                              | Size    | Description
---------------------------------- | ------- | -----------
`unsigned int mailType`            |  4 bits | The type of mail. Must equal `1` for **SOS Mail**, `4` for **A-OK Mail**, and `5` for **Thank-You Mail**. See `MailType` enumeration.
`unsigned int dungeon`             |  7 bits | The dungeon.
`unsigned int floor`               |  7 bits | The floor in absolute value. The game will turn it negative if neccessary.
`unsigned int idk_random`          | 24 bits | Three random bytes. It allows that different mails can have the same info.
`unsigned int pkmnToRescue`        |  9 bits | Pokémon to rescue.
`unsigned int mailID`              | 16 bits | Mail ID.
`unsigned int idk_random2`         | 16 bits | Two random bytes. 
`char pkmnNick[10]`                | 80 bits | The nickname of the pokémon to rescue. `0` marks the end of the string if shorter than `10` characters.
`unsigned int idk_0Or1`            |  8 bits | A byte for unknown purpose. Safe to set to `1` if the mail is a **Thank-You Mail**, else set to `0`.
`unsigned int itemReward`          |  8 bits | The reward item. Safe to set to `0` if not **Thank-You Mail**.
`unsigned int idk_0`               |  8 bits | A byte for unknown purpose. Safe to set to `0`.
`unsigned int teamSeekingHelpID`   | 32 bits | ID of rescue team seeking help.
`unsigned int teamGivingHelpID`    | 32 bits | ID of rescue team giving help.
`unsigned int chancesLeft`         |  8 bits | Rescue chances left; when converting to **A-OK Mail**, subtract `1` from this.
`unsigned int idk_last3Bits`       |  3 bits | Three bits for unknown purpose. Safe to set to `0`.

-----------------------------------------------------------------------------------------------------------------------------------


### `struct WonderMailInfo`

This structure contains the human-readable information of a **Wonder Mail**. This is just an simple utility. In the practice, you may want to make your own way to represent the information:

Field                | Description
-------------------- | -----------
`char head[26]`      | The head of the mail.
`char body1[100]`    | The first line of the mail'd description.
`char body2[100]`    | The second line of the mail'd description.
`char client[11]`    | The client pokémon's species name.
`char objective[22]` | The objective of the mission.
`char place[26]`     | The name of the place.
`char floor[7]`      | The floor (for example `1F` or `B1F`).
`char difficulty`    | The level of difficulty. One of `E`, `D`, `C`, `B`, `A`, `S`, `*`
`char reward[35]`    | The name of the reward item.
`char password[25]`  | The mail's password, in one line.

-----------------------------------------------------------------------------------------------------------------------------------


### `struct SosMailInfo`

This structure contains the human-readable information of a **SOS Mail**. This is just an simple utility. In the practice, you may want to make your own way to represent the information:

Field                 | Description
--------------------- | -----------
`char head[26]`       | The head of the mail.
`char body[100]`      | The first line of the mail'd description.
`char nickname[11]`   | The client pokémon's nickname.
`char client[11]`     | The client pokémon's species name.
`char objective[15]`  | The objective of the mission.
`char place[26]`      | The name of the place.
`char floor[7]`       | The floor (for example `1F` or `B1F`).
`char difficulty`     | The level of difficulty. One of `E`, `D`, `C`, `B`, `A`, `S`, `*`
`char reward[35]`     | The name of the reward item.
`char id[6]`          | The name of the reward item.
`char chancesLeft[4]` | The name of the reward item.
`char password[100]`  | The mail's password, in one line.

-----------------------------------------------------------------------------------------------------------------------------------


## Enumerations


### `enum MailType`

Indicates the type of mail. Note that a value other than `InvalidMailType` can be also make a mail invalid, for example, values `0` or `2` or `3` are also invalid.

Name               | Value              | Description
------------------ | ------------------ | -----------
`SosMailType`      | `1`                | SOS Mail
`AOkMailType`      | `4`                | A-OK Mail
`ThankYouMailType` | `5`                | Thank-You Mail
`WonderMailType`   | `ThankYouMailType` | Wonder Mail
`InvalidMailType`  | `15`               | Invalid Mail

-----------------------------------------------------------------------------------------------------------------------------------

### `enum MissionType`

Indicates the type of mission.

Name           | Value  | Description
-------------- | ------ | -----------
`HelpMe`       | `0`    | Help the pokémon client.
`Find`         | `1`    | Find someone.
`Escort`       | `2`    | Escort someone. You cannot be rescued if you or the client pokémon faint.
`FindItem`     | `3`    | Find an item and bring it outside.
`DeliverItem`  | `4`    | Enter the dungeon with an item to deliver it.
`FriendRescue` | `5`    | A rescue through communication.

-----------------------------------------------------------------------------------------------------------------------------------

### `enum RewardType`

Indicates the type of reward. Note that a value other than `UnknownRewardType` can be also make a mail invalid, for example, values `10` or `11` or `12` are also invalid.

Name                | Value  | Description
------------------- | ------ | -----------
`Money`             | `0`    | Some money.
`MoneyItem`         | `1`    | Some money and an item.
`Item`              | `2`    | An item.
`ItemItem`          | `3`    | Two items.
`UnknownRewardType` | `4`    | An invalid reward type.
`MoneyMoney`        | `5`    | Money (`x2` the money given at `Money` and `MoneyItem`).
`MoneyMoneyItem`    | `6`    | Money (`x2` the money given at `Money` and `MoneyItem`) plus two items.
`Item2`             | `7`    | An item.
`ItemItem2`         | `8`    | Two items.
`FriendArea`        | `9`    | A friend zone.

-----------------------------------------------------------------------------------------------------------------------------------

### `enum ErrorType`

List of errors.

Name                                    | Value   | Description
--------------------------------------- | ------- | -----------
`NoError`                               |  `0`    | No error, all OK
`UnknownError`                          |  `1`    | Unknown error
`MultipleError`                         |  `2`    | Multiple errors
`InputError`                            |  `3`    | Generic input error
`OutputError`                           |  `4`    | Generic output error
`ChecksumError`                         |  `5`    | Checksum error
`MailTypeError`                         |  `6`    | The mail type is invalid
`MissionTypeError`                      |  `7`    | The mission type is invalid
`SpecialJobIndicatorError`              |  `8`    | The special job indicator is invalid
`PokemonOutOfRangeError`                |  `9`    | The pokemon is out of range
`PokemonNotAllowedError`                | `10`    | The pokemon is invalid (for example, a legendary pokémon)
`ItemOutOfRangeError`                   | `11`    | The item is out of range
`NoItemError`                           | `12`    | The item is `0` (*Nothing*), which is not necessarily an error
`ItemCannotBeObtainedError`             | `13`    | The item exists but cannot be obtained, usually the item is a Beatup Orb or a G Machine
`ItemNotExistsInDungeonError`           | `14`    | The item do not exists in the dungeon
`RewardTypeError`                       | `15`    | The reward type is invalid
`FriendAreaOutOfRangeError`             | `16`    | The friend area is out of range
`FriendAreaIsInvalidAsRewardError`      | `17`    | The friend area cannot be set as reward
`DungeonOutOfRangeError`                | `18`    | The dungeon is out of range
`DungeonIsInvalidError`                 | `19`    | The dungeon exists, but it is invalid
`MissionCannotBeAcceptedInDungeonError` | `20`    | The mission can be generated, but cannot be accepted (for example, a peak or the Makuhita's Dojo)
`FloorOutOfRangeError`                  | `21`    | The dungeon do not have the selected floor
`FloorInvalidInDungeonError`            | `22`    | The floor exists, but a mission cannot be done there (for example, boss and warp floors)
`MailIDOutOfRangeError`                 | `23`    | The mail ID is invalid
`NicknameEmptyError`                    | `24`    | The nickname is empty
`ChancesLeftError`                      | `25`    | The amount of chances left is invalid
`IncorrectPasswordLengthError`          | `26`    | The length of the password is invalid
`InvalidCharacterError`                 | `27`    | The password contains an invalid character
`ConversionError`                       | `28`    | The password couldn't be converted

-----------------------------------------------------------------------------------------------------------------------------------



# Function documentation  


## Utility functions  

```c
int printMessage(FILE *stream, enum MessageType messageType, const char* message, ...)
```

Print to `stream` the formatted `message` of type `messageType`. This functions behaves like C `fprintf()` function. `message` can be one of the following:

`enum MessageType`

Name             | Value  | Description
---------------- | ------ | -----------
`DebugMessage`   | `0`    | Debug message. Shouldn't be used on production.
`InfoMessage`    | `1`    | Information message. Use this to notify the user about something (like default actions).
`WarningMessage` | `2`    | Warning message. Use this to warn the user about a possible failure.
`ErrorMessage`   | `3`    | Error message. Use this when you must cancel or discard the current action.
`FatalMessage`   | `4`    | Fatal error message. Use this for errors that will prevent the application for running.

Depending of the type of message, a word is prepended to the message (`"DEBUG: "` for `DebugMessage`, `"ERROR: "` for `ErrorMessage`, and so).

If `NO_USE_COLORS` is not defined, it prints the string that indicates the type of message with colors (light green for `InfoMessage`, yellow for `WarningMessage`, red for `ErrorMessage` and so).

Example of usage:

```c
char pokemonName[51];
int pokemonNameIsValid = 0;
printMessage(stdout, InfoMessage, "Enter the pokemon species's name:\n");
/* ... (do something with those variables) */

if (!pokemonNameIsValid) {
    printMessage(stderr, ErrorMessage, "There is not pokemon named %s.\n", pokemonName);
}
```


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
int canEvolveWithItem(int pkmn, int item)
```  
Returns `1` if the pokémon `pkmn` can use `item` to evolve, `0` otherwise.  

----------  

```c
int isFood(int item)
```  
Returns `1` if `item` is food, `0` otherwise.  

---------- 

```c
int getMailType(const char* password)
```  
Returns the mail type of the mail represented by `password`. If it cannot be determined, `InvalidMailType` is returned.  

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
int checkPokemon(int pokemon, enum MailType mailType)
```  
Check if the `pokemon` is valid for the `mailType`. Returns `PokemonOutOfRangeError` if the `pokemon` is out of range, or `PokemonNotAllowedError` if cannot be choosen (for example, a legendary if the mail is a Wonder Mail). Returns `NoError` if the `pokemon` is valid.  

----------  

```c
int checkDungeon(int dungeon, enum MailType mailType)
```  
Check if the `dungeon` is valid for the `mailType`. Returns `DungeonOutOfRangeError` if the `dungeon` is out of range, or `DungeonIsInvalidError` if it's invalid, or `MissionCannotBeAcceptedInDungeonError` if cannot be choosen (for example, *Mt. Thunder Peak* if the mail is a **Wonder Mail**). Returns `NoError` if the `dungeon` is valid.  

----------  

```c
int checkFloor(int floor, int dungeon)
```  
Check if the `floor` is valid for the `dungeon`. Returns `FloorOutOfRangeError` if the `floor` is out of range, or `FloorInvalidInDungeonError` if a rescue cannot be made in that floor (for example, floor `20` or `99` of *Wish Cave*). This last limitation only applies for **Wonder Mails**. Returns `NoError` if the `floor` is valid.  
**NOTE:** This function assumes that the `dungeon` is valid.  

----------  

```c
int checkItem(int item)
```  
Check if the `item` is valid. Returns `ItemOutOfRangeError` if it's out of range, or `ItemCannotBeObtainedError` if it's not obtainable. If `item` is `0` (*Nothing*), returns `NoItemError`, but this doesn't mean that the item is invalid; for example `0` is a valid reward for **Thank-You Mails**. In all other cases it seems to be invalid. Returns `NoError` if it's valid.  

----------  

```c
int checkItemExistenceInDungeon(int item, int dungeon)
```  
Check if the `item` can be found in the `dungeon`. Returns `ItemNotExistsInDungeonError` if it cannot be found, `NoError` otherwise. The result of this function must only be considered relevant if the `item` is the one to find in missions of type `FindItem`.  
**NOTE:** This function assumes that the `dungeon` is valid.  

----------  

```c
int checkFriendArea(int friendArea)
```  
Check if the `friendArea` is valid. Returns `FriendAreaOutOfRangeError` if it is out of range, or `FriendAreaIsInvalidAsRewardError` if it cannot be set as reward, `NoError` otherwise.  

----------  

```c
int checkMailID(int mailID)
```  
Check if the mail ID `mailID` is valid. Returns `MailIDOutOfRangeError` if it is out of range, `NoError` otherwise.  

----------  

```c
int entryErrorsWonderMail(const struct WonderMail *wm)
```  
This function scans the Wonder Mail `wm` and return the number of errors found while reporting them with high verbosity. This function is called internally by `encodeWonderMail`, but you may want to call it to report entry errors at real-time.  

----------  

```c
int entryErrorsSosMail(const struct SosMail *sos)
```  
This function scans the SOS Mail `sos` and return the number of errors found while reporting them with high verbosity. This function is called internally by `encodeSosMail`, but you may want to call it to report entry errors at real-time.  

----------  


## Decoding


### Wonder Mail decoding functions  
These functions are used to decode Wonder Mails.  

----------  

```c
int decodeWonderMail(const char *password, struct WonderMail *wonderMailResult)
```  
Decodes the Wonder Mail with password `password` and puts the result in `wonderMailResult`. Returns the error code (check the `ErrorType` enumeration).  

----------  


### SOS Mail decoding functions  
These functions are used to decode SOS Mails.  

----------  

```c
int decodeSosMail(const char *password, struct SosMail *sosMailResult)
```  
Decodes the Wonder Mail with password `password` and puts the result in `sosMailResult`. Returns the error code (check the `ErrorType` enumeration).  

----------  


## Encoding


### Wonder Mail encoding functions  
These functions are used to encode Wonder Mails.  

----------  

```c
int encodeWonderMail(struct WonderMail *wm, char* finalPassword, int trySpecialWonderMail)
```  
Encodes the Wonder Mail `wm` and puts the result in `finalPassword`. If `trySpecialWonderMail` is not `0`, special missions related to food or evolutionary items can be generated. Returns the error code (check the `ErrorType` enumeration).  

----------  


### SOS Mail encoding functions  
These functions are used to decode SOS Mails.  

----------  

```c
int encodeSosMail(struct SosMail *sos, char *finalPassword)
```  
Generates the password `finalPassword` by encoding the SOS Mail `sos`. Returns the error code (check the `ErrorType` enumeration).  

----------  


## Converting  

----------  

```c
int convertSosMail(const char *SOSPassword, int idTeamGivingHelp, int item, char *resultAOKMail, char *resultThankYouMail)
```  
This function takes the **SOS Mail** password `SOSPassword` and converts it into an **A-OK Mail** and a **Thank-You Mail**, writting the respective passwords in `resultAOKMail` and `resultThankYouMail`. The `idTeamGivingHelp` is set in the **A-Ok Mail**, unless its value is `0`, in which case it is set to the ID of the team seeking help. The reward item is set to `item`, which can be `0` (*Nothing*), meaning no reward item. If the `SOSPassword` belongs to an **A-OK Mail**, only a **Thank-You Mail** will be generated, and if the `SOSPassword` belongs to an **Thank-You Mail**. Returns the error code (check the `ErrorType` enumeration).  

----------  


# Database documentation  


## Pokémon  

Bellow is the complete database of pokémon. Observe that these **are not** the dex numbers, but the numbers used by the game to identify each criature. The number `0` corresponds to *Decamark* (i.e., *??????????*, *Nothing*, an empty spot) and cannot be used. Also, some mail types add limitations to the species that can be used (for example, legendaries).  

These values are defined as:

```c
const char* pkmnSpeciesStr[];
```  

And the size of that array is defined as:

```c
const unsigned int pkmnSpeciesCount;
```  

No. | Pokémon         | No. | Pokémon         | No. | Pokémon         | No. | Pokémon         | No. | Pokémon
--- | --------------- | --- | --------------- | --- | --------------- | --- | --------------- | --- | -------
  1 | Bulbasaur       | 101 | Electrode       | 201 | UnownA          | 301 | Taillow         | 401 | Salamence
  2 | Ivysaur         | 102 | Exeggcute       | 202 | UnownB          | 302 | Swellow         | 402 | Beldum
  3 | Venusaur        | 103 | Exeggutor       | 203 | UnownC          | 303 | Wingull         | 403 | Metang
  4 | Charmander      | 104 | Cubone          | 204 | UnownD          | 304 | Pelipper        | 404 | Metagross
  5 | Charmeleon      | 105 | Marowak         | 205 | UnownE          | 305 | Ralts           | 405 | Regirock
  6 | Charizard       | 106 | Hitmonlee       | 206 | UnownF          | 306 | Kirlia          | 406 | Regice
  7 | Squirtle        | 107 | Hitmonchan      | 207 | UnownG          | 307 | Gardevoir       | 407 | Registeel
  8 | Wartortle       | 108 | Lickitung       | 208 | UnownH          | 308 | Surskit         | 408 | Latias
  9 | Blastoise       | 109 | Koffing         | 209 | UnownI          | 309 | Masquerain      | 409 | Latios
 10 | Caterpie        | 110 | Weezing         | 210 | UnownJ          | 310 | Shroomish       | 410 | Kyogre
 11 | Metapod         | 111 | Rhyhorn         | 211 | UnownK          | 311 | Breloom         | 411 | Groudon
 12 | Butterfree      | 112 | Rhydon          | 212 | UnownL          | 312 | Slakoth         | 412 | Rayquaza
 13 | Weedle          | 113 | Chansey         | 213 | UnownM          | 313 | Vigoroth        | 413 | Jirachi
 14 | Kakuna          | 114 | Tangela         | 214 | UnownN          | 314 | Slaking         | 414 | Deoxys
 15 | Beedrill        | 115 | Kangaskhan      | 215 | UnownO          | 315 | Nincada         | 415 | Unown!
 16 | Pidgey          | 116 | Horsea          | 216 | UnownP          | 316 | Ninjask         | 416 | Unown?
 17 | Pidgeotto       | 117 | Seadra          | 217 | UnownQ          | 317 | Shedinja        | 417 | Deoxys Atk
 18 | Pidgeot         | 118 | Goldeen         | 218 | UnownR          | 318 | Whismur         | 418 | Deoxys Def
 19 | Rattata         | 119 | Seaking         | 219 | UnownS          | 319 | Loudred         | 419 | Deoxys Spd
 20 | Raticate        | 120 | Staryu          | 220 | UnownT          | 320 | Exploud         | 420 | Munchlax
 21 | Spearow         | 121 | Starmie         | 221 | UnownU          | 321 | Makuhita        | 421 | Decoy
 22 | Fearow          | 122 | Mr. Mime        | 222 | UnownV          | 322 | Hariyama        | 422 | Statue
 23 | Ekans           | 123 | Scyther         | 223 | UnownW          | 323 | Azurill         | 423 | Rayquaza
 24 | Arbok           | 124 | Jynx            | 224 | UnownX          | 324 | Nosepass
 25 | Pikachu         | 125 | Electabuzz      | 225 | UnownY          | 325 | Skitty
 26 | Raichu          | 126 | Magmar          | 226 | UnownZ          | 326 | Delcatty
 27 | Sandshrew       | 127 | Pinsir          | 227 | Wobbuffet       | 327 | Sableye
 28 | Sandslash       | 128 | Tauros          | 228 | Girafarig       | 328 | Mawile
 29 | NidoranF        | 129 | Magikarp        | 229 | Pineco          | 329 | Aron
 30 | Nidorina        | 130 | Gyarados        | 230 | Forretress      | 330 | Lairon
 31 | Nidoqueen       | 131 | Lapras          | 231 | Dunsparce       | 331 | Aggron
 32 | NidoranM        | 132 | Ditto           | 232 | Gligar          | 332 | Meditite
 33 | Nidorino        | 133 | Eevee           | 233 | Steelix         | 333 | Medicham
 34 | Nidoking        | 134 | Vaporeon        | 234 | Snubbull        | 334 | Electrike
 35 | Clefairy        | 135 | Jolteon         | 235 | Granbull        | 335 | Manectric
 36 | Clefable        | 136 | Flareon         | 236 | Qwilfish        | 336 | Plusle
 37 | Vulpix          | 137 | Porygon         | 237 | Scizor          | 337 | Minun
 38 | Ninetales       | 138 | Omanyte         | 238 | Shuckle         | 338 | Volbeat
 39 | Jigglypuff      | 139 | Omastar         | 239 | Heracross       | 339 | Illumise
 40 | Wigglytuff      | 140 | Kabuto          | 240 | Sneasel         | 340 | Roselia
 41 | Zubat           | 141 | Kabutops        | 241 | Teddiursa       | 341 | Gulpin
 42 | Golbat          | 142 | Aerodactyl      | 242 | Ursaring        | 342 | Swalot
 43 | Oddish          | 143 | Snorlax         | 243 | Slugma          | 343 | Carvanha
 44 | Gloom           | 144 | Articuno        | 244 | Magcargo        | 344 | Sharpedo
 45 | Vileplume       | 145 | Zapdos          | 245 | Swinub          | 345 | Wailmer
 46 | Paras           | 146 | Moltres         | 246 | Piloswine       | 346 | Wailord
 47 | Parasect        | 147 | Dratini         | 247 | Corsola         | 347 | Numel
 48 | Venonat         | 148 | Dragonair       | 248 | Remoraid        | 348 | Camerupt
 49 | Venomoth        | 149 | Dragonite       | 249 | Octillery       | 349 | Torkoal
 50 | Diglett         | 150 | Mewtwo          | 250 | Delibird        | 350 | Spoink
 51 | Dugtrio         | 151 | Mew             | 251 | Mantine         | 351 | Grumpig
 52 | Meowth          | 152 | Chikorita       | 252 | Skarmory        | 352 | Spinda
 53 | Persian         | 153 | Bayleef         | 253 | Houndour        | 353 | Trapinch
 54 | Psyduck         | 154 | Meganium        | 254 | Houndoom        | 354 | Vibrava
 55 | Golduck         | 155 | Cyndaquil       | 255 | Kingdra         | 355 | Flygon
 56 | Mankey          | 156 | Quilava         | 256 | Phanpy          | 356 | Cacnea
 57 | Primeape        | 157 | Typhlosion      | 257 | Donphan         | 357 | Cacturne
 58 | Growlithe       | 158 | Totodile        | 258 | Porygon2        | 358 | Swablu
 59 | Arcanine        | 159 | Croconaw        | 259 | Stantler        | 359 | Altaria
 60 | Poliwag         | 160 | Feraligatr      | 260 | Smeargle        | 360 | Zangoose
 61 | Poliwhirl       | 161 | Sentret         | 261 | Tyrogue         | 361 | Seviper
 62 | Poliwrath       | 162 | Furret          | 262 | Hitmontop       | 362 | Lunatone
 63 | Abra            | 163 | Hoothoot        | 263 | Smoochum        | 363 | Solrock
 64 | Kadabra         | 164 | Noctowl         | 264 | Elekid          | 364 | Barboach
 65 | Alakazam        | 165 | Ledyba          | 265 | Magby           | 365 | Whiscash
 66 | Machop          | 166 | Ledian          | 266 | Miltank         | 366 | Corphish
 67 | Machoke         | 167 | Spinarak        | 267 | Blissey         | 367 | Crawdaunt
 68 | Machamp         | 168 | Ariados         | 268 | Raikou          | 368 | Baltoy
 69 | Bellsprout      | 169 | Crobat          | 269 | Entei           | 369 | Claydol
 70 | Weepinbell      | 170 | Chinchou        | 270 | Suicune         | 370 | Lileep
 71 | Victreebel      | 171 | Lanturn         | 271 | Larvitar        | 371 | Cradily
 72 | Tentacool       | 172 | Pichu           | 272 | Pupitar         | 372 | Anorith
 73 | Tentacruel      | 173 | Cleffa          | 273 | Tyranitar       | 373 | Armaldo
 74 | Geodude         | 174 | Igglybuff       | 274 | Lugia           | 374 | Feebas
 75 | Graveler        | 175 | Togepi          | 275 | Ho-Oh           | 375 | Milotic
 76 | Golem           | 176 | Togetic         | 276 | Celebi          | 376 | Castform
 77 | Ponyta          | 177 | Natu            | 277 | Treecko         | 377 | Castform
 78 | Rapidash        | 178 | Xatu            | 278 | Grovyle         | 378 | Castform
 79 | Slowpoke        | 179 | Mareep          | 279 | Sceptile        | 379 | Castform
 80 | Slowbro         | 180 | Flaaffy         | 280 | Torchic         | 380 | Kecleon
 81 | Magnemite       | 181 | Ampharos        | 281 | Combusken       | 381 | Shuppet
 82 | Magneton        | 182 | Bellossom       | 282 | Blaziken        | 382 | Banette
 83 | Farfetch'd      | 183 | Marill          | 283 | Mudkip          | 383 | Duskull
 84 | Doduo           | 184 | Azumarill       | 284 | Marshtomp       | 384 | Dusclops
 85 | Dodrio          | 185 | Sudowoodo       | 285 | Swampert        | 385 | Tropius
 86 | Seel            | 186 | Politoed        | 286 | Poochyena       | 386 | Chimecho
 87 | Dewgong         | 187 | Hoppip          | 287 | Mightyena       | 387 | Absol
 88 | Grimer          | 188 | Skiploom        | 288 | Zigzagoon       | 388 | Wynaut
 89 | Muk             | 189 | Jumpluff        | 289 | Linoone         | 389 | Snorunt
 90 | Shellder        | 190 | Aipom           | 290 | Wurmple         | 390 | Glalie
 91 | Cloyster        | 191 | Sunkern         | 291 | Silcoon         | 391 | Spheal
 92 | Gastly          | 192 | Sunflora        | 292 | Beautifly       | 392 | Sealeo
 93 | Haunter         | 193 | Yanma           | 293 | Cascoon         | 393 | Walrein
 94 | Gengar          | 194 | Wooper          | 294 | Dustox          | 394 | Clamperl
 95 | Onix            | 195 | Quagsire        | 295 | Lotad           | 395 | Huntail
 96 | Drowzee         | 196 | Espeon          | 296 | Lombre          | 396 | Gorebyss
 97 | Hypno           | 197 | Umbreon         | 297 | Ludicolo        | 397 | Relicanth
 98 | Krabby          | 198 | Murkrow         | 298 | Seedot          | 398 | Luvdisc
 99 | Kingler         | 199 | Slowking        | 299 | Nuzleaf         | 399 | Bagon
100 | Voltorb         | 200 | Misdreavus      | 300 | Shiftry         | 400 | Shelgon


## Items  

Bellow is the complete database of items. The number `0` corresponds to *Nothing*. Also, some missions add limitations to the items that can be involved (for example, you cannot find an item that not exist in the mission's dungeon).  

These values are defined as:

```c
const char* itemsStr[];
```  

And the size of that array is defined as:

```c
const unsigned int itemsCount;
```  

No. | Item            | No. | Item            | No. | Item
--- | --------------- | --- | --------------- | --- | ---------------
  0 | \[Nothing\]         | 100 | Royal Gummi     | 200 | Escape Orb
  1 | Stick           | 101 | Black Gummi     | 201 | Scanner Orb
  2 | Iron Thorn      | 102 | Silver Gummi    | 202 | Radar Orb
  3 | Silver Spike    | 103 | Banana          | 203 | Drought Orb
  4 | Gold Fang       | 104 | Chestnut        | 204 | Trapbust Orb
  5 | Cacnea Spike    | 105 | Poke            | 205 | Rollcall Orb
  6 | Corsola Twig    | 106 | Upgrade         | 206 | Invisify Orb
  7 | Gravelerock     | 107 | King's Rock     | 207 | One-Shot Orb
  8 | Geo Pebble      | 108 | Thunderstone    | 208 | Identify Orb
  9 | Mobile Scarf    | 109 | Deepseascale    | 209 | Vacuum-Cut
 10 | Heal Ribbon     | 110 | Deepseatooth    | 210 | Reviver Orb
 11 | Twist Band      | 111 | Sun Stone       | 211 | Shocker Orb
 12 | Scope Lens      | 112 | Moon Stone      | 212 | Sizebust Orb
 13 | Patsy Band      | 113 | Fire Stone      | 213 | One-Room Orb
 14 | No-Stick Cap    | 114 | Water Stone     | 214 | Fill-In Orb
 15 | Pierce Band     | 115 | Metal Coat      | 215 | Trapper Orb
 16 | Joy Ribbon      | 116 | Leaf Stone      | 216 | Possess Orb
 17 | X-Ray Specs     | 117 | Dragon Scale    | 217 | Itemizer Orb
 18 | Persim Band     | 118 | Link Cable      | 218 | Hurl Orb
 19 | Power Band      | 119 | Ice Part        | 219 | Mobile Orb
 20 | Pecha Scarf     | 120 | Steel Part      | 220 | Toss Orb
 21 | Insomniscope    | 121 | Rock Part       | 221 | Stairs Orb
 22 | Warp Scarf      | 122 | Music Box       | 222 | Longtoss Orb
 23 | Tight Belt      | 123 | Key             | 223 | Pierce Orb
 24 | Sneak Scarf     | 124 | Used TM         | 224 | Cut
 25 | Gold Ribbon     | 125 | Focus Punch     | 225 | Fly
 26 | Goggle Specs    | 126 | Dragon Claw     | 226 | Surf
 27 | Diet Ribbon     | 127 | Water Pulse     | 227 | Strength
 28 | Trap Scarf      | 128 | Calm Mind       | 228 | Flash
 29 | Racket Band     | 129 | Roar            | 229 | Rock Smash
 30 | Def. Scarf      | 130 | Toxic           | 230 | Waterfall
 31 | Stamina Band    | 131 | Hail Orb        | 231 | Dive
 32 | Plain Ribbon    | 132 | Bulk Up         | 232 | Link Box
 33 | Special Band    | 133 | Bullet Seed     | 233 | Switch Box
 34 | Zinc Band       | 134 | Hidden Power    | 234 | Weavile Fig
 35 | Detect Band     | 135 | Sunny Orb       | 235 | Mime Jr. Fig
 36 | Alert Specs     | 136 | Taunt           | 236 | Beatup Orb
 37 | Dodge Scarf     | 137 | Ice Beam        | 237 | G Machine 6
 38 | Bounce Band     | 138 | Blizzard        | 238 | G Machine 7
 39 | Curve Band      | 139 | Hyper Beam      | 239 | G Machine 8
 40 | Whiff Specs     | 140 | Light Screen
 41 | No-Aim Scope    | 141 | Protect
 42 | Lockon Specs    | 142 | Rainy Orb
 43 | Munch Belt      | 143 | Giga Drain
 44 | Pass Scarf      | 144 | Safeguard
 45 | Weather Band    | 145 | Frustration
 46 | Friend Bow      | 146 | Solarbeam
 47 | Beauty Scarf    | 147 | Iron Tail
 48 | Sun Ribbon      | 148 | Thunderbolt
 49 | Lunar Ribbon    | 149 | Thunder
 50 | Ring D          | 150 | Earthquake
 51 | Ring E          | 151 | Return
 52 | Ring F          | 152 | Dig
 53 | Heal Seed       | 153 | Psychic
 54 | Wish Stone      | 154 | Shadow Ball
 55 | Oran Berry      | 155 | Brick Break
 56 | Sitrus Berry    | 156 | Evasion Orb
 57 | Eyedrop Seed    | 157 | Reflect
 58 | Reviver Seed    | 158 | Shock Wave
 59 | Blinker Seed    | 159 | Flamethrower
 60 | Doom Seed       | 160 | Sludge Bomb
 61 | Allure Seed     | 161 | Sandy Orb
 62 | Life Seed       | 162 | Fire Blast
 63 | Rawst Berry     | 163 | Rocky Orb
 64 | Hunger Seed     | 164 | Aerial Ace
 65 | Quick Seed      | 165 | Torment
 66 | Pecha Berry     | 166 | Facade
 67 | Cheri Berry     | 167 | Secret Power
 68 | Totter Seed     | 168 | Rest
 69 | Sleep Seed      | 169 | Attract
 70 | Plain Seed      | 170 | Thief
 71 | Warp Seed       | 171 | Steel Wing
 72 | Blast Seed      | 172 | Skill Swap
 73 | Ginseng         | 173 | Snatch Orb
 74 | Joy Seed        | 174 | Overheat
 75 | Chesto Berry    | 175 | Wide Slash
 76 | Stun Seed       | 176 | Excavate
 77 | Max Elixir      | 177 | Spin Slash
 78 | Protein         | 178 | See-Trap Orb
 79 | Calcium         | 179 | Mug Orb
 80 | Iron            | 180 | Rebound Orb
 81 | Zinc            | 181 | Lob Orb
 82 | Apple           | 182 | Switcher Orb
 83 | Big Apple       | 183 | Blowback Orb
 84 | Grimy Food      | 184 | Warp Orb
 85 | Huge Apple      | 185 | Transfer Orb
 86 | White Gummi     | 186 | Slow Orb
 87 | Red Gummi       | 187 | Quick Orb
 88 | Blue Gummi      | 188 | Luminous Orb
 89 | Grass Gummi     | 189 | Petrify Orb
 90 | Yellow Gummi    | 190 | Stayaway Orb
 91 | Clear Gummi     | 191 | Pounce Orb
 92 | Orange Gummi    | 192 | Trawl Orb
 93 | Pink Gummi      | 193 | Cleanse Orb
 94 | Brown Gummi     | 194 | Observer Orb
 95 | Sky Gummi       | 195 | Decoy Orb
 96 | Gold Gummi      | 196 | Slumber Orb
 97 | Green Gummi     | 197 | Totter Orb
 98 | Gray Gummi      | 198 | Two-Edge Orb
 99 | Purple Gummi    | 199 | Silence Orb


## Dungeons  

Bellow is the complete database of dungeons. Dungeons marked as **[INVALID]** cannot be used in mails. Some mail types add limitations to the dungeons that can be involved (for example, you can be rescued in **Sky Tower Summit** by a friend, but you cannot accept a Wonder Mail mission there).  

These values are defined as:

```c
const char* dungeonsStr[];
```  

And the size of that array is defined as:

```c
const unsigned int dungeonsCount;
```  

No. | Dungeon        
--- | ---------------
  0 | Tiny Woods
  1 | Thunderwave Cave
  2 | Mt. Steel
  3 | Sinister Woods
  4 | Silent Chasm
  5 | Mt. Thunder
  6 | Mt. Thunder Peak*
  7 | Great Canyon
  8 | Lapis Cave
  9 | Mt. Blaze
 10 | Mt. Blaze Peak
 11 | Frosty Forest
 12 | Frosty Grotto
 13 | Mt. Freeze
 14 | Mt. Freeze Peak*
 15 | Magma Cavern
 16 | Magma Cavern Pit*
 17 | Sky Tower
 18 | Sky Tower Summit*
 19 | Stormy Sea
 20 | Silver Trench
 21 | Meteor Cave
 22 | Mt. Freeze Peak*
 23 | Western Cave
 24 | \[INVALID\]
 25 | \[INVALID\]
 26 | Wish Cave
 27 | Buried Relic
 28 | Pitfall Valley
 29 | Northern Range
 30 | \[INVALID\]
 31 | Desert Region
 32 | Southern Cavern
 33 | Wyvern Hill
 34 | Fiery Field
 35 | Northwind Field
 36 | Solar Cave
 37 | Lightning Field
 38 | Darknight Relic
 39 | \[INVALID\]
 40 | Murky Cave
 41 | Grand Sea
 42 | Uproar Forest
 43 | Oddity Cave
 44 | Remains Island
 45 | Marvelous Sea
 46 | Fantasy Strait
 47 | Rock Path*
 48 | Snow Path*
 49 | \[INVALID\]
 50 | \[INVALID\]
 51 | \[INVALID\]
 52 | Dojo Registration*
 53 | Howling Forest
 54 | \[INVALID\]
 55 | Fantasy Strait
 56 | Waterfall Pond
 57 | Unown Relic
 58 | Joyous Tower
 59 | Far-off Sea
 60 | Mt. Faraway
 61 | \[INVALID\]
 62 | Purity Forest

**NOTE:** Dungeons marked with a * are valid but cannot be accepted in Wonder Mails.


## Friend areas  

Bellow is the complete database of friend areas. There are limitations regarding the areas that can be offered as reward. Only *Dragon Cave*, *Mt. Moonview*, *Sky Blue Plains* and *Boulder Cave*.  

These values are defined as:

```c
const char* friendAreasStr[];
```  

And the size of that array is defined as:

```c
const unsigned int friendAreasCount;
```  

No. | Friend area
--- | ---------------
  0 | \[None\]
  1 | Bountiful Sea
  2 | Treasure Sea
  3 | Serene Sea
  4 | Deep-Sea Floor
  5 | Deep-Sea Current
  6 | Seafloor Cave
  7 | Shallow Beach
  8 | Mt. Deepgreen
  9 | Dragon Cave
 10 | Mt. Moonview
 11 | Mt. Cleft
 12 | Rainbow Peak
 13 | Wild Plains
 14 | Beau Plains
 15 | Sky Blue Plains
 16 | Safari
 17 | Scorched Plains
 18 | Sacred Field
 19 | Mist-Rise Forest
 20 | Flyaway Forest
 21 | Overgrown Forest
 22 | Energetic Forest
 23 | Mushroom Forest
 24 | Healing Forest
 25 | Transform Forest
 26 | Secretive Forest
 27 | Rub-a-Dub River
 28 | Tadpole Pond
 29 | Turtleshell Pond
 30 | Mystic Lake
 31 | Waterfall Lake
 32 | Peanut Swamp
 33 | Poison Swamp
 34 | Echo Cave
 35 | Cryptic Cave
 36 | Jungle
 37 | Boulder Cave
 38 | Decrepit Lab
 39 | Mt. Discipline
 40 | Thunder Meadow
 41 | Power Plant
 42 | Crater
 43 | Furnace Desert
 44 | Aged Chamber AN
 45 | Aged Chamber O?
 46 | Ancient Relic
 47 | Darkness Ridge
 48 | Frigid Cavern
 49 | Ice Floe Beach
 50 | Volcanic Pit
 51 | Stratos Lookout
 52 | Ravaged Field
 53 | Magnetic Quarry
 54 | Legendary Island
 55 | Southern Island
 56 | Enclosed Island
 57 | Final Island

**END OF API DOCUMENTATION**


# Internal functions  
The rest of functions are not part of the official API, and should not be used directly, because they can change or even being removed without advice.  