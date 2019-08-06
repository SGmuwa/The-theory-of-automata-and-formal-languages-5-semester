#pragma once
#include "string_t.h"
#include "..\Dynamic_Generic_ArrayList_C\arrayList.h"

ArrayList string_splitMalloc(string_t input, string_t separator)
{
	if (input.first == NULL)
		return NULL;
	ArrayList output = ArrayList_malloc(sizeof(string_t));
	if (output == NULL)
		return NULL;
	if (separator.first == NULL || separator.length == 0)
	{
		ArrayList_addLast(output, &input);
		return output;
	}
	char * lastAdded = input.first - 1;
	for (size_t i = 0; i < input.length; i++)
	{
		if (string_equal(
			(string_t) {
			input.first + i, separator.length
		},
			separator))
		{
			if (ArrayList_addLast(output, &(string_t) { lastAdded + 1, input.first + i - 1 - lastAdded }))
			{
				ArrayList_free(output);
				return NULL;
			}
			lastAdded = input.first;
		}
	}
	if (lastAdded != input.first + input.length - 1)
	{
		if (ArrayList_addLast(output, &(string_t) { lastAdded + 1, input.first + input.length - 1 - lastAdded }))
		{
			ArrayList_free(output);
			return NULL;
		}
		lastAdded = input.first + input.length - 1;
	}
	return output;
}
