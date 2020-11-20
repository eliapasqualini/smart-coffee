package smart_coffee;

public class MonitoringAgent extends Thread{
	
	SerialCommChannel channel;
	SmartCoffeeView view;
	
	static final String MSG_WELCOME 	=  "W";
	static final String MSG_MAKING_COFFEE  	= "M";
	static final String MSG_COFFEE_READY  	= "C";
	static final String MSG_NO_COFFEE   	= "N";
	static final String MSG_REFILLED   	= "R";
	static final String MSG_FLUSH = "F";
	static final String MSG_NC = "A";
	static final String MSG_SUGAR = "S";
	static int NC = 0;
	
	public MonitoringAgent(SerialCommChannel channel, SmartCoffeeView view) throws Exception {
		this.view = view;
		this.channel = channel;
	}
	
	public void run(){
		while (true){
			try {
				String msg = channel.receiveMsg();
				if (msg.startsWith(MSG_WELCOME)){
					view.setText("Welcome!");
				} else if (msg.startsWith(MSG_MAKING_COFFEE)) {
					view.setText("Making a coffee");
				} else if (msg.startsWith(MSG_COFFEE_READY)) {
					view.setText("The coffee is ready");
				} else if (msg.startsWith(MSG_NO_COFFEE)) {
					view.setText("No more coffee. Waiting for recharge");
					view.enableButton();
				} else if (msg.startsWith(MSG_FLUSH)) {
					view.setText("");
				} else if (msg.startsWith(MSG_REFILLED)) {
					view.setText("Coffee refilled: " +NC);
					view.disableButton();
				} else if (msg.startsWith(MSG_NC)) {
					String temp = msg.substring(1,2);
					NC = Integer.parseInt(temp);
				} else if (msg.startsWith(MSG_SUGAR)){
					view.setSugar(msg);
				}
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}

}
