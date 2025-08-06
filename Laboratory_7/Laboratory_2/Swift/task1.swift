import Foundation

func isPrime(_ a: Int) -> Bool {
    // Проверяет, является ли число простым
    if a < 2 {
        return false
    }
    
    for i in 2...Int(sqrt(Double(a))) {
        if a % i == 0 {
            return false
        }
    }
    
    return true
}

func calculateNthNum(_ a: Int) -> Int {
    // Ищет N-й член последовательности
    var deviation = 1
    var leftVal = a
    var rightVal = a
    
    while true {
        if isPrime(leftVal) {
            return a - leftVal
        } else if isPrime(rightVal) {
            return a - rightVal
        }
        leftVal = a - deviation  // ищем простое число слева от N
        rightVal = a + deviation // ищем простое число справа от N
        deviation += 1
    }
}

func main() {
    print("Введите свое N: ", terminator: "")
    if let input = readLine(), let n = Int(input) {
        let nth = calculateNthNum(n)
        print("Найден N-й член ряда: \(nth)")
    } else {
        print("Ошибка: ввод некорректен.")
    }
}

main()
