package message.socket;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;


public class Server implements Runnable{
	ServerSocket serverSocket;
	public Server(){
		//1、创建一个服务器端Socket，即ServerSocket，指定绑定的端口，并监听此端口
		try {
			serverSocket = new ServerSocket(12345);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	@Override
	public void run() {
		while (true){
			try {
				waitMessage();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	public void waitMessage() throws IOException {
		//2、调用accept()方法开始监听，等待客户端的连接
		Socket socket = serverSocket.accept();
		//3、获取输入流，并读取客户端信息
		InputStream is = socket.getInputStream();
		InputStreamReader isr = new InputStreamReader(is);
		BufferedReader br = new BufferedReader(isr);
		String info;
		while ((info = br.readLine()) != null) {
			info = info.toUpperCase();
			System.out.println("In Server, Receive a message from Port:(" +socket.getPort() + ")  Message:  "+ info);
		}
		socket.shutdownInput();//关闭输入流
		//4、获取输出流，响应客户端的请求
		OutputStream os = socket.getOutputStream();
		PrintWriter pw = new PrintWriter(os);
//		Scanner in = new Scanner(System.in);
//		String s = in.nextLine();
		pw.write("Client receive your message!");
		pw.flush();
		//5、关闭资源
		pw.close();
		os.close();
		br.close();
		isr.close();
		is.close();
		socket.close();
//		serverSocket.close();
	}
}
