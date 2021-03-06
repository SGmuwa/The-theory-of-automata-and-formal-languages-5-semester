﻿#include "lab3.h"
#include "..\UserInterface-CLanguage\UserInterface.h"
#include "..\string_t\string_t.h"
#include "..\lab2\lab2.h"
#include <locale.h>

int lab3_userInterface(int argc, char * argv[])
{
	setlocale(LC_ALL, "Russian");
	printf(LAB3_HELP_STR "\n");
	size_t memCount = argc > 1
		? (size_t)UserInterface_GetUnsignedLongLongIntLimit("Memory = ", 0, SIZE_MAX)
		: 8192u;
	string_t memory = string_malloc(memCount);
	if (memory.first == NULL)
	{
		printf("Not enough memory...\n");
		return 1;
	}
	string_t str = memory;
	string_t output = memory;
	int error = 0;
	switch (UserInterface_GetUnsignedIntLimit("1 - enter arithmetic notation\n2 - enter reverse polish notation\n", 1, 2))
	{
	case 1:
		str.length = UserInterface_GetStr("Input arithmetic notation: ", str.first, str.length - 1);
		error = lab2(&output, str);
		if (error != 0)
		{
			printf("Error in arithmetic -> RPN: %d", error);
			string_free(memory);
			return 2;
		}
		str.length = strnlen(output.first, output.length);
	case 2:
		if (str.length == memory.length)
			str.length = UserInterface_GetStr("Input reverse polish notation: ", str.first, str.length - 1);
		output = memory;
		error = lab3_run(&output, str, STRING_STATIC((char[]) {' '}));
		if (error != 0)
		{
			string_free(memory);
			return 4;
		}
		printf("result:\n%s\n", output.first);
		return 0;
	default:
		string_free(memory);
		return 5;
	}
}

int main(int argc, char * argv[])
{
	int ret = lab3_userInterface(argc, argv);
	UserInterface_Pause("The end of program \"lab3 (calculate str)\".");
	return ret;
}