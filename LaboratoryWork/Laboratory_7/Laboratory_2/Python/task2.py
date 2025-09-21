def print_bottles(bottle: str, count: int):
    ''' Выводит бутылки на экран. '''
    for i in range(count):
        if i % 3 == 0:
            print()
        print(f"{bottle}", end=' ')


def drink_simulation(n: int, m: int):
    ''' Показывает все шаги питья. '''
    full = n
    empty = 0
    total_drunk = 0
    iterations = 0

    full_bottle = "●"
    empty_bottle = "○"

    # Выведем дано
    print("Дано")
    print_bottles(full_bottle, full)
    print("\n")

    while True:
        # Шаг 1: выпить все полные бутылки 
        if full > 0:
            total_drunk += full
            empty += full
            full = 0
            iterations += 1

            # Выведем все выпитые бутылки 
            print(f"{iterations} шаг", end='')
            print_bottles(empty_bottle, empty)
            print("\n")

            if (empty < m):  # условие завершения
                break

            # Шаг 2: обмен пустых бутылок на полные 
            full = empty // m
            empty = empty % m
            iterations += 1

            # Выведем бутылки после обмена
            print(f"{iterations} шаг", end='')
            print_bottles(full_bottle, full)
            print_bottles(empty_bottle, empty)
            print("\n")
    return [total_drunk, iterations]


def main():
    n, m = [int(i) for i in input("Введите количество полных бутылок и количество бутылок, которых достаточно для обмена: ").split()]
    print(f"Input: {n} {m}")

    total, iters = drink_simulation(n, m)

    print(f"Output (total, iters): {total} {iters}")


if __name__ == "__main__":
    main()