#include "lab3.h"
#include "..\UserInterface-CLanguage\UserInterface.h"
#include "..\string_t\string_t.h"
#include "..\lab2\lab2.h"

int lab3_userInterface(int argc, char * argv[])
{
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
	int error = 0;
	switch (UserInterface_GetUnsignedIntLimit("1 - enter arithmetic notation\n2 - enter reverse polish notation\n", 1, 2))
	{
	case 1:
		str.length = UserInterface_GetStr("Input arithmetic notation: ", str.first, str.length - 1);
		error = lab2(memory, str);
		if (error != 0)
		{
			printf("Error in arithmetic -> RPN: %d", error);
			string_free(memory);
			return 2;
		}
		str.length = strnlen(memory.first, memory.length);
	case 2:
		if (str.length == memory.length)
			str.length = UserInterface_GetStr("Input reverse polish notation: ", str.first, str.length - 1);
		lab3_struct constructor = lab3_malloc();
		if (constructor == NULL)
		{
			string_free(memory);
			return 3;
		}
		lab3_addMath(constructor);
		string_t output = memory;
		error = lab3_run(constructor, &output, str);
		if (error != 0)
		{
			string_free(memory);
			return 4;
		}
		printf("result:\n%s\n", output);
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