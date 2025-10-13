import Foundation

func isNumber(a: Int) -> Bool {
    /* Проверяет, что это число, а не цифра. */
    return a / 10 != 0
}

func cntOddDigits(a: Int) -> Int {
    /* Считает количество нечетных цифр в числе. */
    var res = 0
    var number = abs(a)

    while number > 0 {
        res += number % 2
        number /= 10
    }
    return res
}

// Основная часть программы
print("Введите количество чисел: ", terminator: "")
if let input = readLine(), let n = Int(input) {
    for i in 0..<n {
        print("Введите \(i + 1) число: ", terminator: "")
        if let numInput = readLine(), let num = Int(numInput) {
            
            var cntOdd = 0
            if isNumber(a: num) {
                cntOdd = cntOddDigits(a: num)
            } else {
                print("\(num) - это цифра!")
            }

            print("Количество нечетных цифр: \(cntOdd)")
        }
    }
}
