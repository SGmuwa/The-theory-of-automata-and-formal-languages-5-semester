/*
����, ������� �������� � ���� ��������� �����.
�����: ��������� ������ �������� [SG]Muwa https://github.com/SGmuwa
21.07.2019
*/
#pragma once
// ������������ ����� ��� ������: ������ ��������. char * first, size_t length.
typedef struct {
	// ��������� �� ������ ������ ������.
	char * first;
	// ���������� ��������� �������� ������.
	size_t length;
} string_t;

// ������������ ����� ��� ������: ������ ������� ��������. wchar_t * first, size_t length.
typedef struct {
	// ��������� �� ������ ������ ������.
	wchar_t * first;
	// ���������� ��������� �������� ������.
	size_t length;
} wstring_t;
