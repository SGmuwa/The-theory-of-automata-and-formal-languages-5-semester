/*
Файл, который содержит в себе типизацию строк.
Автор: Сидорекно Михаил Павлович [SG]Muwa https://github.com/SGmuwa
21.07.2019
*/
#pragma once
#include <stdlib.h>
#include <stdbool.h>

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
// Создание новой строки из стандартных символов "" не включая последний ноль.
// Он исключается благодаря length, который уменьшен на единицу.
#define STRING_STATIC0(X) ((string_t){X, sizeof(X) - 1})
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
#define STRING_FOREACHL(I, STR) char * I = STR.first; I < string_getEnd(STR); I++

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
#define STRING_FOREACHR(I, STR) char * I = string_getEnd(STR) - 1; I >= STR.first; I--

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
	string_t string_malloc(size_t count)
	{
		string_t output = (string_t) { malloc(count), count };
		return
			output.first != NULL
			? output
			: (string_t) { NULL, 0 };
	}

	string_t string_mallocCopyLimit(char * source, size_t countCopy)
	{
		string_t output = (string_t) { malloc(sizeof(char) * countCopy), countCopy };
#ifdef _MSC_VER
		errno_t err = memcpy_s(output.first, output.length, source, countCopy);
#else
		unsigned char err = countCopy < 1 || source == NULL || output.first == NULL;
		if(!err)
			memcpy(output.first, source, countCopy);
#endif // _MSC_VER
		if (err)
		{
			if (output.first != NULL) free(output.first);
			return (string_t) { NULL, 0 };
		}
		return output;
	}

	string_t string_mallocCopy(char * source)
	{
		if (source == NULL)
			return (string_t) { NULL, 0 };
		return string_mallocCopyLimit(source, strlen(source));
	}

	/*
	Превращает string_t в char *.
	Заменяются все символы '\0' на ' '.
	В случае, если последний символ не '\0', он будет добавлен к выходному char*.
	*/
	char * string_mallocCopyToChar(string_t source)
	{
		string_t output = string_mallocCopyLimit(source.first, *(string_getEnd(source) - 1) == '\0' ? source.length : source.length + 1);
		if (output.first != NULL)
		{
			for (STRING_FOREACHR(ch, output))
			{
				if (*ch == '\0')
					*ch = ' ';
			}
			*(string_getEnd(output) - 1) = '\0';
		}
		return output.first;
	}

	/*
	Убирает пробелы и символы '\0' слева и справа строки.
	Не выделяет память, меняет указатели. Следовательно,
	если выполнить string_free(source), то результат этой функции
	также будет стёрт.
	*/
	string_t string_trim(string_t source)
	{
		if (source.first == NULL || source.length == 0)
			return source;
		while ((*source.first == ' ' || *source.first == '\0') && source.length > 0)
		{
			source.first++;
			source.length--;
		}
		while ((*(string_getEnd(source) - 1) == ' ' || *(string_getEnd(source) - 1) == '\0') && source.length > 0)
		{
			source.length--;
		}
		return source;
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

	string_t string_removeAllMalloc(string_t input, string_t removeCharactes)
	{
		size_t countRemove = 0;
		for (STRING_FOREACHR(in, input))
		{
			for (STRING_FOREACHR(re, removeCharactes))
			{
				if (*in == *re)
				{
					countRemove++;
					break;
				}
			}
		}
		string_t output = string_malloc(input.length - countRemove);
		char * outputPointer = string_getEnd(output) - 1;
		if (output.first == NULL)
			return output;
		for (STRING_FOREACHR(in, input))
		{
			unsigned char isNeedDelete = 0;
			for (STRING_FOREACHR(re, removeCharactes))
			{
				if (*in == *re)
				{
					isNeedDelete = 1;
					break;
				}
			}
			if (!isNeedDelete)
				*(outputPointer--) = *in;
		}
		return output;
	}

	_Bool string_equal(string_t left, string_t right)
	{
		if (left.first == NULL || right.first == NULL)
			return false;
		if (left.length == 0 && right.length == 0)
			return true;
		if (left.length == 0)
			return false;
		if (left.length != right.length)
			return false;
		_Bool output = memcmp(left.first, right.first, left.length) == 0;
		return output;
	}

#ifdef __cplusplus
}
#endif // __cplusplus
