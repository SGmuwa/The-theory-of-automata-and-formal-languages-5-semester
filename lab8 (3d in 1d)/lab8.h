#pragma once
#include <limits.h>
#include <stdlib.h>
#include <memory.h>

#define LAB8_HELP_STR \
	"Постановка задачи: \"Преобразовать трёхмерный массив в одномерный. " \
	"Реализовать обращение к нему как трёхмерному, используя обратную польскую запись.\"\n"

typedef struct Array3D {
	void * array; // Указатель на массив
	size_t lengthDimension[3]; // Размер каждого пространства.
	size_t size; // size of one element.
} * Array3D;

int size_t_safeMultiply(size_t a, size_t b, size_t * result)
{
	size_t r = a * b;
	if (a > 1 && b > 1 && (r / b != a || (r % b) != 0))
	{
		return 1;
	}
	*result = r;
	return 0;
}

/*
Создание трёхмерного массива.
size_t lengthX, Y, Z - размеры каждого пространства. Размер пространства указывать нуль опасно.
size_t size - размер каждого элемента. Размер равный нулю указывать опасно.
Возвращает: указатель на новый экземпляр. NULL, если не получилось.
*/
Array3D Array3D_malloc(size_t lengthX, size_t lengthY, size_t lengthZ, size_t size)
{
	if (lengthX == 0
		|| lengthY == 0
		|| lengthZ == 0
		|| size == 0
		|| lengthX == SIZE_MAX
		|| lengthY == SIZE_MAX
		|| lengthZ == SIZE_MAX
		|| size == SIZE_MAX)
		return NULL;
	size_t s;
	if (size_t_safeMultiply(lengthX, size, &s)) return NULL;
	if (size_t_safeMultiply(lengthY, s, &s)) return NULL;
	if (size_t_safeMultiply(lengthZ, s, &s)) return NULL;
	Array3D out = (Array3D)malloc(sizeof(struct Array3D));
	if (out == NULL)
		return NULL;
	out->array = (void*)malloc(s);
	if (out->array == NULL)
	{
		free(out);
		return NULL;
	}
	out->lengthDimension[0] = lengthX;
	out->lengthDimension[1] = lengthY;
	out->lengthDimension[2] = lengthZ;
	out->size = size;
	return out;
}

void Array3D_free(Array3D this)
{
	if (this != NULL)
	{
		if (this->array != NULL)
			free(this->array);
		free(this);
	}
}

inline void * Array3D_element(Array3D this, size_t x, size_t y, size_t z)
{
	return (char*)this->array + this-> size * (this->lengthDimension[1] * this->lengthDimension[0] * z + this->lengthDimension[0] * y + x);
}

int Array3D_set(Array3D this, size_t x, size_t y, size_t z, void * elm)
{
	if (this == NULL)
		return 1;
	if (this->array == NULL)
		return 2;
	if (x >= this->lengthDimension[0])
		return 3;
	if (y >= this->lengthDimension[1])
		return 4;
	if (z >= this->lengthDimension[2])
		return 5;
	if (elm == NULL)
		return 6;
#ifdef _MSC_VER
	if (memcpy_s(Array3D_element(this, x, y, z), this->size, elm, this->size))
		return 7;
#else
	memcpy(Array3D_element(this, x, y, z), elm, this->size);
#endif // _MSC_VER
	return 0;
}

int Array3D_get(Array3D this, size_t x, size_t y, size_t z, void * elm)
{
	if (this == NULL)
		return 1;
	if (this->array == NULL)
		return 2;
	if (x >= this->lengthDimension[0])
		return 3;
	if (y >= this->lengthDimension[1])
		return 4;
	if (z >= this->lengthDimension[2])
		return 5;
	if (elm == NULL)
		return 6;
#ifdef _MSC_VER
	if (memcpy_s(elm, this->size, Array3D_element(this, x, y, z), this->size))
		return 7;
#else
	memcpy(elm, Array3D_element(this, x, y, z), this->size);
#endif // _MSC_VER
	return 0;
}
