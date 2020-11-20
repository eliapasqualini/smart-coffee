package smart_coffee;

import javax.swing.SwingUtilities;

public class SmartCoffeeMain {

	static SmartCoffeeView view = null;

	public static void main(String[] args) throws Exception {	
		SwingUtilities.invokeAndWait(() -> {
			view = new SmartCoffeeView();
		});
		Controller contr = new Controller("COM3",view);
		view.registerController(contr);
		SwingUtilities.invokeLater(() -> {
			view.setVisible(true);
		});
	}
}
