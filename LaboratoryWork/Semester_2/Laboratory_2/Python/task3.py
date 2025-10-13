def is_number(a: int) -> bool:
    '''Проверяет, что это число, а не цифра.'''
    return a // 10 != 0


def cnt_odd_digits(a: int) -> int:
    '''Считает количество нечетных цифр в числе'''
    res = 0
    a = abs(a)

    while a > 0:
        res += (a % 2)
        a //= 10
    return res


def main():
    while True:  # проверка на дурака
        try:
            n = int(input("Введите количество чисел: "))
            if n > 0:
                break
            print("N - положительное число!")
        except ValueError:
            print("Ваш ввод некорректен, введите целое число!")
    
    for _ in range(n):
        while True:
            try:
                num = int(input("Введите число: "))
                break
            except ValueError:
                print("Введите целое число!")

        cnt_odd = 0
        if is_number(num):
            cnt_odd = cnt_odd_digits(num)
        else:
            print(f"{num} - это цифра!")
        print(f"Количество нечетных цифр: {cnt_odd}")


if __name__ == "__main__":
    main()