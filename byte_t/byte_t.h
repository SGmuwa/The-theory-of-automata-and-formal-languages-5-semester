/*
���� ������������ �� ���� ��������, ��� ����� ����.
�����: ��������� ������ �������� [SG]Muwa https://github.com/SGmuwa/
21.07.2019
*/
#pragma once

/*
��� ����� � ������������� unsigned char.
*/
typedef unsigned char byte_t;

/*
��� ������������ ����� ������ � ������� ���� �� ������ ���������.
b0 �������� ����� ������� �����.
b7 �������� ����� ������� �����.
b7 b6 b5 b4 b3 b2 b1 b0
 0  0  0  0  0  0  1  1 = 3
*/
typedef struct
{
	byte_t b0 : 1;
	byte_t b1 : 1;
	byte_t b2 : 1;
	byte_t b3 : 1;
	byte_t b4 : 1;
	byte_t b5 : 1;
	byte_t b6 : 1;
	byte_t b7 : 1;
} byte_bits_t;

/*
������������ �� ���� ������� ���������� � 1 ����, � ������� 8 ���.
����� ������������� ��� � ���� �������� �� 0 �� 255, ��� � ��������� ����
�� b0 �� b7.
*/
typedef union
{
	byte_t value;
	byte_bits_t bit;
} byte_union_t;

#ifdef false
#warning ��������� ������������� false ��� �������.
#else
// ����.
#define false (byte_t)0
#endif // false

#ifdef true
#warning ��������� ������������� true ��� �������.
#else
// ������.
#define true (byte_t)!0
#endif // true
