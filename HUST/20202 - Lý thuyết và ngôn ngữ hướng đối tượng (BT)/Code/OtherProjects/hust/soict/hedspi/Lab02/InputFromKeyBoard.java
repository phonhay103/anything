import java.util.Scanner;
public class  InputFromKeyBoard{
    public static void main(String[] args){
        Scanner keyboard = new Scanner(System.in);

        System.out.println("What's your name?");
        String strName = keyboard.nextLine();
        System.out.println("How old are you?");
        int iAge = keyboard.nextInt();
        System.out.println("How tall are you (cm):?");
        double dHeight = keyboard.nextDouble();

        System.out.println("Mrs/Ms. "
                            + strName + ", " 
                            + iAge + " year old. "
                            + "Your height is " + dHeight + ".");
        keyboard.close();
    }
}
