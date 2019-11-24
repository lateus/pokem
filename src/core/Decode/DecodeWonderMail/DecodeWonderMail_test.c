#include "../../../../test/CuTest.h"

#include "DecodeWonderMail.h"

#include <stdlib.h>


CuSuite* DecodeWonderMailGetTestSuite(void);

void decodeWonderMail_test(CuTest *tc);
void wonderMailIsInvalid_test(CuTest *tc);
void reallocateBytesDecodingWM_test(CuTest *tc);
void lookupTableDecodingWM_test(CuTest *tc);
void bitUnpackingDecodingWM_test(CuTest *tc);


CuSuite* DecodeWonderMailGetTestSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, decodeWonderMail_test);
    SUITE_ADD_TEST(suite, wonderMailIsInvalid_test);
    SUITE_ADD_TEST(suite, reallocateBytesDecodingWM_test);
    SUITE_ADD_TEST(suite, lookupTableDecodingWM_test);
    SUITE_ADD_TEST(suite, lookupTableDecodingWM_test);
    SUITE_ADD_TEST(suite, bitUnpackingDecodingWM_test);
    return suite;
}

void decodeWonderMail_test(CuTest *tc)
{
#define ARRAY_SIZE 5
    const char input1[ARRAY_SIZE][24 + 1] = {
        { "1?J9N/X?4P?34??764?0P??W" }, /* (WM - VALID) */
        { "4?6F7M+?4JNRJ*??K??0+9??" }, /* (WM - VALID) */
        { "S62*S40?4P5H8S?869H0!N?W" }, /* (WM - VALID) */
        { "???N+CS?466S*+?RX4?5???W" }, /* (WM - VALID) */
        { "F??CR/0?4/+!*3?7TP?T?7?W" }  /* (WM - VALID) */
    };
    struct WM_INFO input2[ARRAY_SIZE] = {};

    const struct WM_INFO expected[ARRAY_SIZE] = {
        { "Take me!",               "I can't go by myself...",              "Please take me to see Wartortle!",        "Squirtle",  "Escort to Wartortle.", "Thunderwave Cave", "B1F",  'D', "400 poke",                     "1?J9N/X?4P?3\n          4??764?0P??W" },
        { "Take me!",               "Lapras is waiting for me!",            "Please take me to see Lapras!",           "Umbreon",   "Escort to Lapras.",    "Mt. Steel",        " 6F",  'D', "200 poke + ??? [Pecha Scarf]", "4?6F7M+?4JNR\n          J*??K??0+9??" },
        { "Escort me!",             "I have to go!",                        "Someone, please escort me!",              "Combusken", "Escort to Pikachu.",   "Purity Forest",    " 98F", '*', "Friend Zone [Boulder Cave]",   "S62*S40?4P5H\n          8S?869H0!N?W" },
        { "Deliver one Moon Stone", "Having one Moon Stone is reassuring.", "Please give me one!",                     "Dragonite", "Deliver Moon Stone.",  "Tiny Woods",       "B3F",  'E', "100 poke",                     "???N+CS?466S\n          *+?RX4?5???W" },
        { "One Sun Stone wanted!",  "Sun Stone--it's convenient to have.",  "Please! I'm offering a generous reward!", "Blissey",   "Find Sun Stone.",      "Solar Cave",       "B20F", 'A', "500 poke",                     "F??CR/0?4/+!\n          *3?7TP?T?7?W" }
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        decodeWonderMail(input1[i], &input2[i]);
        CuAssertStrEquals(tc, expected[i].head, input2[i].head);
        CuAssertStrEquals(tc, expected[i].body1, input2[i].body1);
        CuAssertStrEquals(tc, expected[i].body2, input2[i].body2);
        CuAssertStrEquals(tc, expected[i].client, input2[i].client);
        CuAssertStrEquals(tc, expected[i].objective, input2[i].objective);
        CuAssertStrEquals(tc, expected[i].place, input2[i].place);
        CuAssertStrEquals(tc, expected[i].floor, input2[i].floor);
        CuAssertIntEquals(tc, (int)expected[i].difficulty, (int)input2[i].difficulty);
        CuAssertStrEquals(tc, expected[i].reward, input2[i].reward);
        CuAssertStrEquals(tc, expected[i].WMail, input2[i].WMail);
    }
#undef ARRAY_SIZE
}

void wonderMailIsInvalid_test(CuTest *tc)
{
#define ARRAY_SIZE 9
    const char input1[ARRAY_SIZE][24 + 1] = {
        { "1?J9N/X?4P?34??764?0P??W" }, /* (WM - VALID) */
        { "2?J9N/X?4P?34??764?0P??W" }, /* (WM - INVALID CHECKSUM) */
        { "4?6F7M+?4JNRJ*??K??0+9??" }, /* (WM - VALID) */
        { "16?WR3T 48MX13?767?6?6?W" }, /* (WM - INVALID INPUT) */
        { "S62*S40?4P5H8S?869H0!N?W" }, /* (WM - VALID) */
        { "???N+CS?466S*+?RX4?5???W" }, /* (WM - VALID) */
        { "???Y0KS?4PR8**?-6??0?N?W" }, /* (WM - INVALID CHECKSUM) */
        { "F??CR/0?4/+!*3?7TP?T?7?W" }, /* (WM - VALID) */
        { "A??CR/0?4/+!*3?7TP?T?7?W" }  /* (WM - INVALID INPUT) */
    };
    char input2[ARRAY_SIZE][15] = {0};

    int actual[ARRAY_SIZE];
    const int expected[ARRAY_SIZE] = { NoError, ChecksumError, NoError, InputError, NoError, NoError, ChecksumError, NoError, InputError };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actual[i] = wonderMailIsInvalid(input1[i], input2[i]);
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
#undef ARRAY_SIZE
}

void reallocateBytesDecodingWM_test(CuTest *tc)
{
#define ARRAY_SIZE 5
    char input1[ARRAY_SIZE][24 + 1] = {0};
    const char input2[ARRAY_SIZE][24 + 1] = {
        { "1?J9N/X?4P?34??764?0P??W" }, /* (WM - VALID) */
        { "4?6F7M+?4JNRJ*??K??0+9??" }, /* (WM - VALID) */
        { "S62*S40?4P5H8S?869H0!N?W" }, /* (WM - VALID) */
        { "???N+CS?466S*+?RX4?5???W" }, /* (WM - VALID) */
        { "F??CR/0?4/+!*3?7TP?T?7?W" }  /* (WM - VALID) */
    };

    const char expected[ARRAY_SIZE][24 + 1] = {
        { "4X04N?7P6JP?1?3/W94?????" },
        { "J+047*?JK6+?49RM?F?N????" },
        { "8004SS8P62!HSNH4W*956???" },
        { "*S54++R6X?????SCWN46????" },
        { "*0T4R37/T???F7!/WCP+????" }
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        reallocateBytesDecodingWM(input1[i], input2[i]);
        CuAssertStrEquals(tc, expected[i], input1[i]);
    }
#undef ARRAY_SIZE
}

void lookupTableDecodingWM_test(CuTest *tc)
{
#define ARRAY_SIZE 5
    char input1[ARRAY_SIZE][24 + 1] = {0};
    const char input2[ARRAY_SIZE][24 + 1] = {
        { "4X04N?7P6JP?1?3/W94?????" }, /* (WM - VALID) */
        { "J+047*?JK6+?49RM?F?N????" }, /* (WM - VALID) */
        { "8004SS8P62!HSNH4W*956???" }, /* (WM - VALID) */
        { "*S54++R6X?????SCWN46????" }, /* (WM - VALID) */
        { "*0T4R37/T???F7!/WCP+????" }  /* (WM - VALID) */
    };

    const int expected[ARRAY_SIZE][24] = {
        { 16, 14,  9, 16,  3,  0,  2,  4,  1, 21,  4,  0, 24,  0, 28, 30, 31,  7, 16,  0,  0,  0,  0,  0 },
        { 21, 10,  9, 16,  2, 27,  0, 21, 23,  1, 10,  0, 16,  7,  5, 18,  0,  8,  0,  3,  0,  0,  0,  0 },
        {  6,  9,  9, 16, 12, 12,  6,  4,  1, 25, 26, 20, 12,  3, 20, 16, 31, 27,  7, 17,  1,  0,  0,  0 },
        { 27, 12, 17, 16, 10, 10,  5,  1, 14,  0,  0,  0,  0,  0, 12, 19, 31,  3, 16,  1,  0,  0,  0,  0 },
        { 27,  9, 13, 16,  5, 28,  2, 30, 13,  0,  0,  0,  8,  2, 26, 30, 31, 19,  4, 10,  0,  0,  0,  0 }
    };

    int i, j;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        lookupTableDecodingWM(input1[i], input2[i]);
        for (j = 0; j < 24; ++j) {
            CuAssertIntEquals(tc, expected[i][j], input1[i][j]);
        }
    }
#undef ARRAY_SIZE
}

void bitUnpackingDecodingWM_test(CuTest *tc)
{
#define ARRAY_SIZE 5
    const char input1[ARRAY_SIZE][14] = {
        { 0x25, 0x38, 0x80, 0x20, 0xA1, 0x12, 0x80, 0x01, 0xF7, 0xFF, 0x40, 0x00, 0x00, 0x00 }, /* (WM - VALID) */
        { 0x25, 0x28, 0x36, 0xA8, 0x37, 0x28, 0x00, 0x4F, 0x91, 0x00, 0x81, 0x01, 0x00, 0x00 }, /* (WM - VALID) */
        { 0x25, 0xC8, 0x98, 0x21, 0x21, 0x6B, 0xCA, 0x06, 0x85, 0x7F, 0x9F, 0x18, 0x00, 0x00 }, /* (WM - VALID) */
        { 0x45, 0xA8, 0x54, 0x09, 0x0E, 0x00, 0x00, 0x00, 0x9B, 0x7F, 0xC0, 0x00, 0x00, 0x00 }, /* (WM - VALID) */
        { 0x35, 0x58, 0xB8, 0xF0, 0x0D, 0x00, 0x80, 0x84, 0xF6, 0x7F, 0x12, 0x05, 0x00, 0x00 }  /* (WM - VALID) */
    };
    struct WONDERMAIL input2[ARRAY_SIZE] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    const struct WONDERMAIL expected[ARRAY_SIZE] = {
        { 5, 2, 0, 7, 8, 9, 5, 9, 0, 3, 238, 255, 1, 1 },
        { 5, 2, 0, 197, 131, 189, 1, 20, 0, 158, 34, 1, 2, 6 },
        { 5, 2, 0, 281, 25, 9, 9, 53, 37, 13, 10, 255, 62, 98 },
        { 5, 4, 0, 149, 149, 112, 0, 0, 0, 0, 54, 255, 0, 3 },
        { 5, 3, 0, 267, 267, 111, 0, 0, 0, 9, 237, 255, 36, 20 }
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        bitUnpackingDecodingWM(input1[i], &input2[i]);
        CuAssertIntEquals(tc, expected[i].mailType, input2[i].mailType);
        CuAssertIntEquals(tc, expected[i].specialJobIndicator, input2[i].specialJobIndicator);
        CuAssertIntEquals(tc, expected[i].pkmnClient, input2[i].pkmnClient);
        CuAssertIntEquals(tc, expected[i].pkmnTarget, input2[i].pkmnTarget);
        CuAssertIntEquals(tc, expected[i].itemDeliverFind, input2[i].itemDeliverFind);
        CuAssertIntEquals(tc, expected[i].rewardType, input2[i].rewardType);
        CuAssertIntEquals(tc, expected[i].itemReward, input2[i].itemReward);
        CuAssertIntEquals(tc, expected[i].friendAreaReward, input2[i].friendAreaReward);
        CuAssertIntEquals(tc, expected[i].flavorText, input2[i].flavorText);
        CuAssertIntEquals(tc, expected[i].random, input2[i].random);
        CuAssertIntEquals(tc, expected[i].idk_always0xFF, input2[i].idk_always0xFF);
        CuAssertIntEquals(tc, expected[i].dungeon, input2[i].dungeon);
        CuAssertIntEquals(tc, expected[i].floor, input2[i].floor);
    }
#undef ARRAY_SIZE
}