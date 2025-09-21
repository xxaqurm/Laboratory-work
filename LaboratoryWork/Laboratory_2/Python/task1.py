def is_prime(a: int) -> bool:
    '''Проверяет, является ли число простым.'''
    if a < 2: return False
    
    for i in range(2, int(a ** 0.5) + 1):
        if a % i == 0: return False
    
    return True


def calculateNthNum(a: int) -> int:
    '''Ищет N-й член последовательности.'''
    deviation = 1
    left_val = a
    right_val = a
    while True:
        if is_prime(left_val):
            return a - left_val
        elif is_prime(right_val):
            return a - right_val
        left_val = a - deviation   # ищем простое число слева от N
        right_val = a + deviation  # ищем простое число справа от N
        deviation += 1


def main():
    while True:  # проверка на дурака
        try:
            n = int(input("Введите свое N: "))
            break
        except ValueError:
            print("Введенное N должно быть числом!")
    
    Nth = calculateNthNum(n)
    print(f"Найден N-й член ряда: {Nth}")
    


if __name__ == "__main__":
    main()
