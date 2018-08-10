package thread;
//在线程中计算阶乘
public class ThreadTest {
	public static void main(String[] args) {
		System.out.println(Thread.currentThread().getName()+" thread starts:");
		SellTicketsThread t = new SellTicketsThread(200);
		//设置多个生产者和消费者
		Producer p1 = new Producer(t,"Producer-1");
		Producer p2 = new Producer(t,"Producer-2");
		Consumer c1 = new Consumer(t,"Consumer-1",100);
		Consumer c2 = new Consumer(t,"Consumer-2",100);
//		Consumer c3 = new Consumer(t,"Consumer-3",50);
		Consumer VIP = new Consumer(t,"VIP",100);

		Thread x1 = new Thread(p1);
		Thread x2 = new Thread(p2);
		Thread y1 = new Thread(c1);
		Thread y2 = new Thread(c2);
//		Thread y3 = new Thread(c3);
		Thread vip = new Thread(VIP);
//		x1.setPriority(9);//设置优先级
		vip.setPriority(10);
//		y.setPriority(9);
		x1.start();
		x2.start();
		y1.start();
		y2.start();
		vip.start();
		System.out.println("main thread ends!");
	}
}
