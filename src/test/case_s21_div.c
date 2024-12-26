#include "test_s21_decimal.h"

START_TEST(test_1) {
  s21_decimal value_1 = {{246, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{123, 0, 0, 0}};

  s21_div(value_1, value_2, &value_result);

  ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{123, 0, 0, 0}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{0, 0, 0, 0}};

  s21_div(value_1, value_2, &value_result);

  ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_3) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal value_result = {{0}};

  int status = s21_div(value_1, value_2, &value_result);

  ck_assert_int_eq(status, S21_DIV_BY_ZERO);
}
END_TEST

START_TEST(test_4) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_sign(1, &value_1);
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_sign(1, &value_expected);

  s21_div(value_1, value_2, &value_result);

  ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_5) {
  s21_decimal value_1 = {{12345678, 0, 0, 0}};
  s21_decimal value_2 = {{87654321, 0, 0, 0}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{0xAD4CB3FC, 0x65776EBA, 0x48D0B03, 28 << 16}};

  s21_div(value_1, value_2, &value_result);

  ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_6) {
  s21_decimal value_1 = {{6, 0, 0, (1 << 16)}};
  set_sign(1, &value_1);
  s21_decimal value_2 = {{3, 0, 0, (5 << 16)}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{20000, 0, 0, 0}};
  set_sign(1, &value_expected);

  s21_div(value_1, value_2, &value_result);

  ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_7) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 5}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 5}};

  s21_div(value_1, value_2, &value_result);

  ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_8) {
  s21_decimal value_1 = {{0, 0, 0, 5}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{0, 0, 0, 0}};

  s21_div(value_1, value_2, &value_result);

  ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_9) {
  s21_decimal value_1 = {{13, 0, 0, (10 << 16)}};
  set_sign(1, &value_1);
  s21_decimal value_2 = {{17, 0, 0, (15 << 16)}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{0x89696969, 0xCC2A1231, 0xF716FCEE, 24 << 16}};
  set_sign(1, &value_expected);

  s21_div(value_1, value_2, &value_result);

  ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_10) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFF1, 0}};
  s21_decimal value_2 = {{123, 0, 0, 7 << 16}};
  s21_decimal value_result = {{0}};

  int status = s21_div(value_1, value_2, &value_result);

  ck_assert_int_eq(status, S21_INFINITY);
}
END_TEST

START_TEST(test_11) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFF1, 1 << 31}};
  s21_decimal value_2 = {{123, 0, 0, 7 << 16}};
  s21_decimal value_result = {{0}};

  int status = s21_div(value_1, value_2, &value_result);

  ck_assert_int_eq(status, S21_NEG_INFINITY);
}
END_TEST

TCase *s21_test_div(void) {
  TCase *testCase = tcase_create("div");

  tcase_add_test(testCase, test_1);
  tcase_add_test(testCase, test_2);
  tcase_add_test(testCase, test_3);
  tcase_add_test(testCase, test_4);
  tcase_add_test(testCase, test_5);
  tcase_add_test(testCase, test_6);
  tcase_add_test(testCase, test_7);
  tcase_add_test(testCase, test_8);
  tcase_add_test(testCase, test_9);
  tcase_add_test(testCase, test_10);
  tcase_add_test(testCase, test_11);

  return testCase;
}
