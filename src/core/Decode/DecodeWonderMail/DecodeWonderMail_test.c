#include "../../../../test/CuTest.h"

#include "DecodeWonderMail.h"

#include <stdlib.h>


CuSuite* DecodeWonderMailGetTestSuite(void);

void decodeWonderMail_test(CuTest *tc);
void bitUnpackingDecodingWonderMail_test(CuTest *tc);
void setFlavorText_test(CuTest *tc);
void setFlavorTextHead_test(CuTest *tc);
void setFlavorTextBody_test(CuTest *tc);
void setWonderMailInfo_test(CuTest *tc);


CuSuite* DecodeWonderMailGetTestSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, decodeWonderMail_test);
    SUITE_ADD_TEST(suite, bitUnpackingDecodingWonderMail_test);
    SUITE_ADD_TEST(suite, setFlavorText_test);
    SUITE_ADD_TEST(suite, setFlavorTextHead_test);
    SUITE_ADD_TEST(suite, setFlavorTextBody_test);
    SUITE_ADD_TEST(suite, setWonderMailInfo_test);
    return suite;
}

void decodeWonderMail_test(CuTest *tc)
{
#define ARRAY_SIZE 11
    const char input1[ARRAY_SIZE][24 + 1] = {
        { "1?J9N/X?4P?34??764?0P??W" }, /* (WM - VALID) */
        { "2?J9N/X?4P?34??764?0P??W" }, /* (WM - INVALID CHECKSUM) */
        { "4?6F7M+?4JNRJ*??K??0+9??" }, /* (WM - VALID) */
        { "16?WR3T 48MX13?767?6?6?W" }, /* (WM - INVALID INPUT) */
        { "S60*SW0?4P5HHS?869H0?N?W" }, /* (WM - VALID) */
        { "???N+CS?466S*+?RX4?5???W" }, /* (WM - VALID) */
        { "???Y0KS?4PR8**?-6??0?N?W" }, /* (WM - INVALID CHECKSUM) */
        { "F??CR/0?4/+!*3?7TP?T?7?W" }, /* (WM - VALID) */
        { "A??CR/0?4/+!*3?7TP?T?7?W" }, /* (WM - INVALID INPUT) */
        { "1?C.MWY?JPS3.F?0XP?5!2?W" }, /* (WM - VALID - SPECIAL EVOLVE) */
        { "F?N.?QY?8RNYYN?4.J75N+?W" }  /* (WM - VALID - SPECIAL FOOD) */
    };
    struct WonderMail input2[ARRAY_SIZE] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    int actualReturnResults[ARRAY_SIZE];

    const int expected1[ARRAY_SIZE] = { NoError, ChecksumError, NoError, InputError, NoError, NoError, ChecksumError, NoError, InputError, NoError, NoError };
    const struct WonderMail expected2[ARRAY_SIZE] = {
        { 5, 2, 0,   7,   8,   9, 5,   9,  0,   3, 238, 255,  1,  1 },
        { 0, 0, 0,   0,   0,   0, 0,   0,  0,   0,   0,   0,  0,  0 },
        { 5, 2, 0, 197, 131, 189, 1,  20,  0, 158,  34,   1,  2,  6 },
        { 0, 0, 0,   0,   0,   0, 0,   0,  0,   0,   0,   0,  0,  0 },
        { 5, 2, 0, 281,  25,   9, 9,   0, 37,  13, 250, 255, 62, 98 },
        { 5, 4, 0, 149, 149, 112, 0,   0,  0,   0,  54, 255,  0,  3 },
        { 0, 0, 0,   0,   0,   0, 0,   0,  0,   0,   0,   0,  0,  0 },
        { 5, 3, 0, 267, 267, 111, 0,   0,  0,   9, 237, 255, 36, 20 },
        { 0, 0, 0,   0,   0,   0, 0,   0,  0,   0,   0,   0,  0,  0 },
        { 5, 4, 5,  37,  37, 113, 3,  53,  0, 103, 254, 255, 34, 24 },
        { 5, 4, 6, 192, 192,  89, 3, 134,  0, 169, 215, 255, 42,  7 }
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actualReturnResults[i] = decodeWonderMail(input1[i], &input2[i]);
        CuAssertIntEquals(tc, expected1[i], actualReturnResults[i]);
        CuAssertIntEquals(tc, expected2[i].mailType,            input2[i].mailType);
        CuAssertIntEquals(tc, expected2[i].missionType,         input2[i].missionType);
        CuAssertIntEquals(tc, expected2[i].specialJobIndicator, input2[i].specialJobIndicator);
        CuAssertIntEquals(tc, expected2[i].pkmnClient,          input2[i].pkmnClient);
        CuAssertIntEquals(tc, expected2[i].pkmnTarget,          input2[i].pkmnTarget);
        CuAssertIntEquals(tc, expected2[i].itemDeliverFind,     input2[i].itemDeliverFind);
        CuAssertIntEquals(tc, expected2[i].rewardType,          input2[i].rewardType);
        CuAssertIntEquals(tc, expected2[i].itemReward,          input2[i].itemReward);
        CuAssertIntEquals(tc, expected2[i].friendAreaReward,    input2[i].friendAreaReward);
        CuAssertIntEquals(tc, expected2[i].flavorText,          input2[i].flavorText);
        CuAssertIntEquals(tc, expected2[i].random,              input2[i].random);
        CuAssertIntEquals(tc, expected2[i].idk_always0xFF,      input2[i].idk_always0xFF);
        CuAssertIntEquals(tc, expected2[i].dungeon,             input2[i].dungeon);
        CuAssertIntEquals(tc, expected2[i].floor,               input2[i].floor);
    }
#undef ARRAY_SIZE
}

void bitUnpackingDecodingWonderMail_test(CuTest *tc)
{
#define ARRAY_SIZE 7
    const char input1[ARRAY_SIZE][14] = {
        { 0x25, 0x38, 0x80, 0x20, 0xA1, 0x12, 0x80, 0x01, 0xF7, 0xFF, 0x40, 0x00, 0x00, 0x00 }, /* (WM - VALID) */
        { 0x25, 0x28, 0x36, 0xA8, 0x37, 0x28, 0x00, 0x4F, 0x91, 0x00, 0x81, 0x01, 0x00, 0x00 }, /* (WM - VALID) */
        { 0x25, 0xC8, 0x98, 0x21, 0x21, 0x6B, 0xCA, 0x06, 0x85, 0x7F, 0x9F, 0x18, 0x00, 0x00 }, /* (WM - VALID) */
        { 0x45, 0xA8, 0x54, 0x09, 0x0E, 0x00, 0x00, 0x00, 0x9B, 0x7F, 0xC0, 0x00, 0x00, 0x00 }, /* (WM - VALID) */
        { 0x35, 0x58, 0xB8, 0xF0, 0x0D, 0x00, 0x80, 0x84, 0xF6, 0x7F, 0x12, 0x05, 0x00, 0x00 }, /* (WM - VALID) */
        { 0xC5, 0x2A, 0x51, 0x22, 0x6E, 0x6A, 0x80, 0x33, 0xFF, 0x7F, 0x11, 0x06, 0x00, 0x00 }, /* (WM - VALID - SPECIAL EVOLVE) */
        { 0x45, 0x03, 0x06, 0x2C, 0x6B, 0x0C, 0x81, 0xD4, 0xEB, 0x7F, 0xD5, 0x01, 0x00, 0x00 }  /* (WM - VALID - SPECIAL FOOD) */
    };
    struct WonderMail input2[ARRAY_SIZE] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    const struct WonderMail expected[ARRAY_SIZE] = {
        { 5, 2, 0,   7,   8,   9, 5,   9,  0,   3, 238, 255,  1,  1 },
        { 5, 2, 0, 197, 131, 189, 1,  20,  0, 158,  34,   1,  2,  6 },
        { 5, 2, 0, 281,  25,   9, 9,  53, 37,  13,  10, 255, 62, 98 },
        { 5, 4, 0, 149, 149, 112, 0,   0,  0,   0,  54, 255,  0,  3 },
        { 5, 3, 0, 267, 267, 111, 0,   0,  0,   9, 237, 255, 36, 20 },
        { 5, 4, 5,  37,  37, 113, 3,  53,  0, 103, 254, 255, 34, 24 },
        { 5, 4, 6, 192, 192,  89, 3, 134,  0, 169, 215, 255, 42,  7 }
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        bitUnpackingDecodingWonderMail(input1[i], &input2[i]);
        CuAssertIntEquals(tc, expected[i].mailType,            input2[i].mailType);
        CuAssertIntEquals(tc, expected[i].specialJobIndicator, input2[i].specialJobIndicator);
        CuAssertIntEquals(tc, expected[i].pkmnClient,          input2[i].pkmnClient);
        CuAssertIntEquals(tc, expected[i].pkmnTarget,          input2[i].pkmnTarget);
        CuAssertIntEquals(tc, expected[i].itemDeliverFind,     input2[i].itemDeliverFind);
        CuAssertIntEquals(tc, expected[i].rewardType,          input2[i].rewardType);
        CuAssertIntEquals(tc, expected[i].itemReward,          input2[i].itemReward);
        CuAssertIntEquals(tc, expected[i].friendAreaReward,    input2[i].friendAreaReward);
        CuAssertIntEquals(tc, expected[i].flavorText,          input2[i].flavorText);
        CuAssertIntEquals(tc, expected[i].random,              input2[i].random);
        CuAssertIntEquals(tc, expected[i].idk_always0xFF,      input2[i].idk_always0xFF);
        CuAssertIntEquals(tc, expected[i].dungeon,             input2[i].dungeon);
        CuAssertIntEquals(tc, expected[i].floor,               input2[i].floor);
    }
#undef ARRAY_SIZE
}

void setFlavorText_test(CuTest *tc)
{
#define ARRAY_SIZE 12
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
        { 5, 1,  9, 374, 129,   9,  6,  49,  0,   3, 211, 255, 57,  1 },
        { 5, 4,  5,  37,  37, 113,  3,  53,  0, 103, 254, 255, 34, 24 },
        { 5, 4,  6, 192, 192,  89,  3, 134,  0, 169, 215, 255, 42,  7 }
    };
    struct WonderMailInfo input2[ARRAY_SIZE] = {
        { {0}, {0}, {0}, "Squirtle",  "Escort to Wartortle.", "Thunderwave Cave", "B1F",  'D', "400 poke",                      "1?J9N/X?4P?34??764?0P??W" },
        { {0}, {0}, {0}, "Umbreon",   "Escort to Lapras.",    "Mt. Steel",        " 6F",  'D', "200 poke + ??? [Pecha Scarf]",  "4?6F7M+?4JNRJ*??K??0+9??" },
        { {0}, {0}, {0}, "Combusken", "Escort to Pikachu.",   "Purity Forest",    " 98F", '*', "Friend Zone [Boulder Cave]",    "S62*S40?4P5H8S?869H0!N?W" },
        { {0}, {0}, {0}, "Dragonite", "Deliver Moon Stone.",  "Tiny Woods",       "B3F",  'E', "100 poke",                      "???N+CS?466S*+?RX4?5???W" },
        { {0}, {0}, {0}, "Blissey",   "Find Sun Stone.",      "Near Solar Cave",  "B20F", 'A', "500 poke",                      "F??CR/0?4/+!*3?7TP?T?7?W" },
        { {0}, {0}, {0}, "Pichu",     "Find Pichu.",          "Meteor Cave",      "B12F", 'A', "500 poke + ??? [Warp Scarf]",   "F?6K-KY?0R84+7?.67?R.7?W" },
        { {0}, {0}, {0}, "NidoranM",  "Find NidoranF.",       "Desert Region",    " 18F", 'A', "Stairs Orb",                    "4?MW4*Y?0P0!9F?96NNRXN?W" },
        { {0}, {0}, {0}, "Plusle",    "Escort to Minum.",     "Wyvern Hill",      " 24F", 'S', "Friend Bow + ???",              "??N9FC+?+8S7MT?H6P?0KN?W" },
        { {0}, {0}, {0}, "Omanyte",   "Find Kabuto.",         "Oddity Cave",      "B7F",  'B', "800 poke",                      "4?JYRHX?0RN?N7?N6J?R*??W" },
        { {0}, {0}, {0}, "Feebas",    "Find Magikarp.",       "Unown Relic",      "B1F",  'B', "800 poke + ??? [Lunar Ribbon]", "1?-9*Q+?0R?8QT??6K?R1??W" },
        { {0}, {0}, {0}, "Vulpix",    "Deliver Fire Stone.",  "Fiery Field",      " 24F", 'A', "Heal Seed + ???",               "1?C.MWY?JPS3.F?0XP?5!2?W" },
        { {0}, {0}, {0}, "Sunflora",  "Deliver Grass Gummi.", "Uproar Forest",    "B7F",  'C', "Hidden Power + ???",            "F?N.?QY?8RNYYN?4.J75N+?W" }
    };

    const struct WonderMailInfo expected[ARRAY_SIZE] = {
        { "Take me!",                "I can't go by myself...",              "Please take me to see Wartortle!",          "Squirtle",  "Escort to Wartortle.", "Thunderwave Cave", "B1F",  'D', "400 poke",                      "1?J9N/X?4P?34??764?0P??W" },
        { "Take me!",                "Lapras is waiting for me!",            "Please take me to see Lapras!",             "Umbreon",   "Escort to Lapras.",    "Mt. Steel",        " 6F",  'D', "200 poke + ??? [Pecha Scarf]",  "4?6F7M+?4JNRJ*??K??0+9??" },
        { "Escort me!",              "I have to go!",                        "Someone, please escort me!",                "Combusken", "Escort to Pikachu.",   "Purity Forest",    " 98F", '*', "Friend Zone [Boulder Cave]",    "S62*S40?4P5H8S?869H0!N?W" },
        { "Deliver one Moon Stone",  "Having one Moon Stone is reassuring.", "Please give me one!",                       "Dragonite", "Deliver Moon Stone.",  "Tiny Woods",       "B3F",  'E', "100 poke",                      "???N+CS?466S*+?RX4?5???W" },
        { "One Sun Stone wanted!",   "Sun Stone--it's convenient to have.",  "Please! I'm offering a generous reward!",   "Blissey",   "Find Sun Stone.",      "Near Solar Cave",  "B20F", 'A', "500 poke",                      "F??CR/0?4/+!*3?7TP?T?7?W" },
        { "Please help my brother!", "My little brother Pichu disappeared!", "I'm really worried! Someone, please help!", "Pichu",     "Find Pichu.",          "Meteor Cave",      "B12F", 'A', "500 poke + ??? [Warp Scarf]",   "F?6K-KY?0R84+7?.67?R.7?W" },
        { "Please save my love!",    "Please! Please rescue NidoranF!",      "We're madly in love!",                      "NidoranM",  "Find NidoranF.",       "Desert Region",    " 18F", 'A', "Stairs Orb",                    "4?MW4*Y?0P0!9F?96NNRXN?W" },
        { "Escort me to my love!",   "I really want to meet Minum!",         "We're in love! Please, take me there!",     "Plusle",    "Escort to Minum.",     "Wyvern Hill",      " 24F", 'S', "Friend Bow + ???",              "??N9FC+?+8S7MT?H6P?0KN?W" },
        { "Rescue my rival!",        "Kabuto has been a rival since my",     "ancestors' time. The rivalry can't end!",   "Omanyte",   "Find Kabuto.",         "Oddity Cave",      "B7F",  'B', "800 poke",                      "4?JYRHX?0RN?N7?N6J?R*??W" },
        { "Please save my friend!",  "Help! Magikarp isn't much now, but",   "my friend is amazing after evolution!",     "Feebas",    "Find Magikarp.",       "Unown Relic",      "B1F",  'B', "800 poke + ??? [Lunar Ribbon]", "1?-9*Q+?0R?8QT??6K?R1??W" },
        { "Deliver one Fire Stone",  "With the item Fire Stone, I can",      "evolve! I'm yearning to evolve! Help!",     "Vulpix",    "Deliver Fire Stone.",  "Fiery Field",      " 24F", 'A', "Heal Seed + ???",               "1?C.MWY?JPS3.F?0XP?5!2?W" },
        { "Deliver one Grass Gummi", "The Grass Gummi! What I love to eat",  "and can't live without! Please get one!",   "Sunflora",  "Deliver Grass Gummi.", "Uproar Forest",    "B7F",  'C', "Hidden Power + ???",            "F?N.?QY?8RNYYN?4.J75N+?W" }
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
        CuAssertStrEquals(tc, expected[i].password, input2[i].password);
    }
#undef ARRAY_SIZE
}

void setFlavorTextHead_test(CuTest *tc)
{
#define ARRAY_SIZE 12
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
        { 5, 1,  9, 374, 129,   9,  6,  49,  0,   3, 211, 255, 57,  1 },
        { 5, 4,  5,  37,  37, 113,  3,  53,  0, 103, 254, 255, 34, 24 },
        { 5, 4,  6, 192, 192,  89,  3, 134,  0, 169, 215, 255, 42,  7 }
    };
    int input2[ARRAY_SIZE] = { 10, 10, 10, 12, 11,  5,  5,  6,  5,  5, 12, 12 };
    int input3[ARRAY_SIZE] = { -1, -1, -1, -1, -1, 44, 33, 38, 42,  5, -1, -1 };
    int input4[ARRAY_SIZE] = { -1, -1, -1, -1, -1, -1,  0,  5, -1, -1, -1, -1 };
    int input5[ARRAY_SIZE] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    struct WonderMailInfo input6[ARRAY_SIZE] = {
        { {0}, {0}, {0}, "Squirtle",  "Escort to Wartortle.", "Thunderwave Cave", "B1F",  'D', "400 poke",                      "1?J9N/X?4P?34??764?0P??W" },
        { {0}, {0}, {0}, "Umbreon",   "Escort to Lapras.",    "Mt. Steel",        " 6F",  'D', "200 poke + ??? [Pecha Scarf]",  "4?6F7M+?4JNRJ*??K??0+9??" },
        { {0}, {0}, {0}, "Combusken", "Escort to Pikachu.",   "Purity Forest",    " 98F", '*', "Friend Zone [Boulder Cave]",    "S62*S40?4P5H8S?869H0!N?W" },
        { {0}, {0}, {0}, "Dragonite", "Deliver Moon Stone.",  "Tiny Woods",       "B3F",  'E', "100 poke",                      "???N+CS?466S*+?RX4?5???W" },
        { {0}, {0}, {0}, "Blissey",   "Find Sun Stone.",      "Near Solar Cave",  "B20F", 'A', "500 poke",                      "F??CR/0?4/+!*3?7TP?T?7?W" },
        { {0}, {0}, {0}, "Pichu",     "Find Pichu.",          "Meteor Cave",      "B12F", 'A', "500 poke + ??? [Warp Scarf]",   "F?6K-KY?0R84+7?.67?R.7?W" },
        { {0}, {0}, {0}, "NidoranM",  "Find NidoranF.",       "Desert Region",    " 18F", 'A', "Stairs Orb",                    "4?MW4*Y?0P0!9F?96NNRXN?W" },
        { {0}, {0}, {0}, "Plusle",    "Escort to Minum.",     "Wyvern Hill",      " 24F", 'S', "Friend Bow + ???",              "??N9FC+?+8S7MT?H6P?0KN?W" },
        { {0}, {0}, {0}, "Omanyte",   "Find Kabuto.",         "Oddity Cave",      "B7F",  'B', "800 poke",                      "4?JYRHX?0RN?N7?N6J?R*??W" },
        { {0}, {0}, {0}, "Feebas",    "Find Magikarp.",       "Unown Relic",      "B1F",  'B', "800 poke + ??? [Lunar Ribbon]", "1?-9*Q+?0R?8QT??6K?R1??W" },
        { {0}, {0}, {0}, "Vulpix",    "Deliver Fire Stone.",  "Fiery Field",      " 24F", 'A', "Heal Seed + ???",               "1?C.MWY?JPS3.F?0XP?5!2?W" },
        { {0}, {0}, {0}, "Sunflora",  "Deliver Grass Gummi.", "Uproar Forest",    "B7F",  'C', "Hidden Power + ???",            "F?N.?QY?8RNYYN?4.J75N+?W" }
    };

    const struct WonderMailInfo expected[ARRAY_SIZE] = {
        { "Take me!",                {0}, {0}, "Squirtle",  "Escort to Wartortle.", "Thunderwave Cave", "B1F",  'D', "400 poke",                      "1?J9N/X?4P?34??764?0P??W" },
        { "Take me!",                {0}, {0}, "Umbreon",   "Escort to Lapras.",    "Mt. Steel",        " 6F",  'D', "200 poke + ??? [Pecha Scarf]",  "4?6F7M+?4JNRJ*??K??0+9??" },
        { "Escort me!",              {0}, {0}, "Combusken", "Escort to Pikachu.",   "Purity Forest",    " 98F", '*', "Friend Zone [Boulder Cave]",    "S62*S40?4P5H8S?869H0!N?W" },
        { "Deliver one Moon Stone",  {0}, {0}, "Dragonite", "Deliver Moon Stone.",  "Tiny Woods",       "B3F",  'E', "100 poke",                      "???N+CS?466S*+?RX4?5???W" },
        { "One Sun Stone wanted!",   {0}, {0}, "Blissey",   "Find Sun Stone.",      "Near Solar Cave",  "B20F", 'A', "500 poke",                      "F??CR/0?4/+!*3?7TP?T?7?W" },
        { "Please help my brother!", {0}, {0}, "Pichu",     "Find Pichu.",          "Meteor Cave",      "B12F", 'A', "500 poke + ??? [Warp Scarf]",   "F?6K-KY?0R84+7?.67?R.7?W" },
        { "Please save my love!",    {0}, {0}, "NidoranM",  "Find NidoranF.",       "Desert Region",    " 18F", 'A', "Stairs Orb",                    "4?MW4*Y?0P0!9F?96NNRXN?W" },
        { "Escort me to my love!",   {0}, {0}, "Plusle",    "Escort to Minum.",     "Wyvern Hill",      " 24F", 'S', "Friend Bow + ???",              "??N9FC+?+8S7MT?H6P?0KN?W" },
        { "Rescue my rival!",        {0}, {0}, "Omanyte",   "Find Kabuto.",         "Oddity Cave",      "B7F",  'B', "800 poke",                      "4?JYRHX?0RN?N7?N6J?R*??W" },
        { "Please save my friend!",  {0}, {0}, "Feebas",    "Find Magikarp.",       "Unown Relic",      "B1F",  'B', "800 poke + ??? [Lunar Ribbon]", "1?-9*Q+?0R?8QT??6K?R1??W" },
        { "Deliver one Fire Stone",  {0}, {0}, "Vulpix",    "Deliver Fire Stone.",  "Fiery Field",      " 24F", 'A', "Heal Seed + ???",               "1?C.MWY?JPS3.F?0XP?5!2?W" },
        { "Deliver one Grass Gummi", {0}, {0}, "Sunflora",  "Deliver Grass Gummi.", "Uproar Forest",    "B7F",  'C', "Hidden Power + ???",            "F?N.?QY?8RNYYN?4.J75N+?W" }
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
        CuAssertStrEquals(tc, expected[i].password, input6[i].password);
    }
#undef ARRAY_SIZE
}

void setFlavorTextBody_test(CuTest *tc)
{
#define ARRAY_SIZE 12
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
        { 5, 1,  9, 374, 129,   9,  6,  49,  0,   3, 211, 255, 57,  1 },
        { 5, 4,  5,  37,  37, 113,  3,  53,  0, 103, 254, 255, 34, 24 },
        { 5, 4,  6, 192, 192,  89,  3, 134,  0, 169, 215, 255, 42,  7 }
    };
    int input2[ARRAY_SIZE] = { 14, 14, 14, 16, 15,  7,  7,  8,  7,  7, 16, 16 };
    int input3[ARRAY_SIZE] = { -1, -1, -1, -1, -1, 44, 33, 38, 42,  5, -1, -1 };
    int input4[ARRAY_SIZE] = { -1, -1, -1, -1, -1, -1,  0,  5, -1, -1, -1, -1 };
    int input5[ARRAY_SIZE] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    struct WonderMailInfo input6[ARRAY_SIZE] = {
        { {0}, {0}, {0}, "Squirtle",  "Escort to Wartortle.", "Thunderwave Cave", "B1F",  'D', "400 poke",                      "1?J9N/X?4P?34??764?0P??W" },
        { {0}, {0}, {0}, "Umbreon",   "Escort to Lapras.",    "Mt. Steel",        " 6F",  'D', "200 poke + ??? [Pecha Scarf]",  "4?6F7M+?4JNRJ*??K??0+9??" },
        { {0}, {0}, {0}, "Combusken", "Escort to Pikachu.",   "Purity Forest",    " 98F", '*', "Friend Zone [Boulder Cave]",    "S62*S40?4P5H8S?869H0!N?W" },
        { {0}, {0}, {0}, "Dragonite", "Deliver Moon Stone.",  "Tiny Woods",       "B3F",  'E', "100 poke",                      "???N+CS?466S*+?RX4?5???W" },
        { {0}, {0}, {0}, "Blissey",   "Find Sun Stone.",      "Near Solar Cave",  "B20F", 'A', "500 poke",                      "F??CR/0?4/+!*3?7TP?T?7?W" },
        { {0}, {0}, {0}, "Pichu",     "Find Pichu.",          "Meteor Cave",      "B12F", 'A', "500 poke + ??? [Warp Scarf]",   "F?6K-KY?0R84+7?.67?R.7?W" },
        { {0}, {0}, {0}, "NidoranM",  "Find NidoranF.",       "Desert Region",    " 18F", 'A', "Stairs Orb",                    "4?MW4*Y?0P0!9F?96NNRXN?W" },
        { {0}, {0}, {0}, "Plusle",    "Escort to Minum.",     "Wyvern Hill",      " 24F", 'S', "Friend Bow + ???",              "??N9FC+?+8S7MT?H6P?0KN?W" },
        { {0}, {0}, {0}, "Omanyte",   "Find Kabuto.",         "Oddity Cave",      "B7F",  'B', "800 poke",                      "4?JYRHX?0RN?N7?N6J?R*??W" },
        { {0}, {0}, {0}, "Feebas",    "Find Magikarp.",       "Unown Relic",      "B1F",  'B', "800 poke + ??? [Lunar Ribbon]", "1?-9*Q+?0R?8QT??6K?R1??W" },
        { {0}, {0}, {0}, "Vulpix",    "Deliver Fire Stone.",  "Fiery Field",      " 24F", 'A', "Heal Seed + ???",               "1?C.MWY?JPS3.F?0XP?5!2?W" },
        { {0}, {0}, {0}, "Sunflora",  "Deliver Grass Gummi.", "Uproar Forest",    "B7F",  'C', "Hidden Power + ???",            "F?N.?QY?8RNYYN?4.J75N+?W" }
    };

    const struct WonderMailInfo expected[ARRAY_SIZE] = {
        { {0}, "I can't go by myself...",              "Please take me to see Wartortle!",          "Squirtle",  "Escort to Wartortle.", "Thunderwave Cave", "B1F",  'D', "400 poke",                      "1?J9N/X?4P?34??764?0P??W" },
        { {0}, "Lapras is waiting for me!",            "Please take me to see Lapras!",             "Umbreon",   "Escort to Lapras.",    "Mt. Steel",        " 6F",  'D', "200 poke + ??? [Pecha Scarf]",  "4?6F7M+?4JNRJ*??K??0+9??" },
        { {0}, "I have to go!",                        "Someone, please escort me!",                "Combusken", "Escort to Pikachu.",   "Purity Forest",    " 98F", '*', "Friend Zone [Boulder Cave]",    "S62*S40?4P5H8S?869H0!N?W" },
        { {0}, "Having one Moon Stone is reassuring.", "Please give me one!",                       "Dragonite", "Deliver Moon Stone.",  "Tiny Woods",       "B3F",  'E', "100 poke",                      "???N+CS?466S*+?RX4?5???W" },
        { {0}, "Sun Stone--it's convenient to have.",  "Please! I'm offering a generous reward!",   "Blissey",   "Find Sun Stone.",      "Near Solar Cave",  "B20F", 'A', "500 poke",                      "F??CR/0?4/+!*3?7TP?T?7?W" },
        { {0}, "My little brother Pichu disappeared!", "I'm really worried! Someone, please help!", "Pichu",     "Find Pichu.",          "Meteor Cave",      "B12F", 'A', "500 poke + ??? [Warp Scarf]",   "F?6K-KY?0R84+7?.67?R.7?W" },
        { {0}, "Please! Please rescue NidoranF!",      "We're madly in love!",                      "NidoranM",  "Find NidoranF.",       "Desert Region",    " 18F", 'A', "Stairs Orb",                    "4?MW4*Y?0P0!9F?96NNRXN?W" },
        { {0}, "I really want to meet Minum!",         "We're in love! Please, take me there!",     "Plusle",    "Escort to Minum.",     "Wyvern Hill",      " 24F", 'S', "Friend Bow + ???",              "??N9FC+?+8S7MT?H6P?0KN?W" },
        { {0}, "Kabuto has been a rival since my",     "ancestors' time. The rivalry can't end!",   "Omanyte",   "Find Kabuto.",         "Oddity Cave",      "B7F",  'B', "800 poke",                      "4?JYRHX?0RN?N7?N6J?R*??W" },
        { {0}, "Help! Magikarp isn't much now, but",   "my friend is amazing after evolution!",     "Feebas",    "Find Magikarp.",       "Unown Relic",      "B1F",  'B', "800 poke + ??? [Lunar Ribbon]", "1?-9*Q+?0R?8QT??6K?R1??W" },
        { {0}, "With the item Fire Stone, I can",      "evolve! I'm yearning to evolve! Help!",     "Vulpix",    "Deliver Fire Stone.",  "Fiery Field",      " 24F", 'A', "Heal Seed + ???",               "1?C.MWY?JPS3.F?0XP?5!2?W" },
        { {0}, "The Grass Gummi! What I love to eat",  "and can't live without! Please get one!",   "Sunflora",  "Deliver Grass Gummi.", "Uproar Forest",    "B7F",  'C', "Hidden Power + ???",            "F?N.?QY?8RNYYN?4.J75N+?W" }
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
        CuAssertStrEquals(tc, expected[i].password, input6[i].password);
    }
#undef ARRAY_SIZE
}

void setWonderMailInfo_test(CuTest *tc)
{
#define ARRAY_SIZE 12
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
        { 5, 1,  9, 374, 129,   9,  6,  49,  0,   3, 211, 255, 57,  1 },
        { 5, 4,  5,  37,  37, 113,  3,  53,  0, 103, 254, 255, 34, 24 },
        { 5, 4,  6, 192, 192,  89,  3, 134,  0, 169, 215, 255, 42,  7 }
    };
    struct WonderMailInfo input2[ARRAY_SIZE] = {
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, "1?J9N/X?4P?34??764?0P??W" },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, "4?6F7M+?4JNRJ*??K??0+9??" },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, "S62*S40?4P5H8S?869H0!N?W" },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, "???N+CS?466S*+?RX4?5???W" },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, "F??CR/0?4/+!*3?7TP?T?7?W" },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, "F?6K-KY?0R84+7?.67?R.7?W" },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, "4?MW4*Y?0P0!9F?96NNRXN?W" },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, "??N9FC+?+8S7MT?H6P?0KN?W" },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, "4?JYRHX?0RN?N7?N6J?R*??W" },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, "1?-9*Q+?0R?8QT??6K?R1??W" },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, "1?C.MWY?JPS3.F?0XP?5!2?W" },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, "F?N.?QY?8RNYYN?4.J75N+?W" }
    };

    const struct WonderMailInfo expected[ARRAY_SIZE] = {
        { "Take me!",                "I can't go by myself...",              "Please take me to see Wartortle!",          "Squirtle",  "Escort to Wartortle.", "Thunderwave Cave", "B1F",  'D', "400 poke",                      "1?J9N/X?4P?34??764?0P??W" },
        { "Take me!",                "Lapras is waiting for me!",            "Please take me to see Lapras!",             "Umbreon",   "Escort to Lapras.",    "Mt. Steel",        " 6F",  'D', "200 poke + ??? [Pecha Scarf]",  "4?6F7M+?4JNRJ*??K??0+9??" },
        { "Escort me!",              "I have to go!",                        "Someone, please escort me!",                "Combusken", "Escort to Pikachu.",   "Purity Forest",    " 98F", '*', "Friend Zone [Boulder Cave]",    "S62*S40?4P5H8S?869H0!N?W" },
        { "Deliver one Moon Stone",  "Having one Moon Stone is reassuring.", "Please give me one!",                       "Dragonite", "Deliver Moon Stone.",  "Tiny Woods",       "B3F",  'E', "100 poke",                      "???N+CS?466S*+?RX4?5???W" },
        { "One Sun Stone wanted!",   "Sun Stone--it's convenient to have.",  "Please! I'm offering a generous reward!",   "Blissey",   "Find Sun Stone.",      "Near Solar Cave",  "B20F", 'A', "500 poke",                      "F??CR/0?4/+!*3?7TP?T?7?W" },
        { "Please help my brother!", "My little brother Pichu disappeared!", "I'm really worried! Someone, please help!", "Pichu",     "Find Pichu.",          "Meteor Cave",      "B12F", 'A', "500 poke + ??? [Warp Scarf]",   "F?6K-KY?0R84+7?.67?R.7?W" },
        { "Please save my love!",    "Please! Please rescue NidoranF!",      "We're madly in love!",                      "NidoranM",  "Find NidoranF.",       "Desert Region",    " 18F", 'A', "Stairs Orb",                    "4?MW4*Y?0P0!9F?96NNRXN?W" },
        { "Escort me to my love!",   "I really want to meet Minum!",         "We're in love! Please, take me there!",     "Plusle",    "Escort to Minum.",     "Wyvern Hill",      " 24F", 'S', "Friend Bow + ???",              "??N9FC+?+8S7MT?H6P?0KN?W" },
        { "Rescue my rival!",        "Kabuto has been a rival since my",     "ancestors' time. The rivalry can't end!",   "Omanyte",   "Find Kabuto.",         "Oddity Cave",      "B7F",  'B', "800 poke",                      "4?JYRHX?0RN?N7?N6J?R*??W" },
        { "Please save my friend!",  "Help! Magikarp isn't much now, but",   "my friend is amazing after evolution!",     "Feebas",    "Find Magikarp.",       "Unown Relic",      "B1F",  'B', "800 poke + ??? [Lunar Ribbon]", "1?-9*Q+?0R?8QT??6K?R1??W" },
        { "Deliver one Fire Stone",  "With the item Fire Stone, I can",      "evolve! I'm yearning to evolve! Help!",     "Vulpix",    "Deliver Fire Stone.",  "Fiery Field",      " 24F", 'A', "Heal Seed + ???",               "1?C.MWY?JPS3.F?0XP?5!2?W" },
        { "Deliver one Grass Gummi", "The Grass Gummi! What I love to eat",  "and can't live without! Please get one!",   "Sunflora",  "Deliver Grass Gummi.", "Uproar Forest",    "B7F",  'C', "Hidden Power + ???",            "F?N.?QY?8RNYYN?4.J75N+?W" }
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        setWonderMailInfo(&input1[i], &input2[i]);
        CuAssertStrEquals(tc, expected[i].head, input2[i].head);
        CuAssertStrEquals(tc, expected[i].body1, input2[i].body1);
        CuAssertStrEquals(tc, expected[i].body2, input2[i].body2);
        CuAssertStrEquals(tc, expected[i].client, input2[i].client);
        CuAssertStrEquals(tc, expected[i].objective, input2[i].objective);
        CuAssertStrEquals(tc, expected[i].place, input2[i].place);
        CuAssertStrEquals(tc, expected[i].floor, input2[i].floor);
        CuAssertIntEquals(tc, (int)expected[i].difficulty, (int)input2[i].difficulty);
        CuAssertStrEquals(tc, expected[i].reward, input2[i].reward);
        CuAssertStrEquals(tc, expected[i].password, input2[i].password);
    }
#undef ARRAY_SIZE
}