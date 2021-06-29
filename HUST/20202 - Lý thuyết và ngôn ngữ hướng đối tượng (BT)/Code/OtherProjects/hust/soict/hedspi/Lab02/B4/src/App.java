import java.util.Scanner;

import javax.swing.JOptionPane;
public class App {
    public static void main(String[] args) throws Exception {
        Scanner keyboard = new Scanner(System.in);
        System.out.print("N = ");
        int n = keyboard.nextInt();

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j < n-i; ++j)
                System.out.print(' ');
            for (int j = 0; j < 2*i-1; ++j)
                System.out.print('*');
            System.out.println();
        }
        System.exit(0);
    }
}
