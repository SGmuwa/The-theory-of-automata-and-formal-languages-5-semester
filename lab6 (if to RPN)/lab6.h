#pragma once
#include "..\lab2\lab2.h"

#define LAB6_HELP_STR \
	"Постановка задачи: " \
	"\"Создать обратную польскую запись для условного оператора.\" " \
	"Так как за основу взята lab4, то программа поддерживает и арифметические, и логические записи." \
	"С помощью данной программы возможно преобразовывать " \
	"математико-логическую запись с условиями в обратную польскую запись. " \
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
	"! (логическое отрицание),\n" \
	"\"if (условие) {выражение}\" (условный оператор),\n" \
	"\"else {выражение}\" (переход по лжи от if).\n" \
	"И скобки: (, ), [, ], {, }.\n" \
	"Также поддерживаются вещественные числа и точка в операндах.\n" \
	"Пример:\n" \
	"test = 0;                                                    \n"\
	"if(!anywhere(!1.0, 2.00 + 5.1 * 3.2 + 2.3^~2.4^2.5)s.a == 0) \n"\
	"{                                                            \n"\
	"    test = 1;                                                \n"\
	"}                                                            \n"\
	"else                                                         \n"\
	"{                                                            \n"\
	"    test = 2;                                                \n"\
	"}                                                            \n"\
	"print(test);                                                 \n"\
	"В результате должно получиться:\n" \
	"test 0 = 1.0 ! 2.00 5.1 3.2 * + 2.3 2.4 ~ 2.5 ^ ^ + anywhere ! s.a * 0 == 30 if test 1 = 33 goto test 2 = test print"


#include <stdlib.h>
#include "..\stack_t\stack_t.h"
#include "..\string_t\string_t.h"
#include <string.h>
#include "..\byte_t\byte_t.h"
#include "..\lab1\lab1.h"
#include "..\lab4 (logical expression to RPN)\lab4.h"
#include "..\Dynamic_Generic_ArrayList_C\arrayList.h"
#include <limits.h>

#if _WIN32 && !_WIN64
// Размер листа для буфера вывода.
#define LAB6_SIZEBUFFER (10u + 1u + 1u) /* 10 цифр, отрицательные, конец строки. */
#else
// Размер листа для буфера вывода.
#define LAB6_SIZEBUFFER (20u + 1u + 1u)
#endif _WIN32

enum lab6_logicaloperator
{
	LAB6_LOGICALOPERATOR_NONE = 0,
	LAB6_LOGICALOPERATOR_IF,
	LAB6_LOGICALOPERATOR_ELSE
};

/*
Ищет логический оператор в входной строке.
Возвращает найденный оператор.
*/
enum lab6_logicaloperator lab6_searchLogicaloperator(string_t input)
{
	if (input.first == NULL || input.length < 2)
		return LAB6_LOGICALOPERATOR_NONE;
#define LAB6_MAKE(STR, CODE) else if(sizeof(STR) - 1 >= input.length && string_equal(STRING_STATIC0(STR), (string_t){input.first, sizeof(STR) - 1})) return CODE
	if (0);
	LAB6_MAKE("if", LAB6_LOGICALOPERATOR_IF);
	LAB6_MAKE("else", LAB6_LOGICALOPERATOR_ELSE);
	else return LAB6_LOGICALOPERATOR_NONE;
#undef LAB6_MAKE
}

/*
Вставляет в конец строки число put и уменьшает length в to.
string_t * to - куда надо вставить число.
size_t put - число, которое надо вставить.
Возвращает: код ошибки.
0 - Всё ок.
1 - Указатель на строку-вставку или result нулевой.
2 - Указатель на начало строки-вставки нулевой.
3 - Недостаточный размер.
4 - Копирование памяти произошло с ошибкой.
*/
int lab6_putSizetToEndString(string_t * to, size_t put, string_t * result)
{
	if (to == NULL || result == NULL)
		return 1;
	if (to->first == NULL)
		return 2;
	char toWrite[LAB6_SIZEBUFFER];
	result->length =
#ifdef _MSC_VER
		sprintf_s(toWrite, sizeof(toWrite) / sizeof(char), "%zu", put);
#else
		sprintf(toWrite, "%zu", list->length);
#endif // _MSC_VER
	if (result->length > to->length)
		return 3;
	result->first = to->first + to->length - result->length;
#ifdef _MSC_VER
	if (memcpy_s(result->first, result->length, toWrite, result->length))
		return 4;
#else
	memcpy(buffer->first + buffer->length - result->length, toWrite, result->length);
#endif // _MSC_VER
	to->length -= result->length;
	return 0;
}

/*
Ищет последний знак вопроса и заменяет его на последний индекс.
ArrayList<string_t> list - лист, в котором идёт поиск и замена.
ArrayList<char[LAB6_SIZEBUFFER]> buffer - лист, в котором 
Возвращает: код ошибки.
0 - Адрес успешно назначен.
1 - Обращение к листу происходит с ошибкой.
2 - Метка вставки адреса не найдена.
3 - Указатель на строку-вставку нулевой.
4 - Указатель на начало строки-вставки нулевой.
5 - Недостаточный размер.
6 - Копирование памяти произошло с ошибкой.
*/
int lab6_putLastAddress(ArrayList list, string_t * buffer)
{
#define LAB6_SAFE(ACT, CODE) if(ACT) return CODE
	for (size_t i = list->length - 1; i != SIZE_MAX; i--)
	{
		string_t b;
		LAB6_SAFE(ArrayList_get(list, i, &b), 1);
		if (string_equal(STRING_STATIC0("?"), b))
		{
			int err;
			LAB6_SAFE(err = lab6_putSizetToEndString(buffer, list->length, &b), err + 2);
			LAB6_SAFE(ArrayList_set(list, i, &b), 7);
			return 0;
		}
	}
	return 2;
#undef LAB6_SAFE
}

int lab6_putElse(ArrayList outList, string_t * buffer)
{
#define LAB6_SAFE(ACT, CODE) if(ACT) return CODE
	LAB6_SAFE(ArrayList_addLast(outList, &STRING_STATIC0("?")), 1);
	LAB6_SAFE(ArrayList_addLast(outList, &STRING_STATIC0("goto")), 2);
	char s[LAB6_SIZEBUFFER];  string_t searchAddress = {s, 
#ifdef _MSC_VER
		sprintf_s(s, sizeof(s) / sizeof(char), "%zu", outList->length - 2)
#else
		sprintf(s, "%zu", outList->length - 1)
#endif
	};
	for (size_t i = outList->length - 1; i != 0; i--)
	{
		string_t a, b;
		LAB6_SAFE(ArrayList_get(outList, i, &a), 3);
		if (string_equal(STRING_STATIC0("if"), a))
		{
			LAB6_SAFE(ArrayList_get(outList, i - 1, &b), 4);
			if (string_equal(searchAddress, b))
			{
				LAB6_SAFE(lab6_putSizetToEndString(buffer, outList->length, &searchAddress), 5);
				LAB6_SAFE(ArrayList_set(outList, i - 1, &searchAddress), 6);
				return 0;
			}
		}
	}
	return 5;
#undef LAB6_SAFE
}

// Создать обратную польскую запись для арифметической, логической формулы с поддержкой условных операторов if if-else.
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
//				6 - Ошибка при работе с else.
int lab6(string_t * output, string_t input)
{
	if (output == NULL || output->first == NULL || output->length == 0 || input.first == NULL || input.length == 0)
		return 4;
	char * oldOut = output->first;
	struct StackMemory stk = Stack_malloc(output->length, sizeof(string_t));
	if (stk.bottom == NULL)
		return 5;
	input = string_removeAllMalloc(input, STRING_STATIC("\n "));
	char * oldIn = input.first;
	if (input.first == NULL)
	{
		Stack_free(stk);
		return 5;
	}
	// Лист, в который складываются элементы для output.
	ArrayList outList = ArrayList_malloc(sizeof(string_t));
	if (outList == NULL)
	{
		Stack_free(stk);
		free(oldIn);
		return 5;
	}
	// Буфер, куда помещаются такие символы, которые надо поместить в outList, но которые отсутствуют в input.
	string_t bufferForOutput = string_malloc(LAB6_SIZEBUFFER * input.length);
	if (bufferForOutput.first == NULL)
	{
		Stack_free(stk);
		free(oldIn);
		ArrayList_free(outList);
		return 5;
	}
	char previous = '\0';
#define LAB6_SAFE(ACT, CODE) if(ACT) { Stack_free(stk); free(oldIn); ArrayList_free(outList); string_free(bufferForOutput); return CODE; }
	while (input.length > 0)
	{ // Пока мы ещё имеем входную строку.
		string_t operand = lab4_searchOperand(input, previous);
		size_t countOfFun = lab2_isFunction(input);
		size_t countOfPrefixOperator = lab4_isPrefixOperator(input);
		string_t operator = lab4_searchOperator(input);
		if (previous == ')' && (countOfFun || operand.length || countOfPrefixOperator) && operator.length == 0) // Поддержка мнимого умножения
		{
			operand = (string_t) { NULL, 0 };
			countOfFun = 0;
			countOfPrefixOperator = 0;
			operator = (string_t) { "*", 1 };
			input.first -= 1;
			input.length += 1;
		}
		if (countOfPrefixOperator && countOfPrefixOperator >= operator.length)
		{ // Префиксый оператор (кроме минуса).
			LAB6_SAFE(Stack_push(&stk, &((string_t) { input.first, countOfPrefixOperator })), 5);
			input.first += countOfPrefixOperator;
			input.length -= countOfPrefixOperator;
		}
		else if (countOfFun)
		{ // Найдена функция
			if (string_equal(STRING_STATIC0("else"), operand))
			{
				LAB6_SAFE(lab6_putElse(outList, &bufferForOutput), 6);
			}
			else
			{
				LAB6_SAFE(Stack_push(&stk, &((string_t) { input.first, countOfFun })), 5);
			}
			input.first += countOfFun;
			input.length -= countOfFun;
		}
		else if (operand.length > 0)
		{ // Это оказалось десятичное число.
			LAB6_SAFE(ArrayList_addLast(outList, &operand), 5);
			input.length -= operand.length;
			input.first += operand.length;
			// Поддержка префиксных операторов:
			string_t stk_elm = (string_t) { NULL, 0 };
			if (Stack_get(stk, &stk_elm) == 0)
			{
				if (lab4_isPrefixOperator(stk_elm) == stk_elm.length)
				{
					LAB6_SAFE(ArrayList_addLast(outList, &stk_elm), 5);
					LAB6_SAFE(Stack_pop(&stk, &stk_elm), 5);
				}
			}
		}
		else if (operator.length > 0)
		{ // Это оператор.
			string_t stk_elm = (string_t) { NULL, 0 };
			if ((Stack_count(stk) == 0) || (Stack_get(stk, &stk_elm) == 0 && lab2_isParenthesOpen(*stk_elm.first) && stk_elm.length == 1)
				|| lab4_getOperatorPriority(operator) > lab4_getOperatorPriority(stk_elm))
			{
				LAB6_SAFE(Stack_push(&stk, &operator), 5);
			}
			else
			{
				while ((lab2_isLeftFirstPriority(operator) ? lab4_getOperatorPriority(operator) : ~lab4_getOperatorPriority(operator)) <= lab4_getOperatorPriority(stk_elm) && !lab2_isParenthesOpen(*stk_elm.first))
				{
					LAB6_SAFE(ArrayList_addLast(outList, &stk_elm) || Stack_pop(&stk, &stk_elm), 5);
					if (Stack_get(stk, &stk_elm))
						break;
				}
				LAB6_SAFE(Stack_push(&stk, &operator), 5);
			}
			input.first += operator.length;
			input.length -= operator.length;
		}
		else if (lab2_isParenthesOpen(*input.first))
		{ // Найдена открытая скобка. Что делать?
			LAB6_SAFE(Stack_push(&stk, &((string_t) { input.first, 1 })), 5);
			input.first += 1;
			input.length -= 1;
		}
		else if (lab2_isParenthesClose(*input.first))
		{ // Найдена закрытая скобка. Что делать?
			string_t stk_elm;
			while (true)
			{
				LAB6_SAFE(Stack_pop(&stk, &stk_elm), 2);
				if (lab2_isParenthesOpen(*stk_elm.first))
					break; // find end.
				LAB6_SAFE(ArrayList_addLast(outList, &stk_elm), 3);
			}
			if (*input.first == '}')
			{
				LAB6_SAFE(lab6_putLastAddress(outList, &bufferForOutput), 4);
			}
			if (Stack_get(stk, &stk_elm) == 0) // Вставка функций.
			{
				if (lab4_isFunctionName(stk_elm) == stk_elm.length)
				{
					if (string_equal(STRING_STATIC0("if"), stk_elm))
					{
						LAB6_SAFE(ArrayList_addLast(outList, &STRING_STATIC0("?")), 3);
					}
					LAB6_SAFE(ArrayList_addLast(outList, &stk_elm), 3);
					LAB6_SAFE(Stack_pop(&stk, &stk_elm), 3);
				}
			}
			input.first++;
			input.length--;
		}
		else if (lab2_isSeparator(*input.first))
		{
			if (*input.first == ';')
			{
				string_t stk_elm = { NULL, 0u };
				while (true)
				{
					if (Stack_pop(&stk, &stk_elm))
						break;
					if (lab2_isParenthesOpen(*stk_elm.first))
						break; // find end.
					LAB6_SAFE(ArrayList_addLast(outList, &stk_elm), 3);
				}
				if (stk_elm.first != NULL && lab2_isParenthesOpen(*stk_elm.first))
				{
					LAB6_SAFE(Stack_push(&stk, &stk_elm), 5);
				}
			}
			input.first++;
			input.length--;
		}
		else
		{
			LAB6_SAFE(true, 2);
		}
		previous = previous == ')' ? '*' : *(input.first - 1);
	}
	string_t stk_elm;
	while (!Stack_pop(&stk, &stk_elm))
	{
		LAB6_SAFE(ArrayList_addLast(outList, &stk_elm), 3);
	}
	LAB6_SAFE(lab2_putListToString(output, outList, STRING_STATIC0(" ")), 1);
	LAB6_SAFE(true, 0);
#undef LAB6_SAFE
}
