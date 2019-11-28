<p align="center"><img src=resources/logo/pokem.png></p>  

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


## Decoding


### Wonder Mail decoding functions  
These functions are used to decode Wonder Mails.  

----------  

```c
int decodeWonderMail(const char *password, struct WonderMailInfo *wonderMailInfoResult)
```  
Decodes the Wonder Mail with password `password` and puts the result in `wonderMailInfoResult`. Returns the error code (check the `ErrorType` enum type). This function must be used in order to get a decoded Wonder Mail info, it's the best approach.  

----------  

```c
int wonderMailIsInvalid(const char *password, char *packed15BytesPassword)
```  
Check whatever `password` belongs to a invalid Wonder Mail. Returns `0` if the Wonder Mail is valid. In such case `packed15BytesPassword` contains the packed password in 15 bytes. Otherwise returns the error code (check the `ErrorType` enum type).  

----------  


### SOS Mail decoding functions  
These functions are used to decode SOS Mails.  

----------  

```c
int decodeSosMail(const char *sosPassword, struct SosMailInfo *sosMailInfoResult)
```  
Decodes the SOS Mail with password `sosPassword` and puts the result in `sosMailInfoResult`. Returns the error code (check the `ErrorType` enum type). This function must be used in order to get a decoded SOS Mail info, it's the best approach.  

----------  

```c
int sosMailIsInvalid(const char *password, char *packed34BytesPassword)
```  
Check whatever `password` belongs to a invalid SOS Mail. Returns `0` if the SOS Mail is valid. In such case `packed34BytesPassword` contains the packed password in 34 bytes. Otherwise returns the error code (check the `ErrorType` enum type).  

----------  


## Encoding


### Wonder Mail encoding functions  
These functions are used to encode Wonder Mails.  

----------  

```c
int encodeWonderMail(struct WonderMail *wm, char *finalPassword)
```  
Encodes the Wonder Mail `wm` and puts the result in `finalPassword`. Returns the error code (check the `ErrorType` enum type). This function must be used in order to get a encoded Wonder Mail password, it's the best approach.  

----------  

```c
int entryErrorsWonderMail(const struct WonderMail *wm)
```  
This function scans the Wonder Mail `wm` and return the number of errors found while reporting them with high verbosity. This function is called internally by `encodeWonderMail`, but you may want to call it to report entry errors at real-time.  

----------  


### SOS Mail encoding functions  
These functions are used to decode SOS Mails.  

----------  

```c
int encodeSosMail(struct SosMail *sos, char *finalPassword)
```  
Generates the password `finalPassword` by encoding the SOS Mail `sos`. Returns the error code (check the `ErrorType` enum type). This function must be used in order to get a encoded SOS Mail password, it's the best approach.  

----------  

```c
int entryErrorsSosMail(const struct SosMail *sos)
```  
This function scans the SOS Mail `sos` and return the number of errors found while reporting them with high verbosity. This function is called internally by `encodeSosMail`, but you may want to call it to report entry errors at real-time.  

----------  


## Converting  

----------  

```c
int convertSosMail(const char *SOSPassword, int item, char *resultAOKMail, char *resultThankYouMail)
```  
This function takes the SOS Mail password `SOSPassword` and converts it into an A-OK Mail and a Thank-You Mail, writting the respective passwords in `resultAOKMail` and `resultThankYouMail`. Returns the error code (check the `ErrorType` enum type). This function must be used in order to convert a SOS Mail into an A-OK Mail and a Thank-You Mail, it's the best approach.  

----------  


# Database documentation  


## Pokémon  

Bellow is the complete database of pokémon. Observe that these **are not** the dex numbers, but the numbers used by the game to identify each criature. The number `0` corresponds to *Decamark* (i.e., nothing, an empty spot) and cannot be used. Also, some mail types add limitations to the species that can be used (for example, legendaries).  

These values are defined as:

```c
const char* pkmnSpeciesStr[];
```  

No. | Pokémon         | No. | Pokémon         | No. | Pokémon         | No. | Pokémon         | No. | Pokémon
--- | --------------- | --- | --------------- | --- | --------------- | --- | --------------- | --- | -------
  1 | Bulbasaur       | 101 | Electrode       | 201 | Unown           | 301 | Taillow         | 401 | Salamence
  2 | Ivysaur         | 102 | Exeggcute       | 202 | Unown           | 302 | Swellow         | 402 | Beldum
  3 | Venusaur        | 103 | Exeggutor       | 203 | Unown           | 303 | Wingull         | 403 | Metang
  4 | Charmander      | 104 | Cubone          | 204 | Unown           | 304 | Pelipper        | 404 | Metagross
  5 | Charmeleon      | 105 | Marowak         | 205 | Unown           | 305 | Ralts           | 405 | Regirock
  6 | Charizard       | 106 | Hitmonlee       | 206 | Unown           | 306 | Kirlia          | 406 | Regice
  7 | Squirtle        | 107 | Hitmonchan      | 207 | Unown           | 307 | Gardevoir       | 407 | Registeel
  8 | Wartortle       | 108 | Lickitung       | 208 | Unown           | 308 | Surskit         | 408 | Latias
  9 | Blastoise       | 109 | Koffing         | 209 | Unown           | 309 | Masquerain      | 409 | Latios
 10 | Caterpie        | 110 | Weezing         | 210 | Unown           | 310 | Shroomish       | 410 | Kyogre
 11 | Metapod         | 111 | Rhyhorn         | 211 | Unown           | 311 | Breloom         | 411 | Groudon
 12 | Butterfree      | 112 | Rhydon          | 212 | Unown           | 312 | Slakoth         | 412 | Rayquaza
 13 | Weedle          | 113 | Chansey         | 213 | Unown           | 313 | Vigoroth        | 413 | Jirachi
 14 | Kakuna          | 114 | Tangela         | 214 | Unown           | 314 | Slaking         | 414 | Deoxys
 15 | Beedrill        | 115 | Kangaskhan      | 215 | Unown           | 315 | Nincada
 16 | Pidgey          | 116 | Horsea          | 216 | Unown           | 316 | Ninjask
 17 | Pidgeotto       | 117 | Seadra          | 217 | Unown           | 317 | Shedinja
 18 | Pidgeot         | 118 | Goldeen         | 218 | Unown           | 318 | Whismur
 19 | Rattata         | 119 | Seaking         | 219 | Unown           | 319 | Loudred
 20 | Raticate        | 120 | Staryu          | 220 | Unown           | 320 | Exploud
 21 | Spearow         | 121 | Starmie         | 221 | Unown           | 321 | Makuhita
 22 | Fearow          | 122 | Mr. Mime        | 222 | Unown           | 322 | Hariyama
 23 | Ekans           | 123 | Scyther         | 223 | Unown           | 323 | Azurill
 24 | Arbok           | 124 | Jynx            | 224 | Unown           | 324 | Nosepass
 25 | Pikachu         | 125 | Electabuzz      | 225 | Unown           | 325 | Skitty
 26 | Raichu          | 126 | Magmar          | 226 | Unown           | 326 | Delcatty
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

No. | Item            | No. | Item            | No. | Item
--- | --------------- | --- | --------------- | --- | ---------------
  0 | Nothing         | 100 | Royal Gummi     | 200 | Escape Orb
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
 24 | [INVALID]
 25 | [INVALID]
 26 | Wish Cave
 27 | Buried Relic
 28 | Pitfall Valley
 29 | Northern Range
 30 | [INVALID]
 31 | Desert Region
 32 | Southern Cavern
 33 | Wyvern Hill
 34 | Fiery Field
 35 | Northwind Field
 36 | Solar Cave
 37 | Lightning Field
 38 | Darknight Relic
 39 | [INVALID]
 40 | Murky Cave
 41 | Grand Sea
 42 | Uproar Forest
 43 | Oddity Cave
 44 | Remains Island
 45 | Marvelous Sea
 46 | Fantasy Strait
 47 | Rock Path*
 48 | Snow Path*
 49 | [INVALID]
 50 | [INVALID]
 51 | [INVALID]
 52 | Dojo Registration*
 53 | Howling Forest
 54 | [INVALID]
 55 | Fantasy Strait
 56 | Waterfall Pond
 57 | Unown Relic
 58 | Joyous Tower
 59 | Far-off Sea
 60 | Mt. Faraway
 61 | [INVALID]
 62 | Purity Forest

**NOTE:** Dungeons marked with a * are valid but cannot be accepted in Wonder Mails.

**END OF API DOCUMENTATION**


# Internal functions  
**This thread is mainly for developers and contributors of this project.**  
These functions are used internally by the official API, and should not be used directly.  


## Decoding/Encoding - common internal functions  

----------  

```c
unsigned int getSpecialJobIndicator(int pairsIndex, int loversIndex, int parentsIndex)
```  
**Internal function, should not be used**  
Returns an indicator representing a number that indicates the type of special job. `pairsIndex`, `loversIndex` and `parentsIndex` are the return values of the functions `arePairs`, `areLovers` and `areParents` respectively. A special job is, for example, any mission that involves pairs of any kind (including lovers and parents). This is an internal function and should not be used.  

----------  


```c
int computeChecksum(const char* packedPassword, int bytes)
```  
**Internal function, should not be used**  
Returns the checksum of the first `bytes` bytes in the array `packedPassword`. The checksum is calculated by initializing a variable to `0`. Then, in each iteration, adds to itself each byte plus its index in the array, while truncating it to 1-byte long. This is an internal function and should not be used.  

----------  


## Decoding - internal functions


### General decoding - internal functions  

----------  

```c
void bitPackingDecoding(char* packedPassword, const char* unpackedPassword, int bytesToPack)
```  
**Internal function, should not be used**  
In a process called *bit packing*, `bytesToPack` bytes are read from `unpackedPassword` and packed in `packedPassword`. This optimization is done because only the first 5 bits of each octet are used. This is an internal function and should not be used.  

----------  


### Wonder Mail decoding - internal functions  

----------  

```c
void reallocateBytesDecodingWonderMail(const char *unallocatedPassword, char *allocatedPassword)
```  
**Internal function, should not be used**  
Returns in `allocatedPassword` a reallocated version of `unallocatedPassword`. This is an internal function and should not be used.  

----------  

```c
int lookupTableDecodingWonderMail(const char *allocatedPassword, char *passwordIntegers)
```  
**Internal function, should not be used**  
Since mails only works with alphanumeric characters plus some others, and not with the whole ASCCI collection, the value of each character can be reasigned in order to save storage space. New values are 5 bit long, instead of 8. The reassignment is done by using a lookup table. This function takes `allocatedPassword` which must be previously allocated with `reallocateBytesDecodingWonderMail` and returns the reassigned values in `passwordIntegers`. This is an internal function and should not be used.  

----------  

```c
void bitUnpackingDecodingWonderMail(const char *packed14BytesPassword, struct WonderMail* mail)
```  
**Internal function, should not be used**  
This function takes the packed 14 bytes stored in `packed14BytesPassword`, decodes them and writes the obtained information into `mail`. This is an internal function and should not be used.  

----------  

```c
int* flavorText(const struct WonderMail *wm, int pairsIndex, int loversIndex, int parentsIndex)
```  
**Internal function, should not be used**  
This function takes the decoded Wonder Mail `wm` as returned the function `bitUnpackingDecodingWonderMail`, and also the index of pairs, lovers and parents stored in `pairsIndex`, `loversIndex` and `parentsIndex` respectively. Only one of the last 3 arguments are relevant. The function returns a two-byte. The first one contains an integer code relative to the HEAD of the flavor text, and the second contains an integer code relative to the BODY of the flavor text. Then you can call `flavorTextHead` and `flavorTextBody` to get the flavor text. This is an internal function and should not be used.  

----------  

```c
void flavorTextHead(const struct WonderMail *wm, int headIndicator, int pairsIndex, int loversIndex, int parentsIndex, struct WonderMailInfo *mailInfo)
```  
**Internal function, should not be used**  
This function takes the decoded Wonder Mail `wm` as returned the function `bitUnpackingDecodingWonderMail`, the HEAD code returned by `flavorText` and stored in `headIndicator`, the index of pairs, lovers and parents stored in `pairsIndex`, `loversIndex` and `parentsIndex` respectively, and a structure `WonderMailInfo` named `mailInfo` in order to save the flavor text. Only one of the last 3 index arguments are relevant. Once this function returns, `mailInfo` contains the head of the flavor text. This is an internal function and should not be used.  

----------  

```c
void flavorTextBody(const struct WonderMail *wm, int bodyIndicator, int pairsIndex, int loversIndex, int parentsIndex, struct WonderMailInfo *mailInfo)
```  
**Internal function, should not be used**  
This function takes the decoded Wonder Mail `wm` as returned the function `bitUnpackingDecodingWonderMail`, the BODY code returned by `flavorText` and stored in `bodyIndicator`, the index of pairs, lovers and parents stored in `pairsIndex`, `loversIndex` and `parentsIndex` respectively, and a structure `WonderMailInfo` named `mailInfo` in order to save the flavor text. Only one of the last 3 index arguments are relevant. Once this function returns, `mailInfo` contains the body of the flavor text. This is an internal function and should not be used.  

----------  

```c
void setWonderMailInfo(const struct WonderMail *mail, struct WonderMailInfo *mailInfo)
```  
**Internal function, should not be used** 
This function extract the information contained in `mail` and write it to `mailInfo` in a mail-style layout. The flavor text is not filled here, you must call `flavorText` and related functions to do so. This is an internal function and should not be used.  

----------  


### SOS Mail decoding - internal functions  

----------

```c
void reallocateBytesDecodingSos(const char *unallocatedPassword, char *allocatedPassword)
```  
**Internal function, should not be used**  
Returns in `allocatedPassword` a reallocated version of `unallocatedPassword`. This is an internal function and should not be used.  

----------  

```c
int lookupTableDecodingSos(const char *allocatedPassword, char *passwordIntegers)
```  
**Internal function, should not be used**  
Since mails only works with alphanumeric characters plus some others, and not with the whole ASCCI collection, the value of each character can be reasigned in order to save storage space. New values are 5 bit long, instead of 8. The reassignment is done by using a lookup table. This function takes `allocatedPassword` which must be previously allocated with `reallocateBytesDecodingSos` and returns the reassigned values in `passwordIntegers`. This is an internal function and should not be used.  

----------  

```c
void bitUnpackingDecodingSos(const char *packed14BytesPassword, struct SosMail* mail)
```  
**Internal function, should not be used**  
This function takes the packed 14 bytes stored in `packed14BytesPassword`, decodes them and writes the obtained information into `mail`. This is an internal function and should not be used.  

----------  

```c
void setSosInfo(const struct SosMail *mail, struct SosMailInfo *sosInfo)
```  
**Internal function, should not be used** 
This function extract the information contained in `mail` and write it to `sosInfo` in a mail-style layout. This is an internal function and should not be used.  

----------  


## Encoding - internal functions


### Wonder Mail encoding - internal functions  

----------  

```c
void bitPackingEncodingWonderMail(const struct WonderMail* mail, char* packed14BytesPassword)
```  
**Internal function, should not be used**  
This function takes the content of the Wonder Mail `wm`, encodes it and writes the result to `packed14BytesPassword` in the form of packed 14 bytes. This is an internal function and should not be used.  

----------  

```c
void lookupTableEncodingWonderMail(const char* password24Integers, char* password24Chars)
```  
**Internal function, should not be used**  
This is the inverse process of decoding. This function takes `password24Integers` and writes the resulting ASCCI buffer in `password24Chars` using a lookup table. This is an internal function and should not be used.  

----------  

```c
void reallocateBytesEncodingWonderMail(const char* unallocatedPassword, char* allocatedPassword)
```  
**Internal function, should not be used**  
Returns in `allocatedPassword` a reallocated version of `unallocatedPassword`. This is an internal function and should not be used.  

----------  


### Wonder Mail encoding - internal functions  

----------  

```c
void bitPackingEncodingSos(const struct SosMail* mail, char* packed33BytesPassword)
```  
**Internal function, should not be used**  
This function takes the content of the SOS Mail `sos`, encodes it and writes the result to `packed33BytesPassword` in the form of packed 33 bytes. This is an internal function and should not be used.  

----------  

```c
void lookupTableEncodingSos(const char* password54Integers, char* password54Chars)
```  
**Internal function, should not be used**  
This is the inverse process of decoding. This function takes `password54Integers` and writes the resulting ASCCI buffer in `password54Chars` using a lookup table. This is an internal function and should not be used.  

----------  

```c
void reallocateBytesEncodingSos(const char* unallocatedPassword, char* allocatedPassword)
```  
**Internal function, should not be used**  
Returns in `allocatedPassword` a reallocated version of `unallocatedPassword`. This is an internal function and should not be used.  

----------  


## Converting - internal functions


----------  

```c
int sosMailIsInvalidForConverting(const char *SOSPassword, char *password54Integers)
```  
**Internal function, should not be used**  
Tries to convert the SOS Mail. Returns the error code (check the `ErrorType` enum type). If success (the mail is valid), the password is already converted to integers and reallocated in `password54Integers`. This is an internal function and should not be used.  

----------  

```c
void convertSosToAOkMail(char *password54Integers)
```  
**Internal function, should not be used**  
Converts the SOS intermediate integers password into a A-OK one. The password `password54Integers` is modified directly, so the SOS password is lost, keep that in mind. No error checking is done, i.e., the received buffer is always assumed as valid. This is an internal function and should not be used.  

----------  

```c
void convertAOkToThankYouMail(char *password54Integers, int item)
```  
**Internal function, should not be used**  
Converts the A-OK intermediate integers password into a Thank-You one with the reward item `item`. The password `password54Integers` is modified directly, so the A-OK password is lost, keep that in mind. No error checking is done, i.e., the received buffer is always assumed as valid. This is an internal function and should not be used.  

----------  
