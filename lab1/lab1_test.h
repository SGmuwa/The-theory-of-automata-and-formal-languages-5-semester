#include "lab1.h"
#include "..\minctest\minctest.h"

#if _DEBUG == 1
void lab1_test(void)
{
	printf("lab1:\tTest start.\n");
	double output = 0;
	double * o = &output;
	int err = 0;
	if ((err = lab1(o, "0", sizeof("0"))) != 0 || output != 0) printf("lab1:\tError[%d]: 0 but %lf\n", err, output);
	if ((err = lab1(o, "1", sizeof("1"))) != 0 || output != 1) printf("lab1:\tError[%d]: 1 but %lf\n", err, output);
	if ((err = lab1(o, "123", sizeof("123"))) != 0 || output != 123) printf("lab1:\tError[%d]: 123 but %lf\n", err, output);
	if ((err = lab1(o, "123.123", sizeof("123.123"))) != 0 || output != 123.123) printf("lab1:\tError[%d]: 123 but %lf\n", err, output);
	if ((err = lab1(o, "", sizeof(""))) != 1) printf("lab1:\tError[%d] but need err 1. res? %lf\n", err, output);
	if ((err = lab1(o, "123.1a23", sizeof("123.1a23"))) != 2) printf("lab1:\tError[%d] but need err 2. res? %lf\n", err, output);
	if ((err = lab1(o, "123..123", sizeof("123..123"))) != 3) printf("lab1:\tError[%d] but need err 3. res? %lf\n", err, output);
	if ((err = lab1(o, ".123", sizeof(".123"))) != 4) printf("lab1:\tError[%d] but need err 4. res? %lf\n", err, output);
	if ((err = lab1(NULL, "123", sizeof("123"))) != 5) printf("lab1:\tError[%d] but need err 5. res? %lf\n", err, output);
	if ((err = lab1(o, NULL, 12)) != 5) printf("lab1:\tError[%d] but need err 5. res? %lf\n", err, output);
	if ((err = lab1(o, "0123456789.0123456789", sizeof("0123456789.0123456789"))) != 0 || output != 0123456789.0123456789) printf("lab1:\tError[%d]: 0123456789.0123456789 but %lf\n", err, output);
	if ((err = lab1(o, "-0123456789.0123456789", sizeof("-0123456789.0123456789"))) != 0 || output != -0123456789.0123456789) printf("lab1:\tError[%d]: -0123456789.0123456789 but %lf\n", err, output);
	if ((err = lab1(o, "-123456789.0123456789", sizeof("-123456789.0123456789"))) != 0 || output != -123456789.0123456789) printf("lab1:\tError[%d]: -123456789.0123456789 but %lf\n", err, output);
	if ((err = lab1(o, "-", sizeof("-"))) != 1) printf("lab1:\tError[%d] but need 1. res? %lf\n", err, output);
	if ((err = lab1(o, "-.1", sizeof("-.1"))) != 6) printf("lab1:\tError[%d] but need 6. res? %lf\n", err, output);
	printf("lab1:\tTest end.\n");
}
#endif