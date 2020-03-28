#include "CuTest.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern CuSuite* UtilCoreGetTestSuite(void);
extern CuSuite* UtilDecodeGetTestSuite(void);
extern CuSuite* UtilEncodeGetTestSuite(void);
extern CuSuite* DecodeWonderMailGetTestSuite(void);
extern CuSuite* DecodeSosMailGetTestSuite(void);
extern CuSuite* EncodeWonderMailGetTestSuite(void);
extern CuSuite* EncodeSosMailGetTestSuite(void);
extern CuSuite* ConvertGetTestSuite(void);

extern int printMessages;

int RunAllTests(void);

int main(void)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    system("");
#endif
    return RunAllTests();
}

int RunAllTests()
{
    int failedTests = 0;
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

    CuSuiteAddSuite(suite, UtilCoreGetTestSuite());
    CuSuiteAddSuite(suite, UtilDecodeGetTestSuite());
    CuSuiteAddSuite(suite, UtilEncodeGetTestSuite());
    CuSuiteAddSuite(suite, DecodeWonderMailGetTestSuite());
    CuSuiteAddSuite(suite, DecodeSosMailGetTestSuite());
    CuSuiteAddSuite(suite, EncodeWonderMailGetTestSuite());
    CuSuiteAddSuite(suite, EncodeSosMailGetTestSuite());
    CuSuiteAddSuite(suite, ConvertGetTestSuite());

    printMessages = 0;
    failedTests = CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    return failedTests ? 1 : 0;
}
