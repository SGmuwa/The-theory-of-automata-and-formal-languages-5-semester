﻿#include "..\minctest\minctest.h"
#include "..\lab1\lab1_test.h"
#include "..\lab2\lab2_test.h"
#include "..\string_t\stringArrayList_test.h"
#include "..\lab3 (calculate RPN)\lab3_test.h"
#include "..\lab3 (calculate RPN)\lab2_lab3_test.h"
#include "..\lab4 (logical expression to RPN)\lab4_test.h"
#include "..\lab5 (logical calculate RPN)\lab5_test.h"
#include "..\lab5 (logical calculate RPN)\lab4_lab5_test.h"
#include "..\lab6 (if to RPN)\lab6_test.h"
#include "..\lab7 (cycle to RPN)\lab7_test.h"

void main()
{
	minctest_reset();
	minctest_run("lab1", lab1_test);
	minctest_run("lab2", lab2_runTests);
	minctest_run("stringArrayList", stringArrayList_runTests);
	minctest_run("lab3", lab3_runTests);
	minctest_run("lab2 and lab3", lab2lab3_runTests);
	minctest_run("lab4", lab4_runTests);
	minctest_run("lab5", lab5_runTests);
	minctest_run("lab4 and lab5", lab4lab5_runTests);
	minctest_run("lab6", lab6_runTests);
	minctest_run("lab7", lab7_runTests);
	minctest_results();
	printf_s("end.\n");
}