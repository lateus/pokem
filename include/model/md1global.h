#ifndef MD1GLOBAL_H
#define MD1GLOBAL_H

#define INPUT_ERROR  1          /* Value returned when an input error ocurr */
#define CHECKSUM_ERROR 2        /* Value returnes when the checksum fails */
#define HELP 3                  /* Value returned when the help is requested (no arguments are received) */
#define PSW_SUCCESS_OPERATION 0 /* All is OK for now */
/* For the text indicator. Used to specify the head or body in flavors texts. */
#define HEAD 0
#define BODY 1

/* Data definitions */
enum MAIL_TYPE { WONDER, SOS };
enum MISSION_TYPE { HELPME, FIND, ESCORT, FINDITEM, DELIVERITEM, FRIENDRESCUE };

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

#endif /* MD1GLOBAL_H */
