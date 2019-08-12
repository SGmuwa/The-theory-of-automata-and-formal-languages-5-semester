#pragma once
#include "..\lab2\lab2.h"

#define LAB4_HELP_STR \
	"Постановка задачи: " \
	"\"Создать обратную польскую запись " \
	"для логической формулы.\" " \
	"Так как за основу взята lab2, то программа поддерживает и арифметические записи." \
	"С помощью данной программы возможно преобразовывать " \
	"математическо-логическую запись в обратную польскую запись. " \
	"Поддерживаются операторы:\n" \
	"|| (логическое или),\n" \
	"&& (логическое и),\n" \
	"| (битовое или),\n" \
	"^^ (битовое исключающее или),\n" \
	"& (битовое и),\n" \
	"== (логическое равенство),\n" \
	"!= (логическое неравенство,\n" \
	"<= (меньше или равно),\n" \
	">= (больше или равно),\n" \
	"> (больше),\n" \
	"< (меньше),\n" \
	">> (битовой сдвиг вправо),\n" \
	"<< (битовой сдвиг влево),\n" \
	"+ (сложение),\n" \
	"- (вычитание),\n" \
	"* (умножение),\n" \
	"/ (деление),\n" \
	"% (остаток от деления),\n" \
	"^ (возведение в степень),\n" \
	"~ (битовое отрицание),\n" \
	"! (логическое отрицание).\n" \
	"И скобки: (, ), [, ], {, }.\n" \
	"Также поддерживаются вещественные числа и точка в операндах."


#include <stdlib.h>
#include "..\stack_t\stack_t.h"
#include "..\string_t\string_t.h"
#include <string.h>
#include "..\byte_t\byte_t.h"
#include "..\lab1\lab1.h"
#include "..\Dynamic_Generic_ArrayList_C\arrayList.h"
#include <limits.h>


size_t lab4_isPrefixOperator(string_t input)
{
	return input.length > 0
		? input.first != NULL && (*input.first == '~' || *input.first == '!')
		: 0;
}

// Определяет, может ли входная строка быть именем функции.
// string_t input - Строка поиска.
// Возвращает: 0 - если не содержится префиксная функция. Иначе - количество занимаемых символов функцией.
size_t lab4_isFunctionName(string_t input)
{
	char * i = input.first;
	if (lab2_is10Number(*i))
		return 0; // Функция не может начинаться с цифры.
	for (; i < string_getEnd(input); i++)
	{
		if (lab2_is10Number(*i) || lab2_isLetter(*i))
			continue;
		else
			return i - input.first;
	}
	return i - input.first;
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
	size_t lenRet = 0;
#define LAB4_MAKE(A) if(A[0] == a && ((A[1] == '\0' && lenRet <= 1) || A[1] == b)) { lenRet = A[1] == '\0' ? 1 : 2; if(lenRet == 2) return (string_t) {input.first, lenRet };}
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
	return (string_t) { input.first, lenRet };
#undef LAB4_MAKE
}

/*
Получает приоритет оператора.
*/
unsigned int lab4_getOperatorPriority(string_t input)
{
	if (input.length == 0)
		return 0;
	char a = input.first[0];
	char b = input.length >= 2 ? input.first[1] : '\0';
	unsigned int i = 1;
	unsigned int ret = 0;
	size_t lenRet = 0;
#define LAB4_MAKE(A) if(A[0] == a && ((A[1] == '\0' && lenRet <= 1) || A[1] == b)) {ret = i; lenRet = A[1] == '\0' ? 1 : 2; if(lenRet == 2) return ret; }
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
	i++;
	return ret;
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
		size_t countOfFun = lab2_isFunction(input);
		size_t countOfPrefixOperator = lab4_isPrefixOperator(input);
		string_t operator = lab4_searchOperator(input);
		if (lab2_isParenthesClose(previous) && (countOfFun || operand.length || countOfPrefixOperator) && operator.length == 0) // Поддержка мнимого умножения
		{
			operand = (string_t){ NULL, 0 };
			countOfFun = 0;
			countOfPrefixOperator = 0;
			operator = (string_t) { "*", 1 };
			input.first -= 1;
			input.length += 1;
		}
		if (countOfPrefixOperator && countOfPrefixOperator >= operator.length)
		{ // Префиксый оператор (кроме минуса).
			Stack_push(&stk, &((string_t) { input.first, countOfPrefixOperator }));
			input.first += countOfPrefixOperator;
			input.length -= countOfPrefixOperator;
		}
		else if (countOfFun)
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
			// Поддержка префиксных операторов:
			string_t stk_elm = (string_t) { NULL, 0 };
			if (Stack_get(stk, &stk_elm) == 0)
			{
				if (lab4_isPrefixOperator(stk_elm) == stk_elm.length)
				{
					if (ArrayList_addLast(outList, &stk_elm))
					{
						Stack_free(stk);
						free(oldIn);
						ArrayList_free(outList);
						return 5;
					}
					if (Stack_pop(&stk, &stk_elm))
					{
						Stack_free(stk);
						free(oldIn);
						ArrayList_free(outList);
						return 5;
					}
				}
			}
		}
		else if (operator.length > 0)
		{ // Это оператор.
			string_t stk_elm = (string_t) { NULL, 0 };
			if ((Stack_count(stk) == 0) || (Stack_get(stk, &stk_elm) == 0 && lab2_isParenthesOpen(*stk_elm.first) && stk_elm.length == 1)
				|| lab4_getOperatorPriority(operator) > lab4_getOperatorPriority(stk_elm))
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
				while ((lab2_isLeftFirstPriority(operator) ? lab4_getOperatorPriority(operator) : ~lab4_getOperatorPriority(operator)) <= lab4_getOperatorPriority(stk_elm) && !lab2_isParenthesOpen(*stk_elm.first))
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
		else if (lab2_isParenthesOpen(*input.first))
		{ // Найдена открытая скобка. Что делать?
			Stack_push(&stk, &((string_t) { input.first, 1 }));
			input.first += 1;
			input.length -= 1;
		}
		else if (lab2_isParenthesClose(*input.first))
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
				if (lab2_isParenthesOpen(*stk_elm.first))
				{ // find end.
					input.first++;
					input.length--;
					if (Stack_get(stk, &stk_elm))
						break;
					if (lab4_isFunctionName(stk_elm) == stk_elm.length)
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
		else if (lab2_isSeparator(*input.first))
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
		previous = lab2_isParenthesClose(previous) ? '*' : *(input.first - 1);
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
	int lab2_putListToString_error = lab2_putListToString(output, outList, STRING_STATIC((char[]) { ' ' }));
	Stack_free(stk);
	free(oldIn);
	ArrayList_free(outList);
	return lab2_putListToString_error == 0 ? 0 : 5;
}
