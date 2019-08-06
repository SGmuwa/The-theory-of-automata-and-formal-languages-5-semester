#pragma once
#include "..\Dynamic_Generic_ArrayList_C\arrayList.h"
#include <stdarg.h>

#define LAB3_HELP_STR \
	"Постановка задачи:\n" \
	"\"Вычислить значение арифметической формулы, используя обратную польскую запись.\"" \



enum lab3_err
{
	// Выполнено успешно.
	LAB3_ERR_OK,
	// Состояние не определено.
	LAB3_ERR_STATE_NULL,
	// Указатель на output равен NULL.
	LAB3_ERR_OUTPUT_NULL,
	// Указатель output->first равен NULL.
	LAB3_ERR_OUTPUT_FIRST_NULL,
	// Указатель input.first равен NULL.
	LAB3_ERR_INPUT_FIRST_NULL,
	// Нехватка памяти.
	LAB3_ERR_OUT_OF_MEMORY
};

enum lab3_typeArg
{
	// Если надо передавать аргумент как целое число.
	LAB3_TYPEARG_INREGER,
	// Если надо передавать аргумент как число с плавающей запятой (точкой).
	LAB3_TYPEARG_FLOAT,
	// Если надо передавать аргумент как указатель на строку (char*).
	LAB3_TYPEARG_CHARS,
	// Если надо пропустить передачу аргумента.
	LAB3_TYPEARG_VOID
};

struct lab3_functionInfoArg
{
	// Размер аргумента в байтах.
	size_t argSize;
	// Представление аргумента.
	enum lab3_typeArg type;
};

typedef struct lab3_functionInfo
{
	// Имя функции.
	string_t name;
	// Количество аргументов функции.
	size_t argsCount;
	// Список на информацию о аргументах.
	ArrayList/*lab3_functionInfoArg*/ argsInfo;
	// Информация о возвращаемом значении функции.
	struct lab3_functionInfoArg outputInfo;
	// Указатель на функцию.
	void * function;
} *lab3_functionInfo;

typedef struct lab3_state
{
	ArrayList/*lab3_functionInfo*/ functionSupports;
} *lab3_state;

lab3_functionInfo lab3_functionInfo_copyMalloc(string_t name, size_t argsCount, struct lab3_functionInfoArg functionReturn, ...)
{
	lab3_functionInfo output = (lab3_functionInfo)malloc(sizeof(struct lab3_functionInfo));
	if (output == NULL)
		return LAB3_ERR_OUT_OF_MEMORY;
	output->name = string_mallocCopyLimit(name.first, name.length);
	output->argsCount = argsCount;
	output->outputInfo = functionReturn;
	output->argsInfo = ArrayList_malloc(sizeof(struct lab3_functionInfoArg));
	if (output->argsInfo == NULL)
	{
		string_free(output->name);
		free(output);
		return NULL;
	}
	va_list argptr;
	va_start(argptr, functionReturn);
	while (--argsCount != SIZE_MAX)
	{
		if (ArrayList_addLast(output->argsInfo, &va_arg(argptr, struct lab3_functionInfoArg)))
		{
			ArrayList_free(output->argsInfo);
			string_free(output->name);
			free(output);
			return NULL;
		}
	}
	va_end(argptr);
	return output;
}

enum ArrayList_err lab3_addFunction(lab3_state this, lab3_functionInfo function)
{
	return ArrayList_addLast(this->functionSupports, &function);
}

enum lab3_err lab3_freeAllFunctions(lab3_state this)
{
	if (this == NULL)
		return LAB3_ERR_OUTPUT_NULL;
}

void lab3_functionInfo_free(lab3_functionInfo this)
{
	if (this != NULL)
	{
		string_free(this->name);
		this->argsCount = 0;
		ArrayList_free(this->argsInfo);
		this->outputInfo = (struct lab3_functionInfoArg) {0, LAB3_TYPEARG_VOID};
		this->function = NULL;
		free(this);
	}
}

enum lab3_err lab3_addFunction(lab3_state this, string_t name, void * function, size_t argsCount, ...)
{

}

lab3_state lab3_malloc()
{
	lab3_state output = (lab3_state)malloc(sizeof(struct lab3_state));
	if (output == NULL)
		return NULL;
	output->functionSupports = ArrayList_malloc(sizeof(lab3_functionInfo));
	if (output->functionSupports == NULL)
	{
		free(output);
		return NULL;
	}
	return output;
}

void lab3_free(lab3_state this)
{
	if (this != NULL)
	{
		if (this->functionSupports != NULL)
		{
			for (size_t i = 0; i < this->functionSupports->length; i++)
			{
				lab3_functionInfo funInfo;
				ArrayList_get(this->functionSupports, i, &funInfo);
				lab3_functionInfo_free(funInfo);
			}
			ArrayList_free(this->functionSupports);
		}
		free(this);
	}
}

enum lab3_err lab3(lab3_state state, string_t * output, string_t input)
{
	if (state == NULL)
		return LAB3_ERR_STATE_NULL;
	if (output == NULL)
		return LAB3_ERR_OUTPUT_NULL;
	if (output->first == NULL)
		return LAB3_ERR_OUTPUT_FIRST_NULL;
	if (input.first == NULL)
		return LAB3_ERR_INPUT_FIRST_NULL;

}