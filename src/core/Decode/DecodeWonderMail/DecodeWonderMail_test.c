#include "../../../../test/CuTest.h"

#include "DecodeWonderMail.h"

#include <stdlib.h>


CuSuite* DecodeWonderMailGetTestSuite(void);
void decodeWonderMail_test(CuTest *tc);


CuSuite* DecodeWonderMailGetTestSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, decodeWonderMail_test);
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

    struct WM_INFO expected[ARRAY_SIZE] = {
        { "Take me!",               "I can't go by myself...",              "Please take me to see Wartortle!",        "Squirtle",  "Escort to Wartortle.", "Thunderwave Cave", "B1F",  'D', "400 poke",                     "1?J9N/X?4P?3\n          4??764?0P??W" },
        { "Take me!",               "Lapras is waiting for me!",            "Please take me to see Lapras!",           "Umbreon",   "Escort to Lapras.",    "Mt. Steel",        " 6F",  'D', "200 poke + ??? [Pecha Scarf]", "4?6F7M+?4JNR\n          J*??K??0+9??" },
        { "Escort me!",             "I have to go!",                        "Someone, please escort me!",              "Combusken", "Escort to Pikachu.",   "Purity Forest",    " 98F", '*', "Friend Zone [Boulder Cave]",   "S62*S40?4P5H\n          8S?869H0!N?W" },
        { "Deliver one Moon Stone", "Having one Moon Stone is reassuring.", "Please give me one!",                     "Dragonite", "Deliver Moon Stone.",  "Tiny Woods",       "B3F",  'E', "100 poke",                     "???N+CS?466S\n          *+?RX4?5???W" },
        { "One Sun Stone wanted!",  "Sun Stone--it's convenient to have.",  "Please! I'm offering a generous reward!", "Blissey",   "Find Sun Stone.",      "Solar Cave",       "B20F", 'A', "500 poke",                     "F??CR/0?4/+!\n          *3?7TP?T?7?W" }
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        decodeWonderMail(input1[i], &input2[i]);
    }

    for (i = 0; i < ARRAY_SIZE; ++i) {
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
