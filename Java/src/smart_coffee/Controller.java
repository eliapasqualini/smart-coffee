package smart_coffee;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class Controller implements ActionListener{
	SerialCommChannel channel;
	SmartCoffeeView view;
	
	
	public Controller(String port, SmartCoffeeView view) throws Exception {
		this.view = view;
		channel = new SerialCommChannel(port,9600);		
		new MonitoringAgent(channel,view).start();
					
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");		
	
	}
	
	public void actionPerformed(ActionEvent ev){
		  try {
			  if (ev.getActionCommand().equals("Recharge")){
					channel.sendMsg("R");
			  } 
		  } catch (Exception ex){
			  ex.printStackTrace();
		  }
	  }

}
