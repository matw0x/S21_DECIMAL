#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdbool.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// bits[0] – содержит младшие 32 бита 96-разрядного целого числа.
// bits[1] – содержит средние 32 бита.
// bits[2] – содержит старшие 32 бита.
// bits[3] – содержит информацию о знаке и коэффициенте масштабирования, упакованную в 32-битное целое число.

// В элементе bits[3]:
// Биты с 0 по 15: не используются и должны быть равны нулю.
// Биты с 16 по 23: содержат степень 10, в диапазоне от 0 до 28.
// Биты с 24 по 30: не используются и также должны быть равны нулю.
// Бит 31: знак числа (0 – положительное, 1 – отрицательное).

// ============================================================================

// arithmetic | matw0x
typedef enum {
    OK,
    OVERFLOW, // число слишком велико или равно бесконечности
    UNDERFLOW, // число слишком мало или равно отрицательной бесконечности
    DIVISION_BY_ZERO // деление на 0
} ARITHMETIC_STATUS;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// ============================================================================

// comparison | Maestro
typedef enum {
    FALSE,
    TRUE
} COMPARISON_STATUS;

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

// ============================================================================

// conversion
typedef enum {
    OK,
    ERROR // ошибка конвертации
} CONVERSION_STATUS;

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// ============================================================================

// other functions

typedef enum {
    OK,
    ERROR
} OPERATION_STATUS;

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// ============================================================================

// support
int is_bits_0_15(const s21_decimal value);
int is_bits_16_23(const s21_decimal value);
int is_bits_24_30(const s21_decimal value);
int get_bit_31(const s21_decimal value);
OPERATION_STATUS is_empty(const s21_decimal value);
OPERATION_STATUS is_valid_decimal(const s21_decimal value);

#endif // S21_DECIMAL_H