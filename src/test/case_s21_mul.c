#include "test_s21_decimal.h"

START_TEST(test_1) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{246, 0, 0, 0}};

  s21_mul(value_1, value_2, &value_result);

  ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_2) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{123, 0, 0xFFFFFFFF, 3 << 16}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{0, 0, 0, 0}};

  s21_mul(value_1, value_2, &value_result);

  ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_3) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0 << 16}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal value_result = {{0}};

  int status = s21_mul(value_1, value_2, &value_result);

  ck_assert_int_eq(status, S21_INFINITY);
}
END_TEST

START_TEST(test_4) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 28 << 16}};
  set_sign(1, &value_1);
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{0}};

  s21_add(value_1, value_1, &value_expected);
  int status = s21_mul(value_1, value_2, &value_result);

  ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_5) {
  s21_decimal value_1 = {{12345678, 0, 0, 0}};
  s21_decimal value_2 = {{87654321, 0, 0, 0}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{652409070, 251958, 0, 0}};

  s21_mul(value_1, value_2, &value_result);

  ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_6) {
  s21_decimal value_1 = {{3, 0, 0, 0}};
  set_sign(1, &value_1);
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{6, 0, 0, 0}};
  set_sign(1, &value_expected);

  s21_mul(value_1, value_2, &value_result);

  ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_7) {
  s21_decimal value_1 = {{123456, 0xFFFFFFFF, 0xFFFFFFFF, 28 << 16}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{123456, 0xFFFFFFFF, 0xFFFFFFFF, 28 << 16}};

  s21_mul(value_1, value_2, &value_result);

  ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_8) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{0, 0, 0, 0}};

  s21_mul(value_1, value_2, &value_result);

  ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_9) {
  s21_decimal value_1 = {{123456, 12345, 0, 13 << 16}};
  s21_decimal value_2 = {{1, 0, 0, 28 << 16}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{5, 0, 0, 28 << 16}};

  s21_mul(value_1, value_2, &value_result);

  ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_10) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 1 << 16}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0, 0, 1 << 31}};
  s21_decimal value_result = {{0}};

  int status = s21_mul(value_1, value_2, &value_result);

  ck_assert_int_eq(status, S21_NEG_INFINITY);
}
END_TEST

START_TEST(test_11) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 10 << 16}};
  s21_decimal value_2 = {{3, 0, 0, 1 << 31}};
  s21_decimal value_result = {{0}};
  s21_decimal value_expected = {{0}};

  s21_add(value_1, value_1, &value_expected);
  s21_add(value_expected, value_1, &value_expected);
  set_sign(1, &value_expected);

  int status = s21_mul(value_1, value_2, &value_result);

  ck_assert_int_eq(status, S21_OK);
}
END_TEST

TCase *s21_test_mul(void) {
  TCase *testCase = tcase_create("mul");

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
