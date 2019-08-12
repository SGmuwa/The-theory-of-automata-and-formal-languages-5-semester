#pragma once
#include "..\Dynamic_Generic_ArrayList_C\arrayList.h"
#include "..\stack_t\stack_t.h"
#include "..\string_t\string_t.h"
#include <math.h>
#include "..\lab1\lab1.h"
#include "..\lab2\lab2.h"
#include "..\lab4 (logical expression to RPN)\lab4.h"
#include "..\string_t\stringArrayList.h"

#define LAB5_HELP_STR \
	"Постановка задачи:\n" \
	"\"Вычислить значение арифметической формулы, используя обратную польскую запись.\"\n" \
	"Поддерживаются операторы +, -, *, /, ^, скобки ( и ), вещественные числа."


enum lab5_err
{
	// Выполнено успешно.
	LAB5_ERR_OK,
	// Указатель на output равен NULL.
	LAB5_ERR_OUTPUT_NULL,
	// Указатель output->first равен NULL.
	LAB5_ERR_OUTPUT_FIRST_NULL,
	// Указатель input.first равен NULL.
	LAB5_ERR_INPUT_FIRST_NULL,
	// Нехватка памяти.
	LAB5_ERR_OUT_OF_MEMORY,
	// Данная операция не поддерживается.
	LAB5_ERR_NOT_SUPPORT,
	// Ошибка преобразования string_t в long double.
	LAB5_ERR_READ_NUMBER,
	// Данный оператор не поддерживается.
	LAB5_ERR_NOT_SUPPORT_OPERATOR,
	// В конце вычислений в стеке получилось количество элементов не равное единице.
	LAB5_ERR_ENDSTACK_COUNT
};

enum lab5_err lab5_runFloat(long double * output, string_t input, string_t separator)
{
	if (output == NULL)
		return LAB5_ERR_OUTPUT_NULL;
	if (input.first == NULL)
		return LAB5_ERR_INPUT_FIRST_NULL;
	struct StackMemory stk = Stack_malloc(input.length, sizeof(long double));
	if (stk.bottom == NULL)
		return LAB5_ERR_OUT_OF_MEMORY;
	if (input.length > 0 && input.first[input.length - 1] == '\0')
		input.length--;
	ArrayList arrayInput = string_splitMalloc(input, separator);
	if (arrayInput == NULL)
	{
		Stack_free(stk);
		return LAB5_ERR_OUT_OF_MEMORY;
	}
	long double pop[2];
	long double push;
#define LAB5_RETURN(ERR) do { Stack_free(stk); ArrayList_free(arrayInput); return ERR; } while(0)
	for (size_t i = 0; i < arrayInput->length; i++)
	{
		string_t current;
		ArrayList_get(arrayInput, i, &current);
		string_t number = lab2_search10Number(current);
		string_t operator = lab4_searchOperator(current);
		if (operator.length == current.length)
		{
			if (operator.length != 1)
				LAB5_RETURN(LAB5_ERR_NOT_SUPPORT_OPERATOR);
			Stack_pop(&stk, pop + 1);
			Stack_pop(&stk, pop);
			switch (*operator.first)
			{
			case '+':
				push = pop[0] + pop[1];
				break;
			case '-':
				push = pop[0] - pop[1];
				break;
			case '/':
				push = pop[0] / pop[1];
				break;
			case '*':
				push = pop[0] * pop[1];
				break;
			case '^':
				push = powl(pop[0], pop[1]);
				break;
			default:
				LAB5_RETURN(LAB5_ERR_NOT_SUPPORT_OPERATOR);
			}
			if (Stack_push(&stk, &push))
				LAB5_RETURN(LAB5_ERR_OUT_OF_MEMORY);
		}
		else if (number.length == current.length)
		{
			if (lab1(&push, number))
				LAB5_RETURN(LAB5_ERR_READ_NUMBER);
			if (Stack_push(&stk, &push))
				LAB5_RETURN(LAB5_ERR_OUT_OF_MEMORY);
		}
		else
			LAB5_RETURN(LAB5_ERR_NOT_SUPPORT);
	}
	if (Stack_count(stk) != 1)
		LAB5_RETURN(LAB5_ERR_ENDSTACK_COUNT);
	Stack_pop(&stk, output);
	LAB5_RETURN(LAB5_ERR_OK);
#undef LAB5_RETURN
}


enum lab5_err lab5_run(string_t * output, string_t input, string_t separator)
{
	if (output == NULL)
		return LAB5_ERR_OUTPUT_NULL;
	if (output->first == NULL)
		return LAB5_ERR_OUTPUT_FIRST_NULL;
	long double toString;
	enum lab5_err err = lab5_runFloat(&toString, input, separator);
	if (err != 0)
		return err;
#ifdef _MSC_VER
	output->length = sprintf_s(output->first, output->length, "%Lf", toString);
#else // _MCS_VER
	output->length = sprintf(output->first, "%Lf", toString);
#endif // _MCS_VER
	return LAB5_ERR_OK;
}
