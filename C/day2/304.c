
#include <stdio.h>

int isRun(int year) {
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		return 1;
	}
	return 0;
}

int main()
{
	int months[12] = {
		31,28,31,30,31,30,31,31,30,31,30,31
	};
	int i;
	int year, month, day, days=0;
	scanf("%d %d %d", &year, &month, &day);
	for (i = 0; i < month-1; i++) {
		days += months[i];
	}
	if (isRun(year) == 1)days++;
	days += day;
	printf("It is the %d year's %dth day\n", year, days);

}

