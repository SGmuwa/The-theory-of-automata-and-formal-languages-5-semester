#pragma once
#include "string_t.h"
#include "..\minctest\minctest.h"

#define minctest_string_t_equal(EXPECT, ACTUAL) do{\
	char * ex = string_mallocCopyToChar(EXPECT);\
	char * ac = string_mallocCopyToChar(ACTUAL);\
	minctest_sequal(EXPECT.first, ACTUAL.first);\
	free(ex);\
	free(ac);\
} while(0)
