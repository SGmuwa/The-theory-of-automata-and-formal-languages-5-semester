/*
Файл представляет из себя описание, что такое байт.
Автор: Сидоренко Михаил Павлович [SG]Muwa https://github.com/SGmuwa/
21.07.2019
*/
#pragma once

/*
Тип байта в представлении unsigned char.
*/
typedef unsigned char byte_t;

/*
Тип представляет собой доступ к каждому биту из восьми доступных.
b0 является самым младшим битом.
b7 является самым старшим битом.
b7 b6 b5 b4 b3 b2 b1 b0
 0  0  0  0  0  0  1  1 = 3
*/
typedef struct
{
	byte_t b0 : 1;
	byte_t b1 : 1;
	byte_t b2 : 1;
	byte_t b3 : 1;
	byte_t b4 : 1;
	byte_t b5 : 1;
	byte_t b6 : 1;
	byte_t b7 : 1;
} byte_bits_t;

/*
Представляет из себя единицу информации в 1 байт, в котором 8 бит.
Можно редактировать как и само значение от 0 до 255, так и отдельные биты
от b0 до b7.
*/
typedef union
{
	byte_t value;
	byte_bits_t bit;
} byte_union_t;

#ifdef false
#warning Директива препроцессора false уже создана.
#else
// Ложь.
#define false (byte_t)0
#endif // false

#ifdef true
#warning Директива препроцессора true уже создана.
#else
// Истина.
#define true (byte_t)!0
#endif // true
