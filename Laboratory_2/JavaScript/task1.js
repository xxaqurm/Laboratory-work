const readlineSync = require('readline-sync');

function is_prime(a) {
    /* Проверяет, является ли число простым. */
    if (a < 2) {
        return false;
    }

    for (let i = 2; i <= parseInt(Math.sqrt(a)); i++) {
        if (a % i == 0) {
            return false;
        }
    }

    return true;
}


function calculateNthNum(a) {
    /* Ищет N-й член последовательности. */
    let deviation = 1;
    let left_val = a;
    let right_val = a;

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


function main() {
    let n = parseInt(readlineSync.question("Введите свое N: "));  // Получает N пользователя
    let Nth = calculateNthNum(n);
    console.log("Найден N-й член ряда: " + Nth);
}


main()