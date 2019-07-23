#pragma once
#include <stddef.h> // #define NULL

/*
* Десятичное число, представленное списком десятичных цифр, представить
* десятичным числом.
* double * output - указатель, куда надо поместить результат
* char * input - входная строка, откуда идёт чтение.
* size_t length - длинна входной строки.
* Возвращает: код ошибки.
*				0 - нет ошибок.
*				1 - на входе пустая строка.
*				2 - В строке встретилась не цифра.
*				3 - В строке две точки или запятых.
*				4 - Точка или запятая не может быть в начале или в конце строки.
*				5 - Входные указатели аргумента указывают на NULL.
*				6 - Число не может быть без целой части.
*/
int lab1(double * output, const char * input, size_t length)
{
	input++;
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
