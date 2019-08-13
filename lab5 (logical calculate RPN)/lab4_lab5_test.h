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
LAB4LAB5_TEST_MAKE_lab5_runFloat(12, true, "true", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(13, false, "false", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(14, 5.12215909091, "10 + 2 - 3 * 2 - 3 / 3.3 + ((2 + false) / 4) / 2 ^ 3 / (true + true)", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(15, true, "true || false", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(16, true, "true | false", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(17, 0b10, "true << 1", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(18, 0b11, "2 | 1", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(19, true, "true && 10", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(20, false, "true && 0", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(21, 0b1010, "4 ^^ 8 ^^ 4 ^^ 2", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(22, false, "4 & 8 & 4 & 2", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(23, 0b100, "4 & 4", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(24, true, "12487 == 12487", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(25, false, "12412 == -12412", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(26, false, "12487 != 12487", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(27, true, "12412 != -12412", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(28, false, "0 / 0 == 0 / 0", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(29, false, "-1 >= 1", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(30, false, "-1 >= 0", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(31, true, "-1 >= -1", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(32, true, "-1 >= -2", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(33, true, "-1 <= 1", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(34, true, "-1 <= 0", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(35, true, "-1 <= -1", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(36, false, "-1 <= -2", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(37, false, "-1 > 1", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(38, false, "-1 > 0", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(39, false, "-1 > -1", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(40, true, "-1 > -2", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(41, true, "-1 < 1", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(42, true, "-1 < 0", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(43, false, "-1 < -1", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(44, false, "-1 < -2", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(45, -1, "-1 >> 1", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(46, -1, "-2 >> 1", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(47, 0b10, "4 >> 1", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(48, 0, "1 >> 1", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(49, 1, "17 % 4", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(50, -2, "-18 % 4", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(51, 4, "(true + true) ^ (true + true)", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(52, -1, "~false", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(53, -2, "~true", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(54, true, "!false", LAB5_ERR_OK);
LAB4LAB5_TEST_MAKE_lab5_runFloat(55, false, "!true", LAB5_ERR_OK);






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
		LAB4LAB5_TEST_GETNAME(11),
		LAB4LAB5_TEST_GETNAME(12),
		LAB4LAB5_TEST_GETNAME(13),
		LAB4LAB5_TEST_GETNAME(14),
		LAB4LAB5_TEST_GETNAME(15),
		LAB4LAB5_TEST_GETNAME(16),
		LAB4LAB5_TEST_GETNAME(17),
		LAB4LAB5_TEST_GETNAME(18),
		LAB4LAB5_TEST_GETNAME(19),
		LAB4LAB5_TEST_GETNAME(20),
		LAB4LAB5_TEST_GETNAME(21),
		LAB4LAB5_TEST_GETNAME(22),
		LAB4LAB5_TEST_GETNAME(23),
		LAB4LAB5_TEST_GETNAME(24),
		LAB4LAB5_TEST_GETNAME(25),
		LAB4LAB5_TEST_GETNAME(26),
		LAB4LAB5_TEST_GETNAME(27),
		LAB4LAB5_TEST_GETNAME(28),
		LAB4LAB5_TEST_GETNAME(29),
		LAB4LAB5_TEST_GETNAME(30),
		LAB4LAB5_TEST_GETNAME(31),
		LAB4LAB5_TEST_GETNAME(32),
		LAB4LAB5_TEST_GETNAME(33),
		LAB4LAB5_TEST_GETNAME(34),
		LAB4LAB5_TEST_GETNAME(35),
		LAB4LAB5_TEST_GETNAME(36),
		LAB4LAB5_TEST_GETNAME(37),
		LAB4LAB5_TEST_GETNAME(38),
		LAB4LAB5_TEST_GETNAME(39),
		LAB4LAB5_TEST_GETNAME(40),
		LAB4LAB5_TEST_GETNAME(41),
		LAB4LAB5_TEST_GETNAME(42),
		LAB4LAB5_TEST_GETNAME(43),
		LAB4LAB5_TEST_GETNAME(44),
		LAB4LAB5_TEST_GETNAME(45),
		LAB4LAB5_TEST_GETNAME(46),
		LAB4LAB5_TEST_GETNAME(47),
		LAB4LAB5_TEST_GETNAME(48),
		LAB4LAB5_TEST_GETNAME(49),
		LAB4LAB5_TEST_GETNAME(50),
		LAB4LAB5_TEST_GETNAME(51),
		LAB4LAB5_TEST_GETNAME(52),
		LAB4LAB5_TEST_GETNAME(53),
		LAB4LAB5_TEST_GETNAME(54),
		LAB4LAB5_TEST_GETNAME(55)
	};

	char prototypeName[] = "lab4lab5_test ";
	// Нужно выделить так, чтобы любую цифру можно было записать в диапазоне size_t. Это не более 20 символов.
	string_t testName = string_malloc(sizeof(prototypeName) + 20u);
	for (size_t i = 0; i < sizeof(tests) / sizeof(void*); i++)
	{
		sprintf_s(testName.first, testName.length, "%s%zu", prototypeName, i);
		minctest_run(testName.first, tests[i]);
	}
	string_free(testName);
}