#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
{
	if (!result)
	{
		return OPERATION_ERROR; // Проверка на NULL
	}
	memset(result, 0, sizeof(s21_decimal));

	int status = s21_normalization(&value_1, &value_2);
	if (status != OPERATION_OK)
	{
		return status;
	}

	int carry = 0;
	for (int i = 0; i < 3; ++i)
	{
		uint64_t temp = (uint64_t)value_1.bits[i] + value_2.bits[i] + carry;
		result->bits[i] = (uint32_t)temp;
		carry = (temp >> 32) & 1;
	}

	if (carry)
	{
		return ARITHMETIC_OVERFLOW;
	}

	set_power(result, get_power(&value_1));
	set_sign(get_sign(&value_1), result);

	return OPERATION_OK;
}
// Сравнение чисел не считая знак
int compare_only_numbers(s21_decimal value_first, s21_decimal value_second)
{
	for (int i = 2; i >= 0; --i)
	{
		if (value_first.bits[i] > value_second.bits[i])
		{
			return 1;
		}
		else if (value_first.bits[i] < value_second.bits[i])
		{
			return -1;
		}
	}
	return 0;
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
	if (!result)
	{
		return OPERATION_ERROR; // Проверка на NULL
	}
	memset(result, 0, sizeof(s21_decimal));

	int sign1 = get_sign(&value_1);
	int sign2 = get_sign(&value_2);

	if (sign1 == sign2)
	{
		if (compare_only_numbers(value_1, value_2) >= 0)
		{
			s21_basic_sub(value_1, value_2, result);
			set_sign(sign1, result);
		}
		else
		{
			s21_basic_sub(value_2, value_1, result);
			set_sign(!sign1, result);
		}
	}
	else
	{
		set_sign(0, &value_2);
		s21_add(value_1, value_2, result);
		set_sign(sign1, result);
	}

	set_power(result, get_power(&value_1));
	return OPERATION_OK;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
{
	if (!result)
	{
		return OPERATION_ERROR; // Проверка на NULL
	}
	memset(result, 0, sizeof(s21_decimal));

	for (int i = 0; i < 96; i++)
	{
		if (s21_get_bit(&value_2, i))
		{
			s21_decimal temp = value_1;
			if (shift_decimal__left(&temp, i) != OPERATION_OK || s21_add(*result, temp, result) != OPERATION_OK)
			{
				return ARITHMETIC_OVERFLOW;
			}
		}
	}

	int final_sign = get_sign(&value_1) ^ get_sign(&value_2);
	set_sign(final_sign, result);

	return OPERATION_OK;
}
int shift_decimal__left(s21_decimal *value, int shift)
{
	int status = ARITHMETIC_OK;
	if (shift < 0 || shift > 96)
	{
		return ARITHMETIC_OVERFLOW;
	}

	while (shift > 0)
	{
		int step = shift > 31 ? 31 : shift; // Максимальный сдвиг за раз
		unsigned int carry = 0;

		for (int i = 0; i < 3; i++)
		{
			unsigned int new_carry = (value->bits[i] >> (32 - step)) & ((1U << step) - 1);
			value->bits[i] = (value->bits[i] << step) | carry;
			carry = new_carry;
		}
		if (carry != 0) // Если есть остаток, значит, переполнение
		{
			status = ARITHMETIC_OVERFLOW;
			break;
		}
		shift -= step;
	}
	return status;
}
int shift_decimal__right(s21_decimal *value, int shift)
{
	int status = ARITHMETIC_OK;
	if (shift < 0 || shift > 96)
	{
		return ARITHMETIC_OVERFLOW;
	}

	while (shift > 0)
	{
		int step = shift > 31 ? 31 : shift;
		unsigned int carry = 0;

		for (int i = 2; i >= 0; i--)
		{
			unsigned int new_carry = (value->bits[i] & ((1U << step) - 1)) << (32 - step);
			value->bits[i] = (value->bits[i] >> step) | carry;
			carry = new_carry;
		}
		shift -= step;
	}
	return status;
}
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
{
	int status = ARITHMETIC_OK;
	memset(result, 0, sizeof(s21_decimal));

	// Проверка деления на 0
	if (is_zero(value_2))
	{
		return ARITHMETIC_DIVISION_BY_ZERO;
	}

	// Нормализация чисел
	status = s21_normalization(&value_1, &value_2);
	if (status != ARITHMETIC_OK)
	{
		return status;
	}

	s21_decimal temp = value_2;
	s21_decimal quotient = {{0}};
	s21_decimal remainder = value_1;
	int shift_count = 0;

	// Увеличиваем делитель до тех пор, пока он не превысит делимое
	while (!s21_is_less(remainder, temp) && shift_count < 96)
	{
		shift_decimal__left(&temp, 1);
		shift_count++;
	}

	// Основной цикл деления
	for (int i = shift_count; i >= 0; --i)
	{
		shift_decimal__right(&temp, 1);
		if (!is_less(remainder, temp))
		{
			s21_sub(remainder, temp, &remainder);
			s21_set_bit(&quotient, i / 32, i % 32, 1);
		}
	}

	*result = quotient;

	// Обработка остатка
	if (!is_zero(remainder))
	{
		int power = 0;
		while (power < 28 && !is_zero(remainder))
		{
			multiply_by_10(&remainder);
			if (!is_less(remainder, value_2))
			{
				s21_sub(remainder, value_2, &remainder);
				s21_set_bit(result, (power + 96) / 32, (power + 96) % 32, 1);
			}
			power++;
		}
		set_power(result, power);
	}

	// Устанавливаем знак результата
	if (get_sign_number(value_1) != get_sign_number(value_2))
	{
		set_sign(1, result);
	}
	else
	{
		set_sign(0, result);
	}

	return status;
}
int is_zero(s21_decimal dec)
{
	for (int i = 0; i < 3; i++)
	{
		if (dec.bits[i] != 0)
		{
			return 0;
		}
	}
	return 1;
}
void set_power(s21_decimal *dec, int power)
{
	for (int i = 16; i <= 23; i++)
	{
		set_bit(power >> (i - 16) & 1, dec, i + 96);
	}
}