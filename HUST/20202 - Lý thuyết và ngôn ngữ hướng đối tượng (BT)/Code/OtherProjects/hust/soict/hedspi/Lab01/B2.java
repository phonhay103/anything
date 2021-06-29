import javax.swing.JOptionPane;

public class B2{
    public static void main(String args[]){
        Double a11 = Double.parseDouble(JOptionPane.showInputDialog("Input a11"));
        Double a12 = Double.parseDouble(JOptionPane.showInputDialog("Input a12"));
        Double b1 = Double.parseDouble(JOptionPane.showInputDialog("Input b1"));
        Double a21 = Double.parseDouble(JOptionPane.showInputDialog("Input a21"));
        Double a22 = Double.parseDouble(JOptionPane.showInputDialog("Input a22"));
        Double b2 = Double.parseDouble(JOptionPane.showInputDialog("Input b2"));
        Double D, D1, D2;
        D = a11 * a22 - a21 * a12;
        D1 = b1 * a22 - b2 * a12;
        D2 = a11 * b2 - a21 * b1;
        if (D == 0)
            if (D1 == 0 && D2 == 0)
                JOptionPane.showMessageDialog(null, "He phuong trinh co vo so nghiem");
            else
                JOptionPane.showMessageDialog(null, "He phuong trinh vo nghiem");
        else 
            JOptionPane.showMessageDialog(null, "He phuong trinh co nghiem duy nhat: (" + D1/D + "," + D2/D + ")");
        System.exit(0);
    }
}