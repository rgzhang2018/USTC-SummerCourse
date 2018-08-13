package thread;


import java.util.ArrayList;
import java.util.concurrent.locks.ReentrantLock;

import static java.lang.Thread.yield;
//改进的方案：采用ReentrantLock
public class SellTicketsThread{
	private int []empty;
	private int []full;
	private ArrayList<ReentrantLock> locks = new ArrayList<>();
	private int count;		//用来统计优先级
	private int num;		//记录当前池子数目
	int testTime;			//测试次数
	public SellTicketsThread(int times,int buffers) {
		testTime = times;
		empty = new int[buffers];
		full = new int[buffers];
		num = buffers;
		count = buffers;
		for(int i = 0;i<buffers;i++){
			empty[i] = 3;
			locks.add(new ReentrantLock());
		}
	}

	public void mutexP(Producer a){
		int rand =(int) (Math.random()*empty.length);
		locks.get(rand).lock();
		if(this.empty[rand]>0&&testTime>0)produce(a,rand);
		else count++;										//得不到空池子则让计数增加，便于调整优先级
		if(count>=2*num)Thread.currentThread().setPriority(6);//如果生产者多次拿不到空池子，证明现在池子大多数满的，则降低其优先级
		else if(count<=0)Thread.currentThread().setPriority(4);//反之增加其优先级
		locks.get(rand).unlock();
	}

	public void produce(Producer a,int rand) {
		testTime--;
		full[rand]++;
		empty[rand]--;
		System.out.println(a + " produce->in NO."+rand+". empty: "+empty[rand]+" full: "+full[rand]+ " testTime:" + testTime+" "+Thread.currentThread().getPriority());
	}
	//注意 不同的池子之间不是互斥的
	public void mutexC(Consumer a){
		int rand =(int) (Math.random()*num);
		locks.get(rand).lock();
		if(full[rand]>0 && testTime>0 && !a.haveDone())consume(a,rand);
		else count--;
		if(count<=0 && !a.toString().equals("VIP"))Thread.currentThread().setPriority(4);//如果经常得不到空池子，则证明空池子太少，降低其优先级，让生产者先生产一些
		else if(count>=2*num && !a.toString().equals("VIP"))Thread.currentThread().setPriority(6);//反之提高优先级（注：VIP的优先级一直是10，不在调整范围内）
		locks.get(rand).unlock();
	}

	public void consume(Consumer a,int rand){
		testTime--;
		empty[rand]++;
		full[rand]--;
		a.getOne();
		System.out.println(a+ " consume->in NO."+rand+". empty: "+empty[rand]+" full: "+full[rand]+" testTime:"+testTime+" "+Thread.currentThread().getPriority());
	}
}
//原本的实现：采用synchronized.
//public class SellTicketsThread{
//	private int []empty;
//	private int []full;
//	private int rand;
//	int testTime;//测试次数
//	public SellTicketsThread(int times,int buffers) {
//		testTime = times;
//		empty = new int[buffers];
//		full = new int[buffers];
//		for(int i = 0;i<buffers;i++){
//			empty[i] = 2;
//			full[i] = 2;
//		}
//	}
//
//	public synchronized void mutexP(Producer a){
//		rand =(int) (Math.random()*empty.length);
//		if(this.empty[rand]>0&&testTime>0)produce(a);
//	}
//
//	public void produce(Producer a) {
//		testTime--;
//		full[rand]++;
//		empty[rand]--;
//		System.out.println(a + " produce->in NO."+rand+". empty: "+empty[rand]+" full: "+full[rand]+ " testTime:" + testTime);
//	}
//	//注意 不同的池子之间不是互斥的
//	public synchronized void mutexC(Consumer a){
//		rand =(int) (Math.random()*empty.length);
//		if(full[rand]>0 && testTime>0 && !a.haveDone())consume(a);
//	}
//
//	public void consume(Consumer a){
//		testTime--;
//		empty[rand]++;
//		full[rand]--;
//		a.getOne();
//		System.out.println(a+ " consume->in NO."+rand+". empty: "+empty[rand]+" full: "+full[rand]+" testTime:"+testTime);
//	}
//}
