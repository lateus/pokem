#include "../../../test/CuTest.h"

#include "UtilCore.h"
#include "../../data/md1global/md1global.h"

#include <stdlib.h>


CuSuite* UtilCoreGetTestSuite(void);
void areParents_test(CuTest *tc);
void arePairs_test(CuTest *tc);
void areLovers_test(CuTest *tc);
void findItemByDungeon_test(CuTest *tc);
void computeDifficulty_test(CuTest *tc);
void computeMoneyReward_test(CuTest *tc);
void computeChecksum_test(CuTest *tc);


CuSuite* UtilCoreGetTestSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, areParents_test);
    SUITE_ADD_TEST(suite, arePairs_test);
    SUITE_ADD_TEST(suite, areLovers_test);
    SUITE_ADD_TEST(suite, findItemByDungeon_test);
    SUITE_ADD_TEST(suite, computeDifficulty_test);
    SUITE_ADD_TEST(suite, computeMoneyReward_test);
    SUITE_ADD_TEST(suite, computeChecksum_test);
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
#define ARRAY_SIZE 5
    unsigned char input1[ARRAY_SIZE][34] = {
        { 0xD0, 0x25, 0x38, 0x80, 0x20, 0xA1, 0x12, 0x80, 0x01, 0xF7, 0xFF, 0x40, 0x00, 0x00, 0x00 }, /* 1?J9N/X?4P?34??764?0P??W (WM - VALID) */
        { 0xD0, 0x25, 0x38, 0x80, 0x20, 0xA1, 0x12, 0x90, 0x01, 0xF7, 0xFF, 0x40, 0x00, 0x00, 0x00 }, /* 2?J9N/X?4P?34??764?0P??W (WM - INVALID) */
        { 0x55, 0x25, 0x28, 0x36, 0xA8, 0x37, 0x28, 0x00, 0x4F, 0x91, 0x00, 0x81, 0x01, 0x00, 0x00 }, /* 4?6F7M+?4JNRJ*??K??0+9?? (WM - VALID) */
        { 0x39, 0xD1, 0x09, 0xEC, 0x1C, 0xA1, 0x60, 0x8E, 0x26, 0x81, 0x92, 0x67, 0xAA, 0xD3, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x7D, 0x49, 0x58, 0x01, 0x00, 0x00, 0x00, 0x50, 0x00 }, /* ?M???.R066???2FC?!?R????3HCP?-??32H???Y?M4C??1J??NQ04? (SOS - VALID) */
        { 0x03, 0x61, 0x0A, 0x4C, 0x11, 0x60, 0x5E, 0xFA, 0xF5, 0xA9, 0xE1, 0x0A, 0x12, 0x2B, 0x63, 0x03, 0x91, 0x7A, 0x13, 0x2B, 0x63, 0x03, 0x00, 0x00, 0x08, 0x7D, 0x49, 0x58, 0x01, 0x00, 0x00, 0x00, 0x50, 0x00 }  /* S6???.RF?6F??NWH*5KC???RH1!9?8?JK7P0??SNMJRPSKJ??7QJ4N (SOS - VALID) */
    };
    int input2[ARRAY_SIZE] = { 15, 15, 15, 34, 34 };

    int actual[ARRAY_SIZE];
    int expected[ARRAY_SIZE] = { 0xD0, 0xE0, 0x55, 0x39, 0x03 };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actual[i] = computeChecksum((char*)input1[i], input2[i]);
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
#undef ARRAY_SIZE
}
