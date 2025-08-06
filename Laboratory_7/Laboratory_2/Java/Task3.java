import java.util.Scanner;

public class Task3 {
    public static boolean is_number(int a) {
        return (a / 10 > 0);
    }


    public static int cnt_odd_digits(int a) {
        int res = 0;
        a = Math.abs(a);

        while (a > 0) {
            res += (a % 2);
            a /= 10;
        }
        return res;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите количество чисел: ");
        int n = scanner.nextInt();


        for (int i = 0; i < n; i++) {
            System.out.print("Введите " + (i + 1) + " число: ");
            int num = scanner.nextInt();

            int cnt_odd = 0;
            if (is_number(num)) {
                cnt_odd = cnt_odd_digits(num);
            } else {
                System.out.println(num + " - это цифра!");
            }

            System.out.println("Количество нечетных цифр: " + cnt_odd);
        }
        scanner.close();    
    }
}