import javax.swing.JOptionPane;
import java.lang.Math;

public class B3{
    public static void main(String args[]){
        Double a = Double.parseDouble(JOptionPane.showInputDialog("Input a"));
        Double b = Double.parseDouble(JOptionPane.showInputDialog("Input b"));
        Double c = Double.parseDouble(JOptionPane.showInputDialog("Input c"));
        Double delta = b * b - 4 * a * c;
        if (delta == 0)
            JOptionPane.showMessageDialog(null, "Phuong trinh co nghiem kep: "
                                                + -b / (2 * a));
        else if (delta > 0)
            JOptionPane.showMessageDialog(null, "Phuong trinh co 2 nghiem phan biet: "
                                                + (-b + Math.sqrt(delta)) / (2 * a) 
                                                + " va "
                                                + (-b - Math.sqrt(delta)) / (2 * a));
        else
            JOptionPane.showMessageDialog(null, "Phuong trinh vo nghiem");
        System.exit(0);
    }
}