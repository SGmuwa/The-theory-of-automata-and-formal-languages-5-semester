#pragma once
#include <stdio.h>
#include <string.h>
#include "lab2.h"
#include "..\minctest\minctest.h"

// Создаёт функцию тестирования.
#define LAB2_TEST_MAKE(NUMBER, EXPECT, INPUT, ERROR) void lab2_test ## NUMBER (void)\
{\
	string_t out = string_malloc(256);\
	*out.first = 0;\
	lequal(ERROR, lab2(out, STRING_STATIC(INPUT)));\
	if(ERROR == 0) lsequal(EXPECT, out.first);\
	string_free(out);\
}

// Получает имя функции по номеру
#define LAB2_TEST_GETNAME(NUMBER) lab2_test ## NUMBER

LAB2_TEST_MAKE(0, "5", "5", 0);
LAB2_TEST_MAKE(1, "5 2 -", "5 - 2", 0);
LAB2_TEST_MAKE(2, "10 15 - 3 *", "(10 - 15) * 3", 0);
LAB2_TEST_MAKE(3, "", "", 0);
LAB2_TEST_MAKE(4, "2 sin", "sin(2)", 0);
LAB2_TEST_MAKE(5, "1 2 3 5 * + anywhere", "anywhere(1, 2 + 5 * 3)", 0);
LAB2_TEST_MAKE(6, "1 2 3 5 * + anywhere wejfwioe *", "anywhere(1, 2 + 5 * 3)wejfwioe", 0); // "anywhere(1, 2 + 5 * 3) * wejfwioe"
LAB2_TEST_MAKE(7, "iju34098gu25gug", "iju34098gu25gug", 0);
LAB2_TEST_MAKE(8, "0", "0", 0);
LAB2_TEST_MAKE(9, "-1", "-1", 0);
LAB2_TEST_MAKE(10, "2 -1 *", "2 * -1", 0);
LAB2_TEST_MAKE(11, (char*)NULL, "2 * -)1", 2);
LAB2_TEST_MAKE(12, "2 -1 *", "2 * - 1", 0);
LAB2_TEST_MAKE(13, "10 15 - 3 *", "(10 − 15) * 3", 0);
#define LAB2_TEST_COUNT 13 + 1

// Тестирование задания lab2.
void lab2_runTests(void)
{
	void(*lab2_tests[LAB2_TEST_COUNT])(void) = {
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
	LAB2_TEST_GETNAME(13)
	};

	char prototypeName[] = "lab2_test ";
	// Нужно выделить так, чтобы любую цифру можно было записать в диапазоне size_t. Это не более 20 символов.
	string_t testName = string_malloc(sizeof(prototypeName) + 20u);
	for (size_t i = 0; i < LAB2_TEST_COUNT; i++)
	{
		sprintf_s(testName.first, testName.length, "%s%zu", prototypeName, i);
		lrun(testName.first, lab2_tests[i]);
	}
}