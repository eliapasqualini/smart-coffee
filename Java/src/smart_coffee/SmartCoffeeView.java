package smart_coffee;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

public class SmartCoffeeView extends JFrame{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private JButton recharge;
	private JTextField text;
	private JSlider slider;
	private JLabel sugarLabel;
	private JLabel infoLabel;
	
	public SmartCoffeeView() {
		super("Smart Coffee");
		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
		this.setSize(400, 120);
		JPanel sugarPanel = new JPanel();
		sugarPanel.setLayout(new BoxLayout(sugarPanel, BoxLayout.X_AXIS));
		text = new JTextField(20); 
		recharge = new JButton("Recharge");
		recharge.setEnabled(false);
		mainPanel.add(recharge);
		slider = new JSlider(JSlider.HORIZONTAL, 0, 5,0);
		slider.setEnabled(false);
		sugarLabel = new JLabel("Sugar level:");
		sugarPanel.add(sugarLabel);
		sugarPanel.add(slider);
		mainPanel.add(sugarPanel);
		JPanel infoPanel = new JPanel();
		infoPanel.setLayout(new BoxLayout(infoPanel, BoxLayout.X_AXIS));
		infoLabel = new JLabel("Info:");
		infoPanel.add(infoLabel);
		infoPanel.add(text);
		mainPanel.add(infoPanel);
		this.getContentPane().add(mainPanel);
		
		addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent ev){
				System.exit(-1);
			}
		});
	}
	
	public void registerController(Controller contr){
		recharge.addActionListener(contr);
	}
	
	public void setSugar(String msg){
		SwingUtilities.invokeLater(() -> {
			String value = msg.substring(1,2);
			slider.setValue(Integer.parseInt(value));
		});
	}
	
	public void setText(String msg){
		SwingUtilities.invokeLater(() -> {
			text.setText(msg);
		});
	}
	
	public void enableButton() {
		SwingUtilities.invokeLater(() -> {
			recharge.setEnabled(true);
		});
		
	}
	
	public void disableButton() {
		SwingUtilities.invokeLater(() -> {
			recharge.setEnabled(false);
		});
	}
	
	public void setNC(String msg) {
		SwingUtilities.invokeLater(() -> {
			text.setText(msg);
		});
	}
}
