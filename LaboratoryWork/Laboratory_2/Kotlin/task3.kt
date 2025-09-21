import java.util.Scanner
import kotlin.math.abs

fun is_number(a: Int): Boolean {
    /* Проверяет, что это число, а не цифра */
    return (a / 10 != 0)
}

fun cnt_odd_digits(a: Int): Int {
    /* Считает количество нечетных цифр в числе. */
    var res = 0
    var num = abs(a)  // Создаём новую переменную, так как параметр `a` неизменяемый

    while (num > 0) {
        res += (num % 2)
        num /= 10
    }

    return res
}

fun main() {
    val scanner = Scanner(System.`in`)  // Исправлено
    print("Введите количество чисел: ")
    val n = scanner.nextInt()

    for (i in 1..n) {
        print("Введите $i число: ")  // Используем строковый шаблон
        val num = scanner.nextInt()

        val cnt_odd = if (is_number(num)) {
            cnt_odd_digits(num)
        } else {
            println("$num - это цифра!")
            0
        }

        println("Количество нечетных цифр: $cnt_odd")  // Исправленный вывод
    }
}
