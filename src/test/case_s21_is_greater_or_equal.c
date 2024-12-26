#include "test_s21_decimal.h"

START_TEST(test_1)
{
	s21_decimal value_1 = {{123, 0, 0, (2 << 16)}};
	s21_decimal value_2 = {{123, 0, 0, (2 << 16)}};

	int expected = S21_TRUE;
	int result = s21_is_greater_or_equal(value_1, value_2);

	ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_2)
{
	s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, (0 << 16)}};
	s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, (0 << 16)}};

	int expected = S21_TRUE;
	int result = s21_is_greater_or_equal(value_1, value_2);

	ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_3)
{
	s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, (2 << 16)}};
	s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, (2 << 16)}};

	set_sign(1, &value_2);

	int expected = S21_TRUE;
	int result = s21_is_greater_or_equal(value_1, value_2);

	ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_4)
{
	s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, (3 << 16)}};
	s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, (2 << 16)}};

	int expected = S21_FALSE;
	int result = s21_is_greater_or_equal(value_1, value_2);

	ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_5)
{
	s21_decimal value_1 = {{12300, 0, 0, (2 << 16)}};
	s21_decimal value_2 = {{123000, 0, 0, (3 << 16)}};

	int expected = S21_TRUE;
	int result = s21_is_greater_or_equal(value_1, value_2);

	ck_assert_int_eq(result, expected);
}
END_TEST
START_TEST(test_6)
{
	s21_decimal value_1 = {{0, 0, 0, (0 << 16)}};
	s21_decimal value_2 = {{0, 0, 0, (1 << 16)}};

	int expected = S21_TRUE;
	int result = s21_is_greater_or_equal(value_1, value_2);

	ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_7)
{
	s21_decimal value_1 = {{0, 0, 0, (0 << 16)}};
	s21_decimal value_2 = {{0, 0, 0, (0 << 16)}};

	set_sign(1, &value_1);

	int expected = S21_TRUE;
	int result = s21_is_greater_or_equal(value_1, value_2);

	ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_8)
{
	s21_decimal value_1 = {{0, 123, 0, (28 << 16)}};
	s21_decimal value_2 = {{0, 122, 0, (28 << 16)}};

	int expected = S21_TRUE;
	int result = s21_is_greater_or_equal(value_1, value_2);

	ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_9)
{
	s21_decimal value_1 = {{0, 123, 0, (28 << 16)}};
	s21_decimal value_2 = {{0, 122, 0, (28 << 16)}};

	int expected = S21_TRUE;
	int result = s21_is_greater_or_equal(value_1, value_2);

	ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_10)
{
	s21_decimal value_1 = {{123, 123, 0, (25 << 16)}};
	s21_decimal value_2 = {{123, 122, 0, (6 << 16)}};

	int expected = S21_FALSE;
	int result = s21_is_greater_or_equal(value_1, value_2);

	ck_assert_int_eq(result, expected);
}
END_TEST

TCase *s21_test_is_greater_or_equal(void)
{
	TCase *testCase = tcase_create("is_greater_or_equal");

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

	return testCase;
}
