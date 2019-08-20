#pragma once
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
LAB7_TEST_MAKE_lab7(63, "3 iri3ri329ri o0r23o2ir3i20ri10ir313rij9j", "o0r23o 2i r3i 20ri 10ir 3 13 rij9       j[3[    iri 3ri 329ri", 0);
LAB7_TEST_MAKE_lab7(64, "test 0 = 1.0 ! 2.00 5.1 3.2 * + 2.3 2.4 ~ 2.5 ^ ^ + anywhere ! s.a * 0 == 52 if test 1 = now 2 % 0 == 50 if now print now 2 % 0 == 48 if now print 50 goto 3.14 print 55 goto test 2 = test print",
	/*                   0    1 2 3   4 5    6   7   8 9 10  11  1213  14151617       1819  202122 23 24 25   2627                                                                             28 29   30   313233   34*/
	/*                   0    1 2 3   4 5    6   7   8 9 10  11  1213  14151617       1819  202122 23 24 25   262728  29303132 33 34 35  36    37  38394041 42 43 44  45    46 47   48   49    50 51   52   535455   56*/
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
	/*                      */ ""
	, 0);
LAB7_TEST_MAKE_lab7(65, "now print", "print(now());", 0);
LAB7_TEST_MAKE_lab7(66, "a 14 if AA0 aa 10 if AA 11 goto BB AA1 16 goto BB0 BB1 end",
	/*                   0 1  2  3   4  5  6  7  8  9    10 11  12 13   14  15  16*/
	"if(a){AA0();if(aa){AA();}else{BB();}AA1();}else{BB0();BB1();}end();", 0);
LAB7_TEST_MAKE_lab7(67, "a 11 if AA0 aa 8 if AA AA1 13 goto BB0 BB1 end",
	/*                   0 1  2  3   4  5 6  7  8   9  10   11  12  13*/
	"if(a){AA0();if(aa){AA();}AA1();}else{BB0();BB1();}end();", 0);
LAB7_TEST_MAKE_lab7(68, "body1 if1 18 if body1.1 if1.1 16 if body1.1.1 if1.1.1 15 if body1.1.1.1 16 goto body1.1.1.2 19 goto body1.2 body2",
	/*                   0     1   2  3  4       5     6  7  8         9       10 11 12          13 14   15          16 17   18      19*/
	/* 0        */ "body1;                        \n" /* body1         */ \
	/* 1 2 3    */ "if(if1){                      \n" /* if1 18 if     */ \
	/* 4        */ "    body1.1;                  \n" /* body1.1       */ \
	/* 5 6 7    */ "    if(if1.1){                \n" /* if1.1 16 if   */ \
	/* 8        */ "		body1.1.1;            \n" /* body1.1.1     */ \
	/* 9 10 11  */ "		if(if1.1.1){          \n" /* if1.1.1 15 if */ \
	/* 12       */ "			body1.1.1.1;      \n" /* body1.1.1.1   */ \
	/* 13 14    */ "		}                     \n" /* 16 goto       */ \
	/* 15       */ "		else { body1.1.1.2; } \n" /* body1.1.1.2   */ \
	/*          */ "    }                         \n" /*               */ \
	/* 16 17    */ "}                             \n" /* 19 goto       */ \
	/* 18       */ "else { body1.2; }             \n" /* body1.2       */ \
	/* 19       */ "body2;                        \n" /* body2         */ \
	/*          */ ""
	, 0);
LAB7_TEST_MAKE_lab7(69, "a 13 if b 11 if c 11 if 11 goto 13 goto",
	/*                   0 1  2  3 4  5  6 7  8  9  10   11 12  */
	/* 0 1 2 */     "if(a){                  \n" /* a 13 if */\
	/* 3 4 5 */     "    if(b){              \n" /* b 11 if */\
	/* 6 7 8 */     "		if(c){           \n" /* c 11 if */\
	/* 9 10  */     "		} else{}         \n" /* 11 goto */\
	/*       */     "    }                   \n" /*         */\
	/* 11 12 */     "} else {}               \n" /* 13 goto */\
	/* 13    */     ""
	, 0);
LAB7_TEST_MAKE_lab7(70, "a 5 if 5 goto", 
	/*0 1 2*/"  if(a){ \n" /* a 5 if */\
	/*3 4  */"    }    \n" /* 5 goto */\
	/*5    */"else{}   \n"\
	"", 0);
LAB7_TEST_MAKE_lab7(71, "a 8 if b 6 if 8 goto",
	/*0 1 2*/ "if(a){   \n" /* a 8 if  */\
	/*3 4 5*/ " if(b){} \n" /* b 6 if  */\
	/*6 7  */ "} else{} \n" /* 8 goto  */\
	/*8    */ "         \n" /*         */\
	"", 0);
LAB7_TEST_MAKE_lab7(72, "a 6 if b 6 if",
	/*0 1 2*/ "if(a){   \n" /* a 6 if  */\
	/*3 4 5*/ " if(b){} \n" /* b 6 if  */\
	/*6    */ "}        \n" /*         */\
	"", 0);
LAB7_TEST_MAKE_lab7(73, "test 0 = 1.0 ! 2.00 5.1 3.2 * + 2.3 2.4 ~ 2.5 ^ ^ + anywhere ! s.a * 0 == 30 if test 1 = 33 goto test 2 = test print ...? TODO",
	/*                   0    1 2 3   4 5    6   7   8 9 10  11  1213  14151617       1819  202122 23 24 25   262728 29   30   313233   34*/
	/*                                              */"test = 0;                                                    \n" /* test 0 =                                                               */\
	/*                                              */"if(!anywhere(!1.0, 2.00 + 5.1 * 3.2 + 2.3^~2.4^2.5)s.a == 0) \n" /* 1.0 ! 2.00 5.1 3.2 * + 2.3 2.4 ~ 2.5 ^ ^ + anywhere ! s.a * 0 == 30 if */\
	/*                                              */"{                                                            \n" /*                                                                        */\
	/*                                              */"    test = 1;                                                \n" /* test 1 =                                                               */\
	/*                                              */"}                                                            \n" /* 33 goto                                                                */\
	/*                                              */"else                                                         \n" /*                                                                        */\
	/*                                              */"{                                                            \n" /*                                                                        */\
	/*                                              */"    test = 2;                                                \n" /* test 2 =                                                               */\
	/*                                              */"}                                                            \n" /*                                                                        */\
	/* 33 34                                        */"print(test);                                                 \n" /* test print                                                             */\
	/* 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 */"for(s = 0; s < 4; s = s + 1)                                 \n" /* s 0 = 45 goto s s 1 + = s 4 < 54 if                                    */\
	/*                                              */"{                                                            \n" /*                                                                        */\
	/* 50 51                                        */"    print(s);                                                \n" /* s print                                                                */\
	/* 52 53                                        */"}                                                            \n" /* 40 goto                                                                */\
	/* 54 55 56 57 58                               */"while(s > 0)                                                 \n" /* s 0 > 66 if                                                            */\
	/*                                              */"{                                                            \n" /*                                                                        */\
	/* 59 60 61 62 63                               */"    s = s - 1;                                               \n" /* s s 1 - =                                                              */\
	/* 64 65                                        */"    print(s);                                                \n" /* s print                                                                */\
	/*                                              */"}                                                            \n" /*                                                                        */\
	/*                                              */"do                                                           \n" /*                                                                        */\
	/*                                              */"{                                                            \n" /*                                                                        */\
	/* 66 67 68 69 70                               */"    s = s + 1;                                               \n" /* s s 1 + =                                                              */\
	/* 71 72                                        */"    print(s);                                                \n" /* s print                                                                */\
	/* 73 74 75 76 77 78                            */"} while(s < 4);                                              \n" /* s 4 < ! 66 if                                                          */\
	/* 79 80                                        */"print(s);                                                    \n" /* s print                                                                */\
	""
	, 0);
LAB7_TEST_MAKE_lab7(74, "s 0 = 10 goto s s 1 + = s 4 < 19 if s print 5 goto s 0 > 31 if s s 1 - = s print s s 1 + = s print s 4 < ! 31 if s print",
	/* 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 */"for(s = 0; s < 4; s = s + 1)\n" /* s 0 = 10 goto s s 1 + = s 4 < 19 if */\
	/*                                    */"{                           \n" /*                                     */\
	/* 15 16                              */"    print(s);               \n" /* s print                             */\
	/* 17 18                              */"}                           \n" /* 5 goto                              */\
	/* 19 20 21 22 23                     */"while(s > 0)                \n" /* s 0 > 31 if                         */\
	/*                                    */"{                           \n" /*                                     */\
	/* 24 25 26 27 28                     */"    s = s - 1;              \n" /* s s 1 - =                           */\
	/* 29 30                              */"    print(s);               \n" /* s print                             */\
	/*                                    */"}                           \n" /*                                     */\
	/*                                    */"do                          \n" /*                                     */\
	/*                                    */"{                           \n" /*                                     */\
	/* 31 32 33 34 35                     */"    s = s + 1;              \n" /* s s 1 + =                           */\
	/* 36 37                              */"    print(s);               \n" /* s print                             */\
	/* 38 39 40 41 42 43                  */"} while(s < 4);             \n" /* s 4 < ! 31 if                       */\
	/* 44 45                              */"print(s);                   \n" /* s print                             */\
	""
	, 0);
LAB7_TEST_MAKE_lab7(75, "s 0 = 10 goto s s 1 + = s 4 < 19 if s print 5 goto",
	/* 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 */"for(s = 0; s < 4; s = s + 1)\n" /* s 0 = 10 goto s s 1 + = s 4 < 19 if */\
	/*                                    */"{                           \n"\
	/* 15 16                              */"    print(s);               \n" /* s print */\
	/* 17 18                              */"}                           \n" /* 5 goto */\
	""
	, 0);
LAB7_TEST_MAKE_lab7(76, "s 0 > 12 if s s 1 - = s print",
	/* 0 1 2 3 4 */"while(s > 0)   \n" /* s 0 > 12 if */\
	/*           */"{              \n"\
	/* 5 6 7 8 9 */"    s = s - 1; \n" /* s s 1 - = */\
	/* 10 11     */"    print(s);  \n" /* s print */\
	/* 12        */"}              \n"\
	""
	, 0);
LAB7_TEST_MAKE_lab7(77, "s s 1 + = s print s 4 < ! 0 if",
	/*                 */"do {            \n"\
	/* 0 1 2 3 4       */"    s = s + 1;  \n" /* s s 1 + = */\
	/* 5 6             */"    print(s);   \n" /* s print */\
	/* 7 8 9 10 11 12  */"} while(s < 4); \n" /* s 4 < ! 0 if */\
	""
	, 0);
LAB7_TEST_MAKE_lab7(78, "n 0 = n n 1 + = n print n 4 < ! 3 if s s 1 + = s print s 4 < ! 0 if",
	/*                   */"do {                 \n"\
	/* 0 1 2             */"    n = 0            \n" /* n 0 = */\
	/*                   */"    do{              \n"\
	/* 3 4 5 6 7         */"        n = n + 1;   \n" /* n n 1 + = */\
	/* 8 9               */"        print(n);    \n" /* n print */\
	/* 10 11 12 13 14 15 */"    } while(n < 4);  \n" /* n 4 < ! 3 if */\
	/* 16 17 18 19 20    */"    s = s + 1;       \n" /* s s 1 + = */ \
	/* 21 22             */"    print(s);        \n" /* s print */\
	/* 23 24 25 26 27 28 */"} while(s < 4);      \n" /* s 4 < ! 0 if */\
	""
	, 0);
LAB7_TEST_MAKE_lab7(79, "s 4 = s 0 > 29 if n 4 = n 0 > 23 if n n 1 - = n print s s 1 - = s print",
	/* 0 1 2          */"s = 4;             \n" /* s 4 =       */\
	/* 3 4 5 6 7      */"while(s > 0) {     \n" /* s 0 > 29 if */\
	/* 8 9 10         */"    n = 4;         \n" /* n 4 =       */\
	/* 11 12 13 14 15 */"    while(n > 0) { \n" /* n 0 > 23 if */\
	/* 16 17 18 19 20 */"        n = n - 1; \n" /* n n 1 - =   */\
	/* 21 22          */"        print(n);  \n" /* n print     */\
	/*                */"    }              \n" /*             */\
	/* 23 24 25 26 27 */"    s = s - 1;     \n" /* s s 1 - =   */\
	/* 28 29          */"    print(s);      \n" /* s print     */\
	/*                */"}                  \n" /*             */\
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
		LAB7_TEST_GETNAME(63),
		LAB7_TEST_GETNAME(64),
		LAB7_TEST_GETNAME(65),
		LAB7_TEST_GETNAME(66),
		LAB7_TEST_GETNAME(67),
		LAB7_TEST_GETNAME(68),
		LAB7_TEST_GETNAME(69),
		LAB7_TEST_GETNAME(70),
		LAB7_TEST_GETNAME(71),
		LAB7_TEST_GETNAME(72),
		LAB7_TEST_GETNAME(73),
		LAB7_TEST_GETNAME(74),
		LAB7_TEST_GETNAME(75),
		LAB7_TEST_GETNAME(76),
		LAB7_TEST_GETNAME(77),
		LAB7_TEST_GETNAME(78),
		LAB7_TEST_GETNAME(79)
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