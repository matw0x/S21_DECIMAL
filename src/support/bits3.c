#include "../s21_decimal.h"

int is_bits_0_15(s21_decimal value)
{
	return (value.bits[3] & 0x0000FFFF) == 0 ? OPERATION_OK : OPERATION_ERROR;
}

// Проверка, что биты 16-23 находятся в диапазоне [0; 28]
int is_bits_16_23(s21_decimal value)
{
	int scale = (value.bits[3] >> 16) & 0xFF;
	return scale <= MAX_SCALE ? OPERATION_OK : OPERATION_ERROR;
}

// Проверка, что биты 24-30 равны 0
int is_bits_24_30(s21_decimal value)
{
	return (value.bits[3] & 0x7F000000) == 0 ? OPERATION_OK : OPERATION_ERROR;
}

// Получение знака числа (-1 или 1)
int get_sign_number(s21_decimal decimal)
{
	return (decimal.bits[3] >> 31) & 1 ? -1 : 1;
}

// Получение масштаба числа (биты 16-23)
int get_bits_16_23(s21_decimal decimal)
{
	return (decimal.bits[3] >> 16) & 0xFF;
}

// Установка значения бита в числе
void s21_set_bit(s21_decimal *decimal, int bit, int pos, int value)
{
	if (value)
	{
		decimal->bits[bit] |= (1 << pos);
	}
	else
	{
		decimal->bits[bit] &= ~(1 << pos);
	}
}

// Нормализация масштабов двух чисел
int s21_normalization(s21_decimal *value1, s21_decimal *value2)
{
	if (!value1 || !value2)
	{
		return OPERATION_ERROR; // Проверка на NULL
	}

	int scale1 = get_power(value1);
	int scale2 = get_power(value2);

	while (scale1 < scale2)
	{
		if (multiply_by_10(value1) == ARITHMETIC_OVERFLOW)
		{
			return ARITHMETIC_OVERFLOW;
		}
		scale1++;
	}

	while (scale2 < scale1)
	{
		if (multiply_by_10(value2) == ARITHMETIC_OVERFLOW)
		{
			return ARITHMETIC_OVERFLOW;
		}
		scale2++;
	}

	if (scale1 > MAX_SCALE || scale2 > MAX_SCALE)
	{
		return ARITHMETIC_OVERFLOW;
	}

	set_power(value1, scale1);
	set_power(value2, scale2);

	return OPERATION_OK;
}
// Умножение числа на 10
int multiply_by_10(s21_decimal *decimal)
{
	s21_decimal ten = {{10, 0, 0, 0}};
	s21_decimal result = {{0, 0, 0, 0}};

	if (s21_mul(*decimal, ten, &result) != ARITHMETIC_OK)
	{
		return ARITHMETIC_OVERFLOW;
	}

	*decimal = result;
	return ARITHMETIC_OK;
}

// Деление числа на 10 с остатком
unsigned int div_mod_ten(s21_decimal *value, int update_value)
{
	s21_decimal ten = {{10, 0, 0, 0}};
	s21_decimal quotient = {{0, 0, 0, 0}};
	s21_decimal remainder = {{0, 0, 0, 0}};

	if (s21_div(*value, ten, &quotient) != ARITHMETIC_OK)
	{
		return 0; // Ошибка деления
	}

	if (s21_mul(quotient, ten, &remainder) != ARITHMETIC_OK)
	{
		return 0; // Ошибка умножения
	}

	if (s21_sub(*value, remainder, &remainder) != ARITHMETIC_OK)
	{
		return 0; // Ошибка вычитания
	}

	if (update_value)
	{
		*value = quotient;
	}

	return remainder.bits[0];
}

void set_power(s21_decimal *value, int scale)
{
	value->bits[3] &= ~(0xFF << 16); // Очистка битов масштаба
	value->bits[3] |= (scale & 0xFF) << 16;
}

// Получение масштаба числа
int get_power(const s21_decimal *value)
{
	return (value->bits[3] >> 16) & 0xFF;
}

// Получение знака числа
int get_sign(const s21_decimal *value)
{
	return (value->bits[3] >> 31) & 1;
}

// Установка знака числа
void set_sign(int sign, s21_decimal *value)
{
	if (sign)
	{
		value->bits[3] |= (1 << 31);
	}
	else
	{
		value->bits[3] &= ~(1 << 31);
	}
}
