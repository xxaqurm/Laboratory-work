<?php
// Включим отображение ошибок
error_reporting(E_ALL);
ini_set("display_errors", 1);


function print_bottles(string $bottle, int $count) {
    /* Выводит бутылки на экран. */
    for ($i = 0; $i < $count; $i++) {
        if ($i % 3 == 0) {
            print("\n");
        }
        print($bottle . " ");
    }
}


function drink_simulation(int $n, int $m) {
    /* Показывает все шаги питья. */
    $full = $n;
    $empty = 0;
    $total_drunk = 0;
    $iterations = 0;

    $full_bottle = "●";
    $empty_bottle = "○";

    // Выведем дано
    print("Дано");
    print_bottles($full_bottle, $full);
    print("\n\n");

    while (true) {
        // Шаг 1: выпить все полные бутылки
        if ($full > 0) {
            $total_drunk += $full;
            $empty += $full;
            $full = 0;
            $iterations++;

            // Выведем все выпитые бутылки
            print($iterations . " шаг");
            print_bottles($empty_bottle, $empty);
            print("\n\n");

            if ($empty < $m) {  // Условие завершения
                break;
            }

            // Шаг 2: обмен пустых бутылок на полные
            $full = (int)($empty / $m);
            $empty = $empty % $m;
            $iterations++;

            // Выведем бутылки после обмена
            print($iterations . " шаг");
            print_bottles($full_bottle, $full);
            print_bottles($empty_bottle, $empty);
            print("\n\n");
        }
    }

    return [$total_drunk, $iterations];
}


function main() {
    // Используем sscanf для извлечения двух чисел
    sscanf(readline("Введите два числа через пробел: "), "%d %d", $n, $m);

    print("Input: " . $n . " " . $m);

    $result = drink_simulation($n, $m);

    $total = $result[0];
    $iters = $result[1];

    print("Output (total, iters): " . $total . " " . $iters);
}

main();
?>