#pragma once
#include "string_t.h"
#include "..\minctest\minctest.h"


void minctest_string_t_equal(string_t expect, string_t actual)
{
	char * ex = string_mallocCopyToChar(expect);
	char * ac = string_mallocCopyToChar(actual);
	minctest_sequal(ex, ac);
	free(ex);
	free(ac);
}
