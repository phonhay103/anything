import java.util.*;

public class App {
    public static void main(String[] args) throws Exception {
        List<Integer> a_list = Arrays.asList(1002, 923, 1231, 9982, 2132);
        Collections.sort(a_list);
        System.out.println("Sorted list:");
        System.out.println(a_list);
        
        Integer sum = a_list.stream().mapToInt(Integer::intValue).sum();
        System.out.println("Sum: " + sum);

        System.out.println("Mean: " + Double.valueOf(sum)/ a_list.size());

    }
}
