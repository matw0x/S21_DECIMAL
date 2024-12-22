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
void s21_normalization(s21_decimal *value1, s21_decimal *value2) {

    int pow_value_1 = is_bits_24_30(*value1);
    int pow_value_2 = is_bits_24_30(*value2);

    while (pow_value_1 < pow_value_2) {
        if (multiply_by_10(value1) == ARITHMETIC_OVERFLOW) break; // Проверка переполнения
        pow_value_1++;
    }
    while (pow_value_2 < pow_value_1) {
        if (multiply_by_10(value2) == ARITHMETIC_OVERFLOW) break; // Проверка переполнения
        pow_value_2++;
    }
}
int multiply_by_10(s21_decimal *decimal) {
    s21_decimal temp = *decimal;
    int status = ARITHMETIC_OK;
    int flag=0;
    for (int i = 0; i < 3 && status != ARITHMETIC_OVERFLOW; i++) {
        for (int j = 0; j < 32 && status != ARITHMETIC_OVERFLOW; j++) {
            int bit = (temp.bits[i] >> j) & 1;
            if (bit) {
                status = s21_add(*decimal, temp, decimal);
                if (status == ARITHMETIC_OVERFLOW) {
                    status= ARITHMETIC_OVERFLOW; 
                }
            }
        }
    }
    return status;
}
void s21_set_bit(s21_decimal *decimal, int bit, int pos, int value) {
    if (!decimal || bit < 0 || bit >= 3 || pos < 0 || pos >= 32) return; // Проверка границ

    if (value) {
        decimal->bits[bit] |= (1 << pos);
    } else {
        decimal->bits[bit] &= ~(1 << pos);
    }
}