#include "../../../../test/CuTest.h"

#include "DecodeSos.h"

#include <stdlib.h>


CuSuite* DecodeSosMailGetTestSuite(void);

void decodeSosMail_test(CuTest *tc);
void bitUnpackingDecodingSosMail_test(CuTest *tc);
void setSosInfo_test(CuTest *tc);


CuSuite* DecodeSosMailGetTestSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, decodeSosMail_test);
    SUITE_ADD_TEST(suite, bitUnpackingDecodingSosMail_test);
    SUITE_ADD_TEST(suite, setSosInfo_test);
    return suite;
}

void decodeSosMail_test(CuTest *tc)
{
#define ARRAY_SIZE 6
    const char input1[ARRAY_SIZE][54 + 1] = {
        { "N???2JR.1W/??R09?!?N????NFC??1??Q3H???X?K-Y??58??WS0T." }, /* (SOS - VALID) */
        { "M???2JR.1W/??R09?!?N????NFC??1??Q3H???X?K-Y??58??WS0T." }, /* (SOS - INVALID CHECKSUM) */
        { "?8?653?0KN4??599/M2.??4R313P?*?8+3H5??TN!T!/X/.??2/Q02" }, /* (SOS - VALID) */
        { "?Y??5S?.694??3W9/M2M??4R33WW?T?85QH5??TN74./X/0??85QJ2" }, /* (SOS - INVALID INPUT) */
        { "????6+7SHX???1?4???H??4?NP???4???TR?????X25??PJ??07?C?" }, /* (SOS - VALID) */
        { "PK?6667SS/???1?4???W??4?NP???P??J???????8?R??P+??NN?W?" }  /* (SOS - INVALID INPUT) */
    };
    struct SosMail input2[ARRAY_SIZE] = {
        { 0, 0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0 }
    };

    int actualReturnResults[ARRAY_SIZE];

    const int expected1[ARRAY_SIZE] = { NoError, ChecksumError, NoError, InputError, NoError, InputError };
    const struct SosMail expected2[ARRAY_SIZE] = {
        { 1, 58, 50, 0, 113, 1234, 0, "Nurcy",      0, 0, 0,  215733663, 0, 10, 0 },
        { 0,  0,  0, 0,   0,    0, 0, {0},          0, 0, 0,          0, 0,  0, 0 },
        { 1, 62, 98, 0, 414, 9999, 0, "Neo Cortex", 0, 0, 0, 1453159363, 0,  1, 0 },
        { 0,  0,  0, 0,   0,    0, 0, {0},          0, 0, 0,          0, 0,  0, 0 },
        { 1,  1,  3, 0, 100,    0, 0, "V",          0, 0, 0,  725035086, 0,  5, 0 },
        { 0,  0,  0, 0,   0,    0, 0, {0},          0, 0, 0,          0, 0,  0, 0 }
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actualReturnResults[i] = decodeSosMail(input1[i], &input2[i]);
        CuAssertIntEquals(tc, expected1[i], actualReturnResults[i]);
        CuAssertIntEquals(tc, expected2[i].mailType,          input2[i].mailType);
        CuAssertIntEquals(tc, expected2[i].dungeon,           input2[i].dungeon);
        CuAssertIntEquals(tc, expected2[i].floor,             input2[i].floor);
        /* skip the `idk_random` field (as it is random) */
        CuAssertIntEquals(tc, expected2[i].pkmnToRescue,      input2[i].pkmnToRescue);
        CuAssertIntEquals(tc, expected2[i].mailID,            input2[i].mailID);
        /* skip the `idk_random2` field (as it is random) */
        CuAssertStrEquals(tc, expected2[i].pkmnNick,          input2[i].pkmnNick);
        CuAssertIntEquals(tc, expected2[i].idk_0Or1,          input2[i].idk_0Or1);
        CuAssertIntEquals(tc, expected2[i].itemReward,        input2[i].itemReward);
        CuAssertIntEquals(tc, expected2[i].idk_0,             input2[i].idk_0);
        CuAssertIntEquals(tc, expected2[i].teamSeekingHelpID, input2[i].teamSeekingHelpID);
        CuAssertIntEquals(tc, expected2[i].teamGivingHelpID,  input2[i].teamGivingHelpID);
        CuAssertIntEquals(tc, expected2[i].chancesLeft,       input2[i].chancesLeft);
        CuAssertIntEquals(tc, expected2[i].idk_last3Bits,     input2[i].idk_last3Bits);
    }
#undef ARRAY_SIZE
}

void bitUnpackingDecodingSosMail_test(CuTest *tc)
{
#define ARRAY_SIZE 6
    const char input1[ARRAY_SIZE][33] = {
        { 0xA1, 0x93, 0xF1, 0xFB, 0x78, 0xC4, 0x91, 0x26, 0xB0, 0xA0, 0x73, 0xAA, 0x93, 0x1B, 0xCB, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xAC, 0xDE, 0x66, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00 }, /* (SOS - VALID) */
        { 0xA1, 0x93, 0xF1, 0xFB, 0x78, 0xC4, 0x91, 0x26, 0xB0, 0xA0, 0x73, 0xAA, 0x93, 0x93, 0xCB, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xAC, 0xDE, 0x66, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00 }, /* (SOS - INVALID) */
        { 0xE1, 0x13, 0xB7, 0xCE, 0x77, 0x79, 0x7E, 0x38, 0x69, 0x46, 0x71, 0x2A, 0x7B, 0x03, 0x19, 0x7A, 0x93, 0xA3, 0x2B, 0xC3, 0x03, 0x00, 0x00, 0x18, 0x9E, 0xEB, 0xB4, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00 }, /* (SOS - VALID) */
        { 0xF1, 0x13, 0xDB, 0x32, 0x41, 0x7A, 0xFE, 0xFF, 0x87, 0x2F, 0x76, 0x2A, 0x7B, 0x03, 0x19, 0x7A, 0x93, 0xA3, 0x2B, 0xC3, 0x03, 0x00, 0x00, 0x38, 0x91, 0x89, 0x9A, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00 }, /* (SOS - INVALID) */
        { 0x11, 0x18, 0x60, 0x4C, 0x94, 0x92, 0x01, 0x00, 0xC8, 0x00, 0xB4, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x42, 0xB9, 0x59, 0x01, 0x00, 0x00, 0x00, 0x28, 0x00 }, /* (SOS - VALID) */
        { 0x11, 0x18, 0x48, 0x19, 0xEC, 0x93, 0x01, 0x00, 0x00, 0xB7, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x23, 0x98, 0xAF, 0x02, 0x00, 0x00, 0x00, 0x28, 0x00 }, /* (SOS - INVALID) */
    };
    struct SosMail input2[ARRAY_SIZE] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    const struct SosMail expected[ARRAY_SIZE] = {
        { 1, 58, 50,  1982204, 113,  1234, 29718, "Nurcy",      0, 0, 0,  215733663, 0, 10, 0 },
        { 1, 58, 50,  1982204, 113,  1234, 29718, "Nurry",      0, 0, 0,  215733663, 0, 10, 0 },
        { 1, 62, 98,  6157229, 414,  9999, 10445, "Neo Cortex", 0, 0, 0, 1453159363, 0,  1, 0 },
        { 1, 63, 98,  9456822, 414, 65535, 50672, "Neo Cortex", 0, 0, 0,  324088359, 0,  1, 0 },
        { 1,  1,  3, 10818328, 100,     0, 32793, "V",          0, 0, 0,  725035086, 0,  5, 0 },
        { 1,  1,  3, 16451154, 100,     0, 22240, "",           0, 0, 0, 1441989758, 0,  5, 0 }
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        bitUnpackingDecodingSosMail(input1[i], &input2[i]);
        CuAssertIntEquals(tc, expected[i].mailType,          input2[i].mailType);
        CuAssertIntEquals(tc, expected[i].dungeon,           input2[i].dungeon);
        CuAssertIntEquals(tc, expected[i].floor,             input2[i].floor);
        CuAssertIntEquals(tc, expected[i].idk_random,        input2[i].idk_random);
        CuAssertIntEquals(tc, expected[i].pkmnToRescue,      input2[i].pkmnToRescue);
        CuAssertIntEquals(tc, expected[i].mailID,            input2[i].mailID);
        CuAssertIntEquals(tc, expected[i].idk_random2,       input2[i].idk_random2);
        CuAssertStrEquals(tc, expected[i].pkmnNick,          input2[i].pkmnNick);
        CuAssertIntEquals(tc, expected[i].idk_0Or1,          input2[i].idk_0Or1);
        CuAssertIntEquals(tc, expected[i].itemReward,        input2[i].itemReward);
        CuAssertIntEquals(tc, expected[i].idk_0,             input2[i].idk_0);
        CuAssertIntEquals(tc, expected[i].teamSeekingHelpID, input2[i].teamSeekingHelpID);
        CuAssertIntEquals(tc, expected[i].teamGivingHelpID,  input2[i].teamGivingHelpID);
        CuAssertIntEquals(tc, expected[i].chancesLeft,       input2[i].chancesLeft);
        CuAssertIntEquals(tc, expected[i].idk_last3Bits,     input2[i].idk_last3Bits);
    }
#undef ARRAY_SIZE
}
#include <stdio.h>
void setSosInfo_test(CuTest *tc)
{
#define ARRAY_SIZE 6
    const struct SosMail input1[ARRAY_SIZE] = {
        { 1, 58, 50,  1982204, 113,  1234, 29718, "Nurcy",      0, 0, 0,  215733663, 0, 10, 0 },
        { 1, 58, 50,  1982204, 113,  1234, 29718, "Nurry",      0, 0, 0,  215733663, 0, 10, 0 },
        { 1, 62, 98,  6157229, 414,  9999, 10445, "Neo Cortex", 0, 0, 0, 1453159363, 0,  1, 0 },
        { 1, 63, 98,  9456822, 414, 65535, 50672, "Neo Cortex", 0, 0, 0,  324088359, 0,  1, 0 },
        { 1,  1,  3, 10818328, 100,     0, 32793, "V",          0, 0, 0,  725035086, 0,  5, 0 },
        { 1,  1,  3, 16451154, 100,     0, 22240, "",           0, 0, 0, 1441989758, 0,  5, 0 }
    };
    struct SosMailInfo input2[ARRAY_SIZE] = {
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0}, {0}, "N???2JR.1W/??R09?!?N????NFC??1??Q3H???X?K-Y??58??WS0T." },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0}, {0}, "M???2JR.1W/??R09?!?N????NFC??1??Q3H???X?K-Y??58??WS0T." },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0}, {0}, "?8?653?0KN4??599/M2.??4R313P?*?8+3H5??TN!T!/X/.??2/Q02" },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0}, {0}, "?Y??5S?.694??3W9/M2M??4R33WW?T?85QH5??TN74./X/0??85QJ2" },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0}, {0}, "????6+7SHX???1?4???H??4?NP???4???TR?????X25??PJ??07?C?" },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0}, {0}, "PK?6667SS/???1?4???W??4?NP???P??J???????8?R??P+??NN?W?" }
    };

    struct SosMailInfo expected[ARRAY_SIZE] = {
        { "This is a rescue through communication.", "Get a friend to help you!", "Nurcy",      "Chansey", "Friend rescue.", "Joyous Tower",     " 50F", 'S', "???", "1234",  "10", "N???2JR.1W/??R09?!?N????NFC??1??Q3H???X?K-Y??58??WS0T." },
        { "This is a rescue through communication.", "Get a friend to help you!", "Nurry",      "Chansey", "Friend rescue.", "Joyous Tower",     " 50F", 'S', "???", "1234",  "10", "M???2JR.1W/??R09?!?N????NFC??1??Q3H???X?K-Y??58??WS0T." },
        { "This is a rescue through communication.", "Get a friend to help you!", "Neo Cortex", "Deoxys",  "Friend rescue.", "Purity Forest",    " 98F", '*', "???", "9999",  "1",  "?8?653?0KN4??599/M2.??4R313P?*?8+3H5??TN!T!/X/.??2/Q02" },
        { "This is a rescue through communication.", "Get a friend to help you!", "Neo Cortex", "Deoxys",  "Friend rescue.", "[INVALID]",        "?98F", 'E', "???", "65535", "1",  "?Y??5S?.694??3W9/M2M??4R33WW?T?85QH5??TN74./X/0??85QJ2" },
        { "This is a rescue through communication.", "Get a friend to help you!", "V",          "Voltorb", "Friend rescue.", "Thunderwave Cave", "B3F",  'E', "???", "0",     "5",  "????6+7SHX???1?4???H??4?NP???4???TR?????X25??PJ??07?C?" },
        { "This is a rescue through communication.", "Get a friend to help you!", "",           "Voltorb", "Friend rescue.", "Thunderwave Cave", "B3F",  'E', "???", "0",     "5", "PK?6667SS/???1?4???W??4?NP???P??J???????8?R??P+??NN?W?" }
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        setSosInfo(&input1[i], &input2[i]);
        CuAssertStrEquals(tc, expected[i].head,        input2[i].head);
        CuAssertStrEquals(tc, expected[i].body,        input2[i].body);
        CuAssertStrEquals(tc, expected[i].nickname,    input2[i].nickname);
        CuAssertStrEquals(tc, expected[i].client,      input2[i].client);
        CuAssertStrEquals(tc, expected[i].objective,   input2[i].objective);
        CuAssertStrEquals(tc, expected[i].place,       input2[i].place);
        CuAssertStrEquals(tc, expected[i].floor,       input2[i].floor);
        CuAssertIntEquals(tc, (int)expected[i].difficulty, (int)input2[i].difficulty);
        CuAssertStrEquals(tc, expected[i].reward,      input2[i].reward);
        CuAssertStrEquals(tc, expected[i].id,          input2[i].id);
        CuAssertStrEquals(tc, expected[i].chancesLeft, input2[i].chancesLeft);
        CuAssertStrEquals(tc, expected[i].password,    input2[i].password);
    }
#undef ARRAY_SIZE
}