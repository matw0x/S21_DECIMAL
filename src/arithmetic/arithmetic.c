int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = ARITHMETIC_OK;

    int sign_value_1 = get_sign_number(value_1);
    int sign_value_2 = get_sign_number(value_2);

    int pow_value_1 = is_bits_24_30(value1);
    int pow_value_2 = is_bits_24_30(value2);

    s21_normalization(&value_1,&value_2);

    if (sign_value_1 == sign_value_2) {
        int buffer = 0;
        for (int bit = 0; bit < 3; ++bit) {
            for (int i = 0; i < 32; ++i) {
                int bit1 = (value_1.bits[bit] >> i) & 1;
                int bit2 = (value_2.bits[bit] >> i) & 1;

                int sum = bit1 + bit2 + buffer;

                if (sum == 2) {
                    s21_set_bit(result, bit, i, 0);
                    buffer = 1;
                } else if (sum == 3) {
                    s21_set_bit(result, bit, i, 1);
                    buffer = 1;
                } else {
                    s21_set_bit(result, bit, i, sum);
                    buffer = 0;
                }
            }
        }
        if (buffer) {
            status = ARITHMETIC_OVERFLOW;
        }
    } else {
        if (sign_value_1) {
            s21_negate(&value_1);
        } else {
            s21_negate(&value_2);
        }
        s21_sub(value_1, value_2, result);
    }

    return status;
}
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){
    
}




