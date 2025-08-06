import * as readlineSync from 'readline-sync';

function is_prime(a: number): boolean {
    /* Проверяет, является ли число простым */
    if (a < 2) {
        return false;
    }

    for (let i: number = 2; i <= Math.floor(Math.sqrt(a)); i++) {
        if (a % i == 0) {
            return false;
        }
    }

    return true;
}


function calculateNthNum(a: number): number {
    /* Ищет N-й член последовательности. */
    let deviation: number = 1;
    let left_val: number = a;
    let right_val: number = a;

    while (true) {
        if (is_prime(left_val)) {
            return a - left_val;
        } else if (is_prime(right_val)) {
            return a - right_val;
        }
        left_val = a - deviation;
        right_val = a + deviation;
        deviation++;
    }
}


function main(): void {
    let n: number = parseInt(readlineSync.question("Введите свое N: "));

    let Nth: number = calculateNthNum(n);
    console.log("Найден N-й член ряда: " + Nth);
}


main()