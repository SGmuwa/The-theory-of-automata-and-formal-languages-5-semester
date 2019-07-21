#include "..\UserInterface-CLanguage\UserInterface.h"
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

#define false 0
#define true !0

typedef struct {
	char * first;
	size_t length;
} String;

typedef unsigned char byte;

// Создать обратную польскую запись для логической формулы.
void lab4(void){}
// Вычислить значение логической формулы, используя обратную польскую запись.
void lab5(void){}
// Создать обратную польскую запись для условного оператора.
void lab6(void){}
// Создать обратную польскую запись для оператора цикла.
void lab7(void){}
// Перечислить пути в ациклическом графе между двумя заданными вершинами.
// Выполнить топографическую сортировать ациклического графа
// *Перечислить пути в неориентированном графе между двумя заданными вершинами. Использовать простые пути.
// Преобразовать недетерминированный автомат в детерминированный.


// Десятичное число, представленное списком десятичных цифр, представить десятичным числом.
// double * output - указатель, куда надо поместить результат
// char * input - входная строка, откуда идёт чтение.
// size_t length - длинна входной строки.
// Возвращает: код ошибки.
// 0 - нет ошибок.
// 1 - на входе пустая строка.
// 2 - В строке встретилась не цифра.
// 3 - В строке две точки или запятых.
// 4 - Точка или запятая не может быть в начале или в конце строки.
// 5 - Входные указатели аргумента указывают на NULL.
// 6 - Число не может быть без целой части.
int lab1(double * output, const char * input, size_t length)
{
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
	//if (input[i] == '.' || input[i] == ',' || input[length - 1] == '.' || input[length - 1] == ',')
	//	return 4;
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
void lab1_interface(void)
{
	char input[256];
	size_t length = UserInterface_GetStr("Input number in decimal format: ", input, sizeof(input) / sizeof(char));
	double output = 0;
	int err;
	switch (err = lab1(&output, input, length))
	{
	case 0:
		printf("Number: %lf\n", output);
		break;
	default:
		printf("Error %d\n", err);
		break;
	}
}

void lab2_interface(void)
{
	String input = { malloc(sizeof(char)*1024), UserInterface_GetStr("Input arithmetic expression:", input.first, 1024) };
	if (input.first == NULL) return;
	String output = { malloc(input.length * sizeof(char) * 2), input.length * sizeof(char) * 2 };
	int err = lab2(output.first, output.length, input.first, input.length);
	if (err != 0) printf("error %d.\n", err);
	printf("%s", output.first);
	free(input.first);
}

#if _DEBUG == 1
void lab1_test(void)
{
	printf("lab1:\tTest start.\n");
	double output = 0;
	double * o = &output;
	int err = 0;
	if((err = lab1(o, "0", sizeof("0"))) != 0 || output != 0) printf("lab1:\tError[%d]: 0 but %lf\n", err, output);
	if ((err = lab1(o, "1", sizeof("1"))) != 0 || output != 1) printf("lab1:\tError[%d]: 1 but %lf\n", err, output);
	if ((err = lab1(o, "123", sizeof("123"))) != 0 || output != 123) printf("lab1:\tError[%d]: 123 but %lf\n", err, output);
	if ((err = lab1(o, "123.123", sizeof("123.123"))) != 0 || output != 123.123) printf("lab1:\tError[%d]: 123 but %lf\n", err, output);
	if ((err = lab1(o, "", sizeof(""))) != 1) printf("lab1:\tError[%d] but need err 1. res? %lf\n", err, output);
	if ((err = lab1(o, "123.1a23", sizeof("123.1a23"))) != 2) printf("lab1:\tError[%d] but need err 2. res? %lf\n", err, output);
	if ((err = lab1(o, "123..123", sizeof("123..123"))) != 3) printf("lab1:\tError[%d] but need err 3. res? %lf\n", err, output);
	if ((err = lab1(o, ".123", sizeof(".123"))) != 4) printf("lab1:\tError[%d] but need err 4. res? %lf\n", err, output);
	if ((err = lab1(NULL, "123", sizeof("123"))) != 5) printf("lab1:\tError[%d] but need err 5. res? %lf\n", err, output);
	if ((err = lab1(o, NULL, 12)) != 5) printf("lab1:\tError[%d] but need err 5. res? %lf\n", err, output);
	if ((err = lab1(o, "0123456789.0123456789", sizeof("0123456789.0123456789"))) != 0 || output != 0123456789.0123456789) printf("lab1:\tError[%d]: 0123456789.0123456789 but %lf\n", err, output);
	if ((err = lab1(o, "-0123456789.0123456789", sizeof("-0123456789.0123456789"))) != 0 || output != -0123456789.0123456789) printf("lab1:\tError[%d]: -0123456789.0123456789 but %lf\n", err, output);
	if ((err = lab1(o, "-123456789.0123456789", sizeof("-123456789.0123456789"))) != 0 || output != -123456789.0123456789) printf("lab1:\tError[%d]: -123456789.0123456789 but %lf\n", err, output);
	if ((err = lab1(o, "-", sizeof("-"))) != 1) printf("lab1:\tError[%d] but need 1. res? %lf\n", err, output);
	if ((err = lab1(o, "-.1", sizeof("-.1"))) != 6) printf("lab1:\tError[%d] but need 6. res? %lf\n", err, output);
	printf("lab1:\tTest end.\n");
}
#endif

inline byte lab2_isParenthesOpen(char in) {
	return in == '(' || in == '[' || in == '{';
}

inline byte lab2_isParenthesClose(char in) {
	return in == ')' || in == ']' || in == '}';
}

// Определяет, является ли входной символ скобками.
inline byte lab2_isParenthes(char in) {
	return lab2_isParenthesOpen(in) || lab2_isParenthesClose(in);
}

// Определяет, является ли входной символ разделителем.
inline byte lab2_isSeparator(char in) {
	return in == ',' || in == '.' || in == ';';
}

// Определяет, принадлежит ли входной символ множеству десятичных цифр.
inline byte lab2_is10Number(char in) {
	return '0' <= in && in <= '9';
}

// Пропускает все символы пробела.
// Возвращает: на следующий символ не-пробел. В случае, если пробелы до конца - то указатель на недоступный символ (следующий за доступным).
inline const char * lab2_skipSpace(char * in, size_t inL) {
	if (in == NULL) return NULL;
	for (const char * i = in; i < in + inL; i++)
		if (*i == ' ')
			continue;
		else return i;
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
// const char * in - указатель на начало поиска.
// size_t inL - количество доступных символов для поиска.
// Возвращает: 0 - если не содержится префиксная функция. Иначе - количество занимаемых символов функцией.
size_t lab2_isFunctionOrOperator(const char * in, size_t inL)
{
	const char * i = lab2_skipSpace(in, inL);
	if (lab2_is10Number(*i) || lab2_isParenthes(*i))
		return 0; // it's number or Parentheses!
	for ( ; i < in + inL; i++)
	{
		if (lab2_isSeparator(*i)) {
			i++;
			break;
		}
		if (lab2_isParenthes(*i) || *i == ' ' || *i == '\0') {
			break;
		}
	}
	return lab2_skipSpace(i, inL) - in;
}

// Создать обратную польскую запись для арифметической формулы.
// char * out - указатель, куда поместить результат.
// size_t outL - количество доступных для записи элементов.
// const char * in - указатель, откуда брать арифметическую запись.
// size_t inL - количество доступных для чтения арифметической записи символов.
// Возвращает: код ошибки.
// 1 - Не хватило место в выходной строке.
// 2 - Не верный входной формат.
// 3 - Неизвестная ошибка при перемещении из стека в выходную строку.
// 4 - не верные входные данные.
int lab2(char * out, size_t outL, const char * in, size_t inL)
{
	if (out == NULL || outL == 0 || in == NULL || inL == 0)
		return 4;
	const char * oldOut = out;
	struct StackMemory stk = Stack_malloc(outL, sizeof(String));
	while(inL > 1)
	{ // Пока мы ещё имеем входную строку
		if(outL < 2)
		{ // В выходной строке кончается место!
			if(outL > 0) *out = '\0';
			out++; outL--;
			Stack_free(stk);
			return 1;
		}
		{
			char * NewIn = lab2_skipSpace(in, inL);
			inL = inL - (NewIn - in);
			in = NewIn;
			if (inL > ~(size_t)0 - 1)
			{
				break;
			}
		}
		if (lab2_is10Number(*in) /*|| lab2_isPostfixFunction(in + i, inL - i) нет времени или идей разработки*/)
		{ // Это оказалось десятичное число
			while (lab2_is10Number(*in) && inL > 1 && outL > 2)
			{
				*out = *in;
				in++; out++; outL--; inL--;
			}
			if (inL > 0 && outL > 2)
			{
				*out = ' ';
				in++; out++; outL--; inL--;
			}
		}
		size_t countOfFun = lab2_isFunctionOrOperator(in, inL);
		if(countOfFun)
		{ // Ого! Найдена функция!
			Stack_push(&stk, &((String) { in, countOfFun }));
			in += countOfFun;
			inL -= countOfFun;
			continue;
		}
		if (lab2_isParenthesOpen(*in))
		{ // Найдена открытая скобка. Что делать?
			Stack_push(&stk, &((String) { in, 1 }));
			in += 1;
			inL -= 1;
			continue;
		}
		if (lab2_isParenthesClose(*in))
		{ // Найдена закрытая скобка. Что делать?
			String stk_elm;
			while(1)
			{
				if (Stack_pop(&stk, &stk_elm))
				{ // error
					Stack_free(stk);
					return 1;
				}
				if (lab2_isParenthesOpen(*stk_elm.first))
				{ // find end.
					in++;
					inL--;
					break;
				}
				int error;
				#ifndef _MSC_VER
					error = memcpy(out, stk_elm.first, stk_elm.length) == NULL ? 1 : 0;
				#else
					error = memcpy_s(out, outL, stk_elm.first, stk_elm.length);
				#endif
				out += stk_elm.length;
				outL -= stk_elm.length;
				if (error)
				{
					Stack_free(stk);
					return 3;
				}

			}
		}
	}

	String stk_elm;
	while (!Stack_pop(&stk, &stk_elm))
	{
		if (lab2_isParenthesOpen(*stk_elm.first))
		{ // find end. ????
			in++;
			inL--;
			break;
		}
		int error;
		#ifndef _MSC_VER
			error = memcpy(out, stk_elm.first, stk_elm.length) == NULL ? 1 : 0;
		#else
			error = memcpy_s(out, outL, stk_elm.first, stk_elm.length);
		#endif
		out += stk_elm.length;
		outL -= stk_elm.length;
		if (error)
		{
			Stack_free(stk);
			return 3;
		}

	}
	if (out > oldOut && *(out - 1) == ' ')
	{ // delete end space.
		out--;
		outL++;
	}
	if (outL > 0) *out = '\0';
	out++; outL--;
	Stack_free(stk);
	return 0;
}

#if _DEBUG == 1
// Тестирование задания lab2.
void lab2_test(void)
{
	printf("lab2\tStart test...\n");
	char out[256] = ""; // 256 - не менять.
	int err = 0;

	err = lab2(out, 256, "5", sizeof("5"));
	if (err != 0)
		printf("lab2.0\tError[%d], res %s", err, out);
	if (strcmp("5", out) != 0)
		printf("lab2.0\tError[%d], exp. %s but %s", err, "5", out);

	err = lab2(out, 256, "5 - 2", sizeof("5 - 2"));
	if (err != 0)
		printf("lab2.0.5\tError[%d], res %s", err, out);
	if (strcmp("5 2 -", out) != 0)
		printf("lab2.0.5\tError[%d], exp. %s but %s", err, "5 2 -", out);

	err = lab2(out, 256, "(10 - 15) * 3", sizeof("(10 - 15) * 3"));
	if (err != 0)
		printf("lab2.1\tError[%d], res %s", err, out);
	if (strcmp("10 15 - 3 *", out) != 0)
		printf("lab2.1\tError[%d], exp. %s but %s", err, "10 15 - 3 *", out);

	err = lab2(out, 256, "", sizeof(""));
	if (err != 0)
		printf("lab2.2\tError[%d], res %s", err, out);
	if (strcmp("", out) != 0)
		printf("lab2.2\tError[%d], exp. %s but %s", err, "", out);

	err = lab2(out, 256, "sin(2)", sizeof("sin(2)"));
	if (err != 0)
		printf("lab2.3\tError[%d], res %s", err, out);
	if (strcmp("2 sin", out) != 0)
		printf("lab2.3\tError[%d], exp. %s but %s", err, "2 sin", out);

	err = lab2(out, 256, "anywhere(1, 2 + 5 * 3)", sizeof("anywhere(1, 2 + 5 * 3)"));
	if (err != 0)
		printf("lab2.4\tError[%d], res %s", err, out);
	if (strcmp("1 2 3 5 * + anywhere", out) != 0)
		printf("lab2.4\tError[%d], exp. %s but %s", err, "1 2 3 5 * + anywhere", out);

	err = lab2(out, 256, "anywhere(1, 2 + 5 * 3)wejfwioe", sizeof("anywhere(1, 2 + 5 * 3)wejfwioe"));
	if (err != 2)
		printf("lab2.5\tError[%d] but need 2, res %s", err, out);

	err = lab2(out, 256, "iju34098gu25gug", sizeof("iju34098gu25gug"));
	if (err != 2)
		printf("lab2.6\tError[%d] but need 2, res %s", err, out);

	err = lab2(out, 256, "0", sizeof("0"));
	if (err != 0)
		printf("lab2.7\tError[%d], res %s", err, out);
	if (strcmp("0", out) != 0)
		printf("lab2.7\tError[%d], exp. %s but %s", err, "0", out);

	err = lab2(out, 256, "-1", sizeof("-1"));
	if (err != 0)
		printf("lab2.8\tError[%d], res %s", err, out);
	if (strcmp("-1", out) != 0)
		printf("lab2.8\tError[%d], exp. %s but %s", err, "-1", out);

	err = lab2(out, 256, "2 * -1", sizeof("2 * -1"));
	if (err != 0)
		printf("lab2.9\tError[%d], res %s", err, out);
	if (strcmp("2 -1 *", out) != 0)
		printf("lab2.9\tError[%d], exp. %s but %s", err, "2 -1 *", out);

	err = lab2(out, 256, "2 * -)1", sizeof("2 * -)1"));
	if (err != 2)
		printf("lab2.10\tError[%d] but need 2, res %s", err, out);

	err = lab2(out, 256, "2 * - 1", sizeof("2 * - 1"));
	if (err != 2)
		printf("lab2.11\tError[%d] but need 2, res %s", err, out);


	err = lab2(out, 256, "(10 − 15) * 3", sizeof("(10 − 15) * 3"));
	if (err != 2)
		printf("lab2.11\tError[%d] but need 2, res %s", err, out);

	printf("lab2\tFinish test!\n");
}
#endif

// Вычислить значение арифметической формулы, используя обратную польскую запись.
void lab3(void){}

// Преобразовать трёхмерный массив в одномерный. Реализовать обращение к нему как трёхмерному, используя обратную польскую запись.
void z8(void)
{
	
}

void main(void)
{
#if _DEBUG == 1
	//lab1_test();
	lab2_test();
#endif
	//lab1_interface();
	//lab2_interface();
	UserInterface_Pause("Press any key...");
}