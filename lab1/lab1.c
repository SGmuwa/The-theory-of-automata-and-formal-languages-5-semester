#include "..\UserInterface-CLanguage\UserInterface.h"
#include <stdlib.h>
#include <string.h>
#include "..\byte_t\byte_t.h"
#include "..\string_t\string_t.h"

// Создать обратную польскую запись для логической формулы.
void lab4(void){}
// Вычислить значение логической формулы, используя обратную польскую запись.
void lab5(void){}
// Создать обратную польскую запись для условного оператора.
void lab6(void){}
// Создать обратную польскую запись для оператора цикла.
void lab7(void){}
// Перечислить пути в ациклическом графе между двумя заданными вершинами.
// Выполнить топографическую сортировать ациклического графа
// *Перечислить пути в неориентированном графе между двумя заданными вершинами. Использовать простые пути.
// Преобразовать недетерминированный автомат в детерминированный.



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

// Вычислить значение арифметической формулы, используя обратную польскую запись.
void lab3(void){}

// Преобразовать трёхмерный массив в одномерный. Реализовать обращение к нему как трёхмерному, используя обратную польскую запись.
void lab8(void)
{
	
}

void main(void)
{
	//lab1_interface();
	UserInterface_Pause("Press any key...");
}