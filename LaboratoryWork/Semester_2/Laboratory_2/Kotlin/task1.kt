import java.util.Scanner

fun isPrime(a: Int): Boolean {
    if (a < 2) return false
    for (i in 2..Math.sqrt(a.toDouble()).toInt()) {
        if (a % i == 0) return false
    }
    return true
}

fun calculateNthTerm(a: Int): Int {
    var deviation = 1
    var leftVal = a
    var rightVal = a

    while (true) {
        if (isPrime(leftVal)) return a - leftVal // ищем простое число слева от N
        if (isPrime(rightVal)) return a - rightVal // ищем простое число справа от N
        leftVal = a - deviation
        rightVal = a + deviation
        deviation++
    }
}

fun main() {
    val scanner = Scanner(System.`in`)
    print("Введите число N: ")
    val n = scanner.nextInt()
    scanner.close()

    val result = calculateNthTerm(n)
    println("Результат: $result")
}
