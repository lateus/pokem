#ifndef MD1DATABASE_H
#define MD1DATABASE_H

/**
 **     C Header developed by Carlos Enrique Pérez Sánchez.
 **     Student of Automatic Engineering (2nd year, Havana, Cuba.
 **     Date: SAT, Juny 18th, 2017. 02:43 UTC.
 **/

/**
 **     
 **     This file is part of the source of the programs:
 **         DecodeWonderMail - Decode a Wonder Mail of Mystery Dungeon Red/Blue Rescue Team -
 **     
 **     So, this file is under the terms of the GNU General Public License v3. See bellow.
 **/

/*
    Copyright (C) 2017  Carlos Enrique Pérez Sánchez

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    CONTACT:
        carlosps@gmail.com

*/

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

#endif /* MD1DATABASE_H */
