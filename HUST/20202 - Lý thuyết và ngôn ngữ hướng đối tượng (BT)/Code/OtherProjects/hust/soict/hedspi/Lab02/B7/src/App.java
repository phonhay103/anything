public class App {
    public static void main(String[] args) throws Exception {
        int a[][] = {{1, 2, 5, 3}, {12, -1, 6, 2}, {-3, -2, -8, 3}};
        int b[][] = {{9, 0, 0, 2}, {9, 1, 0, 8}, {4, -2, 11, 0}};
        
        int c[][] = new int[3][4];

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                c[i][j] = a[i][j] + b[i][j];
                System.out.print(c[i][j] + " ");
            }
            System.out.println();
        }
    }
}
