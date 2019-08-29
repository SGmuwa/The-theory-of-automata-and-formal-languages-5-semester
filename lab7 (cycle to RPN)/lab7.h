#pragma once

#include "..\lab6 (if to RPN)\lab6.h"

#define LAB7_HELP_STR \
	"Постановка задачи: " \
	"\"Создать обратную польскую запись для TODO.\" " \
	"Так как за основу взята lab6, то программа поддерживает и арифметические, и логические записи." \
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
	"\"for(<операция>;<условие>;<операция>){ <Тело цикла> }\" цикл for).\n" \
	"\"where(<условие>){ <Тело цикла> }\" цикл <where>).\n" \
	"\"do{ <Тело цикла> } while(<Тело цикда>);\" цикл do-while).\n" \
	"И скобки: (, ), [, ], {, }.\n" \
	"Также поддерживаются вещественные числа и точка в операндах.\n" \
	"Пример:\n" \
	/*                0 1 2 */ "test = 0;                                                    \n" /* test 0 =                                                               */ \
	/*             3 ... 24 */ "if(!anywhere(!1.0, 2.00 + 5.1 * 3.2 + 2.3^~2.4^2.5)s.a == 0) \n" /* 1.0 ! 2.00 5.1 3.2 * + 2.3 2.4 ~ 2.5 ^ ^ + anywhere ! s.a * 0 == 52 if */ \
	/*                      */ "{                                                            \n" /*                                                                        */ \
	/*             25 26 27 */ "    test = 1;                                                \n" /* test 1 =                                                               */ \
	/* 28 29 30 31 32 33 34 */ "    if(now() % 2 == 0)                                       \n" /* now 2 % 0 == 50 if                                                     */ \
	/*                      */ "    {                                                        \n" /*                                                                        */ \
	/*                35 36 */ "		print(now());                                        \n" /* now print                                                              */ \
	/* 37 38 39 40 41 42 43 */ "		if(now() % 2 == 0)                                   \n" /* now 2 % 0 == 48 if                                                     */ \
	/*                      */ "		{                                                    \n" /*                                                                        */ \
	/*                44 45 */ "			print(now());                                    \n" /* now print                                                              */ \
	/*                46 47 */ "		}                                                    \n" /* 50 goto                                                                */ \
	/*                      */ "		else                                                 \n" /*                                                                        */ \
	/*                      */ "		{                                                    \n" /*                                                                        */ \
	/*                48 49 */ "			print(3.14);                                     \n" /* 3.14 print                                                             */ \
	/*                      */ "		}                                                    \n" /*                                                                        */ \
	/*                      */ "    }                                                        \n" /*                                                                        */ \
	/*                50 51 */ "}                                                            \n" /* 55 goto                                                                */ \
	/*                      */ "else                                                         \n" /*                                                                        */ \
	/*                      */ "{                                                            \n" /*                                                                        */ \
	/*             52 53 54 */ "    test = 2;                                                \n" /* test 2 =                                                               */ \
	/*                      */ "}                                                            \n" /*                                                                        */ \
	/*                55 56 */ "print(test);                                                 \n" /* test print                                                             */ \
	"В результате должно получиться:\n" \
	"test 0 = 1.0 ! 2.00 5.1 3.2 * + 2.3 2.4 ~ 2.5 ^ ^ + anywhere ! s.a * 0 == 52 if test 1 = now 2 % 0 == 50 if now print now 2 % 0 == 48 if now print 50 goto 3.14 print 55 goto test 2 = test print"
/*   0    1 2 3   4 5    6   7   8 9 10  11  1213  14151617       1819  202122 23 24 25   262728  29303132 33 34 35  36    37  38394041 42 43 44  45    46 47   48   49    50 51   52   535455   56*/


typedef struct lab7_mark
{
	// Местоположение метки.
	size_t position;
	// Текстовая информация метки.
	string_t text;
} lab7_mark;


/*
Вставить метку.
NAME - Имя метки.
ALT_POS - позиция относительно последнего доступного элемента.
ERRORCODE - код ошибки в случае неудачи.
*/
#define LAB7_INSERTMARK(NAME, ALT_POS, ERRORCODE) LAB7_SAFE(ArrayList_addLast(anyMarks, &(lab7_mark){ outList->length - 1 + ALT_POS, STRING_STATIC0(NAME) }), ERRORCODE)


inline void lab7_printArrayListOfString(ArrayList toPrint)
{
#if _DEBUG == 1
	string_t b;
	size_t sizeToPrint = 1;
	for (size_t i = 0; i < toPrint->length; i++)
	{
		ArrayList_get(toPrint, i, &b);
		sizeToPrint += b.length + 2;
	}
	b = string_malloc(sizeToPrint);
	if (b.first == NULL)
		return;
	if (lab2_putListToString(&b, toPrint, STRING_STATIC0(", "))) return;
	printf("%.*s\n", (int)b.length, b.first);
	string_free(b);
#endif
}


/*
Функция меняет второй и третий аргумент цикла for местами.
ArrayList<lab7_mark> anyMarks - тут должна быть метка, где начинается аргумент 1 и где начинется аргумент 2.
	Поддерживаемые марки:
		<$>_FOR_ARG1_ARG2 - Указывает на первую команду второго аргумента цикла FOR.
		<$>_FOR_ARG2_ARG3 - Указывает на первую команду третьего аргумента цикла FOR.
ArrayList<string_t> outList - выходной лист, в котором надо менять местами аргументы цикла for.
string_t * bufferGoto - буфер, куда вставляется адрес goto.
Возвращает: код ошибки.
*/
int lab7_switchArg2Arg3End(ArrayList /*lab7_mark*/ anyMarks, ArrayList /*string_t*/ outList, string_t * bufferGoto)
{
#define LAB7_SAFE(ACT, CODE) if(ACT) { return CODE; }
	lab7_printArrayListOfString(outList);
	size_t mark[2] = { SIZE_MAX, SIZE_MAX }; // Две марки.
	size_t toRemove[2];
	lab7_mark buffer;
	for(size_t i = anyMarks->length - 1; i != SIZE_MAX; i--)
	{
		LAB7_SAFE(ArrayList_get(anyMarks, i, &buffer), 1);
		if(string_equal(STRING_STATIC0("<$>_FOR_ARG2_ARG3"), buffer.text))
		{
			mark[1] = buffer.position;
			toRemove[1] = i;
			break;
		}
	}
	LAB7_SAFE(mark[1] == SIZE_MAX, 2);
	for(size_t i = mark[1] - 1; i != SIZE_MAX; i--)
	{
		LAB7_SAFE(ArrayList_get(anyMarks, i - mark[1] + anyMarks->length - 1, &buffer), 3);
		if(string_equal(STRING_STATIC0("<$>_FOR_ARG1_ARG2"), buffer.text))
		{
			mark[0] = buffer.position;
			toRemove[0] = i - mark[1] + anyMarks->length - 1;
			break;
		}
	}
	LAB7_SAFE(mark[0] == SIZE_MAX, 4);
	size_t countBufferOutList = outList->length - mark[1];
	string_t * bufferOutList = (string_t *) malloc(countBufferOutList * sizeof(string_t));
	LAB7_SAFE(bufferOutList == NULL, 5);
#undef LAB7_SAFE
#define LAB7_SAFE(ACT, CODE) if(ACT) { free(bufferOutList); return CODE; }
	for(size_t i = outList->length - 1; i >= mark[1]; i--)
	{
		LAB7_SAFE(ArrayList_get(outList, i, bufferOutList + i - mark[1]), 6);
		LAB7_SAFE(ArrayList_remove(outList, i), 7);
		lab7_printArrayListOfString(outList);
	}
	for(size_t i = countBufferOutList - 1; i != SIZE_MAX; i--)
	{
		LAB7_SAFE(ArrayList_add(outList, mark[0], bufferOutList + i), 8);
		lab7_printArrayListOfString(outList);
	}
	free(bufferOutList);
	string_t setToAddressGoto;
	LAB7_SAFE(lab6_putSizetToEndString(bufferGoto, mark[0] + countBufferOutList, &setToAddressGoto), 11);
	LAB7_SAFE(ArrayList_set(outList, mark[0] - 2, &setToAddressGoto), 12);

#undef LAB7_SAFE
#define LAB7_SAFE(ACT, CODE) if(ACT) { return CODE; }
	LAB7_SAFE(ArrayList_remove(anyMarks, toRemove[1]), 9);
	LAB7_SAFE(ArrayList_remove(anyMarks, toRemove[0]), 10);
	LAB7_SAFE(true, 0);
#undef LAB7_SAFE
}

/*
Находит парную скобку для текущего индекса.
ArrayList parenthes - список кобок.
size_t start - индекс, для какой скобки мы ищем пару.
lab7_parenthesInfo * result - указатель, куда отправить результат.
size_t * indexOfResult - указатель, куда надо поместить индекс результата.
Возвращает: код ошибки.
*/
int lab7_findOpenParenthes(ArrayList /*lab6_parenthesInfo*/ parenthes, size_t start, lab6_parenthesInfo * result, size_t * indexOfResult)
{
#define LAB7_SAFE(ACT, CODE) if(ACT) { return CODE; }
	lab6_parenthesInfo current;
	byte_t(*searchEngine)(char);
	LAB7_SAFE(ArrayList_get(parenthes, start, &current), 1);
	if (lab2_isParenthesOpen(current.c))
		searchEngine = lab2_isParenthesClose;
	else if (lab2_isParenthesClose(current.c))
		searchEngine = lab2_isParenthesOpen;
	else
		LAB7_SAFE(true, 2);
	size_t i = start;
	size_t countOfCorrectOfSearchEngineParenthes = 0;
	while (true)
	{
		LAB7_SAFE(ArrayList_get(parenthes, i, &current), 3);
		if (searchEngine(current.c))
			countOfCorrectOfSearchEngineParenthes++;
		else
			countOfCorrectOfSearchEngineParenthes--;
		if (countOfCorrectOfSearchEngineParenthes == 0)
			break;
		i += searchEngine == lab2_isParenthesOpen ? -1 : 1;
	}
	if(result != NULL)
		*result = current;
	if (indexOfResult != NULL)
		*indexOfResult = i;
	LAB7_SAFE(result == NULL && indexOfResult == NULL, 4);
	LAB7_SAFE(true, 0);
#undef LAB7_SAFE
}

/*
Вставляет после body циклов for и while команду goto в outList.
ArrayList outList - куда надо вставить goto и откуда брать информацию.
ArrayList parenthes - информация о местоположении скобках.
string_t * bufferForOutput - в конец данной строки вставится size_t адрес для goto.
Возвращает: код ошибки.
*/
int lab7_putGotoToEndBodyOfAForOrAWhile(ArrayList /*string_t*/ outList, ArrayList /*lab6_parenthesInfo*/ parenthes, string_t * bufferForOutput)
{
#define LAB7_SAFE(ACT, CODE) if(ACT) { return CODE; }
	lab6_parenthesInfo endArgsFor;
	size_t indexOfParenthesEndArgsFor;
	LAB7_SAFE(lab7_findOpenParenthes(parenthes, parenthes->length - 1, &endArgsFor, &indexOfParenthesEndArgsFor), 1);
	string_t b;
	for (size_t i = endArgsFor.i; i != SIZE_MAX; i--)
	{
		LAB7_SAFE(ArrayList_get(outList, i, &b), 2);
		if (string_equal(b, STRING_STATIC0("goto")))
		{
			i = i + 1;
			LAB7_SAFE(lab6_putSizetToEndString(bufferForOutput, i, &b), 4);
			LAB7_SAFE(ArrayList_addLast(outList, &b), 5);
			LAB7_SAFE(ArrayList_addLast(outList, &STRING_STATIC0("goto")), 5);
			LAB7_SAFE(true, 0);
		}
	}
	LAB7_SAFE(true, 3);
#undef LAB7_SAFE
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
//              7 - Ошибка удаления скобок из выходного листа.
//              8 - Заполнение аргументов цикла for произошло с ошибкой.
int lab7(string_t * output, string_t input)
{
	if (output == NULL || output->first == NULL || output->length == 0 || input.first == NULL || input.length == 0)
		return 4;
	char * oldOut = output->first;
	struct StackMemory stk = Stack_malloc(output->length, sizeof(string_t));
	if (stk.bottom == NULL)
		return 5;
	input = string_removeAllMalloc(input, STRING_STATIC0("\n \0\t"));
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
	ArrayList parenthes = ArrayList_malloc(sizeof(lab6_parenthesInfo));
	if (parenthes == NULL)
	{
		Stack_free(stk);
		free(oldIn);
		ArrayList_free(outList);
		string_free(bufferForOutput);
		return 5;
	}
	char previous = '\0';
	enum lab7_CycleFor
	{
		LAB7_CYCLEFOR_NONE, // Сейчас не заполняются аргументы цикла for.
		LAB7_CYCLEFOR_ARG1, // Сейчас заполняется первый аргумент for.
		LAB7_CYCLEFOR_ARG2, // Сейчас заполняется второй аргумент for.
		LAB7_CYCLEFOR_ARG3, // Сейчас запоняется третий аргумент for.
		LAB7_CYCLEFOR_COUNT // Количество полей в lab7_CycleFor
	} CycleFor = LAB7_CYCLEFOR_NONE; // Стадии заполнения цикла for.
	ArrayList anyMarks = ArrayList_malloc(sizeof(lab7_mark));
	if (anyMarks == NULL)
	{
		Stack_free(stk);
		free(oldIn);
		ArrayList_free(outList);
		string_free(bufferForOutput);
		ArrayList_free(parenthes);
		return 5;
	}
#define LAB7_SAFE(ACT, CODE) if(ACT) { Stack_free(stk); free(oldIn); ArrayList_free(outList); string_free(bufferForOutput); ArrayList_free(parenthes); ArrayList_free(anyMarks); return CODE; }
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
			LAB7_SAFE(Stack_push(&stk, &((string_t) { input.first, countOfPrefixOperator })), 5);
			input.first += countOfPrefixOperator;
			input.length -= countOfPrefixOperator;
		}
		else if (countOfFun)
		{ // Найдена функция
			if (string_equal(STRING_STATIC0("else"), operand))
			{
				LAB7_SAFE(lab6_putElse(outList, &bufferForOutput, parenthes), 6);
			}
			else if (string_equal(STRING_STATIC0("for"), operand))
			{
				LAB7_SAFE(CycleFor != LAB7_CYCLEFOR_NONE, 8);
				CycleFor = LAB7_CYCLEFOR_ARG1;
				LAB7_SAFE(Stack_push(&stk, &((string_t) { input.first, countOfFun })), 8);
			}
			else
			{
				LAB7_SAFE(Stack_push(&stk, &((string_t) { input.first, countOfFun })), 5);
			}
			input.first += countOfFun;
			input.length -= countOfFun;
		}
		else if (operand.length > 0)
		{ // Это оказалось десятичное число.
			LAB7_SAFE(ArrayList_addLast(outList, &operand), 5);
			input.length -= operand.length;
			input.first += operand.length;
			// Поддержка префиксных операторов:
			string_t stk_elm = (string_t) { NULL, 0 };
			if (Stack_get(stk, &stk_elm) == 0)
			{
				if (lab4_isPrefixOperator(stk_elm) == stk_elm.length)
				{
					LAB7_SAFE(ArrayList_addLast(outList, &stk_elm), 5);
					LAB7_SAFE(Stack_pop(&stk, &stk_elm), 5);
				}
			}
		}
		else if (operator.length > 0)
		{ // Это оператор.
			string_t stk_elm = (string_t) { NULL, 0 };
			if ((Stack_count(stk) == 0) || (Stack_get(stk, &stk_elm) == 0 && lab2_isParenthesOpen(*stk_elm.first) && stk_elm.length == 1)
				|| lab4_getOperatorPriority(operator) > lab4_getOperatorPriority(stk_elm))
			{
				LAB7_SAFE(Stack_push(&stk, &operator), 5);
			}
			else
			{
				while ((lab2_isLeftFirstPriority(operator) ? lab4_getOperatorPriority(operator) : ~lab4_getOperatorPriority(operator)) <= lab4_getOperatorPriority(stk_elm) && !lab2_isParenthesOpen(*stk_elm.first))
				{
					LAB7_SAFE(ArrayList_addLast(outList, &stk_elm) || Stack_pop(&stk, &stk_elm), 5);
					if (Stack_get(stk, &stk_elm))
						break;
				}
				LAB7_SAFE(Stack_push(&stk, &operator), 5);
			}
			input.first += operator.length;
			input.length -= operator.length;
		}
		else if (lab2_isParenthesOpen(*input.first))
		{ // Найдена открытая скобка. Что делать?
			LAB7_SAFE(ArrayList_addLast(parenthes, &(lab6_parenthesInfo) { *input.first, outList->length }), 6);
			LAB7_SAFE(Stack_push(&stk, &((string_t) { input.first, 1 })), 5);
			input.first += 1;
			input.length -= 1;
		}
		else if (lab2_isParenthesClose(*input.first))
		{ // Найдена закрытая скобка. Что делать?
			LAB7_SAFE(ArrayList_addLast(parenthes, &(lab6_parenthesInfo) { *input.first, outList->length }), 6);
			string_t stk_elm;
			while (true)
			{
				LAB7_SAFE(Stack_pop(&stk, &stk_elm), 2);
				if (lab2_isParenthesOpen(*stk_elm.first))
					break; // find end.
				LAB7_SAFE(ArrayList_addLast(outList, &stk_elm), 3);
			}
			if (*input.first == '}')
			{
				LAB7_SAFE(lab7_putGotoToEndBodyOfAForOrAWhile(outList, parenthes, &bufferForOutput), 8);
				LAB7_SAFE(lab6_putLastAddress(outList, &bufferForOutput), 4);
			}
			if (Stack_get(stk, &stk_elm) == 0) // Вставка функций.
			{
				if (lab4_isFunctionName(stk_elm) == stk_elm.length)
				{
					if (string_equal(STRING_STATIC0("if"), stk_elm))
					{
						LAB7_SAFE(ArrayList_addLast(outList, &STRING_STATIC0("?")), 3);
						LAB7_SAFE(ArrayList_addLast(outList, &stk_elm), 3);
						LAB7_SAFE(Stack_pop(&stk, &stk_elm), 3);
					}
					else if (string_equal(STRING_STATIC0("for"), stk_elm))
					{ // Завершилось заполнение третьего аргумента for.
						LAB7_SAFE(CycleFor != LAB7_CYCLEFOR_ARG3, 8);
						LAB7_SAFE(Stack_pop(&stk, &stk_elm), 3);
						LAB7_SAFE(lab7_switchArg2Arg3End(anyMarks, outList, &bufferForOutput), 8);
						LAB7_SAFE(ArrayList_addLast(outList, &STRING_STATIC0("?")), 5);
						LAB7_SAFE(ArrayList_addLast(outList, &STRING_STATIC0("if")), 5);
						CycleFor = LAB7_CYCLEFOR_NONE;
					}
					else
					{
						LAB7_SAFE(ArrayList_addLast(outList, &stk_elm), 3);
						LAB7_SAFE(Stack_pop(&stk, &stk_elm), 3);
					}
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
					LAB7_SAFE(ArrayList_addLast(outList, &stk_elm), 3);
				}
				if (stk_elm.first != NULL && lab2_isParenthesOpen(*stk_elm.first))
				{
					LAB7_SAFE(Stack_push(&stk, &stk_elm), 5);
				}
				if (CycleFor > LAB7_CYCLEFOR_NONE)
				{
					CycleFor++;
					if (CycleFor == LAB7_CYCLEFOR_ARG2)
					{ // Закончил первый аргумент, начал второй аргумент.
						LAB7_SAFE(ArrayList_addLast(outList, &STRING_STATIC0("?")), 8);
						LAB7_SAFE(ArrayList_addLast(outList, &STRING_STATIC0("goto")), 8);
						LAB7_INSERTMARK("<$>_FOR_ARG1_ARG2", 1, 8);
					}
					else if (CycleFor == LAB7_CYCLEFOR_ARG3)
					{
						LAB7_INSERTMARK("<$>_FOR_ARG2_ARG3", 1, 8);
					}
					else LAB7_SAFE(CycleFor > LAB7_CYCLEFOR_ARG3, 8);
				}
			}
			input.first++;
			input.length--;
		}
		else
		{
			LAB7_SAFE(true, 2);
		}
		previous = previous == ')' ? '*' : *(input.first - 1);
#if _DEBUG == 1
		lab7_printArrayListOfString(outList);
#endif
	}
	string_t stk_elm;
	while (!Stack_pop(&stk, &stk_elm))
	{
		LAB7_SAFE(ArrayList_addLast(outList, &stk_elm), 3);
	}
	for (size_t i = outList->length - 1; i != SIZE_MAX; i--)
	{
		string_t b;
		LAB7_SAFE(ArrayList_get(outList, i, &b), 7);
		if (b.length == 1 && lab2_isParenthes(*b.first))
		{
			LAB7_SAFE(ArrayList_remove(outList, i), 7);
		}
	}
	LAB7_SAFE(lab2_putListToString(output, outList, STRING_STATIC0(" ")), 1);
	LAB7_SAFE(true, 0);
#undef LAB7_SAFE
}