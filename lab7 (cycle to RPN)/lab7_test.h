﻿#pragma once
#include "lab7.h"
#include "..\minctest\minctest.h"
#include "..\string_t\string_t_forTest.h"

// Создаёт функцию тестирования для функции lab7.
#define LAB7_TEST_MAKE_lab7(NUMBER, EXPECT, INPUT, ERROR) void lab7_test ## NUMBER (void)\
{\
	string_t out = string_malloc(256);\
	*out.first = 0;\
	int err = lab7(&out, STRING_STATIC(INPUT));\
	minctest_equal(ERROR, err);\
	if(ERROR == 0 && err == 0) minctest_sequal(EXPECT, out.first);\
	string_free(out);\
}

// Получает имя функции по номеру
#define LAB7_TEST_GETNAME(NUMBER) lab7_test ## NUMBER

LAB7_TEST_MAKE_lab7(0, "5", "5", 0);
LAB7_TEST_MAKE_lab7(1, "5 2 -", "5 - 2", 0);
LAB7_TEST_MAKE_lab7(2, "10 15 - 3 *", "(10 - 15) * 3", 0);
LAB7_TEST_MAKE_lab7(3, "", "", 0);
LAB7_TEST_MAKE_lab7(4, "2 sin", "sin(2)", 0);
LAB7_TEST_MAKE_lab7(5, "1 2 5 3 * + anywhere", "anywhere(1, 2 + 5 * 3)", 0);
LAB7_TEST_MAKE_lab7(6, "1 2 5 3 * + anywhere wejfwioe *", "anywhere(1, 2 + 5 * 3)wejfwioe", 0); // "anywhere(1, 2 + 5 * 3) * wejfwioe"
LAB7_TEST_MAKE_lab7(7, "iju34098gu25gug", "iju34098gu25gug", 0);
LAB7_TEST_MAKE_lab7(8, "0", "0", 0);
LAB7_TEST_MAKE_lab7(9, "-1", "-1", 0);
LAB7_TEST_MAKE_lab7(10, "2 -1 *", "2 * -1", 0);
LAB7_TEST_MAKE_lab7(11, (char*)NULL, "2 * -)1", 2);
LAB7_TEST_MAKE_lab7(12, "2 -1 *", "2 * - 1", 0);
LAB7_TEST_MAKE_lab7(13, "10 15 - 3 *", "(10 - 15) * 3", 0);
LAB7_TEST_MAKE_lab7(14, "2 2 2 ^ ^", "2^2^2", 0);
LAB7_TEST_MAKE_lab7(15, "2 2 2 ^ ^", "2^(2^2)", 0);
LAB7_TEST_MAKE_lab7(16, "2 2 ^ 2 ^", "(2^2)^2", 0);
LAB7_TEST_MAKE_lab7(17, "1 2 3 * +", "1 + 2 * 3", 0); // Тест приоритетов.
LAB7_TEST_MAKE_lab7(18, "1 2 *", "(1)2", 0);
LAB7_TEST_MAKE_lab7(19, "1 2 3 4 ^ ^ ^", "1^2^3^4", 0);
LAB7_TEST_MAKE_lab7(20, "x y ^ 5 z * / 10 +", "x ^ y / (5 * z) + 10", 0);
LAB7_TEST_MAKE_lab7(21, "2 3 - 3 2 + + 6 1 - -", "   (  ( (2-3) + (3+2) )  -  (6 - 1)  )   ", 0);
LAB7_TEST_MAKE_lab7(22, "2 3 - 3 2 + + 6 1 - -", "(((2-3)+(3+2))-(6-1))", 0);
LAB7_TEST_MAKE_lab7(23, "3 2 + 6 1 - -", "(((3+2))-(6-1))", 0);
LAB7_TEST_MAKE_lab7(24, "3 2 + 6 1 - -", "(3+2)-(6-1)", 0);
LAB7_TEST_MAKE_lab7(25, "3 6 -", "((3)-(6))", 0);
LAB7_TEST_MAKE_lab7(26, "3 1 6 + -", "((3)-(1+6))", 0);
LAB7_TEST_MAKE_lab7(27, "1 3 + 6 -", "((1+3)-(6))", 0);
LAB7_TEST_MAKE_lab7(28, "1 2 -", "(((1))-(2))", 0);
LAB7_TEST_MAKE_lab7(29, "5 -3 8 + *", "5 * (-3 + 8)", 0);
LAB7_TEST_MAKE_lab7(30, "1 2 5 3 * + 2 2 2 ^ ^ + anywhere", "anywhere(1, 2 + 5 * 3 + 2^2^2)", 0);
LAB7_TEST_MAKE_lab7(31, "1 2 5 3 * + 2 2 2 ^ ^ + anywhere s *", "anywhere(1, 2 + 5 * 3 + 2^2^2)s", 0);
LAB7_TEST_MAKE_lab7(32, "10 2 + 3 2 * - 3 3.3 / - 2 4 / 2 3 ^ / 2 / +", "10 + 2 - 3 * 2 - 3 / 3.3 + (2 / 4) / 2 ^ 3 / 2", 0);
LAB7_TEST_MAKE_lab7(33, "0.0", "0.0", 0);
LAB7_TEST_MAKE_lab7(34, "2.0 2.00 2.000 ^ ^", "2.0^2.00^2.000", 0);
LAB7_TEST_MAKE_lab7(35, "2 2 pow", "pow(2, 2)", 0);
LAB7_TEST_MAKE_lab7(36, "2 sin", "sin(2)", 0);
LAB7_TEST_MAKE_lab7(37, "1.0 2.00 5.1 3.2 * + 2.3 2.4 2.5 ^ ^ + anywhere s.a *", "anywhere(1.0, 2.00 + 5.1 * 3.2 + 2.3^2.4^2.5)s.a", 0);
LAB7_TEST_MAKE_lab7(38, "a !", "!a", 0);
LAB7_TEST_MAKE_lab7(39, "1.0 ! 2.00 5.1 3.2 * + 2.3 2.4 ~ 2.5 ^ ^ + anywhere ! s.a *", "!anywhere(!1.0, 2.00 + 5.1 * 3.2 + 2.3^~2.4^2.5)s.a", 0);
LAB7_TEST_MAKE_lab7(40, "2 sin 2 *", "sin(2)2", 0);
LAB7_TEST_MAKE_lab7(41, "a ! if_", "if_(!a)", 0);
LAB7_TEST_MAKE_lab7(42, "a ! if_ ~", "~if_(!a)", 0);
LAB7_TEST_MAKE_lab7(43, "a ! b any", "any(!a, b)", 0);
LAB7_TEST_MAKE_lab7(44, "a ! b", "(!a, b)", 0);
LAB7_TEST_MAKE_lab7(45, "a b + !", "!(a + b)", 0);
LAB7_TEST_MAKE_lab7(46, "a b !", "!(a, b)", 0);
LAB7_TEST_MAKE_lab7(47, "a b !", "a, !b", 0);
LAB7_TEST_MAKE_lab7(48, "a b ! as", "as(a, !b)", 0);
LAB7_TEST_MAKE_lab7(49, "q w e r t y u == i o > p >= a < s d >> f g + h j * k / l z x ~ c ! ^ % - << <= != & ^^ | && ||", "q || w && e | r ^^ t & y == u != i > o >= p < a <= s >> d << f + g - h * j / k % l ^ z ~ x ! c", 0);
LAB7_TEST_MAKE_lab7(50, "a b >>", "a >> b", 0);
LAB7_TEST_MAKE_lab7(51, "1.0 ! 2.00 5.1 3.2 * + 2.3 2.4 ~ 2.5 ^ ^ + anywhere ! s.a * q w e r t y u == i o > p >= a < s d >> f g + h j * k / l z x ~ c ! ^ % - << <= != & ^^ | && || +", "(!anywhere(!1.0, 2.00 + 5.1 * 3.2 + 2.3^~2.4^2.5)s.a)+(q || w && e | r ^^ t & y == u != i > o >= p < a <= s >> d << f + g - h * j / k % l ^ z ~ x ! c)", 0);
LAB7_TEST_MAKE_lab7(52, "-1 -2 >", "-1 > -2", 0);
LAB7_TEST_MAKE_lab7(53, "-1 -2 >=", "-1 >= -2", 0);
LAB7_TEST_MAKE_lab7(54, "-1 -2 <=", "-1 <= -2", 0);
LAB7_TEST_MAKE_lab7(55, "-1 -2 <", "-1 < -2", 0);
LAB7_TEST_MAKE_lab7(56, "true 6 if a 3 =", "if(true) {a = 3}", 0); // Переход по лжи!
LAB7_TEST_MAKE_lab7(57, "false 8 if a 3 = 11 goto b 4 = c 5.0 =", "if(false) {a = 3} else {b = 4} c = 5.0", 0);
LAB7_TEST_MAKE_lab7(58, "true 4 if a", "if(true) {a}", 0); // Переход по лжи!
LAB7_TEST_MAKE_lab7(59, "s 6 if A 7 goto B C", "if(s) {A} else {B} C", 0);
LAB7_TEST_MAKE_lab7(60, "a 2 = now a % 0 == 15 if b 1 = 18 goto b 2 = b print",
	/*                   0 1 2 3   4 5 6 7  8  9  10111213 14   1516171819    */
	"a = 2;             \n"\
	"if(now() % a == 0) \n"\
	"{                  \n"\
	"    b = 1;         \n"\
	"}                  \n"\
	"else               \n"\
	"{                  \n"\
	"    b = 2;         \n"\
	"}                  \n"\
	"print(b);"         , 0);
LAB7_TEST_MAKE_lab7(61, "s 6 if A 7 goto B C", "if(s) {A;} else {B;} C;", 0);
LAB7_TEST_MAKE_lab7(62, "test 0 = 1.0 ! 2.00 5.1 3.2 * + 2.3 2.4 ~ 2.5 ^ ^ + anywhere ! s.a * 0 == 30 if test 1 = 33 goto test 2 = test print",
	/*                   0    1 2 3   4 5    6   7   8 9 10  11  1213  14151617       1819  202122 23 24 25   262728 29   30   313233   34*/
	"test = 0;                                                    \n"\
	"if(!anywhere(!1.0, 2.00 + 5.1 * 3.2 + 2.3^~2.4^2.5)s.a == 0) \n"\
	"{                                                            \n"\
	"    test = 1;                                                \n"\
	"}                                                            \n"\
	"else                                                         \n"\
	"{                                                            \n"\
	"    test = 2;                                                \n"\
	"}                                                            \n"\
	"print(test);                                                   "
	, 0);
LAB7_TEST_MAKE_lab7(63, "3 iri3ri329ri [ [ o0r23o2ir3i20ri10ir313rij9j", "o0r23o 2i r3i 20ri 10ir 3 13 rij9       j[3[    iri 3ri 329ri", 0);
LAB7_TEST_MAKE_lab7(64, "test 0 = 1.0 ! 2.00 5.1 3.2 * + 2.3 2.4 ~ 2.5 ^ ^ + anywhere ! s.a * 0 == 30 if test 1 = 33 goto test 2 = test print",
	/*                   0    1 2 3   4 5    6   7   8 9 10  11  1213  14151617       1819  202122 23 24 25   262728 29   30   313233   34*/
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
	"for(s = 0; s < 4; s = s + 1)                                 \n"\
	"{                                                            \n"\
	"    print(s);                                                \n"\
	"}                                                            \n"\
	"while(s > 0)                                                 \n"\
	"{                                                            \n"\
	"    s = s - 1;                                               \n"\
	"    print(s);                                                \n"\
	"}                                                            \n"\
	"do                                                           \n"\
	"{                                                            \n"\
	"    s = s + 1;                                               \n"\
	"    print(s);                                                \n"\
	"} while(s < 4);                                              \n"\
	"print(s);                                                    \n"\
	""
	, 0);



// Тестирование задания lab7.
void lab7_runTests(void)
{
	void(*tests[])(void) = {
		LAB7_TEST_GETNAME(0),
		LAB7_TEST_GETNAME(1),
		LAB7_TEST_GETNAME(2),
		LAB7_TEST_GETNAME(3),
		LAB7_TEST_GETNAME(4),
		LAB7_TEST_GETNAME(5),
		LAB7_TEST_GETNAME(6),
		LAB7_TEST_GETNAME(7),
		LAB7_TEST_GETNAME(8),
		LAB7_TEST_GETNAME(9),
		LAB7_TEST_GETNAME(10),
		LAB7_TEST_GETNAME(11),
		LAB7_TEST_GETNAME(12),
		LAB7_TEST_GETNAME(13),
		LAB7_TEST_GETNAME(14),
		LAB7_TEST_GETNAME(15),
		LAB7_TEST_GETNAME(16),
		LAB7_TEST_GETNAME(17),
		LAB7_TEST_GETNAME(18),
		LAB7_TEST_GETNAME(19),
		LAB7_TEST_GETNAME(20),
		LAB7_TEST_GETNAME(21),
		LAB7_TEST_GETNAME(22),
		LAB7_TEST_GETNAME(23),
		LAB7_TEST_GETNAME(24),
		LAB7_TEST_GETNAME(25),
		LAB7_TEST_GETNAME(26),
		LAB7_TEST_GETNAME(27),
		LAB7_TEST_GETNAME(28),
		LAB7_TEST_GETNAME(29),
		LAB7_TEST_GETNAME(30),
		LAB7_TEST_GETNAME(31),
		LAB7_TEST_GETNAME(32),
		LAB7_TEST_GETNAME(33),
		LAB7_TEST_GETNAME(34),
		LAB7_TEST_GETNAME(35),
		LAB7_TEST_GETNAME(36),
		LAB7_TEST_GETNAME(37),
		LAB7_TEST_GETNAME(38),
		LAB7_TEST_GETNAME(39),
		LAB7_TEST_GETNAME(40),
		LAB7_TEST_GETNAME(41),
		LAB7_TEST_GETNAME(42),
		LAB7_TEST_GETNAME(43),
		LAB7_TEST_GETNAME(44),
		LAB7_TEST_GETNAME(45),
		LAB7_TEST_GETNAME(46),
		LAB7_TEST_GETNAME(47),
		LAB7_TEST_GETNAME(48),
		LAB7_TEST_GETNAME(49),
		LAB7_TEST_GETNAME(50),
		LAB7_TEST_GETNAME(51),
		LAB7_TEST_GETNAME(52),
		LAB7_TEST_GETNAME(53),
		LAB7_TEST_GETNAME(54),
		LAB7_TEST_GETNAME(55),
		LAB7_TEST_GETNAME(56),
		LAB7_TEST_GETNAME(57),
		LAB7_TEST_GETNAME(58),
		LAB7_TEST_GETNAME(59),
		LAB7_TEST_GETNAME(60),
		LAB7_TEST_GETNAME(61),
		LAB7_TEST_GETNAME(62),
		LAB7_TEST_GETNAME(63)
	};

	char prototypeName[] = "lab7_test ";
	// Нужно выделить так, чтобы любую цифру можно было записать в диапазоне size_t. Это не более 20 символов.
	string_t testName = string_malloc(sizeof(prototypeName) + 20u);
	for (size_t i = 0; i < sizeof(tests) / sizeof(void*); i++)
	{
		sprintf_s(testName.first, testName.length, "%s%zu", prototypeName, i);
		minctest_run(testName.first, tests[i]);
	}
	string_free(testName);
}