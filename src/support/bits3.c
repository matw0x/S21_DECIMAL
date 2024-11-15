#include "../s21_decimal.h"

OPERATION_STATUS is_bits_0_15(const s21_decimal value) { // these bits should be zero
    return (value.bits[3] & 0x0000FFFF) == 0 ? OK : ERROR;
}

OPERATION_STATUS is_bits_16_23(const s21_decimal value) { // these bits 10^[0; 28]
    return ((value.bits[3] & 0x00FF0000) >> 16) <= 28 ? OK : ERROR;
}

OPERATION_STATUS is_bits_24_30(const s21_decimal value) { // these bits should be zero
    return (value.bits[3] & 0xFF000000) == 0 ? OK : ERROR;
}

int get_bit_31(const s21_decimal value) { // get sign of number
    return (value.bits[3] >> 31) == 0 ? 1 : -1;
}