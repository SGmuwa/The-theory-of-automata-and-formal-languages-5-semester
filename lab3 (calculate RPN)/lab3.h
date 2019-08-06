#pragma once
#include "..\Dynamic_Generic_ArrayList_C\arrayList.h"
#include "..\stack_t\stack_t.h"
#include "..\string_t\string_t.h"

#define LAB3_HELP_STR \
	"Постановка задачи:\n" \
	"\"Вычислить значение арифметической формулы, используя обратную польскую запись.\"" \



enum lab3_err
{
	// Выполнено успешно.
	LAB3_ERR_OK,
	// Указатель на output равен NULL.
	LAB3_ERR_OUTPUT_NULL,
	// Указатель output->first равен NULL.
	LAB3_ERR_OUTPUT_FIRST_NULL,
	// Указатель input.first равен NULL.
	LAB3_ERR_INPUT_FIRST_NULL,
	// Нехватка памяти.
	LAB3_ERR_OUT_OF_MEMORY
};

enum lab3_err lab3(string_t * output, string_t input, string_t separator)
{
	if (output == NULL)
		return LAB3_ERR_OUTPUT_NULL;
	if (output->first == NULL)
		return LAB3_ERR_OUTPUT_FIRST_NULL;
	if (input.first == NULL)
		return LAB3_ERR_INPUT_FIRST_NULL;
	struct StackMemory stk = Stack_malloc(input.length, sizeof(string_t));
	ArrayList arrayInput = lab3_splitMalloc(input, separator);
}