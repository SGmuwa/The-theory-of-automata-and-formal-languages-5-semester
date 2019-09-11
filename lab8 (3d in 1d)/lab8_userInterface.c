#include "lab8.h"

void Array3D_printInt(Array3D this)
{
	for (size_t z = 0; z < this->lengthDimension[2]; z++)
	{
		printf("{ ");
		for (size_t y = 0; y < this->lengthDimension[1]; y++)
		{
			printf("(");
			for (size_t x = 0; x < this->lengthDimension[0]; x++)
			{
				printf("%d", *(int*)Array3D_element(this, x, y, z));
				if (x + 1 < this->lengthDimension[0])
				{
					printf(", ");
				}
			}
			printf(")");
		}
		printf("}\n");
	}
}

void main()
{
	int a = 0;
	Array3D test = Array3D_malloc(3, 3, 3, sizeof(int));
	for (size_t z = 0; z < test->lengthDimension[2]; z++)
		for (size_t y = 0; y < test->lengthDimension[1]; y++)
			for (size_t x = 0; x < test->lengthDimension[0]; x++)
			{
				Array3D_set(test, x, y, z, &a);
				a++;
			}
	Array3D_printInt(test);
	Array3D_free(test);
	scanf_s("%*s");
}