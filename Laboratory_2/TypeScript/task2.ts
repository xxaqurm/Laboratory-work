import * as readlineSync from 'readline-sync'

function print_bottles(bottle: string, count: number): void {
    /* Выводит бутылки на экран. */
    for (let i: number = 0; i < count; i++) {
        if (i % 3 == 0) {
            process.stdout.write("\n");
        }
        process.stdout.write(bottle + " ");
    }
}


function drink_simulation(n: number, m: number): number[] {
    /* Показывает все шаги питья */
    let full: number = n;
    let empty: number = 0;
    let total_drunk: number = 0;
    let iterations: number = 0;

    let full_bottle: string = "●";
    let empty_bottle: string = "○";

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
            full = Math.floor(empty / m);
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


function main(): void {
    let input: string = readlineSync.question("Введите через пробел количество полных бутылок и количество бутылок, которых достаточно для обмена: ");
    let numbers: Array<string> = input.split(" ");

    let n: number = parseInt(numbers[0]);
    let m: number = parseInt(numbers[1]);

    process.stdout.write("Input: " + n + " " + m + "\n");

    let result: Array<number> = drink_simulation(n, m);

    let total: number = result[0];
    let iters: number = result[1];

    process.stdout.write("Output: (total, iters): " + total + " " + iters);
}


main();