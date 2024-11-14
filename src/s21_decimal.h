#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// ============================================================================

// arithmetic | matw0x
enum ARITHMETIC_STATUS {
    OK,
    OVERFLOW, // число слишком велико или равно бесконечности
    UNDERFLOW, // число слишком мало или равно отрицательной бесконечности
    DIVISION_BY_ZERO // деление на 0
};

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// ============================================================================

// comparison | Maestro
enum COMPARISON_STATUS {
    FALSE,
    TRUE
};

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

// ============================================================================

// conversion
enum CONVERSION_STATUS {
    OK,
    ERROR // ошибка конвертации
};

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// ============================================================================

// other functions

enum OPERATION_STATUS {
    OK,
    ERROR
};

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// ============================================================================

#endif // S21_DECIMAL_H