package thread;


import static java.lang.Thread.yield;

public class SellTicketsThread{
	int empty=10;
	int full=0;
	int testTime;//测试次数
	public SellTicketsThread(int times) {
		testTime = times;
	}

	public synchronized void mutexP(Producer a){
		if(this.empty>0&&testTime>0)produce(a);
	}

	public void produce(Producer a) {
		testTime--;
		full++;
		empty--;
		System.out.println(a + "  produce one->  empty: " + empty + " full: " + full + " testTime:" + testTime);
	}

	public synchronized void mutexC(Consumer a){
		if(full>0 && testTime>0 && !a.haveDone())consume(a);

	}

	public void consume(Consumer a){
		testTime--;
		empty++;
		full--;
		a.getOne();
		System.out.println(a+ " consume one->  empty: "+empty+" full: "+full+" testTime:"+testTime);
	}
}
