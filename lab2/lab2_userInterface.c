#include "..\UserInterface-CLanguage\UserInterface.h"
#include "lab2.h"
#include <locale.h>

void lab2_interface(int argc, char * argv[])
{
	setlocale(LC_ALL, "Russian");
	printf(LAB2_HELP_STR "\n");
	size_t mem = argc > 1
		? (size_t)UserInterface_GetUnsignedLongLongIntLimit("Memory = ", 0, SIZE_MAX)
		: 8192u;
	string_t input = { (char*) malloc(sizeof(char) * mem), mem }; // string.
	string_t output = input;
	if (input.first == NULL)
		return;
	input.length = UserInterface_GetStr("Input arithmetic expression: ", input.first, mem);
	int err = lab2(&output, input); // error.
	if (err != 0)
		printf("error %d.\n", err);
	printf("%s\n", output.first);
	string_free(input);
}

void main(int argc, char * argv[])
{
	lab2_interface(argc, argv);
	UserInterface_Pause("Press any key for exit...\n");
}