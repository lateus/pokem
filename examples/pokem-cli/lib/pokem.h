#ifndef POKEM_H
#define POKEM_H

/** DEFINITIONS AND DATABASE: */

/*
    This header contains:
         1) Difficulties (by dungeon/floor)
         2) Difficulties characters
         3) Dungeon-up or dungeon-down
         4) Items that can be found in dungeons
         5) Mission type strings
         6) Standard titles and bodies strings
         7) Special flavor texts strings
         8) Pokémon species strings
         9) Items strings
        10) Dungeons strings
        11) Friend area strings
*/


/* Difficulties */
extern const int difficulties[][100];

/* Difficulties characters */
extern const int difficultiesCharsCount;
extern const char* difficultiesChars;

/* Dungeon-up or dungeon-down */
extern const char* dungeonUpOrDown;

/* Items in dungeons */
extern const int itemsInDungeons[][145];

/* Evolution checking */
extern const int thunderStonePkmn[];
extern const int fireStonePkmn[];
extern const int waterStonePkmn[];
extern const int leafStonePkmn[];
extern const int sunStonePkmn[];
extern const int moonStonePkmn[];
extern const int linkCablePkmn[];
extern const int deepSeaScalePkmn[];
extern const int deepSeaToothPkmn[];
extern const int dragonScalePkmn[];
extern const int kingsRockPkmn[];
extern const int metalCoatPkmn[];
extern const int upgradePkmn[];
extern const int sunRibbonPkmn[];
extern const int lunarRibbonPkmn[];
extern const int beautyScarfPkmn[];

/* Mission type */
extern const unsigned int missionTypeObjectiveCount;
extern const char* missionTypeObjectiveStr[];

/** *** Standard titles and bodies *** **/

/** Titles (heads) first... */
extern const char* msgTitleStandard_HelpMe[];
extern const char* msgTitleStandard_FindSomeone[];
extern const char* msgTitleStandard_Escort[];
extern const char* msgTitleStandard_FindItem;
extern const char* msgTitleStandard_DeliverItem;

/** Now, bodies... */
extern const char* msgBodyStandard_1Of2_Help[];
extern const char* msgBodyStandard_2Of2_Help[];
extern const char* msgBodyStandard_1Of2_FindSomeone[];
extern const char* msgBodyStandard_2Of2_FindSomeone[];
extern const char* msgBodyStandard_1Of2_Escort[];
extern const char* msgBodyStandard_2Of2_Escort[];
extern const char* msgBodyStandard_1Of2_FindDeliverItem[];
extern const char* msgBodyStandard_2Of2_FindDeliverItem[];


/** *** Special flavor texts *** **/

/* Parents */
extern const int parents[];
extern const char* parentsHead;
extern const char* parentsBody1Of2[];
extern const char* parentsBody2Of2[];

/* Pairs */
extern const int pairs[];
extern const char* friendsHead;
extern const char* loversHead;
extern const char* rivalsHead;
extern const char* brothersHead;
extern const char* pairsBody1Of2[];
extern const char* pairsBody2Of2[];

/* Lovers flavor text - Escort missions */
extern const int lovers[];
extern const char* loversEscortHead;
extern const char* loversBody1Of2[];
extern const char* loversBody2Of2[];


/* Special missions */
/*
    The following flavors texts are programmed in the game, provided just to complete the database.
    However, only the game can generate the respective Wonder Mail,
    and it also rejects any mail containing the following special missions.
*/
extern const char* mankeyTitle;
extern const char* smeargleTitle;
extern const char* medichamTitle;

extern const char* mankeyBody1Of2;
extern const char* mankeyBody2Of2;
extern const char* smeargleBody1Of2;
extern const char* smeargleBody2Of2;
extern const char* medichamBody1Of2;
extern const char* medichamBody2Of2;

/* Semi-special missions */
extern const char* evolutionBody1Of2;
extern const char* evolutionBody2Of2;
extern const char* foodBody1Of2;
extern const char* foodBody2Of2;

/* Rescue communication (SOS) */
extern const char* SOS_AskHelp1;
extern const char* SOS_AskHelp2;

extern const char* SOS_GoHelp1;
extern const char* SOS_GoHelp2;

extern const char* SOS_Thanks1;
extern const char* SOS_Thanks2;

/* Pokémon species */
extern const unsigned int pkmnSpeciesCount;
extern const char* pkmnSpeciesStr[];

/* Items */
extern const unsigned int itemsCount;
extern const char* itemsStr[];

/* Dungeons */
/* Note: Some of the dungeons bellow are useless because you can't accept a rescue on it, but are still provided as database. There are others unknown dungeons (invalid too) */
extern const unsigned int dungeonsCount;
extern const char* dungeonsStr[];

/* Friend areas */
extern const unsigned int friendAreasCount;
extern const char* friendAreasStr[];

/* Helper texts */
extern const char* friendZoneText;
extern const char* nearPlaceText;


/* Enable (1) or disable (0) debug messages */
#define DEBUG 1

/* Data definitions */

/* Mail type */
enum MailType { SosMailType = 1, AOkMailType = 4, ThankYouMailType = 5, WonderMailType = ThankYouMailType, InvalidMailType = 0x0F };

/* Error codes */
enum ErrorType { NoError, UnknownError, InputError, ChecksumError, OutOfRangeError };

/* The type of a mission */
enum MissionType { HelpMe, Find, Escort, FindItem, DeliverItem, FriendRescue };

/* The type of reward of a mission */
enum RewardType { Money, MoneyItem, Item, ItemItem, UnknownRewardType, MoneyMoney, MoneyMoneyItem, Item2, ItemItem2, FriendArea };

/* Encapsulates a Wonder Mail */
struct WonderMail {
    unsigned int mailType:4;              /* 4 bits: Must equal 5 for Wonder Mail */
    unsigned int missionType:3;           /* 3 bits: Mission Type: 0 (Help me), 1 (Find someone), 2 (Escort), 3 (Find item) and 4 (Deliver item) */
    unsigned int specialJobIndicator:4;   /* 4 bits: Usually 0, except in a few cases, mainly in special jobs */
    unsigned int pkmnClient:9;            /* 9 bits: Client Pokemon */
    unsigned int pkmnTarget:9;            /* 9 bits: Target Pokemon */
    unsigned int itemDeliverFind:8;       /* 8 bits: Item to find/deliver. Safe to set to 0x9 if mission type is 0, 1 or 2 */
    unsigned int rewardType:4;            /* 4 bits: Reward type: 0 (Money), 1 (Money + ?), 2 (Item), 3 (Item + ?), 5 (Money), 6 (Money + ?), 7 (Item), 8 (Item + ?), 9 (Friend area) */
    unsigned int itemReward:8;            /* 8 bits: Item reward */
    unsigned int friendAreaReward:6;      /* 6 bits: Friend Area reward */
    unsigned int flavorText:8;            /* 8 bits: A byte that hold information about the head and body of the mail message */
    unsigned int random:8;                /* 8 bits: A random byte. It allows that different mails (2^8 - 1 = 255) can have exactly the same info */
    unsigned int idk_always0xFF:8;        /* 8 bits: A byte for unknown purpose, maybe for validation (I'm not sure), but always with the value 0xFF */
    unsigned int dungeon:7;               /* 7 bits: Dungeon */
    unsigned int floor:7;                 /* 7 bits: Floor (e.g. set to 2 for 2nd floor). The game will turn the floor negative if necesary */
};

/* Encapsulates a SOS, A-OK or Thank-You Mail */
struct SosMail {
    unsigned int mailType:4;              /*  4 bits: Must equal 1 for SOS Mail, 4 for A-OK Mail, and 5 for Thank-You Mail */
    unsigned int dungeon:7;               /*  7 bits: Dungeon */
    unsigned int floor:7;                 /*  7 bits: Floor (e.g. set to 2 for 2nd floor). The game will turn the floor negative if necesary */
    unsigned int idk_random:24;           /* 24 bits: 3 bytes for unknown purpose, but it's value doesn't appears to influence */
    unsigned int pkmnToRescue:9;          /*  9 bits: Pokemon to be rescued */
    unsigned int mailID:16;               /* 16 bits: Mail ID */
    unsigned int idk_random2:16;          /* 16 bits: 2 bytes for unknown purpose, but it's value appears to be irrelevant */
    char         pkmnNick[10];            /* 80 bits: Pokemon's nickname, 0 marks end of the name string if shorter than 10 bytes */
    unsigned int idk_0Or1:8;              /*  8 bits: A byte for unknown purpose. Safe to set to 1 if Thank-You Mail, else set to 0 */
    unsigned int itemReward:8;            /*  8 bits: Item reward. Safe to set to 0 if not Thank-You Mail */
    unsigned int idk_0:8;                 /*  8 bits: A byte for unknown purpose. Safe to set to 0 */
    unsigned int teamSeekingHelpID:32;    /* 32 bits: ID of rescue team seeking help */
    unsigned int teamGivingHelpID:32;     /* 32 bits: ID of rescue team giving help. For SOS Mail, this is 0; for A-OK Mail, safe to set to rescue team seeking help */
    unsigned int chancesLeft:8;           /*  8 bits: Rescue chances left; when converting to A-OK Mail, subtract 1 from this */
    unsigned int idk_last3Bits:3;         /*  3 bits: Three bits for unknown purpose. Safe to set to 0 */
};

/* Contains the human-readable information of a Wonder Mail */
struct WonderMailInfo {
    char head[26];
    char body1[100];
    char body2[100];
    char client[11];
    char objective[22];
    char place[26];
    char floor[7];
    char difficulty;
    char reward[35];
    char password[25];
};

/* Contains the human-readable information of a SOS, A-OK or Thank-You Mail */
struct SosMailInfo {
    char head[40];
    char body[33];
    char nickname[11];
    char client[11];
    char objective[15];
    char place[26];
    char floor[7];
    char difficulty;
    char reward[19];
    char id[6];
    char chancesLeft[3];
    char password[100];
};


/** CORE FUNCTIONALITIES: */

/* CONVERTING SOS MAIL FUNCTIONS */
int convertSosMail(const char *SOSPassword, int item, char *resultAOKMail, char *resultThankYouMail);
void convertSosToAOkMail(char *password54Integers);
void convertAOkToThankYouMail(char *password54Integers, int item);



/* DECODING SOS MAIL FUNCTIONS */
int decodeSosMail(const char *password, struct SosMail *sosMailResult);
void bitUnpackingDecodingSosMail(const char *packed14BytesPassword, struct SosMail* mail);
void setSosInfo(const struct SosMail *mail, struct SosMailInfo *sosInfo);



/* DECODING WONDER MAIL FUNCTIONS */
int decodeWonderMail(const char *password, struct WonderMail *wonderMailResult);
void bitUnpackingDecodingWonderMail(const char *packed14BytesPassword, struct WonderMail* mail);
void setFlavorText(const struct WonderMail *wm, struct WonderMailInfo *mailInfo);
void setFlavorTextHead(const struct WonderMail *wm, int headIndicator, int pairsIndex, int loversIndex, int parentsIndex, struct WonderMailInfo *mailInfo);
void setFlavorTextBody(const struct WonderMail *wm, int bodyIndicator, int pairsIndex, int loversIndex, int parentsIndex, struct WonderMailInfo *mailInfo);
void setWonderMailInfo(const struct WonderMail *mail, struct WonderMailInfo *mailInfo);


/* DECODING COMMON FUNCTIONS */
void bitPackingDecoding(char* packedPassword, const char* unpackedPassword, int bytesToPack);



/* ENCODING SOS MAIL FUNCTIONS */
int encodeSosMail(struct SosMail *sos, char *finalPassword);
void bitPackingEncodingSos(const struct SosMail* mail, char* packed33BytesPassword);



/* ENCODING WONDER MAIL FUNCTIONS */
int encodeWonderMail(struct WonderMail *wm, char *finalPassword, int trySpecialWonderMail);
void bitPackingEncodingWonderMail(const struct WonderMail* mail, char* packed14BytesPassword);


/* ENCODING COMMON FUNCTIONS */
void bitUnpackingEncoding(const char* packedPassword, char* unpackedIntegers, int bytesToUnpack);



/* DECODING/ENCODING COMMON FUNCTIONS */
int areParents(int pkmnClient, int pkmnTarget);
int arePairs(int pkmnClient, int pkmnTarget);
int areLovers(int pkmnClient, int pkmnTarget);
int canEvolveWithItem(int pkmn, int item);
int isFood(int item);
unsigned int getSpecialJobIndicator(int pkmnClient, int pkmnTarget, int missionType, int trySpecialJobIndicator, int itemToFindDeliver);
int getMailType(const char* password);
int findItemByDungeon(int item, int dungeon);
int computeDifficulty(int dungeon, int dungeonFloor, int missionType);
int computeMoneyReward(int difficulty, int rewardType);
int computeChecksum(const char* packedPassword, int bytes);
int entryErrorsWonderMail(const struct WonderMail *wm);
int entryErrorsSosMail(const struct SosMail *sos);
void reallocateBytes(const char* unallocatedBytes, const unsigned char newPositions[], int n, char* allocatedBytes);
int mapPasswordByPositionInLookupTable(const char* password, const char* lookupTable, int n, char* newPassword);


#endif /* POKEM_H */