#pragma once
#include "..\string_t\string_t.h"
#include <stdbool.h>

#define LAB1_HELP_STR \
	"Постановка задачи:\n" \
	"\"Десятичное число, представленное списком десятичных цифр, представить десятичным числом.\"\n" \
	"Эта программа для демонстрации, что можно считывать вещественное число. " \
	"Разделителем целой части и дробной можно по-желанию использовать " \
	"точку, либо запятую."

enum lab1_errorCodes
{
	// Нет ошибок.
	LAB1_ERRORCODES_OK = 0,
	// На входе пустая строка.
	LAB1_ERRORCODES_EMPTY = 1,
	// В строке встретилась не цифра (например, буква).
	LAB1_ERRORCODES_NOT_SUPPORT_CHARACTER = 2,
	// В строке две точки или запятых.
	LAB1_ERRORCODES_TWICE_DOT = 3,
	// Точка или запятая не может быть в начале или в конце строки.
	LAB1_ERRORCODES_DOT_IN_BEGIN_OR_END = 4,
	// Входные указатели аргумента указывают на NULL.
	LAB1_ERRORCODES_DOT_INPUT_NULL = 5,
	// Число не может быть без целой части.
	LAB1_ERRORCODES_WITHOUT_MAIN = 6
};

/*
* Десятичное число, представленное списком десятичных цифр, представить
* десятичным числом.
* long double * output - указатель, куда надо поместить результат
* string_t * input - входная строка, откуда идёт чтение.
* Возвращает: код ошибки.
*/
enum lab1_errorCodes lab1(long double * output, string_t input)
{
	if (output == NULL || input.first == NULL)
		return LAB1_ERRORCODES_DOT_INPUT_NULL;
	long double out = 0;
	long double outF = 0; // Хранит в себе часть после запятой. Создано для оптимизации.
	size_t numbersLeft = 0; // Количество цифр слева точки.
	size_t numberRight = 0; // Количество цифр справа точки.
	if (input.length < 1) return LAB1_ERRORCODES_EMPTY;
	size_t i = 0;
	if (*input.first == '-')
	{
		i = 1; // Первый символ обработан. 
		if (input.length < 2) return LAB1_ERRORCODES_EMPTY;
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
					return LAB1_ERRORCODES_DOT_IN_BEGIN_OR_END;
				floatPos = i;
				i = input.length - 1 + 1; // Индексация на последний символ + 1 для цикла for.
				continue;
			}
			else
			{
				if (numberRight == 0)
					return LAB1_ERRORCODES_DOT_IN_BEGIN_OR_END;
				if (floatPos != i)
					return LAB1_ERRORCODES_TWICE_DOT;
				break; // Мы нашли точку слева в прошлом, теперь нашли справа.
			}
		}
		else if (input.first[i] < '0' || input.first[i] > '9') return LAB1_ERRORCODES_NOT_SUPPORT_CHARACTER;
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
		return LAB1_ERRORCODES_EMPTY;
	else if (numbersLeft == 0)
		return LAB1_ERRORCODES_WITHOUT_MAIN;
	else
		return LAB1_ERRORCODES_OK;
}
