#pragma once
#include "..\lab2\lab2.h"
#include "lab3.h"
#include "..\minctest\minctest.h"
#include "..\string_t\string_t_forTest.h"

// Создаёт функцию тестирования для функции lab3_runFloat.
#define LAB2LAB3_TEST_MAKE_lab3_runFloat(NUMBER, EXPECT, INPUT, ERROR) void lab2lab3_test ## NUMBER (void)\
{\
	string_t out = string_malloc(10240); \
	int err = lab2(&out, STRING_STATIC(INPUT));\
	minctest_ok(!err);\
	if(err) return;\
	printf("lab2: %s\n", out.first);\
	long double outFloat;\
	minctest_equal(ERROR, lab3_runFloat(&outFloat, out, (string_t){" ", 1}));\
	if(ERROR == 0) minctest_fequal(EXPECT, outFloat, 0.00001);\
	string_free(out);\
}

// Получает имя функции по номеру
#define LAB2LAB3_TEST_GETNAME(NUMBER) lab2lab3_test ## NUMBER

LAB2LAB3_TEST_MAKE_lab3_runFloat(0, 0.0, "0", LAB3_ERR_OK);
LAB2LAB3_TEST_MAKE_lab3_runFloat(1, 4, "2 * 2", LAB3_ERR_OK);
LAB2LAB3_TEST_MAKE_lab3_runFloat(2, 6, "3 * 2", LAB3_ERR_OK);
LAB2LAB3_TEST_MAKE_lab3_runFloat(3, 7, "1 + 3 * 2", LAB3_ERR_OK);
LAB2LAB3_TEST_MAKE_lab3_runFloat(4, 7, "1+3*2", LAB3_ERR_OK);
LAB2LAB3_TEST_MAKE_lab3_runFloat(5, 16, "2^2^2", LAB3_ERR_OK);
LAB2LAB3_TEST_MAKE_lab3_runFloat(6, 2417851639229258349412352.0, "2^3^4", LAB3_ERR_OK);
LAB2LAB3_TEST_MAKE_lab3_runFloat(7, 4096, "(2^3)^4", LAB3_ERR_OK);
LAB2LAB3_TEST_MAKE_lab3_runFloat(8, 8, "(1+3)*2", LAB3_ERR_OK);
LAB2LAB3_TEST_MAKE_lab3_runFloat(9, 8, "2^3", LAB3_ERR_OK);
LAB2LAB3_TEST_MAKE_lab3_runFloat(10, 5.12215909091, "10 + 2 - 3 * 2 - 3 / 3.3 + (2 / 4) / 2 ^ 3 / 2", LAB3_ERR_OK);
LAB2LAB3_TEST_MAKE_lab3_runFloat(11, 17.1221590909, "10 + 2 - -3 * 2 - 3 / 3.3 + (2 / 4) / 2 ^ 3 / 2", LAB3_ERR_OK);


// Тестирование задания lab3.
void lab2lab3_runTests(void)
{
	void(*tests[])(void) = {
		LAB2LAB3_TEST_GETNAME(0),
		LAB2LAB3_TEST_GETNAME(1),
		LAB2LAB3_TEST_GETNAME(2),
		LAB2LAB3_TEST_GETNAME(3),
		LAB2LAB3_TEST_GETNAME(4),
		LAB2LAB3_TEST_GETNAME(5),
		LAB2LAB3_TEST_GETNAME(6),
		LAB2LAB3_TEST_GETNAME(7),
		LAB2LAB3_TEST_GETNAME(8),
		LAB2LAB3_TEST_GETNAME(9),
		LAB2LAB3_TEST_GETNAME(10),
		LAB2LAB3_TEST_GETNAME(11)
	};

	char prototypeName[] = "lab2lab3_test ";
	// Нужно выделить так, чтобы любую цифру можно было записать в диапазоне size_t. Это не более 20 символов.
	string_t testName = string_malloc(sizeof(prototypeName) + 20u);
	for (size_t i = 0; i < sizeof(tests) / sizeof(void*); i++)
	{
		sprintf_s(testName.first, testName.length, "%s%zu", prototypeName, i);
		minctest_run(testName.first, tests[i]);
	}
	string_free(testName);
}