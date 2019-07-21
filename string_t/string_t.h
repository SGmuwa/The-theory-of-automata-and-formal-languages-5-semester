/*
����, ������� �������� � ���� ��������� �����.
�����: ��������� ������ �������� [SG]Muwa https://github.com/SGmuwa
21.07.2019
*/
#pragma once

// �������� ����� ������ �� ����������� �������� "".
#define STRING_STATIC(X) ((string_t){X, sizeof(X)})
// �������� ����� ������� ������ �� ����������� �������� L"".
#define WSTRING_STATIC(X) ((wstring_t){X, sizeof(X)})

/*
������ ������������� ������ ����� �������.
�������������:
string_t name = STRING_STATIC("Jaas");
for(STRING_FOREACH(ch, name))
{
	if(*ch == 'a')
	{
		*ch = 'A';
		break;
	}
}
printf_s("%s", name.first, name.length); // JAas
*/
#define STRING_FOREACHL(I, STR) char * I; I < string_getEnd(STR); I++
/*
������ ������������� ������ ������ ������.
�������������:
string_t name = STRING_STATIC("Jaas");
for(STRING_FOREACHR(ch, name))
{
	if(*ch == 'a')
	{
		*ch = 'A';
		break;
	}
}
printf_s("%s", name.first, name.length); // JaAs
*/
#define STRING_FOREACHR (I, STR) char * I; I < string_getEnd(STR); I--

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

// ����� ������� ������������ ������� ����� ���������.
// string_t input - ������� ������, ����������� ���������� ��������� ��������.
// ���������� ��� ��������� �������.
// ����������: ��������� �� ������ ����������� ������ ����� ��������� input.
inline char * string_getEnd(string_t input)
{
	return input.first + input.length;
}
