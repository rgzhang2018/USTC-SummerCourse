#include <stdio.h>
// 题目：因数分解
// 如 s = a1*a2*a3*...
// 要求a为正整数
// 求所有可能的个数
// 例如：输入s=20，输出4
// 解释：
// s = 1*20
// s = 2*10
// s = 2*2*5
// s = 4*5

int makeIt(int n, int start) {
	if(n==1)return 1;//递归出口，不管带入多少，最后的乘数一定是1，这时表示本次的因数分解完成，因数+1
	int count = 0;
	int temp ;
	for (int i = start; i<=n; i++) {
		if (n%i == 0) {
			temp = n / i;
			count += makeIt(temp,i);//如s=a*b，这里temp是将b也带入到运算。 带入i是为了防止重复计算
		}
	}
	return count;
}
//该方法分解出来的因数实例：
// 12=2*6：  2*2*3*1
// 		     2*6*1
// 12=3*4：  3*4*1
// 12=12*1： 12*1
//共四个。注意最末尾的1是出口

int main(int argc, char const *argv[])
{
	/* code */
	int n;
	scanf("%d", &n);
	int count = makeIt(n, 2);
	printf("%d", count);
	return 0;
}