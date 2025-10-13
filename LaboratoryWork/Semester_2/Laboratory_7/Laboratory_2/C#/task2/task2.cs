using System;

class Task2 {
    static void PrintBottles(string bottle, int count) {
        /* Выводит бутылки на экран. */
        for (int i = 0; i < count; i++) {
            if (i % 3 == 0) Console.WriteLine();
            Console.Write(bottle + " ");
        }
    }

    static (int, int) DrinkSimulation(int n, int m) {
        /* Показывает все шаги питья. */
        int full = n;
        int empty = 0;
        int totalDrunk = 0;
        int iterations = 0;

        string fullBottle = "●";
        string emptyBottle = "○";

        // Выведем дано
        Console.Write("Дано");
        PrintBottles(fullBottle, full);
        Console.WriteLine("\n");

        while (true) {
            // Шаг 1: выпить все полные бутылки
            if (full > 0) {
                totalDrunk += full;
                empty += full;
                full = 0;
                iterations++;

                // Выведем все выпитые бутылки
                Console.Write(iterations + " шаг");
                PrintBottles(emptyBottle, empty);
                Console.WriteLine("\n");

                if (empty < m) break;  // условие завершения

                // Шаг 2: обмен пустых бутылок на полные
                full = empty / m;
                empty = empty % m;
                iterations++;

                // Выведем бутылки после обмена 
                Console.Write(iterations + " шаг");
                PrintBottles(fullBottle, full);
                PrintBottles(emptyBottle, empty);
                Console.WriteLine("\n");
            }
        }

        return (totalDrunk, iterations);
    }

    static void Main() {
        Console.Write("Введите количество полных бутылок и количество бутылок, которых достаточно для обмена: ");
        string[] input = Console.ReadLine().Split();

        if (input.Length < 2 || !int.TryParse(input[0], out int n) || !int.TryParse(input[1], out int m)) {
            Console.WriteLine("Ошибка ввода! Введите два целых числа.");
            return;
        }

        Console.WriteLine("Input: " + n + " " + m);

        (int total, int iters) = DrinkSimulation(n, m);

        Console.WriteLine("Output (total, iters): " + total + " " + iters);
    }
}