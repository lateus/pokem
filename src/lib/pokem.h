#ifndef POKEM_H
#define POKEM_H

/* Data definitions */
enum ERROR_TYPE { ALL_OK, UNKNOWN_ERROR, INPUT_ERROR, CHECKSUM_ERROR, OUT_OF_RANGE_ERROR };
enum MISSION_TYPE { HELPME, FIND, ESCORT, FINDITEM, DELIVERITEM, FRIENDRESCUE };
enum FLAVOR_TEXT_TYPE { FT_HEAD, FT_BODY };

/* If not programming in C, consider use buffers objects instead of structs and bit fields, it will be slower of course, but more safe and readable (performance is not everything) */
struct WONDERMAIL {
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

struct SOSMAIL {
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
    unsigned int idk_last3Bits:3;         /*  3 bits: Three bits for unknown. Safe to set to 0 */
};

/*
    WARNING: Be careful with the size of arrays while translating!
             If not C, consider use dynamic string objects instead of pure and neutral C-style arrays (pointers to have direct low-level access to RAM memory).
             It will be slower of course, but safer (performance is not everything).
             Note: Only a few languages implements arrays as pointers to have fast access to volatile RAM memory, the rest are slow objects and you don't have choice: you can't use pointers.
*/
struct WM_INFO {
    char head[26];
    char body1[100];
    char body2[100];
    char client[11];
    char objective[22];
    char place[26];
    char floor[7];
    char difficulty;
    char reward[35];
    char WMail[50];
};

struct SOS_INFO {
    char head[40];
    char body[26];
    char nickname[11];
    char client[11];
    char objective[15];
    char place[26];
    char floor[7];
    char difficulty;
    char reward[4];
    char id[16];
    char chancesLeft[4];
    char SOSMail[100];
};

/* Difficulties */
extern const int difficulties[][100];

/* Difficulties characters */
extern const char* difficultiesChars;

/* Dungeon-up or dungeon-down */
extern const char* dungeonUpOrDown;

/* Items in dungeons */
extern const int itemsInDungeons[][145];

/* Mission type */
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

/*
    The following flavors texts are programmed in the game, provided just to complete the database.
    However, only the game can generate the respective Wonder Mail,
    and it also make invalid a Wonder Mail that contains the following special missions, rejecting that mail.

    So you can uncomment the code bellow, but it is useless, and only increase the size of the binary executable.
*/
/* Special missions */
/*
extern const char* MankeyTitle;
extern const char* SmeargleTitle;
extern const char* MedichamTitle;

extern const char* Mankey;
extern const char* Smeargle;
extern const char* Medicham;
extern const char* Special1;
extern const char* Special2;
*/

/* Rescue communication (SOS) */
extern const char* SOS_AskHelp1;
extern const char* SOS_AskHelp2;

extern const char* SOS_GoHelp1;
extern const char* SOS_GoHelp2;

extern const char* SOS_Thanks1;
extern const char* SOS_Thanks2;

/* Pokémon species */
extern const char* pkmnSpeciesStr[];

/* Items */
extern const char* itemsStr[];

/* Dungeons */
/* Note: Some of the dungeons bellow are useless because you can't accept a rescue on it, but are still provided as database. There are others unknown dungeons (invalid too) */
extern const char* dungeonsStr[];

/* Friend areas */
extern const char* friendAreasStr[];

/* DECODING/ENCODING COMMON FUNCTIONS */
int areParents(int pkmnClient, int pkmnTarget);
int arePairs(int pkmnClient, int pkmnTarget);
int areLovers(int pkmnClient, int pkmnTarget);
unsigned int getSpecialJobIndicator(int pairsIndex, int loversIndex, int parentsIndex);
int findItemByDungeon(int item, int dungeon);
int computeDifficulty(int dungeon, int dungeonFloor, int missionType);
int computeMoneyReward(int difficulty, int rewardType);
int computeChecksum(const char* packedPassword, int bytes);

/* DECODING COMMON FUNCTIONS */
void bitPackingDecoding(char* packedPassword, const char* unpackedPassword, int bytesToPack);

/* DECODING WONDER MAIL */
int decodeWonderMail(const char *password, struct WM_INFO *wonderMailInfoResult);
int WonderMailIsInvalid(const char *password, char *packed15BytesPassword);
void reallocateBytesDecodingWM(char *allocatePassword, const char *unallocatedPassword);
int lookupTableDecodingWM(char *passwordIntegers, const char *allocatedPassword);
void bitUnpackingDecodingWM(const char *packed14BytesPassword, struct WONDERMAIL* mail);
int* flavorText(const struct WONDERMAIL *wm, int pairsIndex, int loversIndex, int parentsIndex);
void flavorTextHead(const struct WONDERMAIL *wm, int headIndicator, int pairsIndex, int loversIndex, int parentsIndex, struct WM_INFO *mailInfo);
void flavorTextBody(const struct WONDERMAIL *wm, int bodyIndicator, int pairsIndex, int loversIndex, int parentsIndex, struct WM_INFO *mailInfo);
void setWMInfo(struct WM_INFO *mailInfo, const struct WONDERMAIL *mail);

/* DECODING SOS MAIL */
int decodeSOSMail(const char *sosPassword, struct SOS_INFO *sosMailInfoResult);
int SOSMailIsInvalid(const char *password, char *packed34BytesPassword);
void reallocateBytesDecodingSOS(const char *unallocatedPassword, char *allocatedPassword);
int lookupTableDecodingSOS(const char *allocatedPassword, char *passwordIntegers);
void bitUnpackingDecodingSOS(const char *packed14BytesPassword, struct SOSMAIL* mail);
void setSOSInfo(struct SOS_INFO *sosInfo, const struct SOSMAIL *mail);

/* ENCODING COMMON FUNCTIONS */
void bitUnpackingEncoding(char* unpackedIntegers, const char* packedPassword, int bytesToUnpack);

/* ENCODING WONDER MAIL */
int encodeWonderMail(struct WONDERMAIL *wm, char *finalPassword);
int foundErrorsEntriesWM(const struct WONDERMAIL *wm);
void bitPackingEncodingWM(char* packed14BytesPassword, const struct WONDERMAIL* mail);
void lookupTableEncodingWM(const char* password24Integers, char* password24Chars);
void reallocateBytesEncodingWM(const char* unallocatedPassword, char* allocatePassword);

/* ENCODING SOS MAIL */
int encodeSOSMail(struct SOSMAIL *sos, char *finalPassword);
int foundErrorsEntriesSOS(const struct SOSMAIL *sos);
void bitPackingEncodingSOS(char* packed33BytesPassword, const struct SOSMAIL* mail);
void lookupTableEncodingSOS(char* password54Chars, const char* password54Integers);
void realocateBytesEncodingSOS(char* allocatedPassword, const char* unallocatedPassword);

/* CONVERTING SOS MAIL */
int convertSOSMail(const char *SOSPassword, int item, char *resultAOKMail, char *resultThankYouMail);
int SOSMailIsInvalidForConverting(const char *SOSPassword, char *password54Integers);
void convertSOSToAOKMail(char *password54Integers);
void convertAOKToThankYouMail(char *password54Integers, int item);

#endif /* POKEM_H */