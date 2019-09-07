#include<stdio.h>
#include<sys/time.h>
int main()
{
	struct timeval start ,end;
	gettimeofday(&start,NULL);
	double timeuse;
	double sum;
	int j,k;
	for(j=0;j<1000000000;j++)
		for(k=0;k<10;k++)
			sum=sum+1.0;
	gettimeofday(&end,NULL);
			timeuse=1000000*(end.tv_sec-start.tv_sec)+end.tv_usec-start.tv_usec;
			timeuse/=1000000;
			printf("%f\n",timeuse);
}
