package thread;

import static java.lang.Thread.yield;

public class Consumer implements Runnable{
	private SellTicketsThread t = null;
	private  String name;
	private int numbers;
	public Consumer(SellTicketsThread t,String name,int numbers) {
		this.t = t;
		this.name = name;
		this.numbers = numbers;
	}
	@Override
	public String toString(){
		return name;
	}
	public void getOne(){
		this.numbers--;
	}
	public boolean haveDone(){
		return numbers == 0;
	}
	public void run() {
		while (t.testTime>0 && numbers!=0) {
//			if (t.full > 0) t.consume(this);//这里注释掉，放入mutexC里，作为原子操作
//			else yield();//关键步骤，防止饥饿
			t.mutexC(this);
			yield();
		}
		if(numbers==0)System.out.println(this.name+" has sell out!!");
		else System.out.println("Time out! But "+name+" still "+numbers+" people needs tickets");
	}
}
