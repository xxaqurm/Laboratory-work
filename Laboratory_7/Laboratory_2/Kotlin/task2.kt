import java.util.Scanner

fun printBottles(bottle: String, count: Int) {
    /* Выводит бутылки на экран. */
    for (i in 0 until count) {
        if (i % 3 == 0) println()
        print("$bottle ")
    }
}

fun drinkSimulation(n: Int, m: Int): Pair<Int, Int> {
    /* Показывает все шаги питья. */
    var full = n
    var empty = 0
    var totalDrunk = 0
    var iterations = 0

    val fullBottle = "●"
    val emptyBottle = "○"

    // Выведем дано
    println("Дано")
    printBottles(fullBottle, full)
    println("\n")

    while (true) {
        // Шаг 1: выпить все полные бутылки
        if (full > 0) {
            totalDrunk += full
            empty += full
            full = 0
            iterations++

            // Выведем все выпитые бутылки
            print("$iterations шаг")
            printBottles(emptyBottle, empty)
            println("\n")

            if (empty < m) break // условие завершения

            // Шаг 2: обмен пустых бутылок на полные
            full = empty / m
            empty %= m
            iterations++

            // Выведем бутылки после обмена
            print("$iterations шаг")
            printBottles(fullBottle, full)
            printBottles(emptyBottle, empty)
            println("\n")
        }
    }

    return Pair(totalDrunk, iterations)
}

fun main() {
    val scanner = Scanner(System.`in`)
    print("Введите количество полных бутылок и количество бутылок, которых достаточно для обмена: ")
    val n = scanner.nextInt()
    val m = scanner.nextInt()

    println("Input: $n $m")

    val (total, iters) = drinkSimulation(n, m)

    println("Output (total, iters): $total $iters")
}
