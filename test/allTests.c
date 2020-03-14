#include "CuTest.h"

#include <stdio.h>
#include <string.h>

extern CuSuite* UtilCoreGetTestSuite(void);
extern CuSuite* UtilDecodeGetTestSuite(void);
extern CuSuite* UtilEncodeGetTestSuite(void);
extern CuSuite* DecodeWonderMailGetTestSuite(void);
extern CuSuite* DecodeSosMailGetTestSuite(void);
extern CuSuite* EncodeWonderMailGetTestSuite(void);
extern CuSuite* EncodeSosMailGetTestSuite(void);
extern CuSuite* ConvertGetTestSuite(void);

int RunAllTests(void);

int main(void)
{
    return RunAllTests();
}

int RunAllTests()
{
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

    int failedTests = CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    return failedTests ? 1 : 0;
}
