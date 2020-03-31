#include "../../../test/CuTest.h"

#include "UtilCore.h"
#include "../../data/md1global/md1global.h"
#include "../../data/md1database/md1database.h"

#include <stdlib.h>


CuSuite* UtilCoreGetTestSuite(void);

void areParents_test(CuTest *tc);
void arePairs_test(CuTest *tc);
void areLovers_test(CuTest *tc);
void canEvolveWithItem_test(CuTest *tc);
void isFood_test(CuTest *tc);
void getSpecialJobIndicator_test(CuTest *tc);
void getMailType_test(CuTest *tc);
void computeDifficulty_test(CuTest *tc);
void computeMoneyReward_test(CuTest *tc);
void computeChecksum_test(CuTest *tc);
void entryErrorsWonderMail_test(CuTest *tc);
void entryErrorsSosMail_test(CuTest *tc);
void reallocateBytes_test(CuTest *tc);
void mapPasswordByPositionInLookupTable_test(CuTest *tc);
void checkPokemon_test(CuTest *tc);
void checkDungeon_test(CuTest *tc);
void checkFloor_test(CuTest *tc);
void checkItem_test(CuTest *tc);
void checkItemExistenceInDungeon_test(CuTest *tc);
void checkFriendArea_test(CuTest *tc);
void checkMailID_test(CuTest *tc);


CuSuite* UtilCoreGetTestSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, areParents_test);
    SUITE_ADD_TEST(suite, arePairs_test);
    SUITE_ADD_TEST(suite, areLovers_test);
    SUITE_ADD_TEST(suite, canEvolveWithItem_test);
    SUITE_ADD_TEST(suite, isFood_test);
    SUITE_ADD_TEST(suite, getSpecialJobIndicator_test);
    SUITE_ADD_TEST(suite, getMailType_test);
    SUITE_ADD_TEST(suite, computeDifficulty_test);
    SUITE_ADD_TEST(suite, computeMoneyReward_test);
    SUITE_ADD_TEST(suite, computeChecksum_test);
    SUITE_ADD_TEST(suite, entryErrorsWonderMail_test);
    SUITE_ADD_TEST(suite, entryErrorsSosMail_test);
    SUITE_ADD_TEST(suite, reallocateBytes_test);
    SUITE_ADD_TEST(suite, mapPasswordByPositionInLookupTable_test);
    SUITE_ADD_TEST(suite, checkPokemon_test);
    SUITE_ADD_TEST(suite, checkDungeon_test);
    SUITE_ADD_TEST(suite, checkFloor_test);
    SUITE_ADD_TEST(suite, checkItem_test);
    SUITE_ADD_TEST(suite, checkItemExistenceInDungeon_test);
    SUITE_ADD_TEST(suite, checkFriendArea_test);
    SUITE_ADD_TEST(suite, checkMailID_test);
    return suite;
}

void areParents_test(CuTest *tc)
{
#define ARRAY_SIZE 8
    int input1[ARRAY_SIZE] = { 15, 13, 18, 19, 1, 242, 353, 173 };
    int input2[ARRAY_SIZE] = { 13, 15, 16, 20, 1, 323, 329, 273 };

    int actual[ARRAY_SIZE];
    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actual[i] = areParents(input1[i], input2[i]);
    }

    int expected[ARRAY_SIZE] = { 0, -1, 1, -1, -1, -1, -1, -1 };
    for (i = 0; i < ARRAY_SIZE; ++i) {
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
#undef ARRAY_SIZE
}

void arePairs_test(CuTest *tc)
{
#define ARRAY_SIZE 8
    int input1[ARRAY_SIZE] = { 103,  85,  22,  90, 1, 49, 240, 360 };
    int input2[ARRAY_SIZE] = {  85, 103, 112, 394, 1, 57, 323, 175 };

    int actual[ARRAY_SIZE];
    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actual[i] = arePairs(input1[i], input2[i]);
    }

    int expected[ARRAY_SIZE] = { 0, 0, 1, 2, -1, -1, -1, -1 };
    for (i = 0; i < ARRAY_SIZE; ++i) {
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
#undef ARRAY_SIZE
}

void areLovers_test(CuTest *tc)
{
#define ARRAY_SIZE 8
    int input1[ARRAY_SIZE] = { 32, 29, 33, 31, 1, 32, 29, 338 };
    int input2[ARRAY_SIZE] = { 29, 32, 30, 34, 1, 33, 30, 336 };

    int actual[ARRAY_SIZE];
    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actual[i] = areLovers(input1[i], input2[i]);
    }

    int expected[ARRAY_SIZE] = { 0, 0, 1, 2, -1, -1, -1, -1 };
    for (i = 0; i < ARRAY_SIZE; ++i) {
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
#undef ARRAY_SIZE
}

void canEvolveWithItem_test(CuTest *tc)
{
    const int pkmnsToTest[16][6] = {
        /* the first index is the size of the respective array */
        { 2, 25, 133 }, /* thunderStone (108) - Pikachu and Eevee */
        { 3, 37, 58, 133 }, /* fireStone (113) - Vulpix, Growlithe and Eevee */
        { 5, 61, 90, 120, 133, 296 }, /* waterStone (114) - Poliwhirl, Shellder, Staryu, Eevee and Lombre */
        { 4, 44, 70, 102, 299 }, /* leafStone (116) - Gloom, Weepinbell, Exeggcute and Nuzleaf */
        { 2, 44, 191 }, /* sunStone (111) - Gloom and Sunkern */
        { 5, 30, 33, 35, 39, 325 }, /* moonStone (112) - Nidorina, Nidorino, Clefairy, Jigglypuff and Skitty */
        { 4, 64, 67, 75, 93 }, /* linkCable (118) - Kadabra, Machoke, Graveler and Haunter */
        { 1, 394 }, /* deepSeaScale (109) - Clamperl */
        { 1, 394 }, /* deepSeaTooth (110) - Same as `deepSeaScale`: Clamperl */
        { 1, 117 }, /* dragonScale (117) - Seadra */
        { 1, 80 }, /* kingsRock (107) - Slowbro */
        { 2, 95, 123 }, /* metalCoat (115) - Onix and Scyther */
        { 1, 137 }, /* upgrade (106) - Porygon */
        { 1, 133 }, /* sunRibbon (48) - Eevee */
        { 1, 133 }, /* lunarRibbon (49) - Same as `sunRibbonPkmn`: Eevee */
        { 1, 374 } /* beautyScarf (47) - Feebas */
    };
    /* the items mentioned above, in the same order */
    const int itemsToTest[] = { 16, 108, 113, 114, 116, 111, 112, 118, 109, 110, 117, 107, 115, 106, 48, 49, 47 };

    int testResult, expectedResult;
    int itm, itmEvol, pkm, pkmEvol;
    for (itm = 0; itm < itemsCount; ++itm) {
        for (itmEvol = 1; itmEvol <= itemsToTest[0]; ++itmEvol) {
            if (itemsToTest[itmEvol] == itm) {
                break;
            }
        }
        for (pkm = 0; pkm < pkmnSpeciesCount; ++pkm) {
            if (itmEvol <= itemsToTest[0]) {
                for (pkmEvol = 1; pkmEvol <= pkmnsToTest[itmEvol - 1][0]; ++pkmEvol) {
                    if (pkmnsToTest[itmEvol - 1][pkmEvol] == pkm) {
                        break;
                    }
                }
            }
            testResult = canEvolveWithItem(pkm, itm);
            expectedResult = itmEvol <= itemsToTest[0] && pkmEvol <= pkmnsToTest[itmEvol - 1][0];
            CuAssertIntEquals(tc, expectedResult, testResult);
        }
    }
}

void isFood_test(CuTest *tc)
{
    int testResult, expectedResult;
    int itm;
    for (itm = 0; itm < itemsCount; ++itm) {
        testResult = isFood(itm);
        expectedResult = itm == 82  || /* Apple */
                         itm == 83  || /* Big Apple */
                         itm == 85  || /* Huge Apple */
                         itm == 103 || /* Banana */
                         (itm >= 86 && itm <= 102); /* Gummis */;
        CuAssertIntEquals(tc, expectedResult, testResult);
    }
}

void getSpecialJobIndicator_test(CuTest *tc)
{
#define ARRAY_SIZE 30
    /* Tests comments:                          /0 - From here, test validspecial jobs                                                         /11 - From here test same inputs but with wrong mission types                                 /22 - Disable trying of special job              /26 - Wrong pkmn combinations */
    const int input1[ARRAY_SIZE]            = {  176,  169,   49,  266,  172,    266,    337,       25,         123,      102,         300,       176,    169,       49,         266,    172,  266,    337,     25,    123,  102,    300,          25,         123,      102,         300,     175,  169,  200,     21 };
    const int input2[ARRAY_SIZE]            = {  175,   41,  294,  128,  172,    128,    336,        0,         321,      200,           1,       175,     41,      294,         128,    172,  128,    336,      0,    321,  200,      1,           0,         321,      200,           1,     176,   69,  172,     18 };
    const int input3[ARRAY_SIZE]            = { Find, Find, Find, Find, Find, Escort, Escort, FindItem, DeliverItem, FindItem, DeliverItem,    HelpMe, Escort, FindItem, DeliverItem, Escort, FindItem, HelpMe, HelpMe, Escort, Find, HelpMe,    FindItem, DeliverItem, FindItem, DeliverItem,    Find, Find, Find, Escort };
    const int input4[ARRAY_SIZE]            = {    0,    1,    0,    1,    0,      1,      0,        1,           1,        1,           1,         0,      1,        0,           1,      0,    1,      0,      1,      1,    1,      1,           0,           0,        0,           0,       0,    1,    0,      1 };
    const int input5[ARRAY_SIZE]            = {  102,  250,   68,    0,  111,     31,    100,      108,         115,       82,          99,       102,    250,       68,           0,    111,   31,    100,    108,    115,   82,     99,         108,         115,       82,          99,     102,  250,  111,     31 };

    unsigned int actualResults[ARRAY_SIZE];
    const unsigned int expected[ARRAY_SIZE] = { 0x0F, 0x0F, 0x09, 0x09, 0x09,   0x0A,   0x0A,     0x05,        0x05,     0x06,        0x06,         0,      0,        0,           0,      0,    0,      0,      0,      0,    0,      0,           0,           0,        0,           0,       0,    0,    0,      0 };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actualResults[i] = getSpecialJobIndicator(input1[i], input2[i], input3[i], input4[i], input5[i]);
        CuAssertIntEquals(tc, expected[i], actualResults[i]);
    }
#undef ARRAY_SIZE
}

void getMailType_test(CuTest *tc)
{
#define ARRAY_SIZE 20
    char input[ARRAY_SIZE][55 + 1] = {
        "4X04N?7P6JP?1?3/W94?????",  /* (WM - VALID) */
        "4X04N?7P6JP?1?3/W94????",   /* (WM - INVALID) */
        "4X04N?7P6JP?1?3/W94??????", /* (WM - INVALID) */
        "4X04N?7P6JP?1?3/W94????A",  /* (WM - INVALID, but will pass since only the second and third characters are used to get the type in 24 chars passwords) */
        "J+047*?JK6+?49RM?F?N????",  /* (WM - VALID) */
        "8004SS8P62!HSNH4W*956???",  /* (WM - VALID) */
        "*S54++R6X?????SCWN46????",  /* (WM - VALID) */
        "*0T4R37/T???F7!/WCP+????",  /* (WM - VALID) */
        ".Y5JMF0PXC!?123WW.PS????",  /* (WM - VALID - SPECIAL EVOLVE) */
        "YY58?N4R.NN7F+YQW.JN????",  /* (WM - VALID - SPECIAL FOOD) */
        "N???2JR.1W/??R09?!?N????NFC??1??Q3H???X?K-Y??58??WS0T.",  /* (SOS - VALID) */
        "N???2JR.1W/??R09?!?N????NFC??1??Q3H???X?K-Y??58??WS0T",   /* (SOS - INVALID) */
        "N???2JR.1W/??R09?!?N????NFC??1??Q3H???X?K-Y??58??WS0T..", /* (SOS - INVALID) */
        "?8?653?0KN4??599/M2.??4R313P?*?8+3H5??TN!T!/X/.??2/Q02",  /* (SOS - VALID) */
        "????6+7SHX???1?4???H??4?NP???4???TR?????X25??PJ??07?C?",  /* (SOS - VALID) */
        "?M?P?.P766??Y*FC?!?R7?M?3JCP?-H?32H??0Y?M4C??1J-?NQ04?",  /* (AOK - VALID) */
        "???16+67HX??F4?4???HT?M?NR???40??TR??2??X25??PJ-?07?C?",  /* (AOK - VALID) */
        "?M1P?.PS66??Y*FC?!?R7?M?3JCP?-H?32H?30Y?M4C??1J-4NQ04?",  /* (THX - VALID) */
        "??F16+6THX??FT?4???HT?M?NR???40??TR?52??X25??PJ-407?C?",  /* (THX - VALID) */
        ""                                                         /* (INVALID) */
    };

    int actual[ARRAY_SIZE];

    int expected[ARRAY_SIZE] = { WonderMailType, InvalidMailType, InvalidMailType, WonderMailType, WonderMailType, WonderMailType, WonderMailType, WonderMailType, WonderMailType, WonderMailType, SosMailType, InvalidMailType, InvalidMailType, SosMailType, SosMailType, AOkMailType, AOkMailType, ThankYouMailType, ThankYouMailType, InvalidMailType };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actual[i] = getMailType(input[i]);
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
#undef ARRAY_SIZE
}

void computeDifficulty_test(CuTest *tc)
{
#define ARRAY_SIZE 10
    int input1[ARRAY_SIZE] = {    0,      0,       17,     18,          62,     62,           62,     62,     62,     62 };
    int input2[ARRAY_SIZE] = {    1,      1,       25,      1,           1,      1,           20,     25,     25,     60 };
    int input3[ARRAY_SIZE] = { Find, Escort, FindItem, HelpMe, DeliverItem, Escort, FriendRescue, HelpMe, Escort, HelpMe };

    int actual[ARRAY_SIZE];
    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actual[i] = computeDifficulty(input1[i], input2[i], input3[i]);
    }

    int expected[ARRAY_SIZE] = { 0, 1, 3, 3, 4, 5, 4, 5, 6, 6 };
    for (i = 0; i < ARRAY_SIZE; ++i) {
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
#undef ARRAY_SIZE
}

void computeMoneyReward_test(CuTest *tc)
{
#define ARRAY_SIZE 17
    int input1[ARRAY_SIZE] = { 0, 1, 1, 1, 2, 3, 4, 5, 6, 6, 0, 1, 2, 3, 4, 5, 6 };
    int input2[ARRAY_SIZE] = { 0, 1, 5, 6, 0, 0, 0, 1, 1, 5, 2, 3, 4, 7, 8, 9, 9 };

    int actual[ARRAY_SIZE];
    int expected[ARRAY_SIZE] = { 100, 200, 400, 400, 300, 400, 500, 600, 700, 1400, 0, 0, 0, 0, 0, 0, 0 };
    
    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actual[i] = computeMoneyReward(input1[i], input2[i]);
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
#undef ARRAY_SIZE
}

void computeChecksum_test(CuTest *tc)
{
#define ARRAY_SIZE 4
    unsigned char input1[ARRAY_SIZE][34] = {
        { 0xD0, 0x25, 0x38, 0x80, 0x20, 0xA1, 0x12, 0x80, 0x01, 0xF7, 0xFF, 0x40, 0x00, 0x00, 0x00 }, /* 1?J9N/X?4P?34??764?0P??W (WM - VALID) */
        { 0x55, 0x25, 0x28, 0x36, 0xA8, 0x37, 0x28, 0x00, 0x4F, 0x91, 0x00, 0x81, 0x01, 0x00, 0x00 }, /* 4?6F7M+?4JNRJ*??K??0+9?? (WM - VALID) */
        { 0x39, 0xD1, 0x09, 0xEC, 0x1C, 0xA1, 0x60, 0x8E, 0x26, 0x81, 0x92, 0x67, 0xAA, 0xD3, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x7D, 0x49, 0x58, 0x01, 0x00, 0x00, 0x00, 0x50, 0x00 }, /* ?M???.R066???2FC?!?R????3HCP?-??32H???Y?M4C??1J??NQ04? (SOS - VALID) */
        { 0x03, 0x61, 0x0A, 0x4C, 0x11, 0x60, 0x5E, 0xFA, 0xF5, 0xA9, 0xE1, 0x0A, 0x12, 0x2B, 0x63, 0x03, 0x91, 0x7A, 0x13, 0x2B, 0x63, 0x03, 0x00, 0x00, 0x08, 0x7D, 0x49, 0x58, 0x01, 0x00, 0x00, 0x00, 0x50, 0x00 }  /* S6???.RF?6F??NWH*5KC???RH1!9?8?JK7P0??SNMJRPSKJ??7QJ4N (SOS - VALID) */
    };
    int input2[ARRAY_SIZE] = { 14, 14, 33, 33 };

    int actual[ARRAY_SIZE];

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actual[i] = computeChecksum((char*)(input1[i] + 1), input2[i]); /* the first byte is ignored in the calculation, cuz is merely for a checksum */
        CuAssertIntEquals(tc, input1[i][0], actual[i]);
    }
#undef ARRAY_SIZE
}

void entryErrorsWonderMail_test(CuTest *tc)
{
#define ARRAY_SIZE 8
    const struct WonderMail input[ARRAY_SIZE] = {
        /*         Mail type,    Mission type,  Special job, Pkmn Client, Pkmn target, Item F/D,    Reward type, Reward item, Friend area, Flavor, Random, 0xFF, Dungeon, Floor */
        {     WonderMailType,          HelpMe,         0x00,           1,           0,        9,          Money,           0,           0,      0,   0x00, 0x00,       0,     1 },
        {     WonderMailType,     DeliverItem,         0x01,         404,         414,      232,     FriendArea,         239,          37,   0xFF,   0xFF, 0xFF,      62,    98 },
        {     WonderMailType,     DeliverItem,         0x02,         404,         414,      232,     FriendArea,         239,          37,   0xFF,   0xFF, 0xFF,       0,     1 }, /* Friend area ('E' difficulty) */
        {        SosMailType,            Find,         0x03,         405,         415,      255, FriendArea + 1,         240,          60,      0,      0, 0xFF,      63,    99 }, /* Mail type, pkmn client, pkmn target, reward type and dungeon */
        {        AOkMailType,     DeliverItem,         0x04,         415,           0,      233,     FriendArea,         255,           0,      0,      0, 0xFF,       0,     0 }, /* Mail type, pkmn client, friend area and floor  */
        {   ThankYouMailType, DeliverItem + 1,         0x05,         210,         511,      240,      MoneyItem,           0,          63,      0,      0, 0xFF,       0,     4 }, /* Mission type, pkmn client, reward item and floor. Note: Not the Mail type cuz ThankYouMail == WonderMail */
        { WonderMailType + 1,          Escort,         0x0E,         150,         151,        0,      MoneyItem,         240,          19,      0,      0, 0xFF,      10,     4 }, /* Mail type, pkmn client, pkmn target, item reward and floor */
        {    InvalidMailType,        FindItem,         0x0F,         201,           0,        1,     FriendArea,         250,          19,      0,      0, 0xFF,      23,    99 }  /* Mail type, pkmn client, item to find and friend area and floor */
    };

    int actualResults[ARRAY_SIZE];

    const int expectedResults[ARRAY_SIZE] = { 0, 0, 1, 5, 4, 4, 5, 5 };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actualResults[i] = entryErrorsWonderMail(&input[i]);
        CuAssertIntEquals(tc, expectedResults[i], actualResults[i]);
    }
#undef ARRAY_SIZE
}

void entryErrorsSosMail_test(CuTest *tc)
{
#define ARRAY_SIZE 7
    const struct SosMail input[ARRAY_SIZE] = {
        /*           Mail type, Dungeon, Floor, Random 1, Pkmn to rescue, Mail ID, Random 2,     Nickname, 0/1, Reward item, 0, team seeking help, team giving help, chances left, last 3 bits */
        {          SosMailType,       0,     1,        0,              1,       0,        0,          ".",   0,           0, 0,                 0,                0,            1,           0 },
        {     ThankYouMailType,      62,    98, 0xFFFFFF,            414,    9999,   0xFFFF, "Niiickname",   1,         239, 0,              9999,             9999,            9,           0 },
        {      SosMailType + 1,      63,     0,        0,              0,   10000,        0,           "",   0,         240, 0,             10000,            10000,          255,           0 }, /* Mail type, Dungeon, Pkmn to rescue, Mail ID, Nickname and Reward item */
        {          SosMailType,       0,     0,        0,            150,    5555,        0,          ".",   0,           1, 0,                 1,                2,            0,           0 }, /* Floor and chances left */
        {          SosMailType,       0,     4,        0,            150,    1234,        0,          ".",   0,           1, 0,              1000,             1000,           11,           0 }, /* Floor */
        {          AOkMailType,      23,    99,        0,            150,    4321,        0,          ".",   0,           1, 0,               101,              111,           10,           0 }, /* All Ok. Note: Floor-specific prohibitions do not apply in non Wonder Mail requests */
        { ThankYouMailType + 1,      23,    99,        0,            150,    4321,        0,          ".",   0,           1, 0,               101,              111,          100,           0 }  /* Mail type */
    };

    int actualResults[ARRAY_SIZE];

    const int expectedResults[ARRAY_SIZE] = { 0, 0, 6, 2, 1, 0, 1 };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actualResults[i] = entryErrorsSosMail(&input[i]);
        CuAssertIntEquals(tc, expectedResults[i], actualResults[i]);
    }
#undef ARRAY_SIZE
}

void reallocateBytes_test(CuTest *tc)
{
#define ARRAY_SIZE 7
    const char input1[ARRAY_SIZE][24 + 1] = {
        { "1?J9N/X?4P?34??764?0P??W" }, /* (WM - VALID) */
        { "4?6F7M+?4JNRJ*??K??0+9??" }, /* (WM - VALID) */
        { "S62*S40?4P5H8S?869H0!N?W" }, /* (WM - VALID) */
        { "???N+CS?466S*+?RX4?5???W" }, /* (WM - VALID) */
        { "F??CR/0?4/+!*3?7TP?T?7?W" }, /* (WM - VALID) */
        { "1?C.MWY?JPS3.F?0XP?5!2?W" }, /* (WM - VALID - SPECIAL EVOLVE) */
        { "F?N.?QY?8RNYYN?4.J75N+?W" }  /* (WM - VALID - SPECIAL FOOD) */
    };
    const unsigned char input2[ARRAY_SIZE][24] = {
        { 12, 6, 19, 8, 4, 13, 15, 9, 16, 2, 20, 18, 0, 21, 11, 5, 23, 3, 17, 10, 1, 14, 22, 7 },
        { 12, 6, 19, 8, 4, 13, 15, 9, 16, 2, 20, 18, 0, 21, 11, 5, 23, 3, 17, 10, 1, 14, 22, 7 },
        { 12, 6, 19, 8, 4, 13, 15, 9, 16, 2, 20, 18, 0, 21, 11, 5, 23, 3, 17, 10, 1, 14, 22, 7 },
        { 12, 6, 19, 8, 4, 13, 15, 9, 16, 2, 20, 18, 0, 21, 11, 5, 23, 3, 17, 10, 1, 14, 22, 7 },
        { 12, 6, 19, 8, 4, 13, 15, 9, 16, 2, 20, 18, 0, 21, 11, 5, 23, 3, 17, 10, 1, 14, 22, 7 },
        { 12, 6, 19, 8, 4, 13, 15, 9, 16, 2, 20, 18, 0, 21, 11, 5, 23, 3, 17, 10, 1, 14, 22, 7 },
        { 12, 6, 19, 8, 4, 13, 15, 9, 16, 2, 20, 18, 0, 21, 11, 5, 23, 3, 17, 10, 1, 14, 22, 7 }
    };
    const int input3[ARRAY_SIZE] = { 24, 24, 24, 24, 24, 24, 24 };
    char input4[ARRAY_SIZE][24 + 1] = {0};

    const char expected[ARRAY_SIZE][24 + 1] = {
        { "4X04N?7P6JP?1?3/W94?????" },
        { "J+047*?JK6+?49RM?F?N????" },
        { "8004SS8P62!HSNH4W*956???" },
        { "*S54++R6X?????SCWN46????" },
        { "*0T4R37/T???F7!/WCP+????" },
        { ".Y5JMF0PXC!?123WW.PS????" },
        { "YY58?N4R.NN7F+YQW.JN????" }
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        reallocateBytes(input1[i], input2[i], input3[i], input4[i]);
        CuAssertStrEquals(tc, expected[i], input4[i]);
    }
#undef ARRAY_SIZE
}

void mapPasswordByPositionInLookupTable_test(CuTest *tc)
{
#define ARRAY_SIZE 11
    const char* input1[ARRAY_SIZE] = {
        "4X04N?7P6JP?1?3/W94?????", /* (WM - VALID) */
        "4X04N?7P6JP?2?3/W94?????", /* (WM - INVALID CHECKSUM - shall pass) */
        "J+047*?JK6+?49RM?F?N????", /* (WM - VALID) */
        "1T64R3786???16X3WW7M6?? ", /* (WM - INVALID INPUT - shall not pass) */
        "8004SS8P62!HSNH4W*956???", /* (WM - VALID) */
        "*S54++R6X?????SCWN46????", /* (WM - VALID) */
        "*S040*-P6????N8KWY?R????", /* (WM - INVALID CHECKSUM - shall pass) */
        "*0T4R37/T???F7!/WCP+????", /* (WM - VALID) */
        "*0T4R37/T???A7!/WCP+????", /* (WM - INVALID INPUT - shall not pass) */
        ".Y5JMF0PXC!?123WW.PS????", /* (WM - VALID - SPECIAL EVOLVE) */
        "YY58?N4R.NN7F+YQW.JN????"  /* (WM - VALID - SPECIAL FOOD) */
    };
    const char* input2[ARRAY_SIZE] = { /* lookup tables */
        "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W",
        "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W",
        "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W",
        "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W",
        "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W",
        "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W",
        "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W",
        "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W",
        "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W",
        "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W",
        "?67NPR89F0+.STXY45MCHJ-K12!*3Q/W"
    };
    const int input3[ARRAY_SIZE] = { 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24 };
    char input4[ARRAY_SIZE][54 + 1] = {0};

    int actualReturnResults[ARRAY_SIZE];

    const int expected1[ARRAY_SIZE] = { NoError, NoError, NoError, InvalidCharacterError, NoError, NoError, NoError, NoError, InvalidCharacterError, NoError, NoError };
    const int expected2[ARRAY_SIZE][24] = {
        { 16, 14,  9, 16,  3,  0,  2,  4,  1, 21,  4,  0, 24,  0, 28, 30, 31,  7, 16,  0,  0,  0,  0,  0 },
        { 16, 14,  9, 16,  3,  0,  2,  4,  1, 21,  4,  0, 25,  0, 28, 30, 31,  7, 16,  0,  0,  0,  0,  0 },
        { 21, 10,  9, 16,  2, 27,  0, 21, 23,  1, 10,  0, 16,  7,  5, 18,  0,  8,  0,  3,  0,  0,  0,  0 },
        {},
        {  6,  9,  9, 16, 12, 12,  6,  4,  1, 25, 26, 20, 12,  3, 20, 16, 31, 27,  7, 17,  1,  0,  0,  0 },
        { 27, 12, 17, 16, 10, 10,  5,  1, 14,  0,  0,  0,  0,  0, 12, 19, 31,  3, 16,  1,  0,  0,  0,  0 },
        { 27, 12,  9, 16,  9, 27, 22,  4,  1,  0,  0,  0,  0,  3,  6, 23, 31, 15,  0,  5,  0,  0,  0,  0 },
        { 27,  9, 13, 16,  5, 28,  2, 30, 13,  0,  0,  0,  8,  2, 26, 30, 31, 19,  4, 10,  0,  0,  0,  0 },
        {},
        { 11, 15, 17, 21, 18,  8,  9,  4, 14, 19, 26,  0, 24, 25, 28, 31, 31, 11,  4, 12,  0,  0,  0,  0 },
        { 15, 15, 17,  6,  0,  3, 16,  5, 11,  3,  3,  2,  8, 10, 15, 29, 31, 11, 21,  3,  0,  0,  0,  0 }
    };

    int i, j;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actualReturnResults[i] = mapPasswordByPositionInLookupTable(input1[i], input2[i], input3[i], input4[i]);
        CuAssertIntEquals(tc, expected1[i], actualReturnResults[i]);
        if (actualReturnResults[i] != NoError) {
            continue;
        }
        for (j = 0; j < input3[i]; ++j) {
            CuAssertIntEquals(tc, expected2[i][j], input4[i][j]);
        }
    }
#undef ARRAY_SIZE
}

void checkPokemon_test(CuTest *tc)
{
#define ARRAY_SIZE 38
                                          /* [INVALID],              [INVALID],              ??????????,             ??????????,             Bulbasaur,      Voltorb,     Articuno,               Zapdos,      Moltres,                Dragonite,      Mewtwo,                 Mew,                    Chikorita,      Misdreavus,     Unown,                  Unown,       Unown,                  Wobbuffet,      Raikou,                 Larvitar,       Lugia,                  Celebi,                 Treecko,        Metagross,      Metagross,   Regirock,               Regirock,    Deoxys,                 Unown!,                 Unown?,      Deoxys Spdm,            Munchlax,         Munchlax,    Decoy,       Statue,      Rayquaza,    [INVALID],              [INVALID] */
    const int input1[ARRAY_SIZE]         = { -1,                     -1,                     0,                      0,                      1,              100,         144,                    145,         146,                    149,            150,                    151,                    152,            200,            201,                    210,         226,                    227,            268,                    271,            274,                    276,                    277,            404,            404,         405,                    405,         414,                    415,                    416,         419,                    420,              420,         421,         422,         423,         424,                    424 };
    enum MailType input2[ARRAY_SIZE]     = { WonderMailType,         SosMailType,            WonderMailType,         SosMailType,            WonderMailType, SosMailType, WonderMailType,         SosMailType, WonderMailType,         WonderMailType, WonderMailType,         WonderMailType,         WonderMailType, WonderMailType, WonderMailType,         SosMailType, WonderMailType,         WonderMailType, WonderMailType,         WonderMailType, WonderMailType,         WonderMailType,         WonderMailType, WonderMailType, SosMailType, WonderMailType,         SosMailType, WonderMailType,         WonderMailType,         SosMailType, WonderMailType,         WonderMailType,   SosMailType, SosMailType, SosMailType, SosMailType, WonderMailType,         SosMailType };

    int testResult[ARRAY_SIZE];
    const int expectedResult[ARRAY_SIZE] = { PokemonOutOfRangeError, PokemonOutOfRangeError, PokemonOutOfRangeError, PokemonOutOfRangeError, NoError,        NoError,     PokemonNotAllowedError, NoError,     PokemonNotAllowedError, NoError,        PokemonNotAllowedError, PokemonNotAllowedError, NoError,        NoError,        PokemonNotAllowedError, NoError,     PokemonNotAllowedError, NoError,        PokemonNotAllowedError, NoError,        PokemonNotAllowedError, PokemonNotAllowedError, NoError,        NoError,        NoError,     PokemonNotAllowedError, NoError,     PokemonNotAllowedError, PokemonNotAllowedError, NoError,     PokemonNotAllowedError, PokemonNotAllowedError, NoError,     NoError,     NoError,     NoError,     PokemonOutOfRangeError, PokemonOutOfRangeError };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        testResult[i] = checkPokemon(input1[i], input2[i]);
        CuAssertIntEquals(tc, expectedResult[i], testResult[i]);
    }
#undef ARRAY_SIZE
}

void checkDungeon_test(CuTest *tc)
{
#define ARRAY_SIZE 35
                                          /* [INVALID],              [INVALID],              Tiny Woods,     Thunderwave Cave, Mt. Thunder,    Mt. Thunder Peak,                      Mt. Thunder Peak, Mt. Blaze,      Mt. Blaze Peak,                        Frosty Grotto,                         Mt. Freeze Peak,                       Magma Cavern,   Magma Cavern Pit,                      Sky Tower Summit,                      Mt. Freeze Peak,                       Western Cave,   [INVALID],             [INVALID],             Wish Cave,      [INVALID],             [INVALID],             Rock Path,                             Snow Path,                             Snow Path,   [INVALID],             [INVALID],             [INVALID],             Dojo Registration,                     Howling Forest, [INVALID],             Mt. Faraway,    [INVALID],             Purity Forest,  [INVALID],              [INVALID] */
    const int input1[ARRAY_SIZE]         = { -1,                     -1,                     0,              1,                5,              6,                                     6,                9,              10,                                    12,                                    14,                                    15,             16,                                    18,                                    22,                                    23,             24,                    25,                    26,             30,                    39,                    47,                                    48,                                    48,          49,                    50,                    51,                    52,                                    53,             54,                    60,             61,                    62,             63,                     63 };
    enum MailType input2[ARRAY_SIZE]     = { WonderMailType,         SosMailType,            WonderMailType, SosMailType,      WonderMailType, WonderMailType,                        SosMailType,      WonderMailType, WonderMailType,                        WonderMailType,                        WonderMailType,                        WonderMailType, WonderMailType,                        WonderMailType,                        WonderMailType,                        WonderMailType, WonderMailType,        SosMailType,           WonderMailType, WonderMailType,        WonderMailType,        WonderMailType,                        WonderMailType,                        SosMailType, WonderMailType,        WonderMailType,        WonderMailType,        WonderMailType,                        WonderMailType, WonderMailType,        WonderMailType, WonderMailType,        WonderMailType, WonderMailType,         SosMailType };

    int testResult[ARRAY_SIZE];
    const int expectedResult[ARRAY_SIZE] = { DungeonOutOfRangeError, DungeonOutOfRangeError, NoError,        NoError,          NoError,        MissionCannotBeAcceptedInDungeonError, NoError,          NoError,        MissionCannotBeAcceptedInDungeonError, MissionCannotBeAcceptedInDungeonError, MissionCannotBeAcceptedInDungeonError, NoError,        MissionCannotBeAcceptedInDungeonError, MissionCannotBeAcceptedInDungeonError, MissionCannotBeAcceptedInDungeonError, NoError,        DungeonIsInvalidError, DungeonIsInvalidError, NoError,        DungeonIsInvalidError, DungeonIsInvalidError, MissionCannotBeAcceptedInDungeonError, MissionCannotBeAcceptedInDungeonError, NoError,     DungeonIsInvalidError, DungeonIsInvalidError, DungeonIsInvalidError, MissionCannotBeAcceptedInDungeonError, NoError,        DungeonIsInvalidError, NoError,        DungeonIsInvalidError, NoError,        DungeonOutOfRangeError, DungeonOutOfRangeError };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        testResult[i] = checkDungeon(input1[i], input2[i]);
        CuAssertIntEquals(tc, expectedResult[i], testResult[i]);
    }
#undef ARRAY_SIZE
}

void checkFloor_test(CuTest *tc)
{
#define ARRAY_SIZE 25
    const int input1[ARRAY_SIZE]         = { -1,                   0,                    4,                    3,          9,                            13,                           1,                3,                            3,                            2,                            3,                            9,                            40,                           99,                           20,                           99,                           20,                           99,                           25,                           30,                           30,                           30,                           10,                           40,                           99 };
                                          /* Tiny Woods,           Tiny Woods,           Tiny Woods,           Tiny Woods, Mt. Steel,                    Sinister Woods,               Mt. Thunder Peak, Mt. Thunder Peak,             Mt. Blaze Peak,               Magma Cavern Pit,             Magma Cavern Pit,             Sky Tower Summit,             Stormy Sea,                   Silver Trench,                Meteor Cave,                  Western Cave,                 Wish Cave,                    Wish Cave,                    Northern Range,               Fiery Field,                  Northwind Field,              Lightning Field,              Uproar Forest,                Mt. Faraway,                  Purity Forest */
    const int input2[ARRAY_SIZE]         = { 0,                    0,                    0,                    0,          2,                            3,                            6,                6,                            10,                           16,                           16,                           18,                           19,                           20,                           21,                           23,                           26,                           26,                           29,                           34,                           35,                           37,                           42,                           60,                           62 };

    int testResult[ARRAY_SIZE];
    const int expectedResult[ARRAY_SIZE] = { FloorOutOfRangeError, FloorOutOfRangeError, FloorOutOfRangeError, NoError,    FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   NoError,          FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   FloorInvalidInDungeonError,   FloorInvalidInDungeonError };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        testResult[i] = checkFloor(input1[i], input2[i]);
        CuAssertIntEquals(tc, expectedResult[i], testResult[i]);
    }
#undef ARRAY_SIZE
}

void checkItem_test(CuTest *tc)
{
#define ARRAY_SIZE 10
    const int input[ARRAY_SIZE]          = { -1,                  0,           1,       150,     235,     236,                       237,                       238,                       239,                       240 };

    int testResult[ARRAY_SIZE];
    const int expectedResult[ARRAY_SIZE] = { ItemOutOfRangeError, NoItemError, NoError, NoError, NoError, ItemCannotBeObtainedError, ItemCannotBeObtainedError, ItemCannotBeObtainedError, ItemCannotBeObtainedError, ItemOutOfRangeError };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        testResult[i] = checkItem(input[i]);
        CuAssertIntEquals(tc, expectedResult[i], testResult[i]);
    }
#undef ARRAY_SIZE
}

void checkItemExistenceInDungeon_test(CuTest *tc)
{
#define ARRAY_SIZE 4
    int input1[ARRAY_SIZE] = { 55, 56, 232, 105 };
    int input2[ARRAY_SIZE] = {  0,  0,  62,  40 };

    int testResult[ARRAY_SIZE];
    int expectedResult[ARRAY_SIZE] = { NoError, ItemNotExistsInDungeonError, NoError, NoError };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        testResult[i] = checkItemExistenceInDungeon(input1[i], input2[i]);
        CuAssertIntEquals(tc, expectedResult[i], testResult[i]);
    }
#undef ARRAY_SIZE
}

void checkFriendArea_test(CuTest *tc)
{
#define ARRAY_SIZE 16
    const int input[ARRAY_SIZE]          = { -1,                        0,                         1,                                8,                                9,       10,      11,                               14,                               15,      16,                               36,                               37,      38,                               57,                               58,                        100 };

    int testResult[ARRAY_SIZE];
    const int expectedResult[ARRAY_SIZE] = { FriendAreaOutOfRangeError, FriendAreaOutOfRangeError, FriendAreaIsInvalidAsRewardError, FriendAreaIsInvalidAsRewardError, NoError, NoError, FriendAreaIsInvalidAsRewardError, FriendAreaIsInvalidAsRewardError, NoError, FriendAreaIsInvalidAsRewardError, FriendAreaIsInvalidAsRewardError, NoError, FriendAreaIsInvalidAsRewardError, FriendAreaIsInvalidAsRewardError, FriendAreaOutOfRangeError, FriendAreaOutOfRangeError };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        testResult[i] = checkFriendArea(input[i]);
        CuAssertIntEquals(tc, expectedResult[i], testResult[i]);
    }
#undef ARRAY_SIZE
}

void checkMailID_test(CuTest *tc)
{
#define ARRAY_SIZE 5
    const int input[ARRAY_SIZE]          = { -1,                    0,       1,       9999,    10000 };

    int testResult[ARRAY_SIZE];
    const int expectedResult[ARRAY_SIZE] = { MailIDOutOfRangeError, NoError, NoError, NoError, MailIDOutOfRangeError };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        testResult[i] = checkMailID(input[i]);
        CuAssertIntEquals(tc, expectedResult[i], testResult[i]);
    }
#undef ARRAY_SIZE
}
