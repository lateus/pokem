#include "CuTest.h"

#include <stdio.h>
#include <string.h>

extern CuSuite* UtilCoreGetTestSuite(void);
extern CuSuite* UtilDecodeGetTestSuite(void);
extern CuSuite* UtilEncodeGetTestSuite(void);
extern CuSuite* DecodeWonderMailGetTestSuite(void);

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

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    return strstr(output->buffer, "!!!FAILURES!!!") ? 1 : 0;
}
