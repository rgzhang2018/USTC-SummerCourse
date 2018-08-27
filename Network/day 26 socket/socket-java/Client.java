package message.socket;

import java.io.*;
import java.net.Socket;

public class Client implements Runnable {
	String message;
	public Client(String s){
		message = s;
	}
	@Override
	public void run() {
		try {
			go();
		}catch (IOException e){
			e.printStackTrace();
		}

	}

	public void go() throws IOException {
		//客户端
		//1、创建客户端Socket，指定服务器地址和端口
		Socket socket = new Socket("localhost", 12345);//发送到服务器的 这里12345是服务器的端口
		//2、获取输出流，向服务器端发送信息
		System.out.println("In "+Thread.currentThread().getName()+" Sending message: |"+this.message+"| to Server.....");
		OutputStream os = socket.getOutputStream();//字节输出流
		PrintWriter pw = new PrintWriter(os);//将输出流包装成打印流
		pw.write(this.message);
		pw.flush();
		socket.shutdownOutput();
		//3、获取输入流，并读取服务器端的响应信息
		InputStream is = socket.getInputStream();
		byte[] c = is.readAllBytes();
		String s = new String(c);
		s =s.toUpperCase();
		System.out.println("In "+Thread.currentThread().getName()+" Receive a message from Server：" + s);
//		BufferedReader br = new BufferedReader(new InputStreamReader(is));
//		String info;
//		while ((info = br.readLine()) != null) {
//			System.out.println("我是客户端，服务器说：" + info);
//		}
//		br.close();
		//4、关闭资源
		is.close();
		pw.close();
	}
}
