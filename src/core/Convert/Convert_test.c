#include "../../../test/CuTest.h"

#include "Convert.h"
#include "../../data/md1global/md1global.h"

#include <stdlib.h>


CuSuite* ConvertGetTestSuite(void);

void convertSosMail_test(CuTest *tc);
void convertSosToAOkMail_test(CuTest *tc);
void convertAOkToThankYouMail_test(CuTest *tc);


CuSuite* ConvertGetTestSuite()
{
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, convertSosMail_test);
    SUITE_ADD_TEST(suite, convertSosToAOkMail_test);
    SUITE_ADD_TEST(suite, convertAOkToThankYouMail_test);
    return suite;
}
#include <stdio.h>
void convertSosMail_test(CuTest *tc)
{
#define ARRAY_SIZE 15
    const char input1[ARRAY_SIZE][54 + 1] = {
        "S3??7CRFSS1+?N/6?!4X????PSP??+?K*7J6??T?Q52S?35?4Q*RJ.", /* (SOS - VALID) */
        "?F???CRYTPC.?NH5?KKX????F1M7?!?-H!H6??T?7R+/?+!??WQQN0", /* (SOS - VALID) */
        "HM7?PJ?F2M!C?5SN2!MM??4RH387?S?HH!H2??T.7+M+XR2?4X251.", /* (SOS - VALID) */
        "TMN60T7XJ*2R?.35?2?1??4?M3?N?H?9SXP???T?4JKP?1???F/R/.", /* (SOS - VALID, but the item in `input2` is not) */
        "X1765WP619*H?617?121??4?.QN6?2?8!8R6??T?W3H+?43??0-R?C", /* (AOK - VALID) */
        "6C76RP78S63K?50K?HKM????15K7?1?K??J6??S?SQ?8?PJ?41/T0*", /* (AOK - VALID) */
        "S76?6R?9R!26?SPN?K??????H0*6?7??N+R???S?K5S??Y.?4P5TY.", /* (AOK - VALID) */
        "S.N?6TP0X729?7W6?MKN??4?.276?7?8T-H6??S??6M/?3H?406T-.", /* (ThankYou - VALID) */
        "6-76PS?XHHQK?1JK?4?X?????RNN?F?8K*H???X??6-7?X???N75YN", /* (ThankYou - VALID) */
        ".-N67N70YX*H?F3J?HH9???6H5-6?M?K59P5??TN97/PX1R?48JRW*", /* (ThankYou - VALID) */
        "?Y??5S?.694??3W9/M2M??4R33WW?T?85QH5??TN74./X/0??85QJ2", /* (SOS - INVALID INPUT) */
        "..N69PRP!P*-?M17?12T????.QN6?1?859R6??T?S?0+?43?4CHR5C", /* (AOK - INVALID CHECKSUM) */
        "X.N69PRP!P*-?M17?12T????.QN6?1?859R6??T?S?0+?43?4CHR5C", /* (AOK - INVALID INPUT) */
        "S*??7MRS5R2H?78R?MK1????*5H7?H?8FKH6??S?K1N/?3!?4.STM.", /* (ThankYou - INVALID INPUT) */
        "S.N?6TP0X729?7W6?MKN??4?.276?7?8T-H6??S??6M/?3H?406T-"   /* (ThankYou - INVALID INPUT) */
    };
    const int input2[ARRAY_SIZE] = { 199, 0, 1, 500, 30, 100, 123, 43, 56, 0, 167, 65, 5, 30, 43 };
    char input3[ARRAY_SIZE][54 + 1] = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0} };
    char input4[ARRAY_SIZE][54 + 1] = { {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0} };

    int actualReturnResults[ARRAY_SIZE];

    const int expected1[ARRAY_SIZE] = { NoError, NoError, NoError, InputError, NoError, NoError, NoError, NoError, NoError, NoError, InputError, ChecksumError, InputError, InputError, InputError };
    const char expected2[ARRAY_SIZE][54 + 1] = {
        "S3?47CP9SS1+Y+/6?!4XK?M?PTP??+TK*7J6?-T?Q52S?3584Q*RJ.",
        "?F?4?CPRTPC.Y9H5?KKXS?C?F2M7?!H-H!H6?+T?7R+/?+!F?WQQN0",
        "HM7FPJW92M!CKJSN2!MM??CRHQ87?S8HH!H2?+T.7+M+XR294X251.",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        ""
    };
    const char expected3[ARRAY_SIZE][54 + 1] = {
        "S3347CP0SS1+Y0/6?!4XK?M?PTP??+TK*7J61-T?Q52S?3584Q*RJ.",
        "?F?4?CPTTPC.Y4H5?KKXS?C?F2M7?!H-H!H6?+T?7R+/?+!F4WQQN0",
        "HM8FPJWY2M!CK/SN2!MM??CRHQ87?S8HH!H2?+T.7+M+XR294X251.",
        "",
        "X1!65WPF19*H?!17?121??4?.QN6?2?8!8R6N?T?W3H+?43?40-R?C",
        "6CM6RP7YS63K?J0K?HKM????15K7?1?K??J6S?S?SQ?8?PJ?41/T0*",
        "S7T?6R?XR!26?FPN?K??????H0*6?7??N+R?Y?S?K5S??Y.?4P5TY.",
        "S.Y?6TP.X729?*W6?MKN??4?.276?7?8T-H6R?S??6M/?3H?406T-.",
        "6-76PS?SHHQK?2JK?4?X?????RNN?F?8K*H?9?X??6-7?X???N75YN",
        ".-N67N70YX*H?F3J?HH9???6H5-6?M?K59P5??TN97/PX1R?48JRW*",
        "",
        "",
        "",
        "",
        ""
    };

    int i;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        actualReturnResults[i] = convertSosMail(input1[i], input2[i], input3[i], input4[i]);
        CuAssertIntEquals(tc, expected1[i], actualReturnResults[i]);
        CuAssertStrEquals(tc, expected2[i], input3[i]);
        CuAssertStrEquals(tc, expected3[i], input4[i]);
    }
#undef ARRAY_SIZE
}

void convertSosToAOkMail_test(CuTest *tc)
{
#define ARRAY_SIZE 5
    char input[ARRAY_SIZE][54] = {
        { 0x03, 0x0F, 0x18, 0x11, 0x00, 0x1A, 0x0A, 0x1F, 0x0D, 0x0E, 0x0A, 0x08, 0x14, 0x12, 0x02, 0x05, 0x08, 0x14, 0x1A, 0x14, 0x17, 0x1D, 0x0D, 0x00, 0x09, 0x13, 0x1E, 0x16, 0x17, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x04, 0x1D, 0x13, 0x02, 0x03, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00 },
        { 0x11, 0x08, 0x1C, 0x03, 0x04, 0x0C, 0x12, 0x0E, 0x19, 0x12, 0x05, 0x14, 0x0C, 0x06, 0x02, 0x0A, 0x12, 0x14, 0x1A, 0x14, 0x1A, 0x11, 0x0D, 0x14, 0x0B, 0x1A, 0x0A, 0x14, 0x12, 0x19, 0x0E, 0x05, 0x0B, 0x19, 0x00, 0x10, 0x13, 0x02, 0x00, 0x12, 0x19, 0x15, 0x02, 0x18, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00 },
        { 0x10, 0x08, 0x00, 0x04, 0x09, 0x10, 0x18, 0x07, 0x11, 0x1E, 0x04, 0x1B, 0x00, 0x0E, 0x04, 0x15, 0x11, 0x1A, 0x06, 0x14, 0x10, 0x0D, 0x0C, 0x14, 0x0B, 0x1D, 0x06, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x02, 0x14, 0x0D, 0x0C, 0x07, 0x1B, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00 },
        { 0x13, 0x09, 0x08, 0x13, 0x19, 0x16, 0x05, 0x05, 0x11, 0x08, 0x17, 0x01, 0x02, 0x04, 0x00, 0x18, 0x18, 0x19, 0x0E, 0x14, 0x17, 0x11, 0x0D, 0x04, 0x0B, 0x1D, 0x06, 0x16, 0x15, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x03, 0x00, 0x0F, 0x14, 0x17, 0x13, 0x09, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00 },
        { 0x03, 0x08, 0x0C, 0x01, 0x02, 0x0A, 0x19, 0x1D, 0x0C, 0x0E, 0x1C, 0x04, 0x1E, 0x04, 0x00, 0x11, 0x1C, 0x1B, 0x02, 0x15, 0x1A, 0x05, 0x0D, 0x0C, 0x0B, 0x18, 0x0C, 0x17, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0A, 0x00, 0x00, 0x0C, 0x1B, 0x13, 0x1D, 0x15, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00 }
    };

    char expected[ARRAY_SIZE][54] = {
        { 0x03, 0x07, 0x19, 0x11, 0x00, 0x1A, 0x0A, 0x1F, 0x0D, 0x0E, 0x0A, 0x08, 0x14, 0x12, 0x02, 0x05, 0x08, 0x14, 0x1A, 0x14, 0x17, 0x1D, 0x0D, 0x00, 0x09, 0x13, 0x1E, 0x16, 0x17, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x04, 0x1D, 0x13, 0x02, 0x03, 0x1A, 0x10, 0x14, 0x0F, 0x0A, 0x0C, 0x08, 0x13, 0x04, 0x00 },
        { 0x11, 0x00, 0x1D, 0x03, 0x04, 0x0C, 0x12, 0x0E, 0x19, 0x12, 0x05, 0x14, 0x0C, 0x06, 0x02, 0x0A, 0x12, 0x14, 0x1A, 0x14, 0x1A, 0x11, 0x0D, 0x14, 0x0B, 0x1A, 0x0A, 0x14, 0x12, 0x19, 0x0E, 0x05, 0x0B, 0x19, 0x00, 0x10, 0x13, 0x02, 0x00, 0x12, 0x19, 0x15, 0x02, 0x18, 0x19, 0x08, 0x06, 0x17, 0x0A, 0x00, 0x07, 0x13, 0xFF, 0x00 },
        { 0x10, 0x00, 0x01, 0x04, 0x09, 0x10, 0x18, 0x07, 0x11, 0x1E, 0x04, 0x1B, 0x00, 0x0E, 0x04, 0x15, 0x11, 0x1A, 0x06, 0x14, 0x10, 0x0D, 0x0C, 0x14, 0x0B, 0x1D, 0x06, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x02, 0x14, 0x0D, 0x0C, 0x07, 0x1B, 0x09, 0x10, 0x16, 0x11, 0x1D, 0x0C, 0x17, 0x04, 0x00 },
        { 0x13, 0x01, 0x09, 0x13, 0x19, 0x16, 0x05, 0x05, 0x11, 0x08, 0x17, 0x01, 0x02, 0x04, 0x00, 0x18, 0x18, 0x19, 0x0E, 0x14, 0x17, 0x11, 0x0D, 0x04, 0x0B, 0x1D, 0x06, 0x16, 0x15, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x03, 0x00, 0x0F, 0x14, 0x17, 0x13, 0x09, 0x17, 0x1C, 0x11, 0x1E, 0x0E, 0x06, 0x1D, 0x12, 0xFF, 0x00 },
        { 0x03, 0x00, 0x0D, 0x01, 0x02, 0x0A, 0x19, 0x1D, 0x0C, 0x0E, 0x1C, 0x04, 0x1E, 0x04, 0x00, 0x11, 0x1C, 0x1B, 0x02, 0x15, 0x1A, 0x05, 0x0D, 0x0C, 0x0B, 0x18, 0x0C, 0x17, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0A, 0x00, 0x00, 0x0C, 0x1B, 0x13, 0x1D, 0x15, 0x11, 0x10, 0x0D, 0x0F, 0x16, 0x17, 0x06, 0x12, 0x04, 0x00 }
    };

    int i, j;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        convertSosToAOkMail(input[i]);
        for (j = 0; j < 54; ++j) {
            CuAssertIntEquals(tc, expected[i][j], input[i][j]);
        }
    }
#undef ARRAY_SIZE
}

void convertAOkToThankYouMail_test(CuTest *tc)
{
#define ARRAY_SIZE 5
    char input1[ARRAY_SIZE][54] = {
        { 0x07, 0x05, 0x19, 0x11, 0x00, 0x1A, 0x0A, 0x1F, 0x0D, 0x0E, 0x0A, 0x08, 0x14, 0x12, 0x02, 0x05, 0x08, 0x14, 0x1A, 0x14, 0x17, 0x1D, 0x0D, 0x00, 0x09, 0x13, 0x1E, 0x16, 0x17, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x04, 0x1D, 0x13, 0x02, 0x03, 0x1A, 0x10, 0x14, 0x0F, 0x0A, 0x0C, 0x08, 0x13, 0x04, 0x00 },
        { 0x15, 0x07, 0x1D, 0x03, 0x04, 0x0C, 0x12, 0x0E, 0x19, 0x12, 0x05, 0x14, 0x0C, 0x06, 0x02, 0x0A, 0x12, 0x14, 0x1A, 0x14, 0x1A, 0x11, 0x0D, 0x14, 0x0B, 0x1A, 0x0A, 0x14, 0x12, 0x19, 0x0E, 0x05, 0x0B, 0x19, 0x00, 0x10, 0x13, 0x02, 0x00, 0x12, 0x19, 0x15, 0x02, 0x18, 0x19, 0x08, 0x06, 0x17, 0x0A, 0x00, 0x07, 0x13, 0x1F, 0x00 },
        { 0x16, 0x01, 0x01, 0x04, 0x09, 0x10, 0x18, 0x07, 0x11, 0x1E, 0x04, 0x1B, 0x00, 0x0E, 0x04, 0x15, 0x11, 0x1A, 0x06, 0x14, 0x10, 0x0D, 0x0C, 0x14, 0x0B, 0x1D, 0x06, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x02, 0x14, 0x0D, 0x0C, 0x07, 0x1B, 0x09, 0x10, 0x16, 0x11, 0x1D, 0x0C, 0x17, 0x04, 0x00 },
        { 0x16, 0x06, 0x09, 0x13, 0x19, 0x16, 0x05, 0x05, 0x11, 0x08, 0x17, 0x01, 0x02, 0x04, 0x00, 0x18, 0x18, 0x19, 0x0E, 0x14, 0x17, 0x11, 0x0D, 0x04, 0x0B, 0x1D, 0x06, 0x16, 0x15, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x03, 0x00, 0x0F, 0x14, 0x17, 0x13, 0x09, 0x17, 0x1C, 0x11, 0x1E, 0x0E, 0x06, 0x1D, 0x12, 0x1F, 0x00 },
        { 0x0A, 0x07, 0x0D, 0x01, 0x02, 0x0A, 0x19, 0x1D, 0x0C, 0x0E, 0x1C, 0x04, 0x1E, 0x04, 0x00, 0x11, 0x1C, 0x1B, 0x02, 0x15, 0x1A, 0x05, 0x0D, 0x0C, 0x0B, 0x18, 0x0C, 0x17, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0A, 0x00, 0x00, 0x0C, 0x1B, 0x13, 0x1D, 0x15, 0x11, 0x10, 0x0D, 0x0F, 0x16, 0x17, 0x06, 0x12, 0x04, 0x00 }
    };
    const int input2[ARRAY_SIZE] = { 0, 1, 144, 98, 199 };

    char expected[ARRAY_SIZE][54] = {
        { 0x07, 0x0D, 0x19, 0x11, 0x00, 0x1A, 0x0A, 0x1F, 0x0D, 0x0E, 0x0A, 0x08, 0x14, 0x12, 0x02, 0x05, 0x08, 0x14, 0x1A, 0x14, 0x17, 0x1D, 0x0D, 0x00, 0x09, 0x13, 0x1E, 0x16, 0x17, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0B, 0x00, 0x00, 0x04, 0x1D, 0x13, 0x02, 0x03, 0x1A, 0x10, 0x14, 0x0F, 0x0A, 0x0C, 0x08, 0x13, 0x04, 0x00 },
        { 0x15, 0x0F, 0x1D, 0x03, 0x04, 0x0C, 0x12, 0x0E, 0x19, 0x12, 0x05, 0x14, 0x0C, 0x06, 0x02, 0x0A, 0x12, 0x14, 0x1A, 0x14, 0x1A, 0x11, 0x0D, 0x14, 0x0B, 0x1A, 0x0A, 0x14, 0x12, 0x19, 0x0E, 0x05, 0x0B, 0x19, 0x00, 0x10, 0x13, 0x06, 0x00, 0x12, 0x19, 0x15, 0x02, 0x18, 0x19, 0x08, 0x06, 0x17, 0x0A, 0x00, 0x07, 0x13, 0x1F, 0x00 },
        { 0x16, 0x09, 0x01, 0x04, 0x09, 0x10, 0x18, 0x07, 0x11, 0x1E, 0x04, 0x1B, 0x00, 0x0E, 0x04, 0x15, 0x11, 0x1A, 0x06, 0x14, 0x10, 0x0D, 0x0C, 0x14, 0x0B, 0x1D, 0x06, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0C, 0x00, 0x12, 0x02, 0x14, 0x0D, 0x0C, 0x07, 0x1B, 0x09, 0x10, 0x16, 0x11, 0x1D, 0x0C, 0x17, 0x04, 0x00 },
        { 0x16, 0x0E, 0x09, 0x13, 0x19, 0x16, 0x05, 0x05, 0x11, 0x08, 0x17, 0x01, 0x02, 0x04, 0x00, 0x18, 0x18, 0x19, 0x0E, 0x14, 0x17, 0x11, 0x0D, 0x04, 0x0B, 0x1D, 0x06, 0x16, 0x15, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x0B, 0x0C, 0x0F, 0x14, 0x17, 0x13, 0x09, 0x17, 0x1C, 0x11, 0x1E, 0x0E, 0x06, 0x1D, 0x12, 0x1F, 0x00 },
        { 0x0A, 0x0F, 0x0D, 0x01, 0x02, 0x0A, 0x19, 0x1D, 0x0C, 0x0E, 0x1C, 0x04, 0x1E, 0x04, 0x00, 0x11, 0x1C, 0x1B, 0x02, 0x15, 0x1A, 0x05, 0x0D, 0x0C, 0x0B, 0x18, 0x0C, 0x17, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0A, 0x1C, 0x18, 0x0C, 0x1B, 0x13, 0x1D, 0x15, 0x11, 0x10, 0x0D, 0x0F, 0x16, 0x17, 0x06, 0x12, 0x04, 0x00 }
    };

    int i, j;
    for (i = 0; i < ARRAY_SIZE; ++i) {
        convertAOkToThankYouMail(input1[i], input2[i]);
        for (j = 0; j < 54; ++j) {
            CuAssertIntEquals(tc, expected[i][j], input1[i][j]);
        }
    }
#undef ARRAY_SIZE
}