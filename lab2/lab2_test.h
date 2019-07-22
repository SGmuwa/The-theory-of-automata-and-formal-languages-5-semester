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
	string_t out = string_malloc(256);
	int err = 0;

	err = lab2(out, STRING_STATIC("5"));
	if (err != 0)
		printf_s("lab2.0\tError[%d], res %s", err, out.first);
	if (strcmp("5", out.first) != 0)
		printf("lab2.0\tError[%d], exp. %s but %s", err, "5", out.first);

	err = lab2(out, STRING_STATIC("5 - 2"));
	if (err != 0)
		printf("lab2.0.5\tError[%d], res %s", err, out.first);
	if (strcmp("5 2 -", out.first) != 0)
		printf("lab2.0.5\tError[%d], exp. %s but %s", err, "5 2 -", out.first);

	err = lab2(out, STRING_STATIC("(10 - 15) * 3"));
	if (err != 0)
		printf("lab2.1\tError[%d], res %s", err, out.first);
	if (strcmp("10 15 - 3 *", out.first) != 0)
		printf("lab2.1\tError[%d], exp. %s but %s", err, "10 15 - 3 *", out.first);

	err = lab2(out, STRING_STATIC(""));
	if (err != 0)
		printf("lab2.2\tError[%d], res %s", err, out.first);
	if (strcmp("", out.first) != 0)
		printf("lab2.2\tError[%d], exp. %s but %s", err, "", out.first);

	err = lab2(out, STRING_STATIC("sin(2)"));
	if (err != 0)
		printf("lab2.3\tError[%d], res %s", err, out.first);
	if (strcmp("2 sin", out.first) != 0)
		printf("lab2.3\tError[%d], exp. %s but %s", err, "2 sin", out.first);

	err = lab2(out, STRING_STATIC("anywhere(1, 2 + 5 * 3)"));
	if (err != 0)
		printf("lab2.4\tError[%d], res %s", err, out.first);
	if (strcmp("1 2 3 5 * + anywhere", out.first) != 0)
		printf("lab2.4\tError[%d], exp. %s but %s", err, "1 2 3 5 * + anywhere", out.first);

	err = lab2(out, STRING_STATIC("anywhere(1, 2 + 5 * 3)wejfwioe"));
	if (err != 2)
		printf("lab2.5\tError[%d] but need 2, res %s", err, out.first);

	err = lab2(out, STRING_STATIC("iju34098gu25gug"));
	if (err != 2)
		printf("lab2.6\tError[%d] but need 2, res %s", err, out.first);

	err = lab2(out, STRING_STATIC("0"));
	if (err != 0)
		printf("lab2.7\tError[%d], res %s", err, out.first);
	if (strcmp("0", out.first) != 0)
		printf("lab2.7\tError[%d], exp. %s but %s", err, "0", out.first);

	err = lab2(out, STRING_STATIC("-1"));
	if (err != 0)
		printf("lab2.8\tError[%d], res %s", err, out.first);
	if (strcmp("-1", out.first) != 0)
		printf("lab2.8\tError[%d], exp. %s but %s", err, "-1", out.first);

	err = lab2(out, STRING_STATIC("2 * -1"));
	if (err != 0)
		printf("lab2.9\tError[%d], res %s", err, out.first);
	if (strcmp("2 -1 *", out.first) != 0)
		printf("lab2.9\tError[%d], exp. %s but %s", err, "2 -1 *", out.first);

	err = lab2(out, STRING_STATIC("2 * -)1"));
	if (err != 2)
		printf("lab2.10\tError[%d] but need 2, res %s", err, out.first);

	err = lab2(out, STRING_STATIC("2 * - 1"));
	if (err != 2)
		printf("lab2.11\tError[%d] but need 2, res %s", err, out.first);


	err = lab2(out, STRING_STATIC("(10 − 15) * 3"));
	if (err != 2)
		printf("lab2.11\tError[%d] but need 2, res %s", err, out.first);

	string_free(out);
	printf("lab2\tFinish test!\n");
#endif // _DEBUG
}