#pragma once
#include "lab5.h"
#include "..\minctest\minctest.h"
#include "..\string_t\string_t_forTest.h"

// Создаёт функцию тестирования для функции lab5_runFloat.
#define LAB5_TEST_MAKE_lab5_runFloat(NUMBER, EXPECT, INPUT, ERROR) void lab5_test ## NUMBER (void)\
{\
	long double out;\
	minctest_equal(ERROR, lab5_runFloat(&out, STRING_STATIC(INPUT), (string_t){" ", 1}));\
	if(ERROR == 0) minctest_fequal(EXPECT, out, 0.001);\
}

// Получает имя функции по номеру
#define LAB5_TEST_GETNAME(NUMBER) lab5_test ## NUMBER

LAB5_TEST_MAKE_lab5_runFloat(0, 0.0, "0", LAB5_ERR_OK);
LAB5_TEST_MAKE_lab5_runFloat(1, 4, "2 2 *", LAB5_ERR_OK);
LAB5_TEST_MAKE_lab5_runFloat(2, 6, "3 2 *", LAB5_ERR_OK);


#define LAB5_TEST_COUNT 2 + 1


// Тестирование задания lab5.
void lab5_runTests(void)
{
	void(*tests[LAB5_TEST_COUNT])(void) = {
		LAB5_TEST_GETNAME(0),
		LAB5_TEST_GETNAME(1),
		LAB5_TEST_GETNAME(2)
	};

	char prototypeName[] = "lab5_test ";
	// Нужно выделить так, чтобы любую цифру можно было записать в диапазоне size_t. Это не более 20 символов.
	string_t testName = string_malloc(sizeof(prototypeName) + 20u);
	for (size_t i = 0; i < LAB5_TEST_COUNT; i++)
	{
		sprintf_s(testName.first, testName.length, "%s%zu", prototypeName, i);
		minctest_run(testName.first, tests[i]);
	}
	string_free(testName);
}