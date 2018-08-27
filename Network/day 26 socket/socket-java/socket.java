package message.socket;

public class socket {
	public static void main(String[] args) {
		Client client1 = new Client("i am client1");
		Client client2 = new Client("hello,in client2");
		Server server = new Server();
		Thread serverThread = new Thread(server, "server");
		serverThread.setDaemon(true);
		serverThread.start();
		new Thread(client1, "client-1").start();
		new Thread(client2, "client-2").start();
	}
}
