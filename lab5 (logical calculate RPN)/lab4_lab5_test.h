#pragma once
#include "..\lab4 (logical expression to RPN)\lab4.h"
#include "lab5.h"
#include "..\minctest\minctest.h"
#include "..\string_t\string_t_forTest.h"

// Создаёт функцию тестирования для функции lab5_runFloat.
#define LAB4LAB5_TEST_MAKE_lab5_runFloat(NUMBER, EXPECT, INPUT, ERROR) void lab4lab5_test ## NUMBER (void)\
{\
	string_t out = string_malloc(10240); \
	int err = lab4(&out, STRING_STATIC(INPUT));\
	minctest_ok(!err);\
	if(err) return;\
	printf("lab4: %s\n", out.first);\
	long double outFloat;\
	minctest_equal(ERROR, lab5_runFloat(&outFloat, out, (string_t){" ", 1}));\
	if(ERROR == 0) minctest_fequal(EXPECT, outFloat, 0.00001);\
	string_free(out);\
}

// Получает имя функции по номеру
#define LAB4LAB5_TEST_GETNAME(NUMBER) lab4lab5_test ## NUMBER

LAB4LAB5_TEST_MAKE_lab5_runFloat(0, 0.0, "0", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(1, 4, "2 * 2", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(2, 6, "3 * 2", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(3, 7, "1 + 3 * 2", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(4, 7, "1+3*2", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(5, 16, "2^2^2", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(6, 2417851639229258349412352.0, "2^3^4", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(7, 4096, "(2^3)^4", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(8, 8, "(1+3)*2", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(9, 8, "2^3", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(10, 5.12215909091, "10 + 2 - 3 * 2 - 3 / 3.3 + (2 / 4) / 2 ^ 3 / 2", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(11, 17.1221590909, "10 + 2 - -3 * 2 - 3 / 3.3 + (2 / 4) / 2 ^ 3 / 2", LAB5_ERR_OK);


// Тестирование задания lab5.
void lab4lab5_runTests(void)
{
	void(*tests[])(void) = {
		LAB4LAB5_TEST_GETNAME(0),
		LAB4LAB5_TEST_GETNAME(1),
		LAB4LAB5_TEST_GETNAME(2),
		LAB4LAB5_TEST_GETNAME(3),
		LAB4LAB5_TEST_GETNAME(4),
		LAB4LAB5_TEST_GETNAME(5),
		LAB4LAB5_TEST_GETNAME(6),
		LAB4LAB5_TEST_GETNAME(7),
		LAB4LAB5_TEST_GETNAME(8),
		LAB4LAB5_TEST_GETNAME(9),
		LAB4LAB5_TEST_GETNAME(10),
		LAB4LAB5_TEST_GETNAME(11)
	};

	char prototypeName[] = "lab4lab5_test ";
	// Нужно выделить так, чтобы любую цифру можно было записать в диапазоне size_t. Это не более 20 символов.
	string_t testName = string_malloc(sizeof(prototypeName) + 20u);
	for (size_t i = 0; i < sizeof(tests) / sizeof(void*); i++)
	{
		sprintf_s(testName.first, testName.length, "%s%zu", prototypeName, i);
		minctest_run(testName.first, tests[i]);
	}
}