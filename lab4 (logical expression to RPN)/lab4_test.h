#pragma once
#include "lab4.h"
#include "..\minctest\minctest.h"
#include "..\string_t\string_t_forTest.h"

// Создаёт функцию тестирования для функции lab4.
#define LAB4_TEST_MAKE_lab4(NUMBER, EXPECT, INPUT, ERROR) void lab4_test ## NUMBER (void)\
{\
	string_t out = string_malloc(256);\
	*out.first = 0;\
	minctest_equal(ERROR, lab4(&out, STRING_STATIC(INPUT)));\
	if(ERROR == 0) minctest_sequal(EXPECT, out.first);\
	string_free(out);\
}

// Получает имя функции по номеру
#define LAB4_TEST_GETNAME(NUMBER) lab4_test ## NUMBER

LAB4_TEST_MAKE_lab4(0, "5", "5", 0);
LAB4_TEST_MAKE_lab4(1, "5 2 -", "5 - 2", 0);
LAB4_TEST_MAKE_lab4(2, "10 15 - 3 *", "(10 - 15) * 3", 0);
LAB4_TEST_MAKE_lab4(3, "", "", 0);
LAB4_TEST_MAKE_lab4(4, "2 sin", "sin(2)", 0);
LAB4_TEST_MAKE_lab4(5, "1 2 5 3 * + anywhere", "anywhere(1, 2 + 5 * 3)", 0);
LAB4_TEST_MAKE_lab4(6, "1 2 5 3 * + anywhere wejfwioe *", "anywhere(1, 2 + 5 * 3)wejfwioe", 0); // "anywhere(1, 2 + 5 * 3) * wejfwioe"
LAB4_TEST_MAKE_lab4(7, "iju34098gu25gug", "iju34098gu25gug", 0);
LAB4_TEST_MAKE_lab4(8, "0", "0", 0);
LAB4_TEST_MAKE_lab4(9, "-1", "-1", 0);
LAB4_TEST_MAKE_lab4(10, "2 -1 *", "2 * -1", 0);
LAB4_TEST_MAKE_lab4(11, (char*)NULL, "2 * -)1", 2);
LAB4_TEST_MAKE_lab4(12, "2 -1 *", "2 * - 1", 0);
LAB4_TEST_MAKE_lab4(13, "10 15 - 3 *", "(10 - 15) * 3", 0);
LAB4_TEST_MAKE_lab4(14, "2 2 2 ^ ^", "2^2^2", 0);
LAB4_TEST_MAKE_lab4(15, "2 2 2 ^ ^", "2^(2^2)", 0);
LAB4_TEST_MAKE_lab4(16, "2 2 ^ 2 ^", "(2^2)^2", 0);
LAB4_TEST_MAKE_lab4(17, "1 2 3 * +", "1 + 2 * 3", 0);
LAB4_TEST_MAKE_lab4(18, "1 2 *", "(1)2", 0);
LAB4_TEST_MAKE_lab4(19, "1 2 3 4 ^ ^ ^", "1^2^3^4", 0);
LAB4_TEST_MAKE_lab4(20, "x y ^ 5 z * / 10 +", "x ^ y / (5 * z) + 10", 0);
LAB4_TEST_MAKE_lab4(21, "2 3 - 3 2 + + 6 1 - -", "   (  ( (2-3) + (3+2) )  -  (6 - 1)  )   ", 0);
LAB4_TEST_MAKE_lab4(22, "2 3 - 3 2 + + 6 1 - -", "(((2-3)+(3+2))-(6-1))", 0);
LAB4_TEST_MAKE_lab4(23, "3 2 + 6 1 - -", "(((3+2))-(6-1))", 0);
LAB4_TEST_MAKE_lab4(24, "3 2 + 6 1 - -", "(3+2)-(6-1)", 0);
LAB4_TEST_MAKE_lab4(25, "3 6 -", "((3)-(6))", 0);
LAB4_TEST_MAKE_lab4(26, "3 1 6 + -", "((3)-(1+6))", 0);
LAB4_TEST_MAKE_lab4(27, "1 3 + 6 -", "((1+3)-(6))", 0);
LAB4_TEST_MAKE_lab4(28, "1 2 -", "(((1))-(2))", 0);
LAB4_TEST_MAKE_lab4(29, "5 -3 8 + *", "5 * (-3 + 8)", 0);
LAB4_TEST_MAKE_lab4(30, "1 2 5 3 * + 2 2 2 ^ ^ + anywhere", "anywhere(1, 2 + 5 * 3 + 2^2^2)", 0);
LAB4_TEST_MAKE_lab4(31, "1 2 5 3 * + 2 2 2 ^ ^ + anywhere s *", "anywhere(1, 2 + 5 * 3 + 2^2^2)s", 0);
LAB4_TEST_MAKE_lab4(32, "10 2 + 3 2 * - 3 3.3 / - 2 4 / 2 3 ^ / 2 / +", "10 + 2 - 3 * 2 - 3 / 3.3 + (2 / 4) / 2 ^ 3 / 2", 0);
LAB4_TEST_MAKE_lab4(33, "0.0", "0.0", 0);
LAB4_TEST_MAKE_lab4(34, "2.0 2.00 2.000 ^ ^", "2.0^2.00^2.000", 0);
LAB4_TEST_MAKE_lab4(35, "2 2 pow", "pow(2, 2)", 0);
LAB4_TEST_MAKE_lab4(36, "2 sin", "sin(2)", 0);
LAB4_TEST_MAKE_lab4(37, "1.0 2.00 5.1 3.2 * + 2.3 2.4 2.5 ^ ^ + anywhere s.a *", "anywhere(1.0, 2.00 + 5.1 * 3.2 + 2.3^2.4^2.5)s.a", 0);
LAB4_TEST_MAKE_lab4(38, "a !", "!a", 0);

// Тестирование задания lab4.
void lab4_runTests(void)
{
	void(*tests[])(void) = {
		LAB4_TEST_GETNAME(0),
		LAB4_TEST_GETNAME(1),
		LAB4_TEST_GETNAME(2),
		LAB4_TEST_GETNAME(3),
		LAB4_TEST_GETNAME(4),
		LAB4_TEST_GETNAME(5),
		LAB4_TEST_GETNAME(6),
		LAB4_TEST_GETNAME(7),
		LAB4_TEST_GETNAME(8),
		LAB4_TEST_GETNAME(9),
		LAB4_TEST_GETNAME(10),
		LAB4_TEST_GETNAME(11),
		LAB4_TEST_GETNAME(12),
		LAB4_TEST_GETNAME(13),
		LAB4_TEST_GETNAME(14),
		LAB4_TEST_GETNAME(15),
		LAB4_TEST_GETNAME(16),
		LAB4_TEST_GETNAME(17),
		LAB4_TEST_GETNAME(18),
		LAB4_TEST_GETNAME(19),
		LAB4_TEST_GETNAME(20),
		LAB4_TEST_GETNAME(21),
		LAB4_TEST_GETNAME(22),
		LAB4_TEST_GETNAME(23),
		LAB4_TEST_GETNAME(24),
		LAB4_TEST_GETNAME(25),
		LAB4_TEST_GETNAME(26),
		LAB4_TEST_GETNAME(27),
		LAB4_TEST_GETNAME(28),
		LAB4_TEST_GETNAME(29),
		LAB4_TEST_GETNAME(30),
		LAB4_TEST_GETNAME(31),
		LAB4_TEST_GETNAME(32),
		LAB4_TEST_GETNAME(33),
		LAB4_TEST_GETNAME(34),
		LAB4_TEST_GETNAME(35),
		LAB4_TEST_GETNAME(36),
		LAB4_TEST_GETNAME(37),
		LAB4_TEST_GETNAME(38)
	};

	char prototypeName[] = "lab4_test ";
	// Нужно выделить так, чтобы любую цифру можно было записать в диапазоне size_t. Это не более 20 символов.
	string_t testName = string_malloc(sizeof(prototypeName) + 20u);
	for (size_t i = 0; i < sizeof(tests) / sizeof(void*); i++)
	{
		sprintf_s(testName.first, testName.length, "%s%zu", prototypeName, i);
		minctest_run(testName.first, tests[i]);
	}
}