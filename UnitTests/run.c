#include "..\minctest\minctest.h"
#include "..\lab2\lab2_test.h"

#define lreset() ltests = 0; lfails = 0

void main()
{
	lreset();
	lrun("lab2 --- ", lab2_runTests);
	lresults();
	printf_s("end.\n");
}