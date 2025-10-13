using System;

class Task3 {
    static bool is_number(int a) {
        /* Проверяет, что это число, а не цифра. */
        return (a / 10 != 0);
    }

    static int cnt_odd_digits(int a) {
        /* Считает количество нечетных цифр в числе. */
        int res = 0;
        a = Math.Abs(a);

        while (a > 0) {
            res += (a % 2);
            a /= 10;
        }
        return res;
    }

    static void Main(string[] args) {
        int n;
        Console.Write("Введите количество чисел: ");

        n = int.Parse(Console.ReadLine());

        for (int i = 0; i < n; i++) {
            int num;
            Console.Write("Введите " + (i + 1) + " число: ");
            num = int.Parse(Console.ReadLine());

            int cnt_odd = 0;
            if (is_number(num)) {
                cnt_odd = cnt_odd_digits(num);
            } else {
                Console.WriteLine(num + " - это цифра!");
            }

            Console.WriteLine("Количество нечетных цифр: " + cnt_odd);
        }
    }
}