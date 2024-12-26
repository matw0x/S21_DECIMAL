#ifndef TEST_S21_DECIMAL_
#define TEST_S21_DECIMAL_

#include <check.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include "../s21_decimal.h"

TCase *s21_test_add(void);
TCase *s21_test_div(void);
// TCase *s21_test_floor(void);
// TCase *s21_test_from_decimal_to_float(void);
// TCase *s21_test_from_decimal_to_int(void);
// TCase *s21_test_from_float_to_decimal(void);
// TCase *s21_test_from_int_to_decimal(void);
TCase *s21_test_is_equal(void);
TCase *s21_test_is_greater(void);
TCase *s21_test_is_greater_or_equal(void);
TCase *s21_test_is_less(void);
TCase *s21_test_is_less_or_equal(void);
TCase *s21_test_is_not_equal(void);
TCase *s21_test_mul(void);
// TCase *s21_test_negate(void);
// TCase *s21_test_round(void);
TCase *s21_test_sub(void);
// TCase *s21_test_truncate(void);

#endif
