use std::io;

fn is_number(a: i32) -> bool {
    /* Проверяет, что это число, а не цифра. */
    a / 10 != 0
}

fn cnt_odd_digits(mut a: i32) -> i32 {
    /* Считает количество нечетных цифр в числе. */
    let mut res = 0;
    a = a.abs();

    while a > 0 {
        res += a % 2;
        a /= 10;
    }

    res
}

fn main() {
    let mut input = String::new();
    println!("Введите количество чисел: ");
    io::stdin().read_line(&mut input).expect("Ошибка ввода");

    let n: i32 = input.trim().parse().expect("Пожалуйста, введите число");

    for i in 0..n {
        let mut input = String::new();
        println!("Введите {} число: ", i + 1);
        io::stdin().read_line(&mut input).expect("Ошибка ввода");

        let num: i32 = input.trim().parse().expect("Пожалуйста, введите число");

        let mut cnt_odd = 0;
        if is_number(num) {
            cnt_odd = cnt_odd_digits(num);
        } else {
            println!("{} - это цифра!", num);
        }

        println!("Количество нечетных цифр: {}", cnt_odd);
    }
}
