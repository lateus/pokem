#include "../../../test/CuTest.h"

#include "UtilCore.h"
#include "../../data/md1global/md1global.h"

#include <stdlib.h>


CuSuite* UtilCoreGetTestSuite(void);
void areParents_test(CuTest *tc);
void arePairs_test(CuTest *tc);
void areLovers_test(CuTest *tc);
void getMailType_test(CuTest *tc);
void findItemByDungeon_test(CuTest *tc);
void computeDifficulty_test(CuTest *tc);
void computeMoneyReward_test(CuTest *tc);
void computeChecksum_test(CuTest *tc);
void reallocateBytes_test(CuTest *tc);
void mapPasswordByPositionInLookupTable_test(CuTest *tc);


CuSuite* UtilCoreGetTestSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, areParents_test);
    SUITE_ADD_TEST(suite, arePairs_test);
    SUITE_ADD_TEST(suite, areLovers_test);
    SUITE_ADD_TEST(suite, getMailType_test);
    SUITE_ADD_TEST(suite, findItemByDungeon_test);
    SUITE_ADD_TEST(suite, computeDifficulty_test);
    SUITE_ADD_TEST(suite, computeMoneyReward_test);
    SUITE_ADD_TEST(suite, computeChecksum_test);
    SUITE_ADD_TEST(suite, reallocateBytes_test);
    SUITE_ADD_TEST(suite, mapPasswordByPositionInLookupTable_test);
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

void getMailType_test(CuTest *tc)
{
#define ARRAY_SIZE 10 /*20*/
    char input[ARRAY_SIZE][55 + 1] = {
        /* "4X04N?7P6JP?1?3/W94?????",  (WM - VALID) */
        /* "4X04N?7P6JP?1?3/W94????",   (WM - INVALID) */
        /* "4X04N?7P6JP?1?3/W94??????", (WM - INVALID) */
        /* "4X04N?7P6JP?1?3/W94????A",  (WM - INVALID) */
        /* "J+047*?JK6+?49RM?F?N????",  (WM - VALID) */
        /* "8004SS8P62!HSNH4W*956???",  (WM - VALID) */
        /* "*S54++R6X?????SCWN46????",  (WM - VALID) */
        /* "*0T4R37/T???F7!/WCP+????",  (WM - VALID) */
        /* ".Y5JMF0PXC!?123WW.PS????",  (WM - VALID - SPECIAL EVOLVE) */
        /* "YY58?N4R.NN7F+YQW.JN????",  (WM - VALID - SPECIAL FOOD) */
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

    int expected[ARRAY_SIZE] = { /* WonderMailType, -1, -1, -1, WonderMailType, WonderMailType, WonderMailType, WonderMailType, WonderMailType, WonderMailType */ SosMailType, -1, -1, SosMailType, SosMailType, AOkMailType, AOkMailType, ThankYouMailType, ThankYouMailType, -1 };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actual[i] = getMailType(input[i]);
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
#undef ARRAY_SIZE
}

void findItemByDungeon_test(CuTest *tc)
{
#define ARRAY_SIZE 4
    int input1[ARRAY_SIZE] = { 55, 56, 232, 105 };
    int input2[ARRAY_SIZE] = {  0,  0,  62,  40 };

    int actual[ARRAY_SIZE];
    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actual[i] = findItemByDungeon(input1[i], input2[i]);
    }

    int expected[ARRAY_SIZE] = { 1, 0, 1, 1 };
    for (i = 0; i < ARRAY_SIZE; ++i) {
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

    const int expected1[ARRAY_SIZE] = { NoError, NoError, NoError, InputError, NoError, NoError, NoError, NoError, InputError, NoError, NoError };
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
