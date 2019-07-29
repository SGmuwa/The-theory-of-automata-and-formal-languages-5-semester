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
#include "..\Dynamic_Generic_ArrayList_C\arrayList.h"

/*
Пытается найти конец подстроки, символизирующую число. Сначала берёт один символ, затем два
символа, затем три... И пока не дойдёт до ошибки.
string_t input - строка, в которой надо найти число.
Возвращает: найденную подстроку в входной строке, символизирующую число.
			Обратите внимание на то, что ведётся поиск только по началу строки.
*/
string_t lab2_search10Number(string_t input)
{
	long double buffer;
	// Указывает на позицию, где последний раз была ошибка.
	size_t errPos = SIZE_MAX;
	enum lab1_errorCodes errN = LAB1_ERRORCODES_OK;
	enum lab1_errorCodes errorNumberBuffer; // Записывается результат lab1 для передачи в errN.
	size_t i;
	for (i = 1; i < input.length; i++)
		switch (errorNumberBuffer = lab1(&buffer, (string_t) { input.first, i }))
		{
		case LAB1_ERRORCODES_NOT_SUPPORT_CHARACTER:
			return string_trim((string_t) { input.first, errPos == SIZE_MAX ? i - 1 : errPos });
		case LAB1_ERRORCODES_OK:
			errPos = SIZE_MAX;
			errN = LAB1_ERRORCODES_OK;
			break;
		default:
			if (errPos != SIZE_MAX)
				// Две подрят ошибки допускать нельзя.
				return string_trim((string_t) { input.first, errPos });
			errPos = i;
			errN = errorNumberBuffer;
		}
	return string_trim((string_t) { input.first, errPos == SIZE_MAX ? i - 1 : errPos });
}

// Определяет, принадлежит ли входной символ множеству десятичных цифр.
inline byte_t lab2_is10Number(char in) {
	return '0' <= in && in <= '9';
}

inline byte_t lab2_isLetter(char in) {
	return ('a' <= in && in <= 'z')
		|| ('A' <= in && in <= 'Z');
}

string_t lab2_searchOperand(string_t input)
{
	if (input.first == NULL)
		return (string_t) { NULL, 0u };
	char * ch = input.first;
	while (*ch < string_getEnd(input))
	{
		if (!lab2_is10Number(*ch)
			&& !lab2_isLetter(*ch)
			&& *ch != '_')
			return (string_t) {input.first, ch - input.first};
	}
	return input;
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

// Пропускает все символы пробела.
// Возвращает: на следующий символ не-пробел.
//				В случае, если пробелы до конца - то указатель на недоступный символ (следующий за доступным).
string_t lab2_skipSpace(string_t str) {
	if (str.first == NULL) return (string_t) {NULL, 0u};
	char * i;
	while (*str.first == ' ' && str.length > 0)
	{
		str.first++;
		str.length--;
	}
	return str;
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

// Определяет, содержится ли в входной строке префиксная функция.
// string_t input - Строка поиска.
// Возвращает: 0 - если не содержится префиксная функция. Иначе - количество занимаемых символов функцией.
size_t lab2_isFunction(string_t input)
{
	char * i = input.first;
	if (lab2_is10Number(*i) || lab2_isParenthes(*i))
		return 0; // it's number or Parentheses!
	for (; i < string_getEnd(input); i++)
	{
		if (lab2_isSeparator(*i)) {
			i++;
			return 0;
		}
		if (*i == ' ' || *i == '\0')
			break; // Вообще-то, очень бы не рекомендовалось, чтобы всё-таки дело доходило до встречи пробелов.
		if (lab2_isParenthesOpen(*i)) {
			return (i - 1) - input.first;
		}
		if (lab2_is10Number(*i) || ('a' <= *i && *i <= 'z') || ('A' <= *i && *i <= 'Z'))
			continue;
		else
			break;
	}
	return 0;
}

/*
Вставляет из from в to последовательность строк начиная с указателя to.first.
string_t to - куда идёт копирование.
string_t from - откуда идёт копирование.
Возвращает: Оставшаяся часть string_t to.
*/
string_t lab2_putInString(string_t to, string_t from)
{
	if (to.first == NULL || from.first == NULL || to.length < from.length)
		return (string_t) { NULL, 0u };
#ifdef _MSC_VER
	if (memcpy_s(to.first, to.length, from.first, from.length))
		return (string_t) { NULL, 0u };
#else
	memcpy(to.first, from.first, from.length);
#endif // _MSC_VER
	return (string_t) { to.first + from.length, to.length - from.length };
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
//				5 - Нехватка памяти.
int lab2(string_t output, string_t input)
{
	if (output.first == NULL || output.length == 0 || input.first == NULL || input.length == 0)
		return 4;
	const char * oldOut = output.first;
	struct StackMemory stk = Stack_malloc(output.length, sizeof(string_t));
	if (stk.bottom == NULL)
		return 5;
	input = string_removeAllMalloc(input, STRING_STATIC(" "));
	const char * oldIn = input.first;
	if (input.first == NULL)
	{
		Stack_free(stk);
		return 5;
	}
	ArrayList outList = ArrayList_malloc(sizeof(string_t));
	if (outList == NULL)
	{
		Stack_free(stk);
		free(oldIn);
	}
	while (input.length > 0)
	{ // Пока мы ещё имеем входную строку
		string_t operand = lab2_searchOperand(input);
		if (operand.length > 0)
		{ // Это оказалось десятичное число
			ArrayList_addLast(outList, &operand);
			continue;
		}
		size_t countOfFun = lab2_isFunction(input);
		if (countOfFun)
		{ // Найдена функция
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
					free(oldIn);
					ArrayList_free(outList);
					return 1;
				}
				if (lab2_isParenthesOpen(*stk_elm.first))
				{ // find end.
					input.first++;
					input.length--;
					break;
				}
				if (ArrayList_addLast(outList, &stk_elm))
				{
					Stack_free(stk);
					free(oldIn);
					ArrayList_free(outList);
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
			free(oldIn);
			ArrayList_free(outList);
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
	free(oldIn);
	ArrayList_free(outList);
	return 0;
}