#pragma once
#include "lab3.h"
#include "..\minctest\minctest.h"
#include "..\string_t\string_t_forTest.h"

// Создаёт функцию тестирования для функции lab3_runFloat.
#define LAB3_TEST_MAKE_lab3_runFloat(NUMBER, EXPECT, INPUT, ERROR) void lab3_test ## NUMBER (void)\
{\
	long double out;\
	minctest_equal(ERROR, lab3_runFloat(&out, STRING_STATIC(INPUT), (string_t){" ", 1}));\
	if(ERROR == 0) minctest_fequal(EXPECT, out, 0.001);\
	if(ERROR == 0) \
		printf("%s%lf\n", "table: \"" INPUT "\"\t", (double)EXPECT); \
	else \
		printf("%s%d\n", "table: \"" INPUT "\"\t" "Ошибка ", ERROR); \
}

// Получает имя функции по номеру
#define LAB3_TEST_GETNAME(NUMBER) lab3_test ## NUMBER

LAB3_TEST_MAKE_lab3_runFloat(0, 0.0, "0", LAB3_ERR_OK);
LAB3_TEST_MAKE_lab3_runFloat(1, 4, "2 2 *", LAB3_ERR_OK);
LAB3_TEST_MAKE_lab3_runFloat(2, 6, "3 2 *", LAB3_ERR_OK);


#define LAB3_TEST_COUNT 2 + 1


// Тестирование задания lab3.
void lab3_runTests(void)
{
	void(*tests[LAB3_TEST_COUNT])(void) = {
		LAB3_TEST_GETNAME(0),
		LAB3_TEST_GETNAME(1),
		LAB3_TEST_GETNAME(2)
	};

	char prototypeName[] = "lab3_test ";
	// Нужно выделить так, чтобы любую цифру можно было записать в диапазоне size_t. Это не более 20 символов.
	string_t testName = string_malloc(sizeof(prototypeName) + 20u);
	for (size_t i = 0; i < LAB3_TEST_COUNT; i++)
	{
		sprintf_s(testName.first, testName.length, "%s%zu", prototypeName, i);
		minctest_run(testName.first, tests[i]);
	}
	string_free(testName);
}