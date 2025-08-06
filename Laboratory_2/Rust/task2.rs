use std::io;

fn print_bottles(bottle: &str, count: i32) {
    /* Выводит бутылки на экран. */
    for i in 0..count {
        if i % 3 == 0 {
            println!();
        }
        print!("{} ", bottle);
    }
}

fn drink_simulation(n: i32, m: i32) -> (i32, i32) {
    /* Показывает все шаги питья. */
    let mut full = n;
    let mut empty = 0;
    let mut total_drunk = 0;
    let mut iterations = 0;

    let full_bottle = "●";
    let empty_bottle = "○";

    // Выведем дано
    print!("Дано");
    print_bottles(full_bottle, full);
    println!("\n");

    loop {
        // Шаг 1: выпить все полные бутылки
        if full > 0 {
            total_drunk += full;
            empty += full;
            full = 0;
            iterations += 1;

            // Выведем все выпитые бутылки
            print!("{} шаг", iterations);
            print_bottles(empty_bottle, empty);
            println!("\n");

            if empty < m {  // условие завершения
                break;
            }

            // Шаг 2: обмен пустых бутылок на полные
            full = empty / m;
            empty %= m;
            iterations += 1;

            // Выведем бутылки после обмена
            print!("{} шаг", iterations);
            print_bottles(full_bottle, full);
            print_bottles(empty_bottle, empty);
            println!("\n");
        }
    }

    (total_drunk, iterations)
}

fn main() {
    let mut input = String::new();
    println!("Введите количество полных бутылок и количество бутылок, которых достаточно для обмена:");
    io::stdin().read_line(&mut input).expect("Ошибка ввода");

    let nums: Vec<i32> = input
        .trim()
        .split_whitespace()
        .filter_map(|x| x.parse().ok())
        .collect();
    
    if nums.len() != 2 {
        println!("Ошибка: необходимо ввести два числа.");
        return;
    }
    
    let (n, m) = (nums[0], nums[1]);
    println!("Input: {} {}", n, m);
    
    let (total, iters) = drink_simulation(n, m);
    println!("Output(total, iters): {} {}", total, iters);
}
