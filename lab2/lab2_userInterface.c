#include "..\UserInterface-CLanguage\UserInterface.h"
#include "lab2.h"
#include "lab2_test.h"

void lab2_interface(void)
{
	string_t input = { (char*) malloc(sizeof(char) * 1024), 1024 };
	if (input.first == NULL) return;
	input.length = UserInterface_GetStr("Input arithmetic expression:", input.first, 1024);
	string_t output = { (char*) malloc(input.length * sizeof(char) * 2), input.length * sizeof(char) * 2 };
	int err = lab2(output, input);
	if (err != 0) printf("error %d.\n", err);
	printf("%s", output.first);
	free(input.first);
}

void main(void)
{
	lab2_interface();
}