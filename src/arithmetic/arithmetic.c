#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
{
	int status = ARITHMETIC_OK;

	// Получаем знаки и масштабы чисел
	int sign_value_1 = get_sign_number(value_1);
	int sign_value_2 = get_sign_number(value_2);

	int pow_value_1 = is_bits_24_30(value_1);
	int pow_value_2 = is_bits_24_30(value_2);

	// Нормализуем числа, если их масштабы различаются
	while (pow_value_1 < pow_value_2)
	{
		multiply_by_10(&value_1);
		pow_value_1++;
	}
	while (pow_value_2 < pow_value_1)
	{
		multiply_by_10(&value_2);
		pow_value_2++;
	}
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
	}
	else
	{
		// Вычитание для чисел с разными знаками
		// if (sign_value_1)
		// {
		// 	s21_negate(&value_1);
		// }
		// else
		// {
		// 	s21_negate(&value_2);
		// }
		// s21_sub(value_1, value_2, result);
	}

	return status;
}
void multiply_by_10(s21_decimal *decimal)
{
	s21_decimal temp = *decimal;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			int bit = (temp.bits[i] >> j) & 1;
			if (bit)
			{
				s21_add(*decimal, temp, decimal);
			}
		}
	}
}
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
{
	int status = ARITHMETIC_OK;
	return status;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
{
}