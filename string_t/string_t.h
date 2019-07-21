/*
Файл, который содержит в себе типизацию строк.
Автор: Сидорекно Михаил Павлович [SG]Muwa https://github.com/SGmuwa
21.07.2019
*/
#pragma once

// Создание новой строки из стандартных символов "".
#define STRING_STATIC(X) ((string_t){X, sizeof(X)})
// Создание новой широкой строки из стандартных символов L"".
#define WSTRING_STATIC(X) ((wstring_t){X, sizeof(X)})

/*
Создаёт перечислитель строки слева направа.
Использование:
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
Создаёт перечислитель строки справа налево.
Использование:
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

// Представляет собой тип строки: массив символов. char * first, size_t length.
typedef struct {
	// Указатель на первый символ строки.
	char * first;
	// Количество доступных символов строки.
	size_t length;
} string_t;

// Представляет собой тип строки: массив широких символов. wchar_t * first, size_t length.
typedef struct {
	// Указатель на первый символ строки.
	wchar_t * first;
	// Количество доступных символов строки.
	size_t length;
} wstring_t;

// Поиск первого недоступного символа после доступных.
// string_t input - Входная строка, указывающая промежуток доступных символов.
// Пропускает все доступные символы.
// Возвращает: Указатель на первый недоступный символ после доступных input.
inline char * string_getEnd(string_t input)
{
	return input.first + input.length;
}
