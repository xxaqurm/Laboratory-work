<?php
// Включим отображение ошибок
error_reporting(E_ALL);
ini_set('display_errors', 1);

function is_prime(int $a) {
    /* Проверяет, является ли число простым. */
    if ($a < 2) {
        return false;
    }

    for ($i = 2; $i <= (int)sqrt($a); $i++) {
        if ($a % $i == 0) {
            return false;
        }
    }

    return true;
}


function calculateNthNum(int $a) {
    /* Ищет N-й член последовательности. */
    $deviation = 1;
    $left_val = $a;
    $right_val = $a;

    while (true) {
        if (is_prime($left_val)) {
            return $a - $left_val;
        } else if (is_prime($right_val)) {
            return $a - $right_val;
        }
        $left_val = $a - $deviation;   // ищем простое число слева от N
        $right_val = $a + $deviation;  // ищем простое число справа от N
        $deviation++;
    }
}


function main() {
    $n = (int)readline("Введите свое N: ");
    
    $Nth = calculateNthNum($n);

    print("Найден N-й член ряда: " . $Nth);
}

main();
?>