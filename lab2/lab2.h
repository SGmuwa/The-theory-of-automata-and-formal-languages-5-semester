#pragma once

#define _LAB2_HELP_STR	"Постановка задачи:\n" \
						"\"Создать обратную польскую запись\n" \
						"для арифметической формулы.\"\n" \
						"С помощью данной программы возможно преобразовывать\n" \
						"математическую запись в обратную польскую запись.\n" \
						"Поддерживаются операторы: +, -, *, /, (, ), [, ], {,\n" \
						"}, ^. Также поддерживаются вещественные числа.\n" \
						"Функции, а также переменные в данной программе\n" \
						"не поддерживаются."

#include <stdlib.h>
#include "..\stack_t\stack_t.h"
#include "..\string_t\string_t.h"
#include <string.h>
#include "..\byte_t\byte_t.h"
#include "..\lab1\lab1.h"

/*
Пытается найти подстроку, символизирующую число. Если с самого первого
символа строку не удаётся преобразовать в число, то вернётся пустая строка.
string_t input - строка, в которой надо найти число.
Возвращает: найденную подстроку в входной строке, символизирующую число.
*/
string_t lab2_search10Number(string_t input)
{
	long double buffer;
	unsigned char countErrors = 0;
	size_t i;
	for (i = 1; i < input.length && countErrors < 2; i++)
		if (!lab1(&buffer, (string_t) { input.first, i })) // Если ошибка при считывании.
			countErrors++;
	return (string_t) { input.first, i };
}

/*
Функция отвечает на вопрос, явяляется ли символ открытой скобкой.
char in - входной символ.
Возвращает: True, если символ символизирует открытую скобку. Иначе - False.
*/
inline byte_t lab2_isParenthesOpen(char in) {
	return in == '(' || in == '[' || in == '{';
}

/*
Функция отвечает на вопрос, явяляется ли символ закрытой скобкой.
char in - входной символ.
Возвращает: True, если символ символизирует закрыту. скобку. Иначе - False.
*/
inline byte_t lab2_isParenthesClose(char in) {
	return in == ')' || in == ']' || in == '}';
}

// Определяет, является ли входной символ скобкой.
inline byte_t lab2_isParenthes(char in) {
	return lab2_isParenthesOpen(in) || lab2_isParenthesClose(in);
}

// Определяет, является ли входной символ разделителем.
inline byte_t lab2_isSeparator(char in) {
	return in == ',' || in == ';';
}

// Определяет, принадлежит ли входной символ множеству десятичных цифр.
inline byte_t lab2_is10Number(char in) {
	return '0' <= in && in <= '9';
}

// Пропускает все символы пробела.
// Возвращает: на следующий символ не-пробел.
//				В случае, если пробелы до конца - то указатель на недоступный символ (следующий за доступным).
inline char * lab2_skipSpace(string_t str) {
	if (str.first == NULL) return NULL;
	char * i;
	for (i = str.first; i < string_getEnd(str); i++)
		if (*i == ' ')
			continue;
		else return i;
	return i;
}

/*
// Опредеоляет, содержится ли в входной строке до пробела или оператора или скобки постфиксная функция.
// const char * in - указатель на начало поиска.
// size_t inL - количество доступных символов для поиска.
// Возвращает: 0 - если не содержится постфиксная функция. Иначе - количество занимаемых символов функцией.
size_t lab2_isPostfixFunction(const char * in, size_t inL)
{
	if (*in == '!')
		for (const char * i = in + 1; i < in + inL; i++)
			if (*i == ' ') continue;
			else return i - in;
	if(inL )
}*/

// Определяет, содержится ли в входной строке префиксная функция или оператор.
// string_t input - Строка поиска.
// Возвращает: 0 - если не содержится префиксная функция. Иначе - количество занимаемых символов функцией.
size_t lab2_isFunctionOrOperator(string_t input)
{
	char * i = lab2_skipSpace(input);
	if (lab2_is10Number(*i) || lab2_isParenthes(*i))
		return 0; // it's number or Parentheses!
	for (; i < string_getEnd(input); i++)
	{
		if (lab2_isSeparator(*i)) {
			i++;
			break;
		}
		if (lab2_isParenthes(*i) || *i == ' ' || *i == '\0') {
			break;
		}
	}
	return lab2_skipSpace((string_t) { i, input.length }) - input.first;
}

/*
// Опредеоляет, содержится ли в входной строке до пробела или оператора или скобки постфиксная функция.
// const char * in - указатель на начало поиска.
// size_t inL - количество доступных символов для поиска.
// Возвращает: 0 - если не содержится постфиксная функция. Иначе - количество занимаемых символов функцией.
size_t lab2_isPostfixFunction(const char * in, size_t inL)
{
	if (*in == '!')
		for (const char * i = in + 1; i < in + inL; i++)
			if (*i == ' ') continue;
			else return i - in;
	if(inL )
}*/

// Создать обратную польскую запись для арифметической формулы.
// const string_t output - указатель, куда поместить результат.
//							Память должна быть уже выделена и должно
//							быть указано число доступных символов
//							для записи.
// const string_t input - Текстовое представление арифметической записи.
// Возвращает: код ошибки.
//				1 - Не хватило место в выходной строке.
//				2 - Не верный входной формат.
//				3 - Неизвестная ошибка при перемещении из стека в выходную строку.
//				4 - не верные входные данные.
int lab2(string_t output, string_t input)
{
	if (output.first == NULL || output.length == 0 || input.first == NULL || input.length == 0)
		return 4;
	const char * oldOut = output.first;
	struct StackMemory stk = Stack_malloc(output.length, sizeof(string_t));
	while (input.length > 1)
	{ // Пока мы ещё имеем входную строку
		if (output.length < 2)
		{ // В выходной строке кончается место!
			if (output.length > 0)
			{
				*output.first = '\0';
				output.first++; output.length--;
			}
			Stack_free(stk);
			return 1;
		}
		{
			char * NewIn = lab2_skipSpace(input);
			input.length = input.length - (NewIn - input.first);
			input.first = NewIn;
			if (input.length > ~(size_t)0 - 1)
			{
				break;
			}
		}
		if (lab2_is10Number(*input.first) /*|| lab2_isPostfixFunction(in + i, inL - i) нет времени или идей разработки*/)
		{ // Это оказалось десятичное число
			while (lab2_is10Number(*input.first) && input.length > 1 && output.length > 2)
			{
				*output.first = *input.first;
				input.first++; output.first++; output.length--; input.length--;
			}
			if (input.length > 0 && output.length > 2)
			{
				*output.first = ' ';
				input.first++; output.first++; output.length--; input.length--;
			}
		}
		size_t countOfFun = lab2_isFunctionOrOperator(input);
		if (countOfFun)
		{ // Ого! Найдена функция!
			Stack_push(&stk, &((string_t) { input.first, countOfFun }));
			input.first += countOfFun;
			input.length -= countOfFun;
			continue;
		}
		if (lab2_isParenthesOpen(*input.first))
		{ // Найдена открытая скобка. Что делать?
			Stack_push(&stk, &((string_t) { input.first, 1 }));
			input.first += 1;
			input.length -= 1;
			continue;
		}
		if (lab2_isParenthesClose(*input.first))
		{ // Найдена закрытая скобка. Что делать?
			string_t stk_elm;
			while (1)
			{
				if (Stack_pop(&stk, &stk_elm))
				{ // error
					Stack_free(stk);
					return 1;
				}
				if (lab2_isParenthesOpen(*stk_elm.first))
				{ // find end.
					input.first++;
					input.length--;
					break;
				}
				int error;
#ifndef _MSC_VER
				error = memcpy(output.first, stk_elm.first, stk_elm.length) == NULL ? 1 : 0;
#else
				error = memcpy_s(output.first, output.length, stk_elm.first, stk_elm.length);
#endif
				output.first += stk_elm.length;
				output.length -= stk_elm.length;
				if (error)
				{
					Stack_free(stk);
					return 3;
				}

			}
		}
	}

	string_t stk_elm;
	while (!Stack_pop(&stk, &stk_elm))
	{
		if (lab2_isParenthesOpen(*stk_elm.first))
		{ // find end. ????
			input.first++;
			input.length--;
			break;
		}
		int error;
#ifndef _MSC_VER
		error = memcpy(output.first, stk_elm.first, stk_elm.length) == NULL ? 1 : 0;
#else
		error = memcpy_s(output.first, output.length, stk_elm.first, stk_elm.length);
#endif
		output.first += stk_elm.length;
		output.length -= stk_elm.length;
		if (error)
		{
			Stack_free(stk);
			return 3;
		}

	}
	if (output.first > oldOut && *(output.first - 1) == ' ')
	{ // delete end space.
		output.first--;
		output.length++;
	}
	if (output.length > 0) *output.first = '\0';
	output.first++; output.length--;
	Stack_free(stk);
	return 0;
}