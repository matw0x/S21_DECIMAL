#include "test_s21_decimal.h"

START_TEST(test_1)
{
	s21_decimal value_1 = {{123, 0, 0, (2 << 16)}};
	s21_decimal value_2 = {{123, 0, 0, (2 << 16)}};
	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{0, 0, 0, (0 << 16)}};

	int result = s21_sub(value_1, value_2, &value_result);

	ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_2)
{
	s21_decimal value_1 = {{123, 0, 0, (2 << 16)}};
	set_sign(1, &value_1);
	s21_decimal value_2 = {{123, 0, 0, (2 << 16)}};
	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{246, 0, 0, (2 << 16)}};
	set_sign(1, &value_expected);

	s21_sub(value_1, value_2, &value_result);

	ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_3)
{
	s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, (0 << 16)}};
	set_sign(1, &value_1);
	s21_decimal value_2 = {{1, 0, 0, (0 << 16)}};

	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{0}};

	int expected = S21_NEG_INFINITY;
	int result = s21_sub(value_1, value_2, &value_result);

	ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_4)
{
	s21_decimal value_1 = {{123, 0, 0, (0 << 16)}};
	set_sign(1, &value_1);
	s21_decimal value_2 = {{123, 0, 0, (0 << 16)}};
	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{246, 0, 0, (0 << 16)}};
	set_sign(1, &value_expected);

	s21_sub(value_1, value_2, &value_result);

	ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_5)
{
	s21_decimal value_1 = {{123, 0, 0, (2 << 16)}};
	s21_decimal value_2 = {{123, 0, 0, (1 << 16)}};
	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{1107, 0, 0, (2 << 16)}};
	set_sign(1, &value_expected);

	int result = s21_sub(value_1, value_2, &value_result);

	ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST
START_TEST(test_6)
{
	s21_decimal value_1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
	s21_decimal value_2 = {{0x1, 0x0, 0x0, 0x0}};
	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

	int result = s21_sub(value_1, value_2, &value_result);

	ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_7)
{
	s21_decimal value_1 = {{0, 0, 0, (1 << 16)}};
	s21_decimal value_2 = {{0, 0, 0, (2 << 16)}};
	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{0, 0, 0, (2 << 16)}};

	int expected = S21_OK;
	int result = s21_add(value_1, value_2, &value_result);

	ck_assert_int_eq(result, expected);
	ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_8)
{
	s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, (0 << 16)}};
	s21_decimal value_2 = {{1, 0, 0, (0 << 16)}};
	set_sign(1, &value_2);

	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{0}};

	int expected = S21_INFINITY;
	int result = s21_sub(value_1, value_2, &value_result);

	ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(test_9)
{
	s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, (2 << 16)}};
	set_sign(1, &value_1);
	s21_decimal value_2 = {{1, 0, 0, (10 << 16)}};
	set_sign(1, &value_2);
	s21_decimal value_result = {{0}};

	int result = s21_sub(value_1, value_2, &value_result);

	ck_assert(s21_is_equal(value_result, value_1));
	ck_assert_int_eq(result, S21_OK);
}
END_TEST

TCase *s21_test_sub(void)
{
	TCase *testCase = tcase_create("sub");

	tcase_add_test(testCase, test_1);
	tcase_add_test(testCase, test_2);
	tcase_add_test(testCase, test_3);
	tcase_add_test(testCase, test_4);
	tcase_add_test(testCase, test_5);
	tcase_add_test(testCase, test_6);
	tcase_add_test(testCase, test_7);
	tcase_add_test(testCase, test_8);
	tcase_add_test(testCase, test_9);

	return testCase;
}
