#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
{
	int status = ARITHMETIC_OK;
	int sign_value_1 = get_sign_number(value_1);
	int sign_value_2 = get_sign_number(value_2);
	if (s21_normalization(&value_1, &value_2))
	{

		if (sign_value_1 == sign_value_2)
		{
			int buffer = 0;
			for (int bit = 0; bit < 3; ++bit)
			{
				for (int i = 0; i < 32; ++i)
				{
					int bit1 = (value_1.bits[bit] >> i) & 1;
					int bit2 = (value_2.bits[bit] >> i) & 1;

					int sum = bit1 + bit2 + buffer;

					if (sum == 2)
					{
						s21_set_bit(result, bit, i, 0);
						buffer = 1;
					}
					else if (sum == 3)
					{
						s21_set_bit(result, bit, i, 1);
						buffer = 1;
					}
					else
					{
						s21_set_bit(result, bit, i, sum);
						buffer = 0;
					}
				}
			}
			if (buffer)
			{
				status = ARITHMETIC_OVERFLOW;
			}
		}
		else
		{
			// if (sign_value_1)
			// {
			// 	s21_negate(&value_1);
			// }
			// else
			// {
			// 	s21_negate(&value_2);
			// }
			s21_sub(value_1, value_2, result);
		}
	}
	else
	{
		status = ARITHMETIC_OVERFLOW;
	}
	return status;
}

// Сравнение чисел не считая знак
int compare_only_numbers(s21_decimal value_first, s21_decimal value_second)
{
	int res = 0;
	for (int i = 3; i >= 0 && !res; i--)
	{
		if (value_first.bits[i] > value_second.bits[i])
			res = 1;
		if (value_first.bits[i] < value_second.bits[i])
			res = -1;
	}
	return res;
}

void s21_basic_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
{
	uint64_t borrow = 0;
	for (int i = 0; i < 4; i++)
	{
		uint64_t diff = (uint64_t)value_1.bits[i] - value_2.bits[i] - borrow;
		result->bits[i] = diff & 0xFFFFFFFF;
		borrow = (diff >> 32) & 1;
	}
}

// Основная функция вычитания
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
{
	int error = ARITHMETIC_OK;
	memset(result, 0, sizeof(s21_decimal));

	int sign_first = get_sign_number(value_1);
	int sign_second = get_sign_number(value_2);

	if (sign_first == sign_second)
	{
		int scale;
		error = s21_normalization(&value_1, &value_2, &scale);
		if (error != ARITHMETIC_OK)
			return error;

		if (compare_only_numbers(value_1, value_2) >= 0)
		{
			s21_basic_sub(value_1, value_2, result);
			set_sign(sign_first, result);
		}
		else
		{
			s21_basic_sub(value_2, value_1, result);
			set_sign(!sign_first, result);
		}
		set_power(result, scale);
	}
	else
	{
		set_sign(0, &value_2);
		error = s21_add(value_1, value_2, result);
		set_sign(sign_first, result);
	}
	return error;
}
