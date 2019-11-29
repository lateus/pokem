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
        { "?3?658R0W74??SW9/M2-???R31WW?K?8QQH5??TNQXK/X/P??9-Q*2" }, /* (SOS - VALID) */
        { "?Y??5S?.694??3W9/M2M??4R33WW?T?85QH5??TN74./X/0??85QJ2" }, /* (SOS - INVALID INPUT) */
        { "????6+7SHX???1?4???H??4?NP???4???TR?????X25??PJ??07?C?" }, /* (SOS - VALID) */
        { "PK?6667SS/???1?4???W??4?NP???P??J???????8?R??P+??NN?W?" }  /* (SOS - INVALID INPUT) */
    };
    struct SosMailInfo input2[ARRAY_SIZE] = {
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0} },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0} },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0} },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0} },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0} },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0} }
    };

    int actualResults[ARRAY_SIZE];

    const int expected1[ARRAY_SIZE] = { NoError, ChecksumError, NoError, InputError, NoError, InputError };
    const struct SosMailInfo expected2[ARRAY_SIZE] = {
        { "This is a rescue through communication.", "Get a friend to help you!", "Nurcy",        "Chansey", "Friend rescue.",  "Joyous Tower",     " 50F", 'S', "???", "1234",  "10", "N???2JR.1W/??R09?!?N????NFC\n          ??1??Q3H???X?K-Y??58??WS0T." },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0} },
        { "This is a rescue through communication.", "Get a friend to help you!", "Neo Cortex",   "Deoxys",  "Friend rescue.",  "Purity Forest",    " 98F", '*', "???", "65535", "1",  "?3?658R0W74??SW9/M2-???R31W\n          W?K?8QQH5??TNQXK/X/P??9-Q*2" },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0} },
        { "This is a rescue through communication.", "Get a friend to help you!", "V",            "Voltorb", "Friend rescue.",  "Thunderwave Cave", "B3F",  'E', "???", "0",     "5",  "????6+7SHX???1?4???H??4?NP?\n          ??4???TR?????X25??PJ??07?C?" },
        { {0}, {0}, {0}, {0}, {0}, {0}, {0}, '\0', {0}, {0} }
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actualResults[i] = decodeSosMail(input1[i], &input2[i]);
        CuAssertIntEquals(tc, expected1[i], actualResults[i]);
        CuAssertStrEquals(tc, expected2[i].head, input2[i].head);
        CuAssertStrEquals(tc, expected2[i].body, input2[i].body);
        CuAssertStrEquals(tc, expected2[i].nickname, input2[i].nickname);
        CuAssertStrEquals(tc, expected2[i].client, input2[i].client);
        CuAssertStrEquals(tc, expected2[i].objective, input2[i].objective);
        CuAssertStrEquals(tc, expected2[i].place, input2[i].place);
        CuAssertStrEquals(tc, expected2[i].floor, input2[i].floor);
        CuAssertIntEquals(tc, (int)expected2[i].difficulty, (int)input2[i].difficulty);
        CuAssertStrEquals(tc, expected2[i].reward, input2[i].reward);
        CuAssertStrEquals(tc, expected2[i].id, input2[i].id);
        CuAssertStrEquals(tc, expected2[i].password, input2[i].password);
    }
#undef ARRAY_SIZE
}