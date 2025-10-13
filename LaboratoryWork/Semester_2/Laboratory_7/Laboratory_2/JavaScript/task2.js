const readlineSync = require('readline-sync');

function print_bottles(bottle, count) {
    /* Выводит бутылки на экран. */
    for (let i = 0; i < count; i++) {
        if (i % 3 == 0) {
            process.stdout.write("\n");
        }
        process.stdout.write(bottle + " ");
    }
}


function drink_simulation(n, m) {
    /* Показывает все шаги питья. */
    let full = n;
    let empty = 0;
    let total_drunk = 0;
    let iterations = 0;

    let full_bottle = "●";
    let empty_bottle = "○";

    // Выведем дано
    process.stdout.write("Дано");
    print_bottles(full_bottle, full);
    process.stdout.write("\n\n");
    
    while (true) {
        // Шаг 1: выпить все полные бутылки
        if (full > 0) {
            total_drunk += full;
            empty += full;
            full = 0;
            iterations++;

            // Выведем все выпитые бутылки 
            process.stdout.write(iterations + " шаг");
            print_bottles(empty_bottle, empty);
            process.stdout.write("\n\n");

            if (empty < m) {  // условие завершения
                break;
            }

            // Шаг 2: обмен пустых бутылок на полные
            full = parseInt(empty / m);
            empty = empty % m;
            iterations++;

            // Выведем бутылки после обмена
            process.stdout.write(iterations + " шаг");
            print_bottles(full_bottle, full);
            print_bottles(empty_bottle, empty);
            process.stdout.write("\n\n");
        }
    }

    return [total_drunk, iterations];
}


function main() {
    let input = readlineSync.question("Введите через пробел количество полных бутылок и количество бутылок, которых достаточно для обмена: ");
    let numbers = input.split(' ');

    let n = parseInt(numbers[0]);
    let m = parseInt(numbers[1]);

    process.stdout.write("Input: " + n + " " + m + "\n");

    let result = drink_simulation(n, m);

    let total = result[0];
    let iters = result[1];

    process.stdout.write("Output: (total, iters): " + total + " " + iters);
}


main();