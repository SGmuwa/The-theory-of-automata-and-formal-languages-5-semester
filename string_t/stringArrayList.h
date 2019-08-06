#pragma once
#include "string_t.h"
#include "..\Dynamic_Generic_ArrayList_C\arrayList.h"

ArrayList string_splitMalloc(string_t input, string_t separator)
{
	if (input.first == NULL)
		return NULL;
	if (input.length > 0 && input.first[input.length - 1] == '\0')
		input.length--;
	ArrayList output = ArrayList_malloc(sizeof(string_t));
	if (output == NULL)
		return NULL;
	if (separator.first == NULL || separator.length == 0)
	{
		ArrayList_addLast(output, &input);
		return output;
	}
	string_t toSend = { input.first, 0u };
	for (size_t i = 0; i < input.length; i++)
	{
		toSend.length++;
		if (toSend.length >= separator.length && string_equal(
			(string_t) { toSend.first + toSend.length - separator.length, separator.length },
			separator))
		{
			toSend.length -= separator.length;
			if(toSend.length > 0)
				if (ArrayList_addLast(output, &toSend))
				{
					ArrayList_free(output);
					return NULL;
				}
			toSend.first += toSend.length + separator.length;
			toSend.length = 0;
		}
	}
	if (toSend.length > 0)
	{
		if (ArrayList_addLast(output, &toSend))
		{
			ArrayList_free(output);
			return NULL;
		}
	}
	ArrayList_removeTrash(output);
	return output;
}
