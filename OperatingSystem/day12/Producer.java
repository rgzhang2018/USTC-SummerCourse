package thread;

import static java.lang.Thread.yield;

public class Producer implements Runnable {
	private SellTicketsThread t = null;//定义一个生产者-消费者
	private String name;
	public Producer(SellTicketsThread t, String name) {
		this.t = t;//让对象传入这里
		this.name = name;//给这个生产者的名字
	}
	@Override
	public String toString(){
		return name;
	}
	//线程部分，调用到t的内部函数
	public void run() {
		while (t.testTime>0) {//当还有剩余执行次数的时候循环

//			if (t.empty > 0) {//将该步骤注释掉，放到一个mutexP的锁里，使其原子执行
//				t.produce(this);//如果空缓冲池大于0，则生产
//			}else yield();

			t.mutexP(this);
			yield();//此步骤很关键，防止饥饿产生
		}

	}
}
//强制休眠，放开处理机
//				try {
//					Thread.sleep(10);//线程休眠10毫秒
//				} catch (InterruptedException e) {
//					e.printStackTrace();
//				}