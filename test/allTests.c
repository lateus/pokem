#include "CuTest.h"

#include <stdio.h>

extern CuSuite* UtilCoreGetTestSuite(void);
extern CuSuite* UtilDecodeGetTestSuite(void);
extern CuSuite* UtilEncodeGetTestSuite(void);

void RunAllTests(void);

int main(void)
{
    RunAllTests();
}

void RunAllTests()
{
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

    CuSuiteAddSuite(suite, UtilCoreGetTestSuite());
    CuSuiteAddSuite(suite, UtilDecodeGetTestSuite());
    CuSuiteAddSuite(suite, UtilEncodeGetTestSuite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}
