#include "..\minctest\minctest.h"
#include "..\lab1\lab1_test.h"
#include "..\lab2\lab2_test.h"

void main()
{
	minctest_reset();
	minctest_run("lab1", lab1_test);
	minctest_run("lab2", lab2_runTests);
	minctest_results();
	printf_s("end.\n");
}