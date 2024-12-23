#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <float.h>
typedef struct
{
	unsigned int bits[4];
} s21_decimal;
typedef struct s21_int256
{
	s21_decimal decimals[2];
} s21_int256;
// ============================================================================
// Статусы арифметических операций | matw0x
typedef enum
{
	ARITHMETIC_OK,
	ARITHMETIC_OVERFLOW,			 // число слишком велико или равно бесконечности
	ARITHMETIC_UNDERFLOW,		 // число слишком мало или равно отрицательной бесконечности
	ARITHMETIC_DIVISION_BY_ZERO // деление на 0
} ARITHMETIC_STATUS;

// Арифметические функции
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// ============================================================================
// Статусы сравнения | Maestro
typedef enum
{
	COMPARISON_FALSE,
	COMPARISON_TRUE
} COMPARISON_STATUS;

// Функции сравнения
int s21_is_less(s21_decimal decimal1, s21_decimal decimal2);
int s21_is_less_or_equal(s21_decimal decimal1, s21_decimal decimal2);
int s21_is_greater(s21_decimal decimal1, s21_decimal decimal2);
int s21_is_greater_or_equal(s21_decimal decimal1, s21_decimal decimal2);
int s21_is_equal(s21_decimal decimal1, s21_decimal decimal2);
int s21_is_not_equal(s21_decimal decimal1, s21_decimal decimal2);

// ============================================================================
// Статусы конверсий | Maestro
typedef enum
{
	CONVERSION_OK,
	CONVERSION_ERROR // ошибка конвертации
} CONVERSION_STATUS;

// Функции конверсии
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// ============================================================================
// Статусы операций | Maestro
typedef enum
{
	OPERATION_OK,
	OPERATION_ERROR
} OPERATION_STATUS;

// Прочие функции
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// ============================================================================
// Вспомогательные функции | Maestro
int is_bits_0_15(s21_decimal value);
int is_bits_16_23(s21_decimal value);
int is_bits_24_30(s21_decimal value);
int get_bit_31(s21_decimal value);
int is_empty(const s21_decimal value);
int is_valid_decimal(const s21_decimal value);

// ============================================================================
// Вспомогательные мужские функции | Maestro
int get_sign_number(s21_decimal decimal);
int get_bits_16_23(s21_decimal decimal);
int s21_sign_get(s21_decimal decimal1, int index, int numBits);
#endif // S21_DECIMAL_H
