#include "..\UserInterface-CLanguage\UserInterface.h"

void lab1_interface(void)
{
	char input[256];
	size_t length = UserInterface_GetStr("Input number in decimal format: ", input, sizeof(input) / sizeof(char));
	double output = 0;
	int err;
	switch (err = lab1(&output, input, length))
	{
	case 0:
		printf("Number: %lf\n", output);
		break;
	default:
		printf("Error %d\n", err);
		break;
	}
}

void main(void)
{
	lab1_interface();
	UserInterface_Pause("Press any key...");
}