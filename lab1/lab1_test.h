#pragma once
#include "lab1.h"
#include "..\minctest\minctest.h"

#define LAB1_TEST_MAKE(NUMBER, EXPECT, INPUT, ERROR) void lab1_test ## NUMBER (void) \
{ \
	long double output = 0.0; \
	minctest_equal(ERROR, lab1(&output, STRING_STATIC(INPUT))); \
	if(ERROR == 0) minctest_fequal(EXPECT, output, 0); \
}

// Получает имя функции по номеру
#define LAB1_TEST_GETNAME(NUMBER) lab1_test ## NUMBER

LAB1_TEST_MAKE(0, 0, "0", 0);
LAB1_TEST_MAKE(1, 1, "1", 0);
LAB1_TEST_MAKE(2, 123, "123", 0);
LAB1_TEST_MAKE(3, 123.123, "123.123", 0);
LAB1_TEST_MAKE(4, 0.0, "", 1);
LAB1_TEST_MAKE(5, 0.0, "123.1a23", 2);
LAB1_TEST_MAKE(6, 0.0, "123..123", 3);
LAB1_TEST_MAKE(7, 0.0, ".123", 4);
void lab1_test8(void) { minctest_equal(5, lab1(NULL, STRING_STATIC("123"))); };
void lab1_test9(void) { long double a; minctest_equal(5, lab1(&a, STRING_STATIC(NULL))); };
LAB1_TEST_MAKE(10, 0123456789.0123456789, "0123456789.0123456789", 0);
LAB1_TEST_MAKE(11, -0123456789.0123456789, "-0123456789.0123456789", 0);
LAB1_TEST_MAKE(12, -123456789.0123456789, "-123456789.0123456789", 0);
LAB1_TEST_MAKE(13, 0.0, "-", 1);
LAB1_TEST_MAKE(14, 0.0, "-.1", 6);

#define LAB1_TEST_COUNT 14 + 1

void lab1_test(void)
{
	void(*tests[LAB1_TEST_COUNT])(void) = {
		LAB1_TEST_GETNAME(0),
		LAB1_TEST_GETNAME(1),
		LAB1_TEST_GETNAME(2),
		LAB1_TEST_GETNAME(3),
		LAB1_TEST_GETNAME(4),
		LAB1_TEST_GETNAME(5),
		LAB1_TEST_GETNAME(6),
		LAB1_TEST_GETNAME(7),
		LAB1_TEST_GETNAME(8),
		LAB1_TEST_GETNAME(9),
		LAB1_TEST_GETNAME(10),
		LAB1_TEST_GETNAME(11),
		LAB1_TEST_GETNAME(12),
		LAB1_TEST_GETNAME(13),
		LAB1_TEST_GETNAME(14)
	};

	char prototypeName[] = "lab1_test ";
	// Нужно выделить так, чтобы любую цифру можно было записать в диапазоне size_t. Это не более 20 символов.
	string_t testName = string_malloc(sizeof(prototypeName) + 20u);
	for (size_t i = 0; i < LAB1_TEST_COUNT; i++)
	{
		sprintf_s(testName.first, testName.length, "%s%zu", prototypeName, i);
		minctest_run(testName.first, tests[i]);
	}
}
