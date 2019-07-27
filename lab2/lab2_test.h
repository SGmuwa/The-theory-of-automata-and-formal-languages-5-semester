#pragma once
#include "lab2.h"
#include "..\minctest\minctest.h"
#include "..\string_t\string_t_forTest.h"

// Создаёт функцию тестирования для функции lab2.
#define LAB2_TEST_MAKE_lab2(NUMBER, EXPECT, INPUT, ERROR) void lab2_test ## NUMBER (void)\
{\
	string_t out = string_malloc(256);\
	*out.first = 0;\
	minctest_equal(ERROR, lab2(out, STRING_STATIC(INPUT)));\
	if(ERROR == 0) minctest_sequal(EXPECT, out.first);\
	string_free(out);\
}


// Создаёт функцию тестирования для функции lab2.
#define LAB2_TEST_MAKE_lab2_search10Number(NUMBER, EXPECT, INPUT) void lab2_test ## NUMBER (void)\
{\
	string_t result = lab2_search10Number(STRING_STATIC(INPUT));\
	minctest_string_t_equal(STRING_STATIC(EXPECT), result);\
}

// Получает имя функции по номеру
#define LAB2_TEST_GETNAME(NUMBER) lab2_test ## NUMBER

LAB2_TEST_MAKE_lab2(0, "5", "5", 0);
LAB2_TEST_MAKE_lab2(1, "5 2 -", "5 - 2", 0);
LAB2_TEST_MAKE_lab2(2, "10 15 - 3 *", "(10 - 15) * 3", 0);
LAB2_TEST_MAKE_lab2(3, "", "", 0);
LAB2_TEST_MAKE_lab2(4, "2 sin", "sin(2)", 0);
LAB2_TEST_MAKE_lab2(5, "1 2 3 5 * + anywhere", "anywhere(1, 2 + 5 * 3)", 0);
LAB2_TEST_MAKE_lab2(6, "1 2 3 5 * + anywhere wejfwioe *", "anywhere(1, 2 + 5 * 3)wejfwioe", 0); // "anywhere(1, 2 + 5 * 3) * wejfwioe"
LAB2_TEST_MAKE_lab2(7, "iju34098gu25gug", "iju34098gu25gug", 0);
LAB2_TEST_MAKE_lab2(8, "0", "0", 0);
LAB2_TEST_MAKE_lab2(9, "-1", "-1", 0);
LAB2_TEST_MAKE_lab2(10, "2 -1 *", "2 * -1", 0);
LAB2_TEST_MAKE_lab2(11, (char*)NULL, "2 * -)1", 2);
LAB2_TEST_MAKE_lab2(12, "2 -1 *", "2 * - 1", 0);
LAB2_TEST_MAKE_lab2(13, "10 15 - 3 *", "(10 - 15) * 3", 0);
LAB2_TEST_MAKE_lab2(14, "2 2 2 ^ ^", "2^2^2", 0);
LAB2_TEST_MAKE_lab2(15, "2 2 2 ^ ^", "2^(2^2)", 0);
LAB2_TEST_MAKE_lab2(16, "2 2 ^ 2 ^", "(2^2)^2", 0);
LAB2_TEST_MAKE_lab2(17, "1 2 3 * +", "1 + 2 * 3", 0);
LAB2_TEST_MAKE_lab2_search10Number(18, "12.0", "12.0");
LAB2_TEST_MAKE_lab2_search10Number(19, "1", "1a");
LAB2_TEST_MAKE_lab2_search10Number(20, "-34.22", "-34.22 eeeee");
#define LAB2_TEST_COUNT 20 + 1

// Тестирование задания lab2.
void lab2_runTests(void)
{
	void(*tests[LAB2_TEST_COUNT])(void) = {
		LAB2_TEST_GETNAME(0),
		LAB2_TEST_GETNAME(1),
		LAB2_TEST_GETNAME(2),
		LAB2_TEST_GETNAME(3),
		LAB2_TEST_GETNAME(4),
		LAB2_TEST_GETNAME(5),
		LAB2_TEST_GETNAME(6),
		LAB2_TEST_GETNAME(7),
		LAB2_TEST_GETNAME(8),
		LAB2_TEST_GETNAME(9),
		LAB2_TEST_GETNAME(10),
		LAB2_TEST_GETNAME(11),
		LAB2_TEST_GETNAME(12),
		LAB2_TEST_GETNAME(13),
		LAB2_TEST_GETNAME(14),
		LAB2_TEST_GETNAME(15),
		LAB2_TEST_GETNAME(16),
		LAB2_TEST_GETNAME(17),
		LAB2_TEST_GETNAME(18),
		LAB2_TEST_GETNAME(19),
		LAB2_TEST_GETNAME(20)
	};

	char prototypeName[] = "lab2_test ";
	// Нужно выделить так, чтобы любую цифру можно было записать в диапазоне size_t. Это не более 20 символов.
	string_t testName = string_malloc(sizeof(prototypeName) + 20u);
	for (size_t i = 0; i < LAB2_TEST_COUNT; i++)
	{
		sprintf_s(testName.first, testName.length, "%s%zu", prototypeName, i);
		minctest_run(testName.first, tests[i]);
	}
}