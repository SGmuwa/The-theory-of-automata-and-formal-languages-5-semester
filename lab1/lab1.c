#include "..\UserInterface-CLanguage\UserInterface.h"
#include <stdlib.h>
#include <string.h>
#include "..\stack_t\stack_t.h"
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


// Десятичное число, представленное списком десятичных цифр, представить десятичным числом.
// double * output - указатель, куда надо поместить результат
// char * input - входная строка, откуда идёт чтение.
// size_t length - длинна входной строки.
// Возвращает: код ошибки.
// 0 - нет ошибок.
// 1 - на входе пустая строка.
// 2 - В строке встретилась не цифра.
// 3 - В строке две точки или запятых.
// 4 - Точка или запятая не может быть в начале или в конце строки.
// 5 - Входные указатели аргумента указывают на NULL.
// 6 - Число не может быть без целой части.
int lab1(double * output, const char * input, size_t length)
{
	if (output == NULL || input == NULL)
		return 5;
	double out = 0;
	double outF = 0; // Хранит в себе часть после запятой. Создано для оптимизации.
	size_t numbersLeft = 0; // Количество цифр слева точки.
	size_t numberRight = 0; // Количество цифр справа точки.
	if (length < 1) return 1;
	size_t i = 0;
	if (input[0] == '-')
	{
		i = 1; // Первый символ обработан. 
		if (length < 2) return 1;
	}
	size_t isFloat = false; // true, если точка или запятая встречались.
	//if (input[i] == '.' || input[i] == ',' || input[length - 1] == '.' || input[length - 1] == ',')
	//	return 4;
	for (; i < length && i != ~(size_t)0; i += isFloat ? -1 : +1)
	{
		if (input[i] == '\0') continue;
		if (input[i] == '.' || input[i] == ',') // Если встретилась точка или запятая
		{
			if (isFloat != i && isFloat != false)
				if (numbersLeft == 0)
					return 4;
				else
					return 3;
			else
			{
				if (isFloat == i)
					if (numberRight == 0)
						return 4;
					else
						break;
				isFloat = i;
				i = length - 1 + 1; // Индексация на последний символ + 1 для цикла for.
				continue;
			}
		}
		else if (input[i] < '0' || input[i] > '9') return 2;
		if (isFloat)
		{
			outF = outF / 10 + input[i] - '0';
			numberRight++;
		}
		else
		{
			out = out * 10 + input[i] - '0';
			numbersLeft++;
		}
	}
	out += outF / 10;
	if (input[0] == '-')
	{
		out *= -1;
	}
	*output = out;
	if (numberRight == 0 && numbersLeft == 0)
		return 1;
	else if (numbersLeft == 0)
		return 6;
	else 
		return 0;
}
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

#if _DEBUG == 1
void lab1_test(void)
{
	printf("lab1:\tTest start.\n");
	double output = 0;
	double * o = &output;
	int err = 0;
	if((err = lab1(o, "0", sizeof("0"))) != 0 || output != 0) printf("lab1:\tError[%d]: 0 but %lf\n", err, output);
	if ((err = lab1(o, "1", sizeof("1"))) != 0 || output != 1) printf("lab1:\tError[%d]: 1 but %lf\n", err, output);
	if ((err = lab1(o, "123", sizeof("123"))) != 0 || output != 123) printf("lab1:\tError[%d]: 123 but %lf\n", err, output);
	if ((err = lab1(o, "123.123", sizeof("123.123"))) != 0 || output != 123.123) printf("lab1:\tError[%d]: 123 but %lf\n", err, output);
	if ((err = lab1(o, "", sizeof(""))) != 1) printf("lab1:\tError[%d] but need err 1. res? %lf\n", err, output);
	if ((err = lab1(o, "123.1a23", sizeof("123.1a23"))) != 2) printf("lab1:\tError[%d] but need err 2. res? %lf\n", err, output);
	if ((err = lab1(o, "123..123", sizeof("123..123"))) != 3) printf("lab1:\tError[%d] but need err 3. res? %lf\n", err, output);
	if ((err = lab1(o, ".123", sizeof(".123"))) != 4) printf("lab1:\tError[%d] but need err 4. res? %lf\n", err, output);
	if ((err = lab1(NULL, "123", sizeof("123"))) != 5) printf("lab1:\tError[%d] but need err 5. res? %lf\n", err, output);
	if ((err = lab1(o, NULL, 12)) != 5) printf("lab1:\tError[%d] but need err 5. res? %lf\n", err, output);
	if ((err = lab1(o, "0123456789.0123456789", sizeof("0123456789.0123456789"))) != 0 || output != 0123456789.0123456789) printf("lab1:\tError[%d]: 0123456789.0123456789 but %lf\n", err, output);
	if ((err = lab1(o, "-0123456789.0123456789", sizeof("-0123456789.0123456789"))) != 0 || output != -0123456789.0123456789) printf("lab1:\tError[%d]: -0123456789.0123456789 but %lf\n", err, output);
	if ((err = lab1(o, "-123456789.0123456789", sizeof("-123456789.0123456789"))) != 0 || output != -123456789.0123456789) printf("lab1:\tError[%d]: -123456789.0123456789 but %lf\n", err, output);
	if ((err = lab1(o, "-", sizeof("-"))) != 1) printf("lab1:\tError[%d] but need 1. res? %lf\n", err, output);
	if ((err = lab1(o, "-.1", sizeof("-.1"))) != 6) printf("lab1:\tError[%d] but need 6. res? %lf\n", err, output);
	printf("lab1:\tTest end.\n");
}
#endif

// Вычислить значение арифметической формулы, используя обратную польскую запись.
void lab3(void){}

// Преобразовать трёхмерный массив в одномерный. Реализовать обращение к нему как трёхмерному, используя обратную польскую запись.
void lab8(void)
{
	
}

void main(void)
{
	//lab1_interface();
	//lab2_interface();
	UserInterface_Pause("Press any key...");
}