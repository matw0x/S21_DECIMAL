#include "../s21_decimal.h"

OPERATION_STATUS is_empty(const s21_decimal value) {
    return (value.bits[0] == 0 && value.bits[1] == 0 
            && value.bits[2] == 0) == true ? OK : ERROR;
}

OPERATION_STATUS is_valid_decimal(const s21_decimal value) {
    return (!is_empty(value) && is_bits_0_15(value) && is_bits_16_23(value) &&
            is_bits_24_30(value)) == true ? OK : ERROR;
}