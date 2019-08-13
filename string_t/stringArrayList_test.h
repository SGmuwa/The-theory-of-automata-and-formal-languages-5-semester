#pragma once
#include "stringArrayList.h"
#include "..\minctest\minctest.h"

// Создаёт функцию тестирования для функции string_splitMalloc.
#define STRINGARRAYLIST_TEST_MAKE_splitMalloc(NUMBER, EXPECT, INPUT) void stringArrayList_test ## NUMBER (void)\
{\
	ArrayList test = string_splitMalloc(STRING_STATIC(INPUT), STRING_STATIC((char[1]) { ' ' })); \
	minctest_ok(test != NULL); \
	if (test == NULL) return; \
	minctest_equal(EXPECT, test->length); \
	ArrayList_free(test); \
}

// Получает имя функции по номеру
#define STRINGARRAYLIST_TEST_GETNAME(NUMBER) stringArrayList_test ## NUMBER

STRINGARRAYLIST_TEST_MAKE_splitMalloc(0, 1, "0");
STRINGARRAYLIST_TEST_MAKE_splitMalloc(1, 3, "2 2 *");
STRINGARRAYLIST_TEST_MAKE_splitMalloc(2, 3, " 2 2 *");
STRINGARRAYLIST_TEST_MAKE_splitMalloc(3, 3, "  2 2 *");
STRINGARRAYLIST_TEST_MAKE_splitMalloc(4, 3, "    2     2      *     ");
STRINGARRAYLIST_TEST_MAKE_splitMalloc(5, 2, "1 2");
STRINGARRAYLIST_TEST_MAKE_splitMalloc(6, 2, "1  2");


#define STRINGARRAYLIST_TEST_COUNT 6 + 1


// Тестирование задания lab3.
void stringArrayList_runTests(void)
{
	void(*tests[STRINGARRAYLIST_TEST_COUNT])(void) = {
		STRINGARRAYLIST_TEST_GETNAME(0),
		STRINGARRAYLIST_TEST_GETNAME(1),
		STRINGARRAYLIST_TEST_GETNAME(2),
		STRINGARRAYLIST_TEST_GETNAME(3),
		STRINGARRAYLIST_TEST_GETNAME(4),
		STRINGARRAYLIST_TEST_GETNAME(5),
		STRINGARRAYLIST_TEST_GETNAME(6)
	};

	char prototypeName[] = "stringArrayList_test ";
	// Нужно выделить так, чтобы любую цифру можно было записать в диапазоне size_t. Это не более 20 символов.
	string_t testName = string_malloc(sizeof(prototypeName) + 20u);
	for (size_t i = 0; i < STRINGARRAYLIST_TEST_COUNT; i++)
	{
		sprintf_s(testName.first, testName.length, "%s%zu", prototypeName, i);
		minctest_run(testName.first, tests[i]);
	}
	string_free(testName);
}