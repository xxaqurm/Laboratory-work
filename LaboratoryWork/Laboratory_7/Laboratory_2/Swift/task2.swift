import Foundation

func printBottles(bottle: String, count: Int) {
    /* Выводит бутылки на экран. */
    for i in 0..<count {
        if i % 3 == 0 {
            print()
        }
        print(bottle, terminator: " ")
    }
}

func drinkSimulation(n: Int, m: Int) -> (Int, Int) {
    /* Показывает все шаги питья. */
    var full = n
    var empty = 0
    var totalDrunk = 0
    var iterations = 0

    let fullBottle = "●"
    let emptyBottle = "○"

    // Выведем дано
    print("Дано", terminator: " ")
    printBottles(bottle: fullBottle, count: full)
    print("\n")

    while true {
        // Шаг 1: выпить все полные бутылки
        if full > 0 {
            totalDrunk += full
            empty += full
            full = 0
            iterations += 1

            // Выведем все выпитые бутылки
            print("\(iterations) шаг", terminator: " ")
            printBottles(bottle: emptyBottle, count: empty)
            print("\n")

            if empty < m { break } // условие завершения

            // Шаг 2: обмен пустых бутылок на полные
            full = empty / m
            empty = empty % m
            iterations += 1

            // Выведем бутылки после обмена
            print("\(iterations) шаг", terminator: " ")
            printBottles(bottle: fullBottle, count: full)
            printBottles(bottle: emptyBottle, count: empty)
            print("\n")
        }
    }

    return (totalDrunk, iterations)
}

// Основная часть программы
print("Введите количество полных бутылок и количество бутылок, которых достаточно для обмена: ", terminator: "")
if let input = readLine(), let n = Int(input.split(separator: " ")[0]), let m = Int(input.split(separator: " ")[1]) {
    print("Input: \(n) \(m)")

    let result = drinkSimulation(n: n, m: m)
    let total = result.0
    let iters = result.1

    print("Output (total, iters): \(total) \(iters)")
}
