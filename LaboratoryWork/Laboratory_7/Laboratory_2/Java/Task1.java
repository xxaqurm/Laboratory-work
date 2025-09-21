import java.util.Scanner;

public class Task1 {
    public static boolean is_prime(int a) {
        if (a < 2) {
            return false;
        }
        for (int i = 2; i <= (int) Math.sqrt(a); i++) {
            if (a % i == 0) {
                return false;
            }
        }
        return true;
    }


    public static int calculateNthTerm(int a) {
        int deviation = 1;
        int left_val = a;
        int right_val = a;

        while (true) {
            if (is_prime(left_val)) {
                return a - left_val;   // ищем простое число слева от N
            }
            if (is_prime(right_val)) {
                return a - right_val;  // ищем простое число справа от N
            }
            left_val = a - deviation;
            right_val = a + deviation;
            deviation++;
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите число N: ");
        int n = scanner.nextInt();

        scanner.close();

        int result = calculateNthTerm(n);
        System.out.println("Результат: " + result);
    }
}