#pragma once
#include "lab6.h"
#include "..\minctest\minctest.h"
#include "..\string_t\string_t_forTest.h"

// Создаёт функцию тестирования для функции lab6.
#define LAB6_TEST_MAKE_lab6(NUMBER, EXPECT, INPUT, ERROR) void lab6_test ## NUMBER (void)\
{\
	string_t out = string_malloc(256);\
	*out.first = 0;\
	int err = lab6(&out, STRING_STATIC(INPUT));\
	minctest_equal(ERROR, err);\
	if(ERROR == 0 && err == 0) minctest_sequal(EXPECT, out.first);\
	string_free(out);\
}

// Получает имя функции по номеру
#define LAB6_TEST_GETNAME(NUMBER) lab6_test ## NUMBER

LAB6_TEST_MAKE_lab6(0, "5", "5", 0);
LAB6_TEST_MAKE_lab6(1, "5 2 -", "5 - 2", 0);
LAB6_TEST_MAKE_lab6(2, "10 15 - 3 *", "(10 - 15) * 3", 0);
LAB6_TEST_MAKE_lab6(3, "", "", 0);
LAB6_TEST_MAKE_lab6(4, "2 sin", "sin(2)", 0);
LAB6_TEST_MAKE_lab6(5, "1 2 5 3 * + anywhere", "anywhere(1, 2 + 5 * 3)", 0);
LAB6_TEST_MAKE_lab6(6, "1 2 5 3 * + anywhere wejfwioe *", "anywhere(1, 2 + 5 * 3)wejfwioe", 0); // "anywhere(1, 2 + 5 * 3) * wejfwioe"
LAB6_TEST_MAKE_lab6(7, "iju34098gu25gug", "iju34098gu25gug", 0);
LAB6_TEST_MAKE_lab6(8, "0", "0", 0);
LAB6_TEST_MAKE_lab6(9, "-1", "-1", 0);
LAB6_TEST_MAKE_lab6(10, "2 -1 *", "2 * -1", 0);
LAB6_TEST_MAKE_lab6(11, (char*)NULL, "2 * -)1", 2);
LAB6_TEST_MAKE_lab6(12, "2 -1 *", "2 * - 1", 0);
LAB6_TEST_MAKE_lab6(13, "10 15 - 3 *", "(10 - 15) * 3", 0);
LAB6_TEST_MAKE_lab6(14, "2 2 2 ^ ^", "2^2^2", 0);
LAB6_TEST_MAKE_lab6(15, "2 2 2 ^ ^", "2^(2^2)", 0);
LAB6_TEST_MAKE_lab6(16, "2 2 ^ 2 ^", "(2^2)^2", 0);
LAB6_TEST_MAKE_lab6(17, "1 2 3 * +", "1 + 2 * 3", 0); // Тест приоритетов.
LAB6_TEST_MAKE_lab6(18, "1 2 *", "(1)2", 0);
LAB6_TEST_MAKE_lab6(19, "1 2 3 4 ^ ^ ^", "1^2^3^4", 0);
LAB6_TEST_MAKE_lab6(20, "x y ^ 5 z * / 10 +", "x ^ y / (5 * z) + 10", 0);
LAB6_TEST_MAKE_lab6(21, "2 3 - 3 2 + + 6 1 - -", "   (  ( (2-3) + (3+2) )  -  (6 - 1)  )   ", 0);
LAB6_TEST_MAKE_lab6(22, "2 3 - 3 2 + + 6 1 - -", "(((2-3)+(3+2))-(6-1))", 0);
LAB6_TEST_MAKE_lab6(23, "3 2 + 6 1 - -", "(((3+2))-(6-1))", 0);
LAB6_TEST_MAKE_lab6(24, "3 2 + 6 1 - -", "(3+2)-(6-1)", 0);
LAB6_TEST_MAKE_lab6(25, "3 6 -", "((3)-(6))", 0);
LAB6_TEST_MAKE_lab6(26, "3 1 6 + -", "((3)-(1+6))", 0);
LAB6_TEST_MAKE_lab6(27, "1 3 + 6 -", "((1+3)-(6))", 0);
LAB6_TEST_MAKE_lab6(28, "1 2 -", "(((1))-(2))", 0);
LAB6_TEST_MAKE_lab6(29, "5 -3 8 + *", "5 * (-3 + 8)", 0);
LAB6_TEST_MAKE_lab6(30, "1 2 5 3 * + 2 2 2 ^ ^ + anywhere", "anywhere(1, 2 + 5 * 3 + 2^2^2)", 0);
LAB6_TEST_MAKE_lab6(31, "1 2 5 3 * + 2 2 2 ^ ^ + anywhere s *", "anywhere(1, 2 + 5 * 3 + 2^2^2)s", 0);
LAB6_TEST_MAKE_lab6(32, "10 2 + 3 2 * - 3 3.3 / - 2 4 / 2 3 ^ / 2 / +", "10 + 2 - 3 * 2 - 3 / 3.3 + (2 / 4) / 2 ^ 3 / 2", 0);
LAB6_TEST_MAKE_lab6(33, "0.0", "0.0", 0);
LAB6_TEST_MAKE_lab6(34, "2.0 2.00 2.000 ^ ^", "2.0^2.00^2.000", 0);
LAB6_TEST_MAKE_lab6(35, "2 2 pow", "pow(2, 2)", 0);
LAB6_TEST_MAKE_lab6(36, "2 sin", "sin(2)", 0);
LAB6_TEST_MAKE_lab6(37, "1.0 2.00 5.1 3.2 * + 2.3 2.4 2.5 ^ ^ + anywhere s.a *", "anywhere(1.0, 2.00 + 5.1 * 3.2 + 2.3^2.4^2.5)s.a", 0);
LAB6_TEST_MAKE_lab6(38, "a !", "!a", 0);
LAB6_TEST_MAKE_lab6(39, "1.0 ! 2.00 5.1 3.2 * + 2.3 2.4 ~ 2.5 ^ ^ + anywhere ! s.a *", "!anywhere(!1.0, 2.00 + 5.1 * 3.2 + 2.3^~2.4^2.5)s.a", 0);
LAB6_TEST_MAKE_lab6(40, "2 sin 2 *", "sin(2)2", 0);
LAB6_TEST_MAKE_lab6(41, "a ! if_", "if_(!a)", 0);
LAB6_TEST_MAKE_lab6(42, "a ! if_ ~", "~if_(!a)", 0);
LAB6_TEST_MAKE_lab6(43, "a ! b any", "any(!a, b)", 0);
LAB6_TEST_MAKE_lab6(44, "a ! b", "(!a, b)", 0);
LAB6_TEST_MAKE_lab6(45, "a b + !", "!(a + b)", 0);
LAB6_TEST_MAKE_lab6(46, "a b !", "!(a, b)", 0);
LAB6_TEST_MAKE_lab6(47, "a b !", "a, !b", 0);
LAB6_TEST_MAKE_lab6(48, "a b ! as", "as(a, !b)", 0);
LAB6_TEST_MAKE_lab6(49, "q w e r t y u == i o > p >= a < s d >> f g + h j * k / l z x ~ c ! ^ % - << <= != & ^^ | && ||", "q || w && e | r ^^ t & y == u != i > o >= p < a <= s >> d << f + g - h * j / k % l ^ z ~ x ! c", 0);
LAB6_TEST_MAKE_lab6(50, "a b >>", "a >> b", 0);
LAB6_TEST_MAKE_lab6(51, "1.0 ! 2.00 5.1 3.2 * + 2.3 2.4 ~ 2.5 ^ ^ + anywhere ! s.a * q w e r t y u == i o > p >= a < s d >> f g + h j * k / l z x ~ c ! ^ % - << <= != & ^^ | && || +", "(!anywhere(!1.0, 2.00 + 5.1 * 3.2 + 2.3^~2.4^2.5)s.a)+(q || w && e | r ^^ t & y == u != i > o >= p < a <= s >> d << f + g - h * j / k % l ^ z ~ x ! c)", 0);
LAB6_TEST_MAKE_lab6(52, "-1 -2 >", "-1 > -2", 0);
LAB6_TEST_MAKE_lab6(53, "-1 -2 >=", "-1 >= -2", 0);
LAB6_TEST_MAKE_lab6(54, "-1 -2 <=", "-1 <= -2", 0);
LAB6_TEST_MAKE_lab6(55, "-1 -2 <", "-1 < -2", 0);
LAB6_TEST_MAKE_lab6(56, "true 6 if a 3 =", "if(true) {a = 3}", 0); // Переход по лжи!
LAB6_TEST_MAKE_lab6(57, "false 8 if a 3 = 11 goto b 4 = c 5.0 =", "if(false) {a = 3} else {b = 4} c = 5.0", 0);
LAB6_TEST_MAKE_lab6(58, "true 4 if a", "if(true) {a}", 0); // Переход по лжи!
LAB6_TEST_MAKE_lab6(59, "s 6 if A 7 goto B C", "if(s) {A} else {B} C", 0);
LAB6_TEST_MAKE_lab6(60, "a 2 = now a % 0 == 15 if b 1 = 18 goto b 2 = b print",
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
LAB6_TEST_MAKE_lab6(61, "s 6 if A 7 goto B C", "if(s) {A;} else {B;} C;", 0);
LAB6_TEST_MAKE_lab6(62, "test 0 = 1.0 ! 2.00 5.1 3.2 * + 2.3 2.4 ~ 2.5 ^ ^ + anywhere ! s.a * 0 == 30 if test 1 = 33 goto test 2 = test print",
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
LAB6_TEST_MAKE_lab6(63, (char*)NULL, "o0r23o 2i r3i 20ri 10ir 3 13 rij9       j[3[    iri 3ri 329ri", 2);



// Тестирование задания lab6.
void lab6_runTests(void)
{
	void(*tests[])(void) = {
		LAB6_TEST_GETNAME(0),
		LAB6_TEST_GETNAME(1),
		LAB6_TEST_GETNAME(2),
		LAB6_TEST_GETNAME(3),
		LAB6_TEST_GETNAME(4),
		LAB6_TEST_GETNAME(5),
		LAB6_TEST_GETNAME(6),
		LAB6_TEST_GETNAME(7),
		LAB6_TEST_GETNAME(8),
		LAB6_TEST_GETNAME(9),
		LAB6_TEST_GETNAME(10),
		LAB6_TEST_GETNAME(11),
		LAB6_TEST_GETNAME(12),
		LAB6_TEST_GETNAME(13),
		LAB6_TEST_GETNAME(14),
		LAB6_TEST_GETNAME(15),
		LAB6_TEST_GETNAME(16),
		LAB6_TEST_GETNAME(17),
		LAB6_TEST_GETNAME(18),
		LAB6_TEST_GETNAME(19),
		LAB6_TEST_GETNAME(20),
		LAB6_TEST_GETNAME(21),
		LAB6_TEST_GETNAME(22),
		LAB6_TEST_GETNAME(23),
		LAB6_TEST_GETNAME(24),
		LAB6_TEST_GETNAME(25),
		LAB6_TEST_GETNAME(26),
		LAB6_TEST_GETNAME(27),
		LAB6_TEST_GETNAME(28),
		LAB6_TEST_GETNAME(29),
		LAB6_TEST_GETNAME(30),
		LAB6_TEST_GETNAME(31),
		LAB6_TEST_GETNAME(32),
		LAB6_TEST_GETNAME(33),
		LAB6_TEST_GETNAME(34),
		LAB6_TEST_GETNAME(35),
		LAB6_TEST_GETNAME(36),
		LAB6_TEST_GETNAME(37),
		LAB6_TEST_GETNAME(38),
		LAB6_TEST_GETNAME(39),
		LAB6_TEST_GETNAME(40),
		LAB6_TEST_GETNAME(41),
		LAB6_TEST_GETNAME(42),
		LAB6_TEST_GETNAME(43),
		LAB6_TEST_GETNAME(44),
		LAB6_TEST_GETNAME(45),
		LAB6_TEST_GETNAME(46),
		LAB6_TEST_GETNAME(47),
		LAB6_TEST_GETNAME(48),
		LAB6_TEST_GETNAME(49),
		LAB6_TEST_GETNAME(50),
		LAB6_TEST_GETNAME(51),
		LAB6_TEST_GETNAME(52),
		LAB6_TEST_GETNAME(53),
		LAB6_TEST_GETNAME(54),
		LAB6_TEST_GETNAME(55),
		LAB6_TEST_GETNAME(56),
		LAB6_TEST_GETNAME(57),
		LAB6_TEST_GETNAME(58),
		LAB6_TEST_GETNAME(59),
		LAB6_TEST_GETNAME(60),
		LAB6_TEST_GETNAME(61),
		LAB6_TEST_GETNAME(62),
		LAB6_TEST_GETNAME(63)
	};

	char prototypeName[] = "lab6_test ";
	// Нужно выделить так, чтобы любую цифру можно было записать в диапазоне size_t. Это не более 20 символов.
	string_t testName = string_malloc(sizeof(prototypeName) + 20u);
	for (size_t i = 0; i < sizeof(tests) / sizeof(void*); i++)
	{
		sprintf_s(testName.first, testName.length, "%s%zu", prototypeName, i);
		minctest_run(testName.first, tests[i]);
	}
	string_free(testName);
}