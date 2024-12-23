#include "../s21_decimal.h"
#define OPERATION_OK 1
#define OPERATION_ERROR 0
int is_bits_0_15(s21_decimal value)
{ // these bits should be zero
	return (value.bits[3] & 0x0000FFFF) == 0 ? OPERATION_OK : OPERATION_ERROR;
}

int is_bits_16_23(s21_decimal value)
{ // these bits 10^[0; 28]
	return ((value.bits[3] & 0x00FF0000) >> 16) <= 28 ? OPERATION_OK : OPERATION_ERROR;
}

int is_bits_24_30(s21_decimal value)
{ // these bits should be zero
	return (value.bits[3] & 0xFF000000) == 0 ? OPERATION_OK : OPERATION_ERROR;
}

int get_sign_number(s21_decimal decimal)
{ // get sign of number
	return (decimal.bits[3] >> 31) & 1 ? 1 : -1;
}
int get_bits_16_23(s21_decimal decimal)
{ // these bits 10^[0; 28]
	return ((decimal.bits[3] & 0x00FF0000) >> 16);
}
int s21_sign_get(s21_decimal decimal1, int index, int numBits)
{
	return (decimal1.bits[numBits] >> index) & 1;
}
int s21_normalization(s21_decimal *value1, s21_decimal *value2)
{
	int pow_value_1 = is_bits_24_30(*value1);
	int pow_value_2 = is_bits_24_30(*value2);

	// Максимальный допустимый масштаб
	const int MAX_SCALE = 28;
	bool error = 1;
	// Нормализуем первое число до масштаба второго
	while (pow_value_1 < pow_value_2 && error)
	{
		if (multiply_by_10(value1) == ARITHMETIC_OVERFLOW)
		{
			error = 0;
		}
		pow_value_1++;
	}

	// Нормализуем второе число до масштаба первого
	while (pow_value_2 < pow_value_1 && error)
	{
		if (multiply_by_10(value2) == ARITHMETIC_OVERFLOW)
		{
			error = 0;
		}
		pow_value_2++;
	}

	// Проверка, что итоговый масштаб не превышает допустимый
	if (pow_value_1 > MAX_SCALE || pow_value_2 > MAX_SCALE)
	{

		error = 0;
	}

	// Дополнительные проверки на корректность знаков и масштабов
	unsigned int sign_bit1 = value1->bits[3] & 0x80000000;
	unsigned int sign_bit2 = value2->bits[3] & 0x80000000;
	// под вопросом нужна ли эта проверка но я оставлю
	value1->bits[3] = (value1->bits[3] & 0x7FFFFFFF) | sign_bit1;
	value2->bits[3] = (value2->bits[3] & 0x7FFFFFFF) | sign_bit2;
	return error;
}

int multiply_by_10(s21_decimal *decimal)
{
	s21_decimal temp = *decimal;
	int status = ARITHMETIC_OK;
	int flag = 0;
	for (int i = 0; i < 3 && status != ARITHMETIC_OVERFLOW; i++)
	{
		for (int j = 0; j < 32 && status != ARITHMETIC_OVERFLOW; j++)
		{
			int bit = (temp.bits[i] >> j) & 1;
			if (bit)
			{
				status = s21_add(*decimal, temp, decimal);
				if (status == ARITHMETIC_OVERFLOW)
				{
					status = ARITHMETIC_OVERFLOW;
				}
			}
		}
	}
	return status;
}
void s21_set_bit(s21_decimal *decimal, int bit, int pos, int value)
{
	if (!decimal || bit < 0 || bit >= 3 || pos < 0 || pos >= 32)
		return; // Проверка границ

	if (value)
	{
		decimal->bits[bit] |= (1 << pos);
	}
	else
	{
		decimal->bits[bit] &= ~(1 << pos);
	}
}