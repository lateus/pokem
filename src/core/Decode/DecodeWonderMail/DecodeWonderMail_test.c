#include "../../../../test/CuTest.h"

#include "DecodeWonderMail.h"

#include <stdlib.h>


CuSuite* DecodeWonderMailGetTestSuite(void);

void decodeWonderMail_test(CuTest *tc);
void wonderMailIsInvalid_test(CuTest *tc);
void reallocateBytesDecodingWM_test(CuTest *tc);
void lookupTableDecodingWM_test(CuTest *tc);
void bitUnpackingDecodingWM_test(CuTest *tc);
void setFlavorText_test(CuTest *tc);
void setFlavorTextHead_test(CuTest *tc);
void setFlavorTextBody_test(CuTest *tc);


CuSuite* DecodeWonderMailGetTestSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, decodeWonderMail_test);
    SUITE_ADD_TEST(suite, wonderMailIsInvalid_test);
    SUITE_ADD_TEST(suite, reallocateBytesDecodingWM_test);
    SUITE_ADD_TEST(suite, lookupTableDecodingWM_test);
    SUITE_ADD_TEST(suite, lookupTableDecodingWM_test);
    SUITE_ADD_TEST(suite, bitUnpackingDecodingWM_test);
    SUITE_ADD_TEST(suite, setFlavorText_test);
    SUITE_ADD_TEST(suite, setFlavorTextHead_test);
    SUITE_ADD_TEST(suite, setFlavorTextBody_test);
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
    struct WonderMailInfo input2[ARRAY_SIZE] = {};

    const struct WonderMailInfo expected[ARRAY_SIZE] = {
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
    struct WonderMail input2[ARRAY_SIZE] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    const struct WonderMail expected[ARRAY_SIZE] = {
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

void setFlavorText_test(CuTest *tc)
{
#define ARRAY_SIZE 10
    const struct WonderMail input1[ARRAY_SIZE] = {
        { 5, 2,  0,   7,   8,   9,  5,   9,  0,   3, 238, 255,  1,  1 },
        { 5, 2,  0, 197, 131, 189,  1,  20,  0, 158,  34,   1,  2,  6 }, /* 1 instead of 255??? */
        { 5, 2,  0, 281,  25,   9,  9,  53, 37,  13,  10, 255, 62, 98 },
        { 5, 4,  0, 149, 149, 112,  0,   0,  0,   0,  54, 255,  0,  3 },
        { 5, 3,  0, 267, 267, 111,  0,   0,  0,   9, 237, 255, 36, 20 },
        { 5, 1,  9, 172, 172,   9,  1,  22,  0,   9, 120, 255, 21, 12 },
        { 5, 1,  9,  32,  29,   9,  2, 221,  0,  14, 189, 255, 31, 18 },
        { 5, 2, 10, 336, 337,   9,  3,  46,  0,  12, 192, 255, 33, 24 },
        { 9, 1,  9, 138, 140,   9,  5,  55,  0,   2,  64, 255, 43,  7 },
        { 5, 1,  9, 374, 129,   9,  6,  49,  0,   3, 211, 255, 57,  1 }
    };
    struct WonderMailInfo input2[ARRAY_SIZE] = {
        { {0}, {0}, {0}, "Squirtle",  "Escort to Wartortle.", "Thunderwave Cave", "B1F",  'D', "400 poke",                      "1?J9N/X?4P?3\n          4??764?0P??W" },
        { {0}, {0}, {0}, "Umbreon",   "Escort to Lapras.",    "Mt. Steel",        " 6F",  'D', "200 poke + ??? [Pecha Scarf]",  "4?6F7M+?4JNR\n          J*??K??0+9??" },
        { {0}, {0}, {0}, "Combusken", "Escort to Pikachu.",   "Purity Forest",    " 98F", '*', "Friend Zone [Boulder Cave]",    "S62*S40?4P5H\n          8S?869H0!N?W" },
        { {0}, {0}, {0}, "Dragonite", "Deliver Moon Stone.",  "Tiny Woods",       "B3F",  'E', "100 poke",                      "???N+CS?466S\n          *+?RX4?5???W" },
        { {0}, {0}, {0}, "Blissey",   "Find Sun Stone.",      "Solar Cave",       "B20F", 'A', "500 poke",                      "F??CR/0?4/+!\n          *3?7TP?T?7?W" },
        { {0}, {0}, {0}, "Pichu",     "Find Pichu.",          "Meteor Cave",      "B12F", 'A', "500 poke + ??? [Warp Scarf]",   "F?6K-KY?0R84\n          +7?.67?R.7?W" },
        { {0}, {0}, {0}, "NidoranM",  "Find NidoranF.",       "Desert Region",    " 18F", 'A', "Stairs Orb",                    "4?MW4*Y?0P0!\n          9F?96NNRXN?W" },
        { {0}, {0}, {0}, "Plusle",    "Escort to Minum.",     "Wyvern Hill",      " 24F", 'S', "Friend Bow + ???",              "??N9FC+?+8S7\n          MT?H6P?0KN?W" },
        { {0}, {0}, {0}, "Omanyte",   "Find Kabuto.",         "Oddity Cave",      "B7F",  'B', "800 poke",                      "4?JYRHX?0RN?\n          N7?N6J?R*??W" },
        { {0}, {0}, {0}, "Feebas",    "Find Magikarp.",       "Unown Relic",      "B1F",  'B', "800 poke + ??? [Lunar Ribbon]", "1?-9*Q+?0R?8\n          QT??6K?R1??W" }
    };

    const struct WonderMailInfo expected[ARRAY_SIZE] = {
        { "Take me!",                "I can't go by myself...",              "Please take me to see Wartortle!",          "Squirtle",  "Escort to Wartortle.", "Thunderwave Cave", "B1F",  'D', "400 poke",                      "1?J9N/X?4P?3\n          4??764?0P??W" },
        { "Take me!",                "Lapras is waiting for me!",            "Please take me to see Lapras!",             "Umbreon",   "Escort to Lapras.",    "Mt. Steel",        " 6F",  'D', "200 poke + ??? [Pecha Scarf]",  "4?6F7M+?4JNR\n          J*??K??0+9??" },
        { "Escort me!",              "I have to go!",                        "Someone, please escort me!",                "Combusken", "Escort to Pikachu.",   "Purity Forest",    " 98F", '*', "Friend Zone [Boulder Cave]",    "S62*S40?4P5H\n          8S?869H0!N?W" },
        { "Deliver one Moon Stone",  "Having one Moon Stone is reassuring.", "Please give me one!",                       "Dragonite", "Deliver Moon Stone.",  "Tiny Woods",       "B3F",  'E', "100 poke",                      "???N+CS?466S\n          *+?RX4?5???W" },
        { "One Sun Stone wanted!",   "Sun Stone--it's convenient to have.",  "Please! I'm offering a generous reward!",   "Blissey",   "Find Sun Stone.",      "Solar Cave",       "B20F", 'A', "500 poke",                      "F??CR/0?4/+!\n          *3?7TP?T?7?W" },
        { "Please help my brother!", "My little brother Pichu disappeared!", "I'm really worried! Someone, please help!", "Pichu",     "Find Pichu.",          "Meteor Cave",      "B12F", 'A', "500 poke + ??? [Warp Scarf]",   "F?6K-KY?0R84\n          +7?.67?R.7?W" },
        { "Please save my love!",    "Please! Please rescue NidoranF!",      "We're madly in love!",                      "NidoranM",  "Find NidoranF.",       "Desert Region",    " 18F", 'A', "Stairs Orb",                    "4?MW4*Y?0P0!\n          9F?96NNRXN?W" },
        { "Escort me to my love!",   "I really want to meet Minun!",         "We're in love! Please, take me there!",     "Plusle",    "Escort to Minum.",     "Wyvern Hill",      " 24F", 'S', "Friend Bow + ???",              "??N9FC+?+8S7\n          MT?H6P?0KN?W" },
        { "Rescue my rival!",        "Kabuto has been a rival since my",     "ancestors' time. The rivalry can't end!",   "Omanyte",   "Find Kabuto.",         "Oddity Cave",      "B7F",  'B', "800 poke",                      "4?JYRHX?0RN?\n          N7?N6J?R*??W" },
        { "Please save my friend!",  "Help! Magikarp isn't much now, but",   "my friend is amazing after evolution!",     "Feebas",    "Find Magikarp.",       "Unown Relic",      "B1F",  'B', "800 poke + ??? [Lunar Ribbon]", "1?-9*Q+?0R?8\n          QT??6K?R1??W" }
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        setFlavorText(&input1[i], &input2[i]);
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

void setFlavorTextHead_test(CuTest *tc)
{
#define ARRAY_SIZE 10
    const struct WonderMail input1[ARRAY_SIZE] = {
        { 5, 2,  0,   7,   8,   9,  5,   9,  0,   3, 238, 255,  1,  1 },
        { 5, 2,  0, 197, 131, 189,  1,  20,  0, 158,  34,   1,  2,  6 }, /* 1 instead of 255??? */
        { 5, 2,  0, 281,  25,   9,  9,  53, 37,  13,  10, 255, 62, 98 },
        { 5, 4,  0, 149, 149, 112,  0,   0,  0,   0,  54, 255,  0,  3 },
        { 5, 3,  0, 267, 267, 111,  0,   0,  0,   9, 237, 255, 36, 20 },
        { 5, 1,  9, 172, 172,   9,  1,  22,  0,   9, 120, 255, 21, 12 },
        { 5, 1,  9,  32,  29,   9,  2, 221,  0,  14, 189, 255, 31, 18 },
        { 5, 2, 10, 336, 337,   9,  3,  46,  0,  12, 192, 255, 33, 24 },
        { 9, 1,  9, 138, 140,   9,  5,  55,  0,   2,  64, 255, 43,  7 },
        { 5, 1,  9, 374, 129,   9,  6,  49,  0,   3, 211, 255, 57,  1 }
    };
    int input2[ARRAY_SIZE] = { 10, 10, 10, 12, 11,  5,  5,  6,  5,  5 };
    int input3[ARRAY_SIZE] = { -1, -1, -1, -1, -1, 44, 33, 38, 42,  5 };
    int input4[ARRAY_SIZE] = { -1, -1, -1, -1, -1, -1,  0,  5, -1, -1 };
    int input5[ARRAY_SIZE] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    struct WonderMailInfo input6[ARRAY_SIZE] = {
        { {0}, {0}, {0}, "Squirtle",  "Escort to Wartortle.", "Thunderwave Cave", "B1F",  'D', "400 poke",                      "1?J9N/X?4P?3\n          4??764?0P??W" },
        { {0}, {0}, {0}, "Umbreon",   "Escort to Lapras.",    "Mt. Steel",        " 6F",  'D', "200 poke + ??? [Pecha Scarf]",  "4?6F7M+?4JNR\n          J*??K??0+9??" },
        { {0}, {0}, {0}, "Combusken", "Escort to Pikachu.",   "Purity Forest",    " 98F", '*', "Friend Zone [Boulder Cave]",    "S62*S40?4P5H\n          8S?869H0!N?W" },
        { {0}, {0}, {0}, "Dragonite", "Deliver Moon Stone.",  "Tiny Woods",       "B3F",  'E', "100 poke",                      "???N+CS?466S\n          *+?RX4?5???W" },
        { {0}, {0}, {0}, "Blissey",   "Find Sun Stone.",      "Solar Cave",       "B20F", 'A', "500 poke",                      "F??CR/0?4/+!\n          *3?7TP?T?7?W" },
        { {0}, {0}, {0}, "Pichu",     "Find Pichu.",          "Meteor Cave",      "B12F", 'A', "500 poke + ??? [Warp Scarf]",   "F?6K-KY?0R84\n          +7?.67?R.7?W" },
        { {0}, {0}, {0}, "NidoranM",  "Find NidoranF.",       "Desert Region",    " 18F", 'A', "Stairs Orb",                    "4?MW4*Y?0P0!\n          9F?96NNRXN?W" },
        { {0}, {0}, {0}, "Plusle",    "Escort to Minum.",     "Wyvern Hill",      " 24F", 'S', "Friend Bow + ???",              "??N9FC+?+8S7\n          MT?H6P?0KN?W" },
        { {0}, {0}, {0}, "Omanyte",   "Find Kabuto.",         "Oddity Cave",      "B7F",  'B', "800 poke",                      "4?JYRHX?0RN?\n          N7?N6J?R*??W" },
        { {0}, {0}, {0}, "Feebas",    "Find Magikarp.",       "Unown Relic",      "B1F",  'B', "800 poke + ??? [Lunar Ribbon]", "1?-9*Q+?0R?8\n          QT??6K?R1??W" }
    };

    const struct WonderMailInfo expected[ARRAY_SIZE] = {
        { "Take me!",                {0}, {0}, "Squirtle",  "Escort to Wartortle.", "Thunderwave Cave", "B1F",  'D', "400 poke",                      "1?J9N/X?4P?3\n          4??764?0P??W" },
        { "Take me!",                {0}, {0}, "Umbreon",   "Escort to Lapras.",    "Mt. Steel",        " 6F",  'D', "200 poke + ??? [Pecha Scarf]",  "4?6F7M+?4JNR\n          J*??K??0+9??" },
        { "Escort me!",              {0}, {0}, "Combusken", "Escort to Pikachu.",   "Purity Forest",    " 98F", '*', "Friend Zone [Boulder Cave]",    "S62*S40?4P5H\n          8S?869H0!N?W" },
        { "Deliver one Moon Stone",  {0}, {0}, "Dragonite", "Deliver Moon Stone.",  "Tiny Woods",       "B3F",  'E', "100 poke",                      "???N+CS?466S\n          *+?RX4?5???W" },
        { "One Sun Stone wanted!",   {0}, {0}, "Blissey",   "Find Sun Stone.",      "Solar Cave",       "B20F", 'A', "500 poke",                      "F??CR/0?4/+!\n          *3?7TP?T?7?W" },
        { "Please help my brother!", {0}, {0}, "Pichu",     "Find Pichu.",          "Meteor Cave",      "B12F", 'A', "500 poke + ??? [Warp Scarf]",   "F?6K-KY?0R84\n          +7?.67?R.7?W" },
        { "Please save my love!",    {0}, {0}, "NidoranM",  "Find NidoranF.",       "Desert Region",    " 18F", 'A', "Stairs Orb",                    "4?MW4*Y?0P0!\n          9F?96NNRXN?W" },
        { "Escort me to my love!",   {0}, {0}, "Plusle",    "Escort to Minum.",     "Wyvern Hill",      " 24F", 'S', "Friend Bow + ???",              "??N9FC+?+8S7\n          MT?H6P?0KN?W" },
        { "Rescue my rival!",        {0}, {0}, "Omanyte",   "Find Kabuto.",         "Oddity Cave",      "B7F",  'B', "800 poke",                      "4?JYRHX?0RN?\n          N7?N6J?R*??W" },
        { "Please save my friend!",  {0}, {0}, "Feebas",    "Find Magikarp.",       "Unown Relic",      "B1F",  'B', "800 poke + ??? [Lunar Ribbon]", "1?-9*Q+?0R?8\n          QT??6K?R1??W" }
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        setFlavorTextHead(&input1[i], input2[i], input3[i], input4[i], input5[i], &input6[i]);
        CuAssertStrEquals(tc, expected[i].head, input6[i].head);
        CuAssertStrEquals(tc, expected[i].body1, input6[i].body1);
        CuAssertStrEquals(tc, expected[i].body2, input6[i].body2);
        CuAssertStrEquals(tc, expected[i].client, input6[i].client);
        CuAssertStrEquals(tc, expected[i].objective, input6[i].objective);
        CuAssertStrEquals(tc, expected[i].place, input6[i].place);
        CuAssertStrEquals(tc, expected[i].floor, input6[i].floor);
        CuAssertIntEquals(tc, (int)expected[i].difficulty, (int)input6[i].difficulty);
        CuAssertStrEquals(tc, expected[i].reward, input6[i].reward);
        CuAssertStrEquals(tc, expected[i].WMail, input6[i].WMail);
    }
#undef ARRAY_SIZE
}

void setFlavorTextBody_test(CuTest *tc)
{
#define ARRAY_SIZE 10
    const struct WonderMail input1[ARRAY_SIZE] = {
        { 5, 2,  0,   7,   8,   9,  5,   9,  0,   3, 238, 255,  1,  1 },
        { 5, 2,  0, 197, 131, 189,  1,  20,  0, 158,  34,   1,  2,  6 }, /* 1 instead of 255??? */
        { 5, 2,  0, 281,  25,   9,  9,  53, 37,  13,  10, 255, 62, 98 },
        { 5, 4,  0, 149, 149, 112,  0,   0,  0,   0,  54, 255,  0,  3 },
        { 5, 3,  0, 267, 267, 111,  0,   0,  0,   9, 237, 255, 36, 20 },
        { 5, 1,  9, 172, 172,   9,  1,  22,  0,   9, 120, 255, 21, 12 },
        { 5, 1,  9,  32,  29,   9,  2, 221,  0,  14, 189, 255, 31, 18 },
        { 5, 2, 10, 336, 337,   9,  3,  46,  0,  12, 192, 255, 33, 24 },
        { 9, 1,  9, 138, 140,   9,  5,  55,  0,   2,  64, 255, 43,  7 },
        { 5, 1,  9, 374, 129,   9,  6,  49,  0,   3, 211, 255, 57,  1 }
    };
    int input2[ARRAY_SIZE] = { 14, 14, 14, 16, 15,  7,  7,  8,  7,  7 };
    int input3[ARRAY_SIZE] = { -1, -1, -1, -1, -1, 44, 33, 38, 42,  5 };
    int input4[ARRAY_SIZE] = { -1, -1, -1, -1, -1, -1,  0,  5, -1, -1 };
    int input5[ARRAY_SIZE] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    struct WonderMailInfo input6[ARRAY_SIZE] = {
        { {0}, {0}, {0}, "Squirtle",  "Escort to Wartortle.", "Thunderwave Cave", "B1F",  'D', "400 poke",                      "1?J9N/X?4P?3\n          4??764?0P??W" },
        { {0}, {0}, {0}, "Umbreon",   "Escort to Lapras.",    "Mt. Steel",        " 6F",  'D', "200 poke + ??? [Pecha Scarf]",  "4?6F7M+?4JNR\n          J*??K??0+9??" },
        { {0}, {0}, {0}, "Combusken", "Escort to Pikachu.",   "Purity Forest",    " 98F", '*', "Friend Zone [Boulder Cave]",    "S62*S40?4P5H\n          8S?869H0!N?W" },
        { {0}, {0}, {0}, "Dragonite", "Deliver Moon Stone.",  "Tiny Woods",       "B3F",  'E', "100 poke",                      "???N+CS?466S\n          *+?RX4?5???W" },
        { {0}, {0}, {0}, "Blissey",   "Find Sun Stone.",      "Solar Cave",       "B20F", 'A', "500 poke",                      "F??CR/0?4/+!\n          *3?7TP?T?7?W" },
        { {0}, {0}, {0}, "Pichu",     "Find Pichu.",          "Meteor Cave",      "B12F", 'A', "500 poke + ??? [Warp Scarf]",   "F?6K-KY?0R84\n          +7?.67?R.7?W" },
        { {0}, {0}, {0}, "NidoranM",  "Find NidoranF.",       "Desert Region",    " 18F", 'A', "Stairs Orb",                    "4?MW4*Y?0P0!\n          9F?96NNRXN?W" },
        { {0}, {0}, {0}, "Plusle",    "Escort to Minum.",     "Wyvern Hill",      " 24F", 'S', "Friend Bow + ???",              "??N9FC+?+8S7\n          MT?H6P?0KN?W" },
        { {0}, {0}, {0}, "Omanyte",   "Find Kabuto.",         "Oddity Cave",      "B7F",  'B', "800 poke",                      "4?JYRHX?0RN?\n          N7?N6J?R*??W" },
        { {0}, {0}, {0}, "Feebas",    "Find Magikarp.",       "Unown Relic",      "B1F",  'B', "800 poke + ??? [Lunar Ribbon]", "1?-9*Q+?0R?8\n          QT??6K?R1??W" }
    };

    const struct WonderMailInfo expected[ARRAY_SIZE] = {
        { {0}, "I can't go by myself...",              "Please take me to see Wartortle!",          "Squirtle",  "Escort to Wartortle.", "Thunderwave Cave", "B1F",  'D', "400 poke",                      "1?J9N/X?4P?3\n          4??764?0P??W" },
        { {0}, "Lapras is waiting for me!",            "Please take me to see Lapras!",             "Umbreon",   "Escort to Lapras.",    "Mt. Steel",        " 6F",  'D', "200 poke + ??? [Pecha Scarf]",  "4?6F7M+?4JNR\n          J*??K??0+9??" },
        { {0}, "I have to go!",                        "Someone, please escort me!",                "Combusken", "Escort to Pikachu.",   "Purity Forest",    " 98F", '*', "Friend Zone [Boulder Cave]",    "S62*S40?4P5H\n          8S?869H0!N?W" },
        { {0}, "Having one Moon Stone is reassuring.", "Please give me one!",                       "Dragonite", "Deliver Moon Stone.",  "Tiny Woods",       "B3F",  'E', "100 poke",                      "???N+CS?466S\n          *+?RX4?5???W" },
        { {0}, "Sun Stone--it's convenient to have.",  "Please! I'm offering a generous reward!",   "Blissey",   "Find Sun Stone.",      "Solar Cave",       "B20F", 'A', "500 poke",                      "F??CR/0?4/+!\n          *3?7TP?T?7?W" },
        { {0}, "My little brother Pichu disappeared!", "I'm really worried! Someone, please help!", "Pichu",     "Find Pichu.",          "Meteor Cave",      "B12F", 'A', "500 poke + ??? [Warp Scarf]",   "F?6K-KY?0R84\n          +7?.67?R.7?W" },
        { {0}, "Please! Please rescue NidoranF!",      "We're madly in love!",                      "NidoranM",  "Find NidoranF.",       "Desert Region",    " 18F", 'A', "Stairs Orb",                    "4?MW4*Y?0P0!\n          9F?96NNRXN?W" },
        { {0}, "I really want to meet Minun!",         "We're in love! Please, take me there!",     "Plusle",    "Escort to Minum.",     "Wyvern Hill",      " 24F", 'S', "Friend Bow + ???",              "??N9FC+?+8S7\n          MT?H6P?0KN?W" },
        { {0}, "Kabuto has been a rival since my",     "ancestors' time. The rivalry can't end!",   "Omanyte",   "Find Kabuto.",         "Oddity Cave",      "B7F",  'B', "800 poke",                      "4?JYRHX?0RN?\n          N7?N6J?R*??W" },
        { {0}, "Help! Magikarp isn't much now, but",   "my friend is amazing after evolution!",     "Feebas",    "Find Magikarp.",       "Unown Relic",      "B1F",  'B', "800 poke + ??? [Lunar Ribbon]", "1?-9*Q+?0R?8\n          QT??6K?R1??W" }
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        setFlavorTextBody(&input1[i], input2[i], input3[i], input4[i], input5[i], &input6[i]);
        CuAssertStrEquals(tc, expected[i].head, input6[i].head);
        CuAssertStrEquals(tc, expected[i].body1, input6[i].body1);
        CuAssertStrEquals(tc, expected[i].body2, input6[i].body2);
        CuAssertStrEquals(tc, expected[i].client, input6[i].client);
        CuAssertStrEquals(tc, expected[i].objective, input6[i].objective);
        CuAssertStrEquals(tc, expected[i].place, input6[i].place);
        CuAssertStrEquals(tc, expected[i].floor, input6[i].floor);
        CuAssertIntEquals(tc, (int)expected[i].difficulty, (int)input6[i].difficulty);
        CuAssertStrEquals(tc, expected[i].reward, input6[i].reward);
        CuAssertStrEquals(tc, expected[i].WMail, input6[i].WMail);
    }
#undef ARRAY_SIZE
}