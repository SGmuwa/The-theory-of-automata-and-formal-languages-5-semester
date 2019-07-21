#pragma once
#include <stdio.h>
#include <string.h>
#include "lab2.h"

#define LAB2_TEST_OUTPUT_LENGTH

// Тестирование задания lab2.
void lab2_test(void)
{
#ifdef _DEBUG // Запуск тестов в debug версии.
	printf("lab2\tStart test...\n");
	char wefkwio[] = (STRING_CONST_2);
	string_t out = (string_t) {char a[256], 256}; // 256 - не менять.
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
#endif // _DEBUG
}