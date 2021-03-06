﻿#pragma once

#define LAB2_HELP_STR \
	"Постановка задачи:\n" \
	"\"Создать обратную польскую запись " \
	"для арифметической формулы.\"\n" \
	"С помощью данной программы возможно преобразовывать " \
	"математическую запись в обратную польскую запись. " \
	"Поддерживаются операторы и скобки: +, -, *, /, (, ), [, ], {, " \
	"}, ^. Также поддерживаются вещественные числа. " \
	"Функции, а также переменные в данной программе " \
	"поддерживаются."

#include <stdlib.h>
#include "..\stack_t\stack_t.h"
#include "..\string_t\string_t.h"
#include <string.h>
#include "..\byte_t\byte_t.h"
#include "..\lab1\lab1.h"
#include "..\Dynamic_Generic_ArrayList_C\arrayList.h"
#include <limits.h>

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
	for (i = 1; i <= input.length; i++)
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


/*
Функция отвечает на вопрос, явяляется ли символ открытой скобкой.
char in - входной символ.
Возвращает: True, если символ символизирует открытую скобку. Иначе - False.
*/
inline byte_t lab2_isParenthesOpen(char in) {
	return in == '(' || in == '[' || in == '{';
}



/*
Находит начиная с первого символа оператор.
*/
string_t lab2_searchOperator(string_t input)
{
	if (input.first == NULL)
		return (string_t) { NULL, 0 };
	switch (*input.first)
	{
	default:
		return (string_t) { input.first, 0 };
	case '-':
	case '+':
	case '*':
	case '/':
	case '^': // Возведение в степень.
		return (string_t) { input.first, 1 };
	}
}

string_t lab2_searchOperand(string_t input, char previous)
{
	if (input.first == NULL)
		return (string_t) { NULL, 0u };
	char * ch = input.first - 1;
	if (previous == '\0' || lab2_isParenthesOpen(previous) || lab2_searchOperator((string_t) { (char[]) { previous}, 0u }).length > 0)
	{
		if (ch[1] == '-') // Бинарный минус.
			ch++;
	}
	char * first = ch + 1;
	while (++ch < string_getEnd(input))
	{
		if (!lab2_is10Number(*ch)
			&& !lab2_isLetter(*ch)
			&& *ch != '_'
			&& (first == ch || *ch != '.'))
		{
			if (*ch == '.')
				ch--;
			return input.first[0] == '-' && (size_t)ch - (size_t)input.first <= 1
				? (string_t) { input.first, 0 } : (string_t) { input.first, ch - input.first };
		}
	}
	return input;
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
			return i - input.first;
		}
		if (lab2_is10Number(*i) || lab2_isLetter(*i) || *i == '_')
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
Получает приоритет оператора.
*/
unsigned int lab2_getOperatorPreority(string_t input)
{
	if (input.length != 1)
		return UINT_MAX;
	switch (*input.first)
	{
	default:
		return UINT_MAX;
	case '-':
	case '+':
		return 0;
	case '*':
	case '/':
		return 1;
	case '^': // Возведение в степень.
		return 2;
	}
}

/*
Помещает элементы листа типа string_t в итоговую строку toResult.
Возвращает: код ошибки.
*/
int lab2_putListToString(string_t * toResult_, ArrayList from, string_t separator)
{
	string_t toResult = *toResult_;
	if (from == NULL)
		return 1;
	if (toResult.first == NULL && from->length != 0)
		return 2;
	if (separator.first == NULL)
		separator = (string_t) { NULL, 0 };
	string_t str;
	for (size_t i = 0; i < from->length * 2; i++)
	{
		if (i % 2 == 0)
		{
			if (ArrayList_get(from, i / 2, &str)) return 3;
		}
		else if (i + 1 < from->length * 2)
			str = separator;
		else
			str = (string_t) { NULL, 0u };
		if (toResult.length - 1 < str.length) return 4;
#ifdef _MSC_VER
		if (memcpy_s(toResult.first, toResult.length, str.first, str.length))
			return 5;
#else
		memcpy(toResult.first, str.first, str.length);
#endif // _MSC_VER
		toResult.first += str.length;
		toResult.length -= str.length;
	}
	if (toResult.first == NULL)
		return 0;
	if (toResult.length > 0)
		*toResult.first = '\0';
	toResult_->length = (size_t)toResult.first - (size_t)toResult_->first;
	return 0;
}


unsigned char lab2_isLeftFirstPriority(string_t input)
{
	return input.length != 1 || *input.first != '^';
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
int lab2(string_t * output, string_t input)
{
	if (output == NULL || output->first == NULL || output->length == 0 || input.first == NULL || input.length == 0)
		return 4;
	char * oldOut = output->first;
	struct StackMemory stk = Stack_malloc(output->length, sizeof(string_t));
	if (stk.bottom == NULL)
		return 5;
	input = string_removeAllMalloc(input, STRING_STATIC(" "));
	char * oldIn = input.first;
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
		return 5;
	}
	char previous = '\0';
#define LAB2_SAFE(ACT, CODE) if(ACT) { Stack_free(stk); free(oldIn); ArrayList_free(outList); return CODE; }
	while (input.length > 0)
	{ // Пока мы ещё имеем входную строку.
		string_t operand = lab2_searchOperand(input, previous);
		size_t countOfFun = lab2_isFunction(input);
		string_t operator = lab2_searchOperator(input);
		if (lab2_isParenthesClose(previous) && (countOfFun || operand.length) && operator.length == 0) // Поддержка мнимого умножения
		{
			operand = (string_t){ NULL, 0 };
			countOfFun = 0;
			operator = (string_t) { "*", 1 };
			input.first -= 1;
			input.length += 1;
		}
		if (countOfFun)
		{ // Найдена функция
			LAB2_SAFE(Stack_push(&stk, &((string_t) { input.first, countOfFun })), 5);
			input.first += countOfFun;
			input.length -= countOfFun;
		}
		else if (operand.length > 0)
		{ // Это оказалось десятичное число.
			LAB2_SAFE(ArrayList_addLast(outList, &operand), 5);
			input.length -= operand.length;
			input.first += operand.length;
		}
		else if (operator.length > 0)
		{ // Это оператор.
			string_t stk_elm = (string_t) { NULL, 0 };
			if ((Stack_count(stk) == 0) || (Stack_get(stk, &stk_elm) == 0 && lab2_isParenthesOpen(*stk_elm.first) && stk_elm.length == 1)
				|| lab2_getOperatorPreority(operator) > lab2_getOperatorPreority(stk_elm))
			{
				LAB2_SAFE(Stack_push(&stk, &operator), 5);
			}
			else
			{
				while ((lab2_isLeftFirstPriority(operator) ? lab2_getOperatorPreority(operator) : ~lab2_getOperatorPreority(operator)) <= lab2_getOperatorPreority(stk_elm) && !lab2_isParenthesOpen(*stk_elm.first))
				{
					LAB2_SAFE(ArrayList_addLast(outList, &stk_elm) || Stack_pop(&stk, &stk_elm), 5);
					if (Stack_get(stk, &stk_elm))
						break;
				}
				LAB2_SAFE(Stack_push(&stk, &operator), 5);
			}
			input.first += operator.length;
			input.length -= operator.length;
		}
		else if (lab2_isParenthesOpen(*input.first))
		{ // Найдена открытая скобка. Что делать?
			LAB2_SAFE(Stack_push(&stk, &((string_t) { input.first, 1 })), 5);
			input.first += 1;
			input.length -= 1;
		}
		else if (lab2_isParenthesClose(*input.first))
		{ // Найдена закрытая скобка. Что делать?
			string_t stk_elm;
			while (true)
			{
				LAB2_SAFE(Stack_pop(&stk, &stk_elm), 2);
				if (lab2_isParenthesOpen(*stk_elm.first))
				{ // find end.
					input.first++;
					input.length--;
					if (Stack_get(stk, &stk_elm))
						break;
					if (lab2_isFunction(stk_elm))
					{
						LAB2_SAFE(ArrayList_addLast(outList, &stk_elm), 3);
						LAB2_SAFE(Stack_pop(&stk, &stk_elm), 3);
					}
					break;
				}
				LAB2_SAFE(ArrayList_addLast(outList, &stk_elm), 3);
			}
		}
		else if (lab2_isSeparator(*input.first))
		{
			input.first++;
			input.length--;
		}
		else
		{
			LAB2_SAFE(true, 2);
		}
		previous = lab2_isParenthesClose(previous) ? '*' : *(input.first - 1);
	}
	string_t stk_elm;
	while (!Stack_pop(&stk, &stk_elm))
	{
		LAB2_SAFE(ArrayList_addLast(outList, &stk_elm), 3);
	}
	LAB2_SAFE(lab2_putListToString(output, outList, STRING_STATIC((char[]) { ' ' })), 1);
	LAB2_SAFE(true, 0);
}
