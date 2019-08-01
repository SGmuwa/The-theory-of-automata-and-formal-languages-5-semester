#pragma once

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif // _INC_STDLIB

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	/// Структура организует хранение данных о пользовательском стеке.
	/// </summary>
	typedef struct StackMemory
	{
		/// <summary> Указывает на текущий элемент. </summary>
		void * current;
		/// <summary> Указывает на самый последний доступный элемент. </summary>
		void * top;
		/// <summary> Указывает на самый первый элемент. </summary>
		void * bottom;
		/// <summary> Размер одного элемента. </summary>
		size_t sizeElement;
	} stack_t;

	// Выделить память для стека.
	// countElements - Количество элементов в стеке.
	// sizeElement - Размер одного элемента.
	// Возвращает: Структуру, которая содержит информацию о новом стеке.
	//				Возвращает все элементы структуры NULL или 0,
	//				если память не выделилась.
	struct StackMemory Stack_malloc(size_t countElements, size_t sizeElement)
	{
		struct StackMemory output;
		output.top = output.bottom = output.current = malloc(countElements*sizeElement);
		if (output.bottom != NULL)
		{
			((char*)output.top) += countElements * sizeElement - 1;
			output.sizeElement = sizeElement;
		}
		else
		{
			output.sizeElement = 0;
		}
		return output;
	}

	/// <summary>
	/// Освобождает память от стека.
	/// </summary>
	/// <param name="stack">Стек, который нужно освободить.</param>
	void Stack_free(struct StackMemory stack)
	{
		free(stack.bottom);
	}

	/// <summary>Добавить элемент в стек.</summary>
	/// <param name="stack">Стек, с которым мы работаем.</param>
	/// <param name="element">Элемент, который нужно добавить</param>
	/// <return>0 - операция успешна. 1 - не хватило место в стеке.</return>
	unsigned short int Stack_push(struct StackMemory * stack, void * element)
	{
		size_t i;
		if ((size_t)stack->top - (size_t)stack->current >= stack->sizeElement)
		{
			for (i = 0; i < stack->sizeElement; i++)
			{
				*((char*)stack->current) = ((char*)element)[i];
				((char*)stack->current)++;
			}
			return 0;
		}
		return 1;
	}

	/// <summary>Извлечь информацию из стека.</summary>
	/// <param name="stack">Стек, с которым мы работаем.</param>
	/// <param name="output">Указатель на элемент, куда нужно вывести результат.</param>
	/// <return>0 - операция успешна. 1 - стек пуст.</return>
	unsigned short int Stack_pop(struct StackMemory * stack, void * output)
	{
		size_t i;
		if ((size_t)stack->current - (size_t)stack->bottom >= stack->sizeElement)
		{
			for (i = stack->sizeElement - 1; i != ~(size_t)0; i--)
			{
				((char*)stack->current)--;
				((char*)output)[i] = *((char*)stack->current);
			}
			return 0;
		}
		return 1;
	}

	/// <summary>Получает из стека последний элемент.</summary>
	/// <param name="stack">Стек, с которым мы работаем.</param>
	/// <param name="output">Указатель на элемент, куда нужно вывести результат.</param>
	/// <return>0 - операция успешна. 1 - стек пуст.</return>
	unsigned short int Stack_get(struct StackMemory stack, void * output)
	{
		size_t i;
		if ((size_t)stack.current - (size_t)stack.bottom >= stack.sizeElement)
		{
			for (i = stack.sizeElement - 1; i != ~(size_t)0; i--)
			{
				((char*)stack.current)--;
				((char*)output)[i] = *((char*)stack.current);
			}
			return 0;
		}
		return 1;
	}
	
	/// <summary>Получает количество добавленных элементов в стеке.</summary>
	/// <param name="stack">Стек, в котором надо узнать количество элементов.</param>
	/// <return>Количество добавленных элементов в стеке.</return>
	size_t Stack_count(struct StackMemory stack)
	{
		return ((size_t)stack.current - (size_t)stack.bottom) / stack.sizeElement;
	}

#ifdef __cplusplus
}
#endif // __cplusplus