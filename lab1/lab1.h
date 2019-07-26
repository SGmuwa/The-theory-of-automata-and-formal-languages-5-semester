#pragma once
#include "..\string_t\string_t.h"
#include <stdbool.h>

/*
* Десятичное число, представленное списком десятичных цифр, представить
* десятичным числом.
* long double * output - указатель, куда надо поместить результат
* string_t * input - входная строка, откуда идёт чтение.
* Возвращает: код ошибки.
*				0 - нет ошибок.
*				1 - на входе пустая строка.
*				2 - В строке встретилась не цифра.
*				3 - В строке две точки или запятых.
*				4 - Точка или запятая не может быть в начале или в конце строки.
*				5 - Входные указатели аргумента указывают на NULL.
*				6 - Число не может быть без целой части.
*/
int lab1(long double * output, string_t input)
{
	if (output == NULL || input.first == NULL)
		return 5;
	long double out = 0;
	long double outF = 0; // Хранит в себе часть после запятой. Создано для оптимизации.
	size_t numbersLeft = 0; // Количество цифр слева точки.
	size_t numberRight = 0; // Количество цифр справа точки.
	if (input.length < 1) return 1;
	size_t i = 0;
	if (*input.first == '-')
	{
		i = 1; // Первый символ обработан. 
		if (input.length < 2) return 1;
	}
	size_t floatPos = SIZE_MAX;	// 0...(SIZE_MAX-1), если точка или запятая встречалась.
								// SIZE_MAX, если точка или запятая не встречалась.
	for (; i < input.length && i != ~(size_t)0; i += floatPos == SIZE_MAX ? +1 : -1)
	{
		if (input.first[i] == '\0' || input.first[i] == ' ') continue;
		if (input.first[i] == '.' || input.first[i] == ',') // Если встретилась точка или запятая
		{
			if (floatPos == SIZE_MAX)
			{
				if (numbersLeft == 0)
					return 4;
				floatPos = i;
				i = input.length - 1 + 1; // Индексация на последний символ + 1 для цикла for.
				continue;
			}
			else
			{
				if (numberRight == 0)
					return 4;
				if (floatPos != i)
					return 3;
				break; // Мы нашли точку слева в прошлом, теперь нашли справа.
			}
		}
		else if (input.first[i] < '0' || input.first[i] > '9') return 2;
		if (floatPos != SIZE_MAX)
		{
			outF = outF / 10 + input.first[i] - '0';
			numberRight++;
		}
		else
		{
			out = out * 10 + input.first[i] - '0';
			numbersLeft++;
		}
	}
	out += outF / 10;
	if (*input.first == '-')
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
