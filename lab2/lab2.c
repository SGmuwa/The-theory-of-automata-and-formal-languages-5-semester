#include "..\byte_t\byte_t.h"
#include "..\UserInterface-CLanguage\UserInterface.h"
#include <stdlib.h>
#include "..\stack_t\stack_t.h"
#include "..\string_t\string_t.h"
#include <string.h>
void lab2_interface(void)
{
	string_t input = { (char*) malloc(sizeof(char) * 1024), UserInterface_GetStr("Input arithmetic expression:", input.first, 1024) };
	if (input.first == NULL) return;
	string_t output = { (char*) malloc(input.length * sizeof(char) * 2), input.length * sizeof(char) * 2 };
	int err = lab2(output.first, output.length, input.first, input.length);
	if (err != 0) printf("error %d.\n", err);
	printf("%s", output.first);
	free(input.first);
}

inline byte_t lab2_isParenthesOpen(char in) {
	return in == '(' || in == '[' || in == '{';
}

inline byte_t lab2_isParenthesClose(char in) {
	return in == ')' || in == ']' || in == '}';
}

// Определяет, является ли входной символ скобками.
inline byte_t lab2_isParenthes(char in) {
	return lab2_isParenthesOpen(in) || lab2_isParenthesClose(in);
}

// Определяет, является ли входной символ разделителем.
inline byte_t lab2_isSeparator(char in) {
	return in == ',' || in == '.' || in == ';';
}

// Определяет, принадлежит ли входной символ множеству десятичных цифр.
inline byte_t lab2_is10Number(char in) {
	return '0' <= in && in <= '9';
}

// Пропускает все символы пробела.
// Возвращает: на следующий символ не-пробел. В случае, если пробелы до конца - то указатель на недоступный символ (следующий за доступным).
inline const char * lab2_skipSpace(const char * in, size_t inL) {
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
	for (; i < in + inL; i++)
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
	struct StackMemory stk = Stack_malloc(outL, sizeof(string_t));
	while (inL > 1)
	{ // Пока мы ещё имеем входную строку
		if (outL < 2)
		{ // В выходной строке кончается место!
			if (outL > 0) *out = '\0';
			out++; outL--;
			Stack_free(stk);
			return 1;
		}
		{
			const char * NewIn = lab2_skipSpace(in, inL);
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
		if (countOfFun)
		{ // Ого! Найдена функция!
			Stack_push(&stk, &((string_t) { in, countOfFun }));
			in += countOfFun;
			inL -= countOfFun;
			continue;
		}
		if (lab2_isParenthesOpen(*in))
		{ // Найдена открытая скобка. Что делать?
			Stack_push(&stk, &((string_t) { in, 1 }));
			in += 1;
			inL -= 1;
			continue;
		}
		if (lab2_isParenthesClose(*in))
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

	string_t stk_elm;
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
inline byte_t lab2_isParenthesOpen(char in) {
	return in == '(' || in == '[' || in == '{';
}

inline byte_t lab2_isParenthesClose(char in) {
	return in == ')' || in == ']' || in == '}';
}

// Определяет, является ли входной символ скобками.
inline byte_t lab2_isParenthes(char in) {
	return lab2_isParenthesOpen(in) || lab2_isParenthesClose(in);
}

// Определяет, является ли входной символ разделителем.
inline byte_t lab2_isSeparator(char in) {
	return in == ',' || in == '.' || in == ';';
}

// Определяет, принадлежит ли входной символ множеству десятичных цифр.
inline byte_t lab2_is10Number(char in) {
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
	for (; i < in + inL; i++)
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
	struct StackMemory stk = Stack_malloc(outL, sizeof(string_t));
	while (inL > 1)
	{ // Пока мы ещё имеем входную строку
		if (outL < 2)
		{ // В выходной строке кончается место!
			if (outL > 0) *out = '\0';
			out++; outL--;
			Stack_free(stk);
			return 1;
		}
		{
			const char * NewIn = lab2_skipSpace(in, inL);
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
		if (countOfFun)
		{ // Ого! Найдена функция!
			Stack_push(&stk, &((string_t) { in, countOfFun }));
			in += countOfFun;
			inL -= countOfFun;
			continue;
		}
		if (lab2_isParenthesOpen(*in))
		{ // Найдена открытая скобка. Что делать?
			Stack_push(&stk, &((string_t) { in, 1 }));
			in += 1;
			inL -= 1;
			continue;
		}
		if (lab2_isParenthesClose(*in))
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

	string_t stk_elm;
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

void main(void)
{
	lab2_interface();
}
