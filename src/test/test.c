#include "test_s21_decimal.h"

int main(void)
{
	int failed = 0;
	Suite *suite_s21_decimal = suite_create("s21_decimal.h");
	// suite_add_tcase(suite_s21_decimal, s21_test_add());
	// suite_add_tcase(suite_s21_decimal, s21_test_sub());
	// suite_add_tcase(suite_s21_decimal, s21_test_mul());
	// suite_add_tcase(suite_s21_decimal, s21_test_div());

	suite_add_tcase(suite_s21_decimal, s21_test_is_equal());
	suite_add_tcase(suite_s21_decimal, s21_test_is_greater_or_equal());
	suite_add_tcase(suite_s21_decimal, s21_test_is_greater());
	suite_add_tcase(suite_s21_decimal, s21_test_is_less_or_equal());
	suite_add_tcase(suite_s21_decimal, s21_test_is_less());
	suite_add_tcase(suite_s21_decimal, s21_test_is_not_equal());
	//   suite_add_tcase(suite_s21_decimal, s21_test_from_decimal_to_float());
	//   suite_add_tcase(suite_s21_decimal, s21_test_from_decimal_to_int());
	//   suite_add_tcase(suite_s21_decimal, s21_test_from_float_to_decimal());
	//   suite_add_tcase(suite_s21_decimal, s21_test_from_int_to_decimal());

	//   suite_add_tcase(suite_s21_decimal, s21_test_negate());
	//   suite_add_tcase(suite_s21_decimal, s21_test_round());
	//   suite_add_tcase(suite_s21_decimal, s21_test_truncate());
	//   suite_add_tcase(suite_s21_decimal, s21_test_floor());

	SRunner *runner = srunner_create(suite_s21_decimal);

	srunner_run_all(runner, CK_NORMAL);
	failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	return (failed == 0) ? 0 : 1;
}