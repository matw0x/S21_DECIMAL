#include "test_s21_decimal.h"

START_TEST(test_1)
{
	s21_decimal value_1 = {{123, 0, 0, (0 << 16)}};
	s21_decimal value_2 = {{123, 0, 0, (0 << 16)}};
	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{246, 0, 0, (0 << 16)}};

	s21_add(value_1, value_2, &value_result);

	ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_2)
{
	s21_decimal value_1 = {{123, 0, 0, (0 << 16)}};
	set_sign(1, &value_1);
	s21_decimal value_2 = {{123, 0, 0, (0 << 16)}};
	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{0, 0, 0, (0 << 16)}};

	s21_add(value_1, value_2, &value_result);

	ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_3)
{
	s21_decimal value_1 = {{123, 123, 123, (2 << 16)}};
	s21_decimal value_2 = {{123, 123, 123, (2 << 16)}};
	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{246, 246, 246, (2 << 16)}};

	s21_add(value_1, value_2, &value_result);

	ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_4)
{
	s21_decimal value_1 = {{0, 0, 0, (0 << 16)}};
	s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFF1, (0 << 16)}};
	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {
		 {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFF1, (0 << 16)}};

	s21_add(value_1, value_2, &value_result);

	ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_5)
{
	s21_decimal value_1 = {{0xFFFFFFF1, 0xFFFFFFFF, 0xFFFFFFFF, (0 << 16)}};
	s21_decimal value_2 = {{0xFFFFFFF1, 0xFFFFFFFF, 0xFFFFFFF1, (0 << 16)}};
	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{0}};

	int expected = S21_INFINITY;
	int result = s21_add(value_1, value_2, &value_result);

	ck_assert_int_eq(result, expected);
}
END_TEST
START_TEST(test_6)
{
	s21_decimal value_1 = {{0, 0, 0, (0 << 16)}};
	s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, (0 << 16)}};
	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0, (0 << 16)}};

	s21_add(value_1, value_2, &value_result);

	ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_7)
{
	s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, (28 << 16)}};
	s21_decimal value_2 = {{0xFFFFFFF1, 0xFFFFFFFF, 0xFFFFFFFF, (28 << 16)}};
	set_sign(1, &value_2);
	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{14, 0, 0, (28 << 16)}};

	s21_add(value_1, value_2, &value_result);

	ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_8)
{
	s21_decimal value_1 = {{123, 0, 0, (2 << 16)}};
	s21_decimal value_2 = {{123, 0, 0, (1 << 16)}};

	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{1353, 0, 0, (2 << 16)}};

	s21_add(value_1, value_2, &value_result);

	ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_9)
{
	s21_decimal value_1 = {{123, 0, 0, (2 << 16)}};
	s21_decimal value_2 = {{123, 0, 0, (1 << 16)}};
	set_sign(1, &value_2);
	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{1107, 0, 0, (2 << 16)}};
	set_sign(1, &value_expected);

	s21_add(value_1, value_2, &value_result);

	ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_10)
{
	s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
	s21_decimal value_2 = {{6, 0, 0, (1 << 16)}};
	s21_decimal value_result = {{0}};

	int status = s21_add(value_1, value_2, &value_result);

	ck_assert_int_eq(status, S21_INFINITY);
}
END_TEST

START_TEST(test_11)
{
	s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFF155, (7 << 16)}};
	s21_decimal value_2 = {{2, 0, 0, 0}};
	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{0}};
	s21_mul(value_1, value_2, &value_expected);

	s21_add(value_1, value_1, &value_result);

	ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

START_TEST(test_12)
{
	s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFF155, (3 << 16)}};
	s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFF333, (26 << 16)}};
	s21_decimal value_result = {{0}};
	s21_decimal value_expected = {{0x000C16D8, 0, 0xFFFFF156, 3 << 16}};

	s21_add(value_1, value_2, &value_result);

	ck_assert(s21_is_equal(value_result, value_expected));
}
END_TEST

TCase *s21_test_add(void)
{
	TCase *testCase = tcase_create("add");

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
	tcase_add_test(testCase, test_12);

	return testCase;
}
