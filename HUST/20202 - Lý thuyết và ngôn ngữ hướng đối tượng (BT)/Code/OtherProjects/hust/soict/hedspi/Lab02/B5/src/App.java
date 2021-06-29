import java.util.Scanner;

public class App {
    public static void main(String[] args) throws Exception {
        Scanner keyboard = new Scanner(System.in);
        String month_input;
        int year;
        int month = 0;

        System.out.print("Year = ");
        year = keyboard.nextInt();

        System.out.print("Month = ");
        keyboard.nextLine();
        month_input = keyboard.nextLine();
        switch (month_input) {
            case "January":
            case "Jan.":
            case "Jan":
            case "1":
                month = 1;
                break;
            case "February":
            case "Feb.":
            case "Feb":
            case "2":
                month = 2;
                break;

            case "March":
            case "Mar.":
            case "Mar":
            case "3":
                month = 3;
                break;

            case "April":
            case "Apr.":
            case "Apr":
            case "4":
                month = 4;
                break;

            case "May":
            case "5":
                month = 5;
                break;

            case "June":
            case "Jun":
            case "6":
                month = 6;
                break;

            case "July":
            case "Jul":
            case "7":
                month = 7;
                break;

            case "August":
            case "Aug.":
            case "Aug":
                month = 8;
                break;

            case "September":
            case "Sept.":
            case "Sep":
            case "9":
                month = 9;
                break;

            case "October":
            case "Oct.":
            case "Oct":
            case "10":
                month = 10;
                break;
            
            case "November":
            case "Nov.":
            case "Nov":
            case "11":
                month = 11;
                break;
            
            case "December":
            case "Dec.":
            case "Dec":
            case "12":
                month = 12;
                break;

            default:
                System.out.println("Invalid Month");
                keyboard.close();
                System.exit(0);
        }

        switch (month) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                System.err.println("Days of month: 31");
                break;
            
            case 4:
            case 6:
            case 9:
            case 11:
                System.out.println("Days of month: 30");
                break;

            case 2:
                if (year % 4 != 0)
                    System.out.println("Days of month: 28");
                else if (year % 100 == 0 && year % 400 == 0)
                    System.out.println("Days of month: 29");
                else
                    System.out.println("Days of month: 28");
        
            default:
                break;
        }

        keyboard.close();
        System.exit(0);
    }
}
