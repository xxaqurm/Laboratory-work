import * as readlineSync from 'readline-sync';

function is_number(a: number): boolean {
    /* Проверяет, что это число, а не цифра. */
    return (Math.floor(a / 10) != 0);
}


function cnt_odd_digits(a: number): number {
    /* Считает количество нечетных цифр в числе. */
    let res: number = 0;
    a = Math.abs(a);

    while (a > 0) {
        res += (a % 2);
        a = Math.floor(a / 10);
    }

    return res;
}


function main() {
    let n: number = parseInt(readlineSync.question("Введите количество чисел: "));

    for (let i: number = 0; i < n; i++) {
        let num: number = parseInt(readlineSync.question("Введите " + (i + 1) + " число: "));
        let cnt_odd: number = 0;

        if (is_number(num)) {
            cnt_odd = cnt_odd_digits(num);
        } else {
            console.log(num + " - это цифра!");
        }

        console.log("Количество нечетных цифр: " + cnt_odd);
    }
}


main();