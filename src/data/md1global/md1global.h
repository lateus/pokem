#ifndef MD1GLOBAL_H
#define MD1GLOBAL_H

/* Data definitions */

/* Error codes */
enum ErrorType {
    NoError,                                /* no error, all OK */
    UnknownError,                           /* unknown error */
    MultipleError,                          /* multiple errors */
    InputError,                             /* generic input error */
    OutputError,                            /* generic output error */
    ChecksumError,                          /* checksum error */
    MailTypeError,                          /* the mail type is invalid */
    MissionTypeError,                       /* the mission type is invalid */
    SpecialJobIndicatorError,               /* the special job indicator is invalid */
    PokemonOutOfRangeError,                 /* the pokemon is out of range */
    PokemonNotAllowedError,                 /* the pokemon is invalid (for example, a legendary) */
    ItemOutOfRangeError,                    /* the item is out of range */
    NoItemError,                            /* the item is `0` (Nothing), which is not necessarily an error */
    ItemCannotBeObtainedError,              /* the item exists but cannot be obtained, usually the item is a Beatup Orb or a G Machine */
    ItemNotExistsInDungeonError,            /* the item do not exists in the dungeon */
    RewardTypeError,                        /* the reward type is invalid */
    FriendAreaOutOfRangeError,              /* the friend area is out of range */
    FriendAreaIsInvalidAsRewardError,       /* the friend area cannot be set as reward */
    DungeonOutOfRangeError,                 /* the dungeon is out of range */
    DungeonIsInvalidError,                  /* the dungeon exists, but it is invalid */
    MissionCannotBeAcceptedInDungeonError,  /* the mission can be generated, but cannot be accepted (for example, a peak or the Makuhita's Dojo) */
    FloorOutOfRangeError,                   /* the dungeon do not have the selected floor */
    FloorInvalidInDungeonError,             /* the floor exists, but a mission cannot be done there (for example, boss and warp floors) */
    MailIDOutOfRangeError,                  /* the mail ID is invalid */
    NicknameEmptyError,                     /* the nickname is empty */
    ChancesLeftError,                       /* the amount of chances left is invalid */
    IncorrectPasswordLengthError,           /* the length of the password is invalid */
    InvalidCharacterError,                  /* the password contains an invalid character */
    ConversionError                         /* the password couldn't be converted */
};

/* Mail type */
enum MailType { SosMailType = 1, AOkMailType = 4, ThankYouMailType = 5, WonderMailType = ThankYouMailType, InvalidMailType = 0x0F };

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
    unsigned int random:8;                /* 8 bits: A random byte. It allows that different mails (2^8 = 256) can have exactly the same info */
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
    char chancesLeft[4];
    char password[100];
};

#endif /* MD1GLOBAL_H */