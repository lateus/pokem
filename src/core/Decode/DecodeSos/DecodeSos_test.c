#include "../../../../test/CuTest.h"

#include "DecodeSos.h"

#include <stdlib.h>


CuSuite* DecodeSosMailGetTestSuite(void);

void decodeSosMail_test(CuTest *tc);


CuSuite* DecodeSosMailGetTestSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, decodeSosMail_test);
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

    int actualResults[ARRAY_SIZE];

    const int expected1[ARRAY_SIZE] = { NoError, ChecksumError, NoError, InputError, NoError, InputError };
    const struct SosMail expected2[ARRAY_SIZE] = {
        { 1, 58, 50, 0, 113, 1234, 0, "Nurcy", 0, 0, 0, 215733663, 0, 10, 0 },
        { 0, 0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 62, 98, 0, 414, 9999, 0, "Neo Cortex", 0, 0, 0, 1453159363, 0, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 3, 0, 100, 0, 0, "V", 0, 0, 0, 725035086, 0, 5, 0 },
        { 0, 0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, 0 }
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actualResults[i] = decodeSosMail(input1[i], &input2[i]);
        CuAssertIntEquals(tc, expected1[i], actualResults[i]);
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