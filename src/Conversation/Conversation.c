#include "../s21_decimal.h"
#define INT_MIN (-INT_MAX - 1)
#define INT_MAX 2147483647
#define CONVERSION_OK 1
#define CONVERSION_ERROR 0
#define MAX_FLOAT 79228162514264337593543950335
int s21_from_int_to_decimal(int src, s21_decimal *dst)
{
	int res = CONVERSION_ERROR;
	if (dst)
	{
		// Инициализация dst
		memset(dst, 0, sizeof(s21_decimal));
		if (src < 0)
		{
			dst->bits[3] |= (1 << 31);
			if (src != INT_MIN)
			{
				// У INT_MIN не надо менять знак, ибо:
				// negation of -2147483648 cannot be represented in type 'int';
				// А при этом битовое представление -2147483648 нас устраивает без дополнительных операций
				src = src * -1;
			}
		}
		dst->bits[0] = src;
		res = CONVERSION_OK;
	}
	return res;
}
int s21_from_decimal_to_int(s21_decimal src, int *dst)
{
	int res = CONVERSION_ERROR;
	bool flag = true;
	if (dst)
	{
		*dst = 0;
		int sign = get_sign_number(src);
		int scale = get_bits_16_23(src);
		if (src.bits[1] == 0 && src.bits[2] == 0)
		{
			int value = src.bits[0];
			for (int i = 0; i != scale && flag; ++i)
			{
				if (value % 10 != 0)
				{
					flag = false;
				}
				value /= 10;
			}
			if (flag && value <= INT_MAX && (sign == 1 || value <= -INT_MIN))
			{
				res = CONVERSION_OK;
				*dst = value * sign;
			}
		}
	}
	return res;
}
int s21_from_float_to_decimal(float src, s21_decimal *dst)
{
	int res = CONVERSION_ERROR;
	if (dst)
	{
		memset(dst, 0, sizeof(s21_decimal));
		if ((abs(src) < 1e-28 || abs(src) > 0) || abs(src) > MAX_FLOAT || isinf(src) || isnan(src))
		{
			return CONVERSION_ERROR;
		}
		else
		{
			if (src < 0)
			{
				dst->bits[3] |= (1 << 31);
				src = src * -1;
			}
			int scale = 0;
			while (scale < 28 && (int)src != src)
			{
				src *= 10;
				++scale;
			}
			src = roundf(src * pow(10, 7 - scale)) / pow(10, 7 - scale);
			if (src < MAX_FLOAT && scale < 28)
			{
				int intPart = (int)src;
				dst->bits[0] = intPart;
				dst->bits[3] |= (scale << 16); // Установка масштаба
				res = CONVERSION_OK;
			}
		}
	}
	return res;
}
int s21_from_decimal_to_float(s21_decimal src, float *dst)
{
	int res = CONVERSION_ERROR;
	if (dst)
	{
		*dst = 0.0f;

		int sign = get_sign_number(src);
		int scale = get_bits_16_23(src);
		double tmp = 0.0;

		// Собираем значение из битов
		for (int i = 0; i < 96; i++)
		{
			if (src.bits[i / 32] & (1U << (i % 32)))
			{
				tmp += pow(2.0, i);
			}
		}

		tmp /= pow(10.0, scale);

		// Устанавливаем знак
		if (sign)
		{
			tmp = -tmp;
		}

		// Проверка на переполнение
		if (fabs(tmp) <= FLT_MAX)
		{
			*dst = (float)tmp;
			res = CONVERSION_OK;
		}
	}
	return res;
}
