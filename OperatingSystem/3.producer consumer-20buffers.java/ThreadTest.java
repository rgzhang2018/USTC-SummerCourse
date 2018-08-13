package thread;
//多线程实现生产者消费者
public class ThreadTest {
	public static void main(String[] args) {
		System.out.println(Thread.currentThread().getName()+" thread starts:");
		//创建该卖票机器，总销售次数，缓存区的个数
		SellTicketsThread t = new SellTicketsThread(500,20);
		//设置多个生产者和消费者
		Producer p1 = new Producer(t,"Producer-1");
		Producer p2 = new Producer(t,"Producer-2");
		Consumer c1 = new Consumer(t,"Consumer-1",200);
		Consumer c2 = new Consumer(t,"Consumer-2",100);
//		Consumer c3 = new Consumer(t,"Consumer-3",50);
		Consumer VIP = new Consumer(t,"VIP",50);

		Thread x1 = new Thread(p1,"T1");
		Thread x2 = new Thread(p2,"T2");
		Thread y1 = new Thread(c1,"T3");
		Thread y2 = new Thread(c2,"T4");
//		Thread y3 = new Thread(c3);
		Thread vip = new Thread(VIP,"T5");
		vip.setPriority(10);
		x1.start();
		x2.start();
		y1.start();
		y2.start();
		vip.start();
		System.out.println("main thread ends!");
	}
}
