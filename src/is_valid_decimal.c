#include "s21_decimal.h"
#define OPERATION_OK 1
#define OPERATION_ERROR 0
int is_empty(const s21_decimal value)
{
	return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0) == true ? OPERATION_OK : OPERATION_ERROR;
}

int is_valid_decimal(const s21_decimal value)
{
	return (!is_empty(value) && is_bits_0_15(value) && is_bits_16_23(value) &&
			  is_bits_24_30(value)) == true
				  ? OPERATION_OK
				  : OPERATION_ERROR;
}