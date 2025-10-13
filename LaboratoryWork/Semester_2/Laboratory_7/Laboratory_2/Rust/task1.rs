use std::io;

fn is_prime(a: i32) -> bool {
    /* Проверяет, является ли число простым. */
    if a < 2 {
        return false;
    }
    for i in 2..=((a as f64).sqrt() as i32) {
        if a % i == 0 {
            return false;
        }
    }
    true
}

fn calculate_nth_num(a: i32) -> i32 {
    /* Ищет N-й член последовательности. */
    let mut deviation = 1;
    let mut left_val = a;
    let mut right_val = a;
    
    loop {
        if is_prime(left_val) {
            return a - left_val;
        } else if is_prime(right_val) {
            return a - right_val;
        }
        left_val = a - deviation;   // ищем простое число слева от N
        right_val = a + deviation;  // ищем простое число справа от N
        deviation += 1;
    }
}

fn main() {
    println!("Введите свое N: ");
    
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Ошибка ввода");
    
    let n: i32 = match input.trim().parse() {
        Ok(num) => num,
        Err(_) => {
            println!("Ошибка: введите целое число!");
            return;
        }
    };
    
    let nth = calculate_nth_num(n);
    println!("Найден N-й член ряда: {}", nth);
}