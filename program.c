#include "UserInterface.h"
#include <stdlib.h>
#if _DEBUG == 1
	#include <string.h>
#endif

#define false 0
#define true !0

// Создать обратную польскую запись для логической формулы.
void z4(void){}
// Вычислить значение логической формулы, используя обратную польскую запись.
void z5(void){}
// Создать обратную польскую запись для условного оператора.
void z6(void){}
// Создать обратную польскую запись для оператора цикла.
void z7(void){}
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
int z1(double * output, const char * input, size_t length)
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
void z1_interface(void)
{
	char input[256];
	size_t length = UserInterface_GetStr("Input number in decimal format: ", input, sizeof(input) / sizeof(char));
	double output = 0;
	int err;
	switch (err = z1(&output, input, length))
	{
	case 0:
		printf("Number: %lf\n", output);
		break;
	default:
		printf("Error %d\n", err);
		break;
	}
}

#if _DEBUG == 1
void z1_test(void)
{
	printf("z1:\tTest start.\n");
	double output = 0;
	double * o = &output;
	int err = 0;
	if((err = z1(o, "0", sizeof("0"))) != 0 || output != 0) printf("z1:\tError[%d]: 0 but %lf\n", err, output);
	if ((err = z1(o, "1", sizeof("1"))) != 0 || output != 1) printf("z1:\tError[%d]: 1 but %lf\n", err, output);
	if ((err = z1(o, "123", sizeof("123"))) != 0 || output != 123) printf("z1:\tError[%d]: 123 but %lf\n", err, output);
	if ((err = z1(o, "123.123", sizeof("123.123"))) != 0 || output != 123.123) printf("z1:\tError[%d]: 123 but %lf\n", err, output);
	if ((err = z1(o, "", sizeof(""))) != 1) printf("z1:\tError[%d] but need err 1. res? %lf\n", err, output);
	if ((err = z1(o, "123.1a23", sizeof("123.1a23"))) != 2) printf("z1:\tError[%d] but need err 2. res? %lf\n", err, output);
	if ((err = z1(o, "123..123", sizeof("123..123"))) != 3) printf("z1:\tError[%d] but need err 3. res? %lf\n", err, output);
	if ((err = z1(o, ".123", sizeof(".123"))) != 4) printf("z1:\tError[%d] but need err 4. res? %lf\n", err, output);
	if ((err = z1(NULL, "123", sizeof("123"))) != 5) printf("z1:\tError[%d] but need err 5. res? %lf\n", err, output);
	if ((err = z1(o, NULL, 12)) != 5) printf("z1:\tError[%d] but need err 5. res? %lf\n", err, output);
	if ((err = z1(o, "0123456789.0123456789", sizeof("0123456789.0123456789"))) != 0 || output != 0123456789.0123456789) printf("z1:\tError[%d]: 0123456789.0123456789 but %lf\n", err, output);
	if ((err = z1(o, "-0123456789.0123456789", sizeof("-0123456789.0123456789"))) != 0 || output != -0123456789.0123456789) printf("z1:\tError[%d]: -0123456789.0123456789 but %lf\n", err, output);
	if ((err = z1(o, "-123456789.0123456789", sizeof("-123456789.0123456789"))) != 0 || output != -123456789.0123456789) printf("z1:\tError[%d]: -123456789.0123456789 but %lf\n", err, output);
	if ((err = z1(o, "-", sizeof("-"))) != 1) printf("z1:\tError[%d] but need 1. res? %lf\n", err, output);
	if ((err = z1(o, "-.1", sizeof("-.1"))) != 6) printf("z1:\tError[%d] but need 6. res? %lf\n", err, output);
	printf("z1:\tTest end.\n");
}
#endif

// Определяет, содержится ли в входной строке до пробела или скобки оператор.
// const char * in - укащатель на начало поиска.
// size_t inL - количество доступных символов для поиска.
// Возвращает: 0 - если не содержится оператор. Иначе - количество занимаемых символов функцией.
size_t z2_isOperator(const char * in, size_t inL)
{
	if(in == NULL || inL < 1)
		return 0;
	size_t i = 0;
	for(; in[i] == ' ' && i < inL; i++);
	if(i == inL)
		return 0;
	if(in[i] == '+' || in[i] == '-' || in[i] == '*' || in[i] == '/' || in[i] == '^' || in[i] == '|' || in[i] == '&' || in[i] == '=' || in[i] == '%' || in[i] == '>' || in[i] == '>')
		return i + 1;

/*
+
-
/
*
%
==
!=
>
<
>=
<=
!a
&&
||
~a
&
|
^
<<
>>
+=
-=
*=
/=
%=
&=
|=
^=
<<=
>>=
a[b]
*a
&b
->
.
->*
.*

*/
}

// Опредеоляет, содержится ли в входной строке до пробела или оператора или скобки постфиксная функция.
// const char * in - указатель на начало поиска.
// size_t inL - количество доступных символов для поиска.
// Возвращает: 0 - если не содержится постфиксная функция. Иначе - количество занимаемых символов функцией.
size_t z2_isPostfixFunction(const char * in, size_t inL)
{
	
}

// Определяет, содержится ли в входной строке префиксная функция.
// const char * in - указатель на начало поиска.
// size_t inL - количество доступных символов для поиска.
// Возвращает: 0 - если не содержится префиксная функция. Иначе - количество занимаемых символов функцией.
size_t z2_isPrefixFunction(const char * in, size_t inL)
{

}

// Создать обратную польскую запись для арифметической формулы.
// char * out - указатель, куда поместить результат.
// size_t outL - количество доступных для записи элементов.
// const char * in - указатель, откуда брать арифметическую запись.
// size_t inL - количество доступных для чтения арифметической записи символов.
// Возвращает: код ошибки.
// 1 - Не хватило место в выходной строке.
// 2 - Не верный входной формат.
int z2(char * out, size_t outL, const char * in, size_t inL)
{
	char * stack = (char*) malloc((inL + 1)*sizeof(char));
	char buffer;
	size_t outI = 0; // Индекс, который указывает местоположение в выходной строке.
	for(size_t i = 0; i < inL; i++)
	{
		if(outI == outL - 2 || outL < 2)
		{
			if(outL > 0) out[outI++] = '\0';
			return 1;
		}
		buffer = in[i];
		if((buffer >= '0' && buffer <= '9') || z2_isPostfixFunction(in + i, inL - i))
		{
			out[outI++] = buffer;
		}
		else if(z2_isPrefixFunction(in + i, inL - i))
		{
			
		}
	}
	free(stack);
}

#if _DEBUG == 1
// Тестирование задания z2.
void z2_test(void)
{
	printf("z2\tStart test...\n");
	char out[256] = ""; // 256 - не менять.
	int err = 0;

	err = z2(out, 256, "(10 − 15) * 3", sizeof("(10 − 15) * 3"));
	if (err != 0)
		printf("z2.1\tError[%d], res %256s", err, out);
	if (strcmp("10 15 − 3 *", out) != 0)
		printf("z2.1\tError[%d], exp. %s but %256s", "10 15 − 3 *", out);

	err = z2(out, 256, "", sizeof(""));
	if (err != 0)
		printf("z2.2\tError[%d], res %256s", err, out);
	if (strcmp("", out) != 0)
		printf("z2.2\tError[%d], exp. %s but %256s", "", out);

	err = z2(out, 256, "sin(2)", sizeof("sin(2)"));
	if (err != 0)
		printf("z2.3\tError[%d], res %256s", err, out);
	if (strcmp("2 sin", out) != 0)
		printf("z2.3\tError[%d], exp. %s but %256s", "2 sin", out);

	err = z2(out, 256, "anywhere(1, 2 + 5 * 3)", sizeof("anywhere(1, 2 + 5 * 3)"));
	if (err != 0)
		printf("z2.4\tError[%d], res %256s", err, out);
	if (strcmp("1 2 3 5 * + anywhere", out) != 0)
		printf("z2.4\tError[%d], exp. %s but %256s", "1 2 3 5 * + anywhere", out);

	err = z2(out, 256, "anywhere(1, 2 + 5 * 3)wejfwioe", sizeof("anywhere(1, 2 + 5 * 3)wejfwioe"));
	if (err != 2)
		printf("z2.5\tError[%d] but need 2, res %256s", err, out);

	err = z2(out, 256, "iju34098gu25gug", sizeof("iju34098gu25gug"));
	if (err != 2)
		printf("z2.6\tError[%d] but need 2, res %256s", err, out);

	err = z2(out, 256, "0", sizeof("0"));
	if (err != 0)
		printf("z2.7\tError[%d], res %256s", err, out);
	if (strcmp("0", out) != 0)
		printf("z2.7\tError[%d], exp. %s but %256s", "0", out);

	err = z2(out, 256, "-1", sizeof("-1"));
	if (err != 0)
		printf("z2.8\tError[%d], res %256s", err, out);
	if (strcmp("-1", out) != 0)
		printf("z2.8\tError[%d], exp. %s but %256s", "-1", out);

	err = z2(out, 256, "2 * -1", sizeof("2 * -1"));
	if (err != 0)
		printf("z2.9\tError[%d], res %256s", err, out);
	if (strcmp("2 -1 *", out) != 0)
		printf("z2.9\tError[%d], exp. %s but %256s", "2 -1 *", out);

	err = z2(out, 256, "2 * -)1", sizeof("2 * -)1"));
	if (err != 2)
		printf("z2.10\tError[%d] but need 2, res %256s", err, out);

	err = z2(out, 256, "2 * - 1", sizeof("2 * - 1"));
	if (err != 2)
		printf("z2.11\tError[%d] but need 2, res %256s", err, out);

	printf("z2\tFinish test!\n");
}
#endif

// Вычислить значение арифметической формулы, используя обратную польскую запись.
void z3(void){}

// Преобразовать трёхмерный массив в одномерный. Реализовать обращение к нему как трёхмерному, используя обратную польскую запись.
void z8(void)
{
	
}

void main(void)
{
#if _DEBUG == 1
	z1_test();
#endif
	z1_interface();
	UserInterface_Pause("Press any key...");
}