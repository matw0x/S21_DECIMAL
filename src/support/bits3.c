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
void s21_set_bit(s21_decimal *decimal, int bit, int pos, int value)
{
	if (value)
	{
		decimal->bits[bit] |= (1 << pos); // Устанавливаем бит в 1
	}
	else
	{
		decimal->bits[bit] &= ~(1 << pos); // Устанавливаем бит в 0
	}
}