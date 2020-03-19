#ifndef MD1DATABASE_H
#define MD1DATABASE_H

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

/* Forbidden floors in dungeons */
extern const int forbiddenFloorsInDungeons[][3];

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

#endif /* MD1DATABASE_H */
