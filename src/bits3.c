#include "s21_decimal.h"
#include <stdlib.h>
#define MAX_SCALE 28
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
	return (decimal.bits[3] >> 31) & 1;
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
		
		return OPERATION_ERROR;
	}

	int scale1 = get_power(value1);
	int scale2 = get_power(value2);
	s21_decimal temp1 = *value1;

	bool flag1 = false;
	int temp_scale1 = scale1;
	

	while (scale1 < scale2)
	{
	
		if (multiply_by_10(&temp1) == ARITHMETIC_OVERFLOW)
		{

			flag1 = true;
			break;
		}
		scale1++;
		temp_scale1++;
		
		
	}
	if (!flag1)
	{
		
		*value1 = temp1;
		scale1 = temp_scale1;
	}
	
	s21_decimal temp2 = *value2;
	bool flag2 = false;
	int temp_scale2 = scale2;
	while (temp_scale2 < scale1)
	{
		if (multiply_by_10(&temp2) == ARITHMETIC_OVERFLOW)
		{
			flag2 = true;
			break;
		}
		temp_scale2++;
	}
	if (!flag2)
	{
		*value2 = temp2;
		scale2 = temp_scale2;
	}

	while (scale1 > scale2)
	{

		div_by_10_manual(value1);
		scale1--;
	}

	while (scale2 > scale1)
	{

		div_by_10_manual(value2);
		scale2--;
	}

	set_power(value1, scale1);
	set_power(value2, scale2);
	
	return 1;
}

// Умножение числа на 10
int multiply_by_10(s21_decimal *decimal) {
    // Работаем с 96-битным целым числом
    uint32_t part0 = decimal->bits[0]; // Младшая часть
    uint32_t part1 = decimal->bits[1]; // Средняя часть
    uint32_t part2 = decimal->bits[2]; // Старшая часть

    uint64_t carry = 0; // Перенос для умножения
    uint64_t temp;

    // Умножение младшей части на 10
    temp = (uint64_t)part0 * 10 + carry;
    carry = temp >> 32;
    decimal->bits[0] = (uint32_t)(temp & 0xFFFFFFFF);

    // Умножение средней части на 10
    temp = (uint64_t)part1 * 10 + carry;
    carry = temp >> 32;
    decimal->bits[1] = (uint32_t)(temp & 0xFFFFFFFF);

    // Умножение старшей части на 10
    temp = (uint64_t)part2 * 10 + carry;
    carry = temp >> 32;
    decimal->bits[2] = (uint32_t)(temp & 0xFFFFFFFF);

    // Если есть перенос после старшей части, то переполнение
    if (carry > 0) {
        return ARITHMETIC_OVERFLOW;
    }

    // Работаем с коэффициентом масштабирования
    int scale = get_power(decimal); // Извлекаем степень
    if (scale < 28) {
        scale += 1;
        decimal->bits[3] = (decimal->bits[3] & 0xFF00FFFF) | (scale << 16);
    } else {
        // Если степень слишком велика, проверяем, можно ли округлить
        return ARITHMETIC_OVERFLOW;
    }

    return ARITHMETIC_OK;
}


// деление числа на 10
int div_by_10(s21_decimal *decimal)
{
	s21_decimal ten = {{10, 0, 0, 0}};
	s21_decimal result = {{0, 0, 0, 0}};

	if (s21_div(*decimal, ten, &result) != ARITHMETIC_OK)
	{
		return ARITHMETIC_OVERFLOW;
	}

	*decimal = result;
	return ARITHMETIC_OK;
}
// Деление числа на 10 с остатком
int div_mod_ten(s21_decimal *decimal, int flag)
{
	s21_decimal ten = {{10, 0, 0, 0}};
	s21_decimal quotient = {{0, 0, 0, 0}};
	s21_decimal remainder = {{0, 0, 0, 0}};

	// Деление на 10
	if (s21_div(*decimal, ten, &quotient) != ARITHMETIC_OK)
	{
		return OPERATION_ERROR; // Ошибка деления
	}

	// Умножение результата на 10
	if (s21_mul(quotient, ten, &remainder) != ARITHMETIC_OK)
	{
		return OPERATION_ERROR; // Ошибка умножения
	}

	// Вычисление остатка
	if (s21_sub(*decimal, remainder, &remainder) != ARITHMETIC_OK)
	{
		return OPERATION_ERROR; // Ошибка вычитания
	}

	// Обновление значения, если установлен флаг
	if (flag)
	{
		*decimal = quotient;
	}

	// Возврат младших 32 бит остатка
	return remainder.bits[0];
}

void set_power(s21_decimal *value, int scale)
{
	value->bits[3] &= ~(0xFF << 16); // Очистка битов масштаба
	value->bits[3] |= (scale & 0xFF) << 16;
}

// Получение масштаба числа
int get_power(s21_decimal *value)
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
int s21_get_bit(const s21_decimal *decimal, int position)
{
	if (position < 0 || position >= 128)
	{
		return 0; // Если позиция вне диапазона, возвращаем 0
	}
	int bit_index = position / 32;
	int bit_position = position % 32;
	return (decimal->bits[bit_index] >> bit_position) & 1;
}
int div_by_10_manual(s21_decimal *decimal)
{
	s21_decimal result = {{0, 0, 0, 0}};
	s21_decimal remainder = {{0, 0, 0, 0}};
	s21_decimal ten = {{10, 0, 0, 0}};

	for (int i = 127; i >= 0; i--)
	{
		// Сдвигаем остаток влево
		shift_decimal__left(&remainder, 1);

		// Добавляем текущий бит
		if (s21_get_bit(decimal, i))
		{
			remainder.bits[0] |= 1;
		}

		// Если остаток больше или равен 10, вычитаем 10
		if (compare_only_numbers(remainder, ten) >= 0)
		{
			s21_sub(remainder, ten, &remainder);
			result.bits[0] |= 1;
		}

		// Сдвигаем результат влево
		if (i != 0)
		{
			shift_decimal__left(&result, 1);
		}
	}

	*decimal = result;
	return OPERATION_OK;
}
int s21_round_mantissa(s21_decimal *value) {
    int scale = get_power(value);
    if (scale == 0) {
			printf("\nMISTAKE\n");
        return 1; // Ошибка: невозможность округления
    }

    // Уменьшаем масштаб
    scale--;
    set_power(value, scale);

    // Округляем мантиссу
    int remainder = value->bits[0] % 10;
    int quotient = value->bits[0] / 10;

    if (remainder > 5 || (remainder == 5 && (quotient & 1) == 1)) {
        quotient++; // Округляем вверх
    }

    value->bits[0] = (int)quotient;
    return 0; // ОК
}
