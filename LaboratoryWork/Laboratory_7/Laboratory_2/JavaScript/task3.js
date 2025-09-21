const readlineSync = require('readline-sync');

function is_number(a) {
    /* Проверяет, что это число, а не цифра. */
    return (parseInt(a / 10) != 0);
}


function cnt_odd_digits(a) {
    /* Считает количество нечетных цифр в числе. */
    let res = 0;
    a = Math.abs(a);

    while (a > 0) {
        res += (a % 2);
        a = parseInt(a / 10);
    }

    return res;
}


function main() {
    let n = parseInt(readlineSync.question("Введите количество чисел: "));

    for (let i = 0; i < n; i++) {
        let num = parseInt(readlineSync.question("Введите " + (i + 1) + " число: "));
        let cnt_odd = 0;
        if (is_number(num)) {
            cnt_odd = cnt_odd_digits(num);
        } else {
            console.log(num, " - это цифра!");
        }

        console.log("Количество нечетных цифр: ", cnt_odd);
    }
}


main()