<?php
// Включим отображение ошибок
error_reporting(E_ALL);
ini_set("display_errors", 1);


function is_number(int $a) {
    /* Проверяет, что это число, а не цифра. */
    return ((int)($a / 10) != 0);
}


function cnt_odd_digits(int $a) {
    /* Считает количество нечетных цифр в числе. */
    $res = 0;
    $a = abs($a);

    while ($a > 0) {
        $res += ($a % 2);
        $a = (int)($a / 10);
    }
    return $res;
}


function main() {
    $n = (int)readline("Введите количество чисел: ");

    for ($i = 0; $i < $n; $i++) {
        $num = (int)readline("Введите " . ($i + 1) . " число: ");
        $cnt_odd = 0;
        
        if (is_number($num)) {
            $cnt_odd = cnt_odd_digits($num);
        } else {
            print($num . " - это цифра!");
        }

        print("Количество нечетных цифр: " . $cnt_odd . "\n");
    }
}

main();
?>