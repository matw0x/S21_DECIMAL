
#include "../s21_decimal.h"

int s21_is_equal(s21_decimal decimal1, s21_decimal decimal2)
{
	COMPARISON_STATUS res = COMPARISON_FALSE;

	s21_normalization(&decimal1, &decimal2);
	if (decimal1.bits[0] == 0 && decimal1.bits[1] == 0 && decimal1.bits[2] == 0 && decimal2.bits[0] == 0 && decimal2.bits[1] == 0 && decimal2.bits[2] == 0)
	{
		res = COMPARISON_TRUE;
	}
	else
	{
		if (decimal1.bits[0] == decimal2.bits[0] && decimal1.bits[1] == decimal2.bits[1] && decimal1.bits[2] == decimal2.bits[2] && decimal1.bits[3] == decimal2.bits[3])
		{
			res = COMPARISON_TRUE;
		}
	}
	return res;
}
int s21_is_not_equal(s21_decimal decimal1, s21_decimal decimal2)
{
	COMPARISON_STATUS res;
	if (s21_is_equal(decimal1, decimal2))
	{
		res = COMPARISON_FALSE;
	}
	else
	{
		res = COMPARISON_TRUE;
	}
	return res;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2)
{
	int result = COMPARISON_FALSE;

	// Проверка на случай равенства нулей
	if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0 && value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0)
	{
		result = COMPARISON_FALSE; // 0 не больше -0
	}
	else
	{
		int sign1 = s21_decimal_get_sign(value_1);
		int sign2 = s21_decimal_get_sign(value_2);

		if (sign1 == 1 && sign2 == 0)
		{
			// Положительное число всегда больше отрицательного
			result = COMPARISON_TRUE;
		}
		else if (sign1 == 0 && sign2 == 1)
		{
			// Отрицательное число всегда меньше положительного
			result = COMPARISON_FALSE;
		}
		else if (sign1 == 0 && sign2 == 0)
		{
			// Для двух отрицательных чисел выполняем сравнение по модулю
			result = s21_is_less_handle(s21_abs(value_2), s21_abs(value_1));
		}
		else
		{
			// Для положительных чисел сравниваем их значения
			result = s21_is_greater_handle(value_1, value_2);
		}
	}

	return result;
}

int s21_is_greater_handle(s21_decimal value_1, s21_decimal value_2)
{
	int result = COMPARISON_FALSE;

	// Нормализация чисел (выравнивание степеней)
	s21_normalization(&value_1, &value_2);
	bool success = 1;
	// Сравнение чисел побитово, начиная с более значимых битов
	for (int bit = 2; bit >= 0 && success; --bit)
	{ // Начинаем с младшего разряда
		if (value_1.bits[bit] > value_2.bits[bit])
		{
			result = COMPARISON_TRUE;
			success = 0;
		}
		else if (value_1.bits[bit] < value_2.bits[bit])
		{
			result = COMPARISON_FALSE;
			success = 0;
		}
	}
	return result;
}

int s21_is_greater_or_equal(s21_decimal decimal1, s21_decimal decimal2)
{
	COMPARISON_STATUS res = COMPARISON_FALSE;

	// Проверка условия: числа равны или первое больше второго
	if (s21_is_equal(decimal1, decimal2) || s21_is_greater(decimal1, decimal2))
	{
		res = COMPARISON_TRUE;
	}

	return res;
}

int s21_is_less(s21_decimal decimal1, s21_decimal decimal2)
{
	COMPARISON_STATUS res = COMPARISON_FALSE;

	// Проверка условия: первое число не больше или равно второму
	if (!s21_is_greater_or_equal(decimal1, decimal2))
	{
		res = COMPARISON_TRUE;
	}

	return res;
}

int s21_is_less_or_equal(s21_decimal decimal1, s21_decimal decimal2)
{
	COMPARISON_STATUS res = COMPARISON_FALSE;

	// Проверка условия: первое число не больше второго
	if (!s21_is_greater(decimal1, decimal2))
	{
		res = COMPARISON_TRUE;
	}

	return res;
}

// int main()
// {
// 	// Примеры чисел для тестов
// 	s21_decimal decimal1 = {{1, 0, 0, 0}};				// 1
// 	s21_decimal decimal2 = {{2, 0, 0, 0}};				// 2
// 	s21_decimal decimal3 = {{1, 0, 0, 0}};				// 1
// 	s21_decimal decimal4 = {{1, 0, 0, 0x80000000}}; // -1

// 	// Тестирование s21_is_equal
// 	printf("s21_is_equal(decimal1, decimal2): %d\n", s21_is_equal(decimal1, decimal2));
// 	printf("s21_is_equal(decimal1, decimal3): %d\n", s21_is_equal(decimal1, decimal3));
// 	printf("s21_is_equal(decimal1, decimal4): %d\n", s21_is_equal(decimal1, decimal4));
// 	// Тестирование s21_is_not_equal
// 	printf("s21_is_not_equal(decimal1, decimal2): %d\n", s21_is_not_equal(decimal1, decimal2));
// 	printf("s21_is_not_equal(decimal1, decimal3): %d\n", s21_is_not_equal(decimal1, decimal3));

// 	// Тестирование s21_is_greater
// 	printf("s21_is_greater(decimal1, decimal2): %d\n", s21_is_greater(decimal1, decimal2));
// 	printf("s21_is_greater(decimal2, decimal1): %d\n", s21_is_greater(decimal2, decimal1));

// 	// Тестирование s21_is_less
// 	printf("s21_is_less(decimal1, decimal2): %d\n", s21_is_less(decimal1, decimal2));
// 	printf("s21_is_less(decimal2, decimal1): %d\n", s21_is_less(decimal2, decimal1));

// 	// Тестирование s21_is_greater_or_equal
// 	printf("s21_is_greater_or_equal(decimal1, decimal2): %d\n", s21_is_greater_or_equal(decimal1, decimal2));
// 	printf("s21_is_greater_or_equal(decimal1, decimal3): %d\n", s21_is_greater_or_equal(decimal1, decimal3));

// 	// Тестирование s21_is_less_or_equal
// 	printf("s21_is_less_or_equal(decimal1, decimal2): %d\n", s21_is_less_or_equal(decimal1, decimal2));
// 	printf("s21_is_less_or_equal(decimal1, decimal3): %d\n", s21_is_less_or_equal(decimal1, decimal3));

// 	return 0;
// }