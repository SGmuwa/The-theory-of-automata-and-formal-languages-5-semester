#pragma once

#define _LAB2_HELP_STR	"� ������� ������ ��������� �������� ���������������\n" \
						"�������������� ������ � �������� �������� ������.\n" \
						"�������������� ���������: +, -, *, /, (, ), [, ], {,\n" \
						"}, ^. ����� �������������� ������������ �����." \
						"�������, � ����� ���������� � ������ ��������� " \
						"�� ��������������."

#include <stdlib.h>
#include "..\stack_t\stack_t.h"
#include "..\string_t\string_t.h"
#include <string.h>
#include "..\byte_t\byte_t.h"

inline byte_t lab2_isParenthesOpen(char in) {
	return in == '(' || in == '[' || in == '{';
}

inline byte_t lab2_isParenthesClose(char in) {
	return in == ')' || in == ']' || in == '}';
}

// ����������, �������� �� ������� ������ ��������.
inline byte_t lab2_isParenthes(char in) {
	return lab2_isParenthesOpen(in) || lab2_isParenthesClose(in);
}

// ����������, �������� �� ������� ������ ������������.
inline byte_t lab2_isSeparator(char in) {
	return in == ',' || in == '.' || in == ';';
}

// ����������, ����������� �� ������� ������ ��������� ���������� ����.
inline byte_t lab2_is10Number(char in) {
	return '0' <= in && in <= '9';
}

// ���������� ��� ������� �������.
// ����������: �� ��������� ������ ��-������.
//				� ������, ���� ������� �� ����� - �� ��������� �� ����������� ������ (��������� �� ���������).
inline const char * lab2_skipSpace(string_t str) {
	if (str.first == NULL) return NULL;
	for (const STRING_FOREACHL(i, str))
		if (*i == ' ')
			continue;
		else return i;
}

/*
// �����������, ���������� �� � ������� ������ �� ������� ��� ��������� ��� ������ ����������� �������.
// const char * in - ��������� �� ������ ������.
// size_t inL - ���������� ��������� �������� ��� ������.
// ����������: 0 - ���� �� ���������� ����������� �������. ����� - ���������� ���������� �������� ��������.
size_t lab2_isPostfixFunction(const char * in, size_t inL)
{
	if (*in == '!')
		for (const char * i = in + 1; i < in + inL; i++)
			if (*i == ' ') continue;
			else return i - in;
	if(inL )
}*/

// ����������, ���������� �� � ������� ������ ���������� ������� ��� ��������.
// string_t input - ������ ������.
// ����������: 0 - ���� �� ���������� ���������� �������. ����� - ���������� ���������� �������� ��������.
size_t lab2_isFunctionOrOperator(string_t input)
{
	const char * i = lab2_skipSpace(input);
	if (lab2_is10Number(*i) || lab2_isParenthes(*i))
		return 0; // it's number or Parentheses!
	for (; i < string_getEnd(input); i++)
	{
		if (lab2_isSeparator(*i)) {
			i++;
			break;
		}
		if (lab2_isParenthes(*i) || *i == ' ' || *i == '\0') {
			break;
		}
	}
	return lab2_skipSpace((string_t) { i, input.length }) - input.first;
}

/*
// �����������, ���������� �� � ������� ������ �� ������� ��� ��������� ��� ������ ����������� �������.
// const char * in - ��������� �� ������ ������.
// size_t inL - ���������� ��������� �������� ��� ������.
// ����������: 0 - ���� �� ���������� ����������� �������. ����� - ���������� ���������� �������� ��������.
size_t lab2_isPostfixFunction(const char * in, size_t inL)
{
	if (*in == '!')
		for (const char * i = in + 1; i < in + inL; i++)
			if (*i == ' ') continue;
			else return i - in;
	if(inL )
}*/

// ������� �������� �������� ������ ��� �������������� �������.
// const string_t output - ���������, ���� ��������� ���������.
//							������ ������ ���� ��� �������� � ������
//							���� ������� ����� ��������� ��������
//							��� ������.
// const string_t input - ��������� ������������� �������������� ������.
// ����������: ��� ������.
//				1 - �� ������� ����� � �������� ������.
//				2 - �� ������ ������� ������.
//				3 - ����������� ������ ��� ����������� �� ����� � �������� ������.
//				4 - �� ������ ������� ������.
int lab2(string_t output, string_t input)
{
	if (output.first == NULL || output.length == 0 || input.first == NULL || input.length == 0)
		return 4;
	const char * oldOut = output.first;
	struct StackMemory stk = Stack_malloc(output.length, sizeof(string_t));
	while (input.length > 1)
	{ // ���� �� ��� ����� ������� ������
		if (output.length < 2)
		{ // � �������� ������ ��������� �����!
			if (output.length > 0) *output.first = '\0';
			output.first++; output.length--;
			Stack_free(stk);
			return 1;
		}
		{
			const char * NewIn = lab2_skipSpace(input);
			input.length = input.length - (NewIn - input.first);
			input.first = NewIn;
			if (input.length > ~(size_t)0 - 1)
			{
				break;
			}
		}
		if (lab2_is10Number(*input.first) /*|| lab2_isPostfixFunction(in + i, inL - i) ��� ������� ��� ���� ����������*/)
		{ // ��� ��������� ���������� �����
			while (lab2_is10Number(*input.first) && input.length > 1 && output.length > 2)
			{
				*output.first = *input.first;
				input.first++; output.first++; output.length--; input.length--;
			}
			if (input.length > 0 && output.length > 2)
			{
				*output.first = ' ';
				input.first++; output.first++; output.length--; input.length--;
			}
		}
		size_t countOfFun = lab2_isFunctionOrOperator(input);
		if (countOfFun)
		{ // ���! ������� �������!
			Stack_push(&stk, &((string_t) { input.first, countOfFun }));
			input.first += countOfFun;
			input.length -= countOfFun;
			continue;
		}
		if (lab2_isParenthesOpen(*input.first))
		{ // ������� �������� ������. ��� ������?
			Stack_push(&stk, &((string_t) { input.first, 1 }));
			input.first += 1;
			input.length -= 1;
			continue;
		}
		if (lab2_isParenthesClose(*input.first))
		{ // ������� �������� ������. ��� ������?
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
					input.first++;
					input.length--;
					break;
				}
				int error;
#ifndef _MSC_VER
				error = memcpy(output.first, stk_elm.first, stk_elm.length) == NULL ? 1 : 0;
#else
				error = memcpy_s(output.first, output.length, stk_elm.first, stk_elm.length);
#endif
				output.first += stk_elm.length;
				output.length -= stk_elm.length;
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
			input.first++;
			input.length--;
			break;
		}
		int error;
#ifndef _MSC_VER
		error = memcpy(output.first, stk_elm.first, stk_elm.length) == NULL ? 1 : 0;
#else
		error = memcpy_s(output.first, output.length, stk_elm.first, stk_elm.length);
#endif
		output.first += stk_elm.length;
		output.length -= stk_elm.length;
		if (error)
		{
			Stack_free(stk);
			return 3;
		}

	}
	if (output.first > oldOut && *(output.first - 1) == ' ')
	{ // delete end space.
		output.first--;
		output.length++;
	}
	if (output.length > 0) *output.first = '\0';
	output.first++; output.length--;
	Stack_free(stk);
	return 0;
}