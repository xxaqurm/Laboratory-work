import java.util.Scanner;

public class Task2 {
    public static void print_bottles(String bottle, int count) {
        /* Выводит бутылки на экран. */
        for (int i = 0; i < count; i++) {
            if (i % 3 == 0) System.out.println();
            System.out.print(bottle + " ");
        }
    }

    public static int[] drink_simulation(int n, int m) {
        /* Показывает все шаги питья. */
        int full = n;
        int empty = 0;
        int total_drunk = 0;
        int iterations = 0;

        String full_bottle = "●";
        String empty_bottle = "○";

        // Выведем дано
        System.out.print("Дано");
        print_bottles(full_bottle, full);
        System.out.print("\n\n");

        while (true) {
            // Шаг 1: выпить все полные бутылки
            if (full > 0) {
                total_drunk += full;
                empty += full;
                full = 0;
                iterations++;
                
                // Выведем все выпитые бутылки
                System.out.print(iterations + " шаг");
                print_bottles(empty_bottle, empty);
                System.out.print("\n\n");

                if (empty < m) break;

                // Шаг 2: обмен пустых бутылок на полные
                full = empty / m;
                empty = empty % m;
                iterations++;

                // Выведем бутылки после обмена
                System.out.print(iterations + " шаг");
                print_bottles(full_bottle, full);
                print_bottles(empty_bottle, empty);
                System.out.print("\n\n");
            }
        }

        int[] res = {total_drunk, iterations};
        return res;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n, m;

        System.out.print("Введите количество полных бутылок и количество бутылок, которых достаточно для обмена: ");
        n = scanner.nextInt();
        m = scanner.nextInt();
        System.out.println("Input: " + n + " " + m);

        scanner.close();

        int[] result = drink_simulation(n, m);

        int total = result[0];
        int iters = result[1];

        System.out.println("Output (total, iters): " + total + " " + iters);
    }
}