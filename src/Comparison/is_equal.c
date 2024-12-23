
#include "../s21_decimal.h"
#define COMPARISON_FALSE 0
#define COMPARISON_TRUE 1
int s21_is_equal(s21_decimal decimal1, s21_decimal decimal2)
{
	COMPARISON_STATUS res = COMPARISON_FALSE;
	if (get_sign_number(decimal1) == get_sign_number(decimal2))
	{
		if (get_bits_16_23(decimal1) == get_bits_16_23(decimal2))
		{
			if (decimal1.bits[0] == decimal2.bits[0] && decimal1.bits[1] == decimal2.bits[1] && decimal1.bits[2] == decimal2.bits[2])
			{
				res = COMPARISON_TRUE;
			}
		}
	}
	return res;
}
int s21_is_not_equal(s21_decimal decimal1, s21_decimal decimal2)
{
	COMPARISON_STATUS res;
	if (s21_is_equal(decimal1, decimal2))
	{
		res = COMPARISON_FALSE;
	}
	else
	{
		res = COMPARISON_TRUE;
	}
	return res;
}

int s21_is_greater(s21_decimal decimal1, s21_decimal decimal2)
{
	COMPARISON_STATUS res = COMPARISON_FALSE;

	if (get_sign_number(decimal1) < get_sign_number(decimal2))
	{
		res = COMPARISON_TRUE;
	}
	else if (get_sign_number(decimal1) > get_sign_number(decimal2))
	{
		res = COMPARISON_FALSE;
	}
	else if (get_bits_16_23(decimal1) != get_bits_16_23(decimal2))
	{
		res = get_bits_16_23(decimal1) > get_bits_16_23(decimal2) ? COMPARISON_TRUE : COMPARISON_FALSE;
	}
	else
	{
		bool flag = COMPARISON_TRUE;
		for (int i = 2; i >= 0 && flag; --i)
		{
			if (decimal1.bits[i] > decimal2.bits[i])
			{
				res = COMPARISON_TRUE;
				flag = COMPARISON_FALSE;
			}
			else if (decimal1.bits[i] < decimal2.bits[i])
			{
				res = COMPARISON_FALSE;
				flag = COMPARISON_FALSE;
			}
		}
	}
	return res;
}

int s21_is_greater_or_equal(s21_decimal decimal1, s21_decimal decimal2)
{
	COMPARISON_STATUS res = COMPARISON_FALSE;
	if (s21_is_equal(decimal1, decimal2) || s21_is_greater(decimal1, decimal2))
	{
		res = COMPARISON_TRUE;
	}
	return res;
}
int s21_is_less(s21_decimal decimal1, s21_decimal decimal2)
{
	COMPARISON_STATUS res = COMPARISON_FALSE;
	if (!s21_is_greater_or_equal(decimal1, decimal2))
	{
		res = COMPARISON_TRUE;
	}
	return res;
}
int s21_is_less_or_equal(s21_decimal decimal1, s21_decimal decimal2)
{
	COMPARISON_STATUS res = COMPARISON_FALSE;
	if (!s21_is_greater(decimal1, decimal2))
	{
		res = COMPARISON_TRUE;
	}
	return res;
}
// int main()
// {
// 	// Примеры чисел для тестов
// 	s21_decimal decimal1 = {{1, 0, 0, 0}};				// 1
// 	s21_decimal decimal2 = {{2, 0, 0, 0}};				// 2
// 	s21_decimal decimal3 = {{1, 0, 0, 0}};				// 1
// 	s21_decimal decimal4 = {{1, 0, 0, 0x80000000}}; // -1

// 	// Тестирование s21_is_equal
// 	printf("s21_is_equal(decimal1, decimal2): %d\n", s21_is_equal(decimal1, decimal2));
// 	printf("s21_is_equal(decimal1, decimal3): %d\n", s21_is_equal(decimal1, decimal3));
// 	printf("s21_is_equal(decimal1, decimal4): %d\n", s21_is_equal(decimal1, decimal4));
// 	// Тестирование s21_is_not_equal
// 	printf("s21_is_not_equal(decimal1, decimal2): %d\n", s21_is_not_equal(decimal1, decimal2));
// 	printf("s21_is_not_equal(decimal1, decimal3): %d\n", s21_is_not_equal(decimal1, decimal3));

// 	// Тестирование s21_is_greater
// 	printf("s21_is_greater(decimal1, decimal2): %d\n", s21_is_greater(decimal1, decimal2));
// 	printf("s21_is_greater(decimal2, decimal1): %d\n", s21_is_greater(decimal2, decimal1));

// 	// Тестирование s21_is_less
// 	printf("s21_is_less(decimal1, decimal2): %d\n", s21_is_less(decimal1, decimal2));
// 	printf("s21_is_less(decimal2, decimal1): %d\n", s21_is_less(decimal2, decimal1));

// 	// Тестирование s21_is_greater_or_equal
// 	printf("s21_is_greater_or_equal(decimal1, decimal2): %d\n", s21_is_greater_or_equal(decimal1, decimal2));
// 	printf("s21_is_greater_or_equal(decimal1, decimal3): %d\n", s21_is_greater_or_equal(decimal1, decimal3));

// 	// Тестирование s21_is_less_or_equal
// 	printf("s21_is_less_or_equal(decimal1, decimal2): %d\n", s21_is_less_or_equal(decimal1, decimal2));
// 	printf("s21_is_less_or_equal(decimal1, decimal3): %d\n", s21_is_less_or_equal(decimal1, decimal3));

// 	return 0;
// }