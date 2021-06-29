import javax.swing.JOptionPane;

public class B1{
    public static void main(String args[]){
        // y = ax + b
        Double a = Double.parseDouble(JOptionPane.showInputDialog("Nhap a"));
        Double b = Double.parseDouble(JOptionPane.showInputDialog("Nhap b"));
        if (a == 0)
            if (b == 0)
                JOptionPane.showMessageDialog(null, "Phuong trinh vo so nghiem", "PT y = " + a + "x + " + b, 
                        JOptionPane.INFORMATION_MESSAGE);
            else
                JOptionPane.showMessageDialog(null, "Phuong trinh vo nghiem", "PT y = " + a + "x + " + b, 
                        JOptionPane.INFORMATION_MESSAGE);
        else
            JOptionPane.showMessageDialog(null, "Phuong trinh co nghiem duy nhat: " + -b/a, "PT y = " + a + "x + " + b, 
                    JOptionPane.INFORMATION_MESSAGE);
        System.exit(0);
    }
}