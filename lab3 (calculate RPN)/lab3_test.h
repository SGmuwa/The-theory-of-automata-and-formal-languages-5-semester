#pragma once
#include "lab3.h"
#include "..\minctest\minctest.h"
#include "..\string_t\string_t_forTest.h"

// Создаёт функцию тестирования для функции lab3.
#define LAB3_TEST_MAKE_lab3_run(NUMBER, EXPECT, INPUT, ERROR) void lab3_test ## NUMBER (void)\
{\
	string_t out = string_malloc(256);\
	*out.first = 0;\
	lab3_state st = lab3_malloc();\
	minctest_ok(st != NULL);\
	if(st != NULL) \
	{\
		minctest_equal(ERROR, lab3(st, &out, STRING_STATIC(INPUT)));\
		if(ERROR == 0) minctest_sequal(EXPECT, out.first);\
		lab3_free(st);\
	}\
	string_free(out);\
}

// Получает имя функции по номеру
#define LAB3_TEST_GETNAME(NUMBER) lab3_test ## NUMBER

LAB3_TEST_MAKE_lab3_run(0, "0", "0", LAB3_ERR_OK);


#define LAB3_TEST_COUNT 0 + 1


// Тестирование задания lab3.
void lab3_runTests(void)
{
	void(*tests[LAB3_TEST_COUNT])(void) = {
		//LAB3_TEST_GETNAME(0)
	};

	char prototypeName[] = "lab3_test ";
	// Нужно выделить так, чтобы любую цифру можно было записать в диапазоне size_t. Это не более 20 символов.
	string_t testName = string_malloc(sizeof(prototypeName) + 20u);
	for (size_t i = 0; i < LAB2_TEST_COUNT; i++)
	{
		sprintf_s(testName.first, testName.length, "%s%zu", prototypeName, i);
		minctest_run(testName.first, tests[i]);
	}
}