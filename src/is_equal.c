
#include "s21_decimal.h"

int s21_is_equal(s21_decimal decimal1, s21_decimal decimal2)
{
	COMPARISON_STATUS res = COMPARISON_FALSE;

	s21_normalization(&decimal1, &decimal2);
	if (decimal1.bits[0] == 0 && decimal1.bits[1] == 0 && decimal1.bits[2] == 0 && decimal2.bits[0] == 0 && decimal2.bits[1] == 0 && decimal2.bits[2] == 0)
	{
		res = COMPARISON_TRUE;
	}
	else
	{
		if (decimal1.bits[0] == decimal2.bits[0] && decimal1.bits[1] == decimal2.bits[1] && decimal1.bits[2] == decimal2.bits[2] && decimal1.bits[3] == decimal2.bits[3])
		{
			res = COMPARISON_TRUE;
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

int s21_is_greater(s21_decimal value_1, s21_decimal value_2)
{
	int result = COMPARISON_FALSE;

	if (is_zero(value_1) && is_zero(value_2))
	{

		return COMPARISON_FALSE; // 0 и -0
	}
	int sign1 = get_sign_number(value_1);
	int sign2 = get_sign_number(value_2);
	
	if (sign1 == 0 && sign2 == 1)
	{
		return COMPARISON_TRUE;
	}
	if (sign1 == 1 && sign2 == 0)
	{
		return COMPARISON_FALSE;
	}
	if (sign1 == 1 && sign2 == 1)
	{
		result = s21_is_less_handle(value_1, value_2);
	}
	else
	{
		result = s21_is_greater_handle(value_1, value_2);
	}

	return result;
}

int s21_is_greater_handle(s21_decimal value_1, s21_decimal value_2)
{
	
	int result = COMPARISON_FALSE;
	
	if (!s21_normalization(&value_1, &value_2))
	{
	
		return result;
	}
	
	
	for (int bit = 0; bit != 3; ++bit)
	{
		if (value_1.bits[bit] > value_2.bits[bit])
		{
			result= COMPARISON_TRUE;
		}
		else if (value_1.bits[bit] < value_2.bits[bit])
		{
			result= COMPARISON_FALSE;
		}
	}

	return result;
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

	// Проверка условия: первое число не больше или равно второму
	if (!s21_is_greater_or_equal(decimal1, decimal2))
	{
		res = COMPARISON_TRUE;
	}

	return res;
}

int s21_is_less_or_equal(s21_decimal decimal1, s21_decimal decimal2)
{
	COMPARISON_STATUS res = COMPARISON_FALSE;

	// Проверка условия: первое число не больше второго
	if (!s21_is_greater(decimal1, decimal2))
	{
		res = COMPARISON_TRUE;
	}

	return res;
}

int s21_is_less_handle(s21_decimal value_1, s21_decimal value_2)
{
	int result = COMPARISON_FALSE;

	// Нормализация чисел
	s21_normalization(&value_1, &value_2);

	// Сравнение побитово
	for (int bit = 2; bit >= 0; --bit)
	{
		if (value_1.bits[bit] < value_2.bits[bit])
		{
			result = COMPARISON_TRUE;
			break;
		}
		else if (value_1.bits[bit] > value_2.bits[bit])
		{
			result = COMPARISON_FALSE;
			break;
		}
	}
	return result;
}
s21_decimal s21_abs(s21_decimal value)
{
	s21_decimal result = value;
	result.bits[3] &= ~(1 << 31); // Убираем знак
	return result;
}