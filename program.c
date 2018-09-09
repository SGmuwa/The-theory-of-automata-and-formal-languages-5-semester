#include "UserInterface.h"

#define false 0
#define true !0

// Вычислить значение арифметической формулы, используя обратную польскую запись.
// Создать обратную польскую запись для логической формулы.
// Вычислить значение логической формулы, используя обратную польскую запись.
// Создать обратную польскую запись для условного оператора.
// Создать обратную польскую запись для оператора цикла.
// Преобразовать трёхмерный массив в одномерный. Реализовать обращение к нему как трёхмерному, используя обратную польскую запись.
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
// 2 - В строке встретилось не число.
// 3 - В строке две точки или запятых.
// 4 - Точка или запятая не может быть в начале или в конце строки.
// 5 - Входные указатели аргумента указывают на NULL.
int z1(double * output, const char * input, size_t length)
{
	if (output == NULL || input == NULL)
		return 5;
	double out = 0;
	double outF = 0; // Хранит в себе часть после запятой. Создано для оптимизации.
	if (length < 1) return 1;
	length--; // Не обрабатываем символ \0
	size_t i = 0;
	if (input[0] == '-')
	{
		i = 1; // Первый символ обработан. 
	}
	size_t isFloat = false; // true, если точка или запятая встречались.
	if (input[i] == '.' || input[i] == ',' || input[length] == '.' || input[length] == ',')
		return 4;
	for (; i < length; i += isFloat ? -1 : +1)
	{
		if (input[i] == '.' || input[i] == ',') // Если встретилась точка или запятая
		{
			if (isFloat != i && isFloat != 0)
				return 3;
			else
			{
				isFloat = i;
			}
		}
		else if (input[i] < '0' || input[i] > '9') return 2;
		if (isFloat)
		{
			outF = outF / 10 + input[i] - '0';
		}
		else
			out = out * 10 + input[i] - '0';
	}
	out += outF;
	if (input[0] == '-')
	{
		out *= -1;
	}
	*output = out;
	return 0;
}

void z1_interface(void)
{
	char input[256];
	size_t length = UserInterface_GetStr("Input number in decimal format.", input, sizeof(input) / sizeof(char));
	double output = 0;
	int err;
	switch (err = z1(&output, input, length))
	{
	case 0:
		printf("Number: %lf\n", output);
	default:
		printf("Error %d\n", err);
	}
}

void z1_test(void)
{
	printf("z1:\tTest start.\n");
	double output = 0;
	double * o = &output;
	int err = 0;
	if((err = z1(o, "0", sizeof("0"))) != 0 || output != 0) printf("z1:\tError[%d]: 0 but %lf\n", err, output);
	if ((err = z1(o, "1", sizeof("1"))) != 0 || output != 1) printf("z1:\tError[%d]: 1 but %lf\n", err, output);
	if ((err = z1(o, "123", sizeof("123"))) != 0 || output != 123) printf("z1:\tError[%d]: 123 but %lf\n", err, output);
	if ((err = z1(o, "123.123", sizeof("123.123"))) != 0 || output != 123.123) printf("z1:\tError[%d]: 123 but %lf\n", err, output);
	if ((err = z1(o, "", sizeof(""))) != 1) printf("z1:\tError[%d] but need err 1. res? %lf\n", err, output);
	if ((err = z1(o, "123.1a23", sizeof("123.1a23"))) != 2) printf("z1:\tError[%d] but need err 2. res? %lf\n", err, output);
	if ((err = z1(o, "123..123", sizeof("123..123"))) != 3) printf("z1:\tError[%d] but need err 3. res? %lf\n", err, output);
	if ((err = z1(o, ".123", sizeof(".123"))) != 4) printf("z1:\tError[%d] but need err 4. res? %lf\n", err, output);
	if ((err = z1(NULL, "123", sizeof("123"))) != 5) printf("z1:\tError[%d] but need err 5. res? %lf\n", err, output);
	if ((err = z1(o, NULL, 12)) != 5) printf("z1:\tError[%d] but need err 5. res? %lf\n", err, output);
	if ((err = z1(o, "0123456789.0123456789", sizeof("0123456789.0123456789"))) != 0 || output != 0123456789.0123456789) printf("z1:\tError[%d]: 0123456789.0123456789 but %lf\n", err, output);
	printf("z1:\tTest end.\n");
}

// Создать обратную польскую запись для арифметической формулы.



void main(void)
{
	z1_test();
	z1_interface();
}