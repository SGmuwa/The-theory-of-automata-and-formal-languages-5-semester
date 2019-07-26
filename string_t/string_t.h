/*
Файл, который содержит в себе типизацию строк.
Автор: Сидорекно Михаил Павлович [SG]Muwa https://github.com/SGmuwa
21.07.2019
*/
#pragma once
#include <stdlib.h>

#ifdef __cplusplus
// Создание новой строки из стандартных символов "".
#define STRING_STATIC(X) (string_t{X, sizeof(X)})
// Создание новой широкой строки из стандартных символов L"".
#define WSTRING_STATIC(X) (wstring_t{X, sizeof(X)})
#else
// Создание новой строки из стандартных символов "".
#define STRING_STATIC(X) ((string_t){X, sizeof(X)})
// Создание новой широкой строки из стандартных символов L"".
#define WSTRING_STATIC(X) ((wstring_t){X, sizeof(X)})
#endif // __cplusplus

// Создаёт массив пробелов. Размер в байтах: 1
#define STRING_CONST_1 ""
// Создаёт массив пробелов. Размер в байтах: 2
#define STRING_CONST_2 " " STRING_CONST_1 STRING_CONST_1
// Создаёт массив пробелов. Размер в байтах: 4
#define STRING_CONST_4 " " STRING_CONST_2 STRING_CONST_2
// Создаёт массив пробелов. Размер в байтах: 8
#define STRING_CONST_8 " " STRING_CONST_4 STRING_CONST_4
// Создаёт массив пробелов. Размер в байтах: 16
#define STRING_CONST_16 " " STRING_CONST_8 STRING_CONST_8
// Создаёт массив пробелов. Размер в байтах: 32
#define STRING_CONST_32 " " STRING_CONST_16 STRING_CONST_16
// Создаёт массив пробелов. Размер в байтах: 64
#define STRING_CONST_64 " " STRING_CONST_32 STRING_CONST_32
// Создаёт массив пробелов. Размер в байтах: 128
#define STRING_CONST_128 " " STRING_CONST_64 STRING_CONST_64
// Создаёт массив пробелов. Размер в байтах: 256
#define STRING_CONST_256 " " STRING_CONST_128 STRING_CONST_128
// Создаёт массив пробелов. Размер в байтах: 512
#define STRING_CONST_512 " " STRING_CONST_256 STRING_CONST_256
// Создаёт массив пробелов. Размер в байтах: 1024
#define STRING_CONST_1024 " " STRING_CONST_512 STRING_CONST_512

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

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

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

	// Выделение в памяти пространства для строки.
	// size_t count - количество доступных символов.
	// Возвращает: строка в памяти. В случае, если не получилось,
	//				то указатель равен NULL, а length = 0.
	inline string_t string_malloc(size_t count)
	{
		string_t output = (string_t) { malloc(count), count };
		return
			output.first != NULL
			? output
			: (string_t) { NULL, 0 };
	}

	// Освобождение памяти от строки.
	// string_t str - строка, которую нужно удалить из памяти.
	inline void string_free(string_t str)
	{
		free(str.first);
	}

	/*
	Превращает указатель на char в строку, ведя поиск по \0 невключительно (strlen).
	Данная функция используется, если не известно, сколько символов в входной строке.
	В случае, если количество символов изветсно, используйте STRING_STATIC.
	char * string - входной указатель на строку.
	Возвращает: string_t с данной строкой и количеством доступных символов.
	*/
	inline string_t string_dynamic(char * string)
	{
		return (string_t) { string, strlen(string) };
	}

#ifdef __cplusplus
}
#endif // __cplusplus
