#pragma once
#include "..\lab2\lab2.h"

#define LAB4_HELP_STR \
	"Постановка задачи:\n" \
	"\"Создать обратную польскую запись " \
	"для арифметической и логической записи.\"\n" \
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


// Определяет, принадлежит ли входной символ множеству десятичных цифр.
inline byte_t lab4_is10Number(char in) {
	return '0' <= in && in <= '9';
}

inline byte_t lab4_isLetter(char in) {
	return ('a' <= in && in <= 'z')
		|| ('A' <= in && in <= 'Z');
}

/*
Функция отвечает на вопрос, явяляется ли символ открытой скобкой.
char in - входной символ.
Возвращает: True, если символ символизирует открытую скобку. Иначе - False.
*/
inline byte_t lab4_isParenthesOpen(char in) {
	return in == '(' || in == '[' || in == '{';
}



/*
Находит начиная с первого символа оператор.
*/
string_t lab4_searchOperator(string_t input)
{
	if (input.first == NULL)
		return (string_t) { NULL, 0 };
	char a = *input.first;
	char b = input.length >= 2 ? input.first[1] : '\0';
	size_t countReturn = 0;
#define LAB4_MAKE(A) if(a == A[0] && b == A[1]) return (string_t) {input.first, b == '\0' ? 1 : 2 }
	LAB4_MAKE("||");
	LAB4_MAKE("&&");
	LAB4_MAKE("|");
	LAB4_MAKE("^^");
	LAB4_MAKE("&");
	LAB4_MAKE("==");
	LAB4_MAKE("!=");
	LAB4_MAKE("<=");
	LAB4_MAKE(">=");
	LAB4_MAKE(">");
	LAB4_MAKE("<");
	LAB4_MAKE(">>");
	LAB4_MAKE("<<");
	LAB4_MAKE("+");
	LAB4_MAKE("-");
	LAB4_MAKE("*");
	LAB4_MAKE("/");
	LAB4_MAKE("%");
	LAB4_MAKE("^");
	LAB4_MAKE("~");
	LAB4_MAKE("!");
	return (string_t) { input.first, 0 };
#undef LAB4_MAKE
}

/*
Получает приоритет оператора.
*/
unsigned int lab4_getOperatorPreority(string_t input)
{
	if (input.length != 1)
		return ~UINT_MAX;
	char a = input.first[0];
	char b = input.length >= 2 ? input.first[1] : '\0';
	unsigned int i = 1;
#define LAB4_MAKE(A) if(a == A[0] && b == A[1]) return ~i;
	LAB4_MAKE("||"); // Самый низкий приоритет
	i++;
	LAB4_MAKE("&&");
	i++;
	LAB4_MAKE("|");
	i++;
	LAB4_MAKE("^^"); // XOR
	i++;
	LAB4_MAKE("&");
	i++;
	LAB4_MAKE("==");
	LAB4_MAKE("!=");
	i++;
	LAB4_MAKE(">");
	LAB4_MAKE(">=");
	LAB4_MAKE("<");
	LAB4_MAKE("<=");
	i++;
	LAB4_MAKE(">>");
	LAB4_MAKE("<<");
	i++;
	LAB4_MAKE("+");
	LAB4_MAKE("-");
	i++;
	LAB4_MAKE("*");
	LAB4_MAKE("/");
	LAB4_MAKE("%"); // Остаток от деления
	i++;
	LAB4_MAKE("^"); // Возведение в степень.
	i++;
	LAB4_MAKE("~"); // Битовое не
	LAB4_MAKE("!"); // Логическое не
#undef LAB4_MAKE2
}


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
int lab4(string_t * output, string_t input)
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
	}
	char previous = '\0';
	while (input.length > 0)
	{ // Пока мы ещё имеем входную строку.
		string_t operand = lab2_searchOperand(input, previous);
		size_t countOfFun = lab4_isFunction(input);
		string_t operator = lab2_searchOperator(input);
		if (lab4_isParenthesClose(previous) && (countOfFun || operand.length) && operator.length == 0) // Поддержка мнимого умножения
		{
			operand = (string_t){ NULL, 0 };
			countOfFun = 0;
			operator = (string_t) { "*", 1 };
			input.first -= 1;
			input.length += 1;
		}
		if (countOfFun)
		{ // Найдена функция
			Stack_push(&stk, &((string_t) { input.first, countOfFun }));
			input.first += countOfFun;
			input.length -= countOfFun;
		}
		else if (operand.length > 0)
		{ // Это оказалось десятичное число.
			if (ArrayList_addLast(outList, &operand))
			{
				Stack_free(stk);
				free(oldIn);
				ArrayList_free(outList);
				return 5;
			}
			input.length -= operand.length;
			input.first += operand.length;
		}
		else if (operator.length > 0)
		{ // Это оператор.
			string_t stk_elm = (string_t) { NULL, 0 };
			if ((Stack_count(stk) == 0) || (Stack_get(stk, &stk_elm) == 0 && lab4_isParenthesOpen(*stk_elm.first) && stk_elm.length == 1)
				|| lab4_getOperatorPreority(operator) > lab4_getOperatorPreority(stk_elm))
			{
				if (Stack_push(&stk, &operator))
				{
					Stack_free(stk);
					free(oldIn);
					ArrayList_free(outList);
					return 5;
				}
			}
			else
			{
				while ((lab4_isLeftFirstPriority(operator) ? lab4_getOperatorPreority(operator) : ~lab4_getOperatorPreority(operator)) <= lab4_getOperatorPreority(stk_elm) && !lab4_isParenthesOpen(*stk_elm.first))
				{
					if (ArrayList_addLast(outList, &stk_elm) || Stack_pop(&stk, &stk_elm))
					{
						Stack_free(stk);
						free(oldIn);
						ArrayList_free(outList);
						return 5;
					}
					if (Stack_get(stk, &stk_elm))
						break;
				}
				if (Stack_push(&stk, &operator))
				{
					Stack_free(stk);
					free(oldIn);
					ArrayList_free(outList);
					return 5;
				}
			}
			input.first += operator.length;
			input.length -= operator.length;
		}
		else if (lab4_isParenthesOpen(*input.first))
		{ // Найдена открытая скобка. Что делать?
			Stack_push(&stk, &((string_t) { input.first, 1 }));
			input.first += 1;
			input.length -= 1;
		}
		else if (lab4_isParenthesClose(*input.first))
		{ // Найдена закрытая скобка. Что делать?
			string_t stk_elm;
			while (1)
			{
				if (Stack_pop(&stk, &stk_elm))
				{ // error
					Stack_free(stk);
					free(oldIn);
					ArrayList_free(outList);
					return 2;
				}
				if (lab4_isParenthesOpen(*stk_elm.first))
				{ // find end.
					input.first++;
					input.length--;
					if (Stack_get(stk, &stk_elm))
						break;
					if (lab4_isFunction(stk_elm))
					{
						if (ArrayList_addLast(outList, &stk_elm))
						{
							Stack_free(stk); free(oldIn); ArrayList_free(outList);
							return 3;
						}
						if (Stack_pop(&stk, &stk_elm))
						{
							Stack_free(stk); free(oldIn); ArrayList_free(outList);
							return 3;
						}
					}
					break;
				}
				if (ArrayList_addLast(outList, &stk_elm))
				{
					Stack_free(stk); free(oldIn); ArrayList_free(outList);
					return 3;
				}
			}
		}
		else if (lab4_isSeparator(*input.first))
		{
			input.first++;
			input.length--;
		}
		else
		{
			Stack_free(stk);
			free(oldIn);
			ArrayList_free(outList);
			return 2;
		}
		previous = lab4_isParenthesClose(previous) ? '*' : *(input.first - 1);
	}
	string_t stk_elm;
	while (!Stack_pop(&stk, &stk_elm))
	{
		if (ArrayList_addLast(outList, &stk_elm))
		{
			Stack_free(stk);
			free(oldIn);
			ArrayList_free(outList);
			return 3;
		}

	}
	int lab4_putListToString_error = lab4_putListToString(output, outList, STRING_STATIC((char[]) { ' ' }));
	Stack_free(stk);
	free(oldIn);
	ArrayList_free(outList);
	return lab4_putListToString_error == 0 ? 0 : 5;
}
