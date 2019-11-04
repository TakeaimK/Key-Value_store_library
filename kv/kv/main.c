#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	struct timeval tv1,tv2;
	int rs, i;
	char key[4096]; // 예제 크기임. 실제로는 다양한 크기를 처리할 수 있어야 함.
	char value[256]; // 예제 크기임. 실제로는 다양한 크기를 처리할 수 있어야 함.
	char buf[256]; // 예제 크기임. 실제로는 다양한 크기를 처리할 수 있어야 함.
	

	gettimeofday(&tv1, NULL);
	rs=kvopen();
	gettimeofday(&tv2, NULL);
	printf("kvopen ok %d\n", rs);
	printf("time : %f\n",((tv2.tv_sec+tv2.tv_usec*0.000001)-(tv1.tv_sec+tv1.tv_usec*0.000001)));



	gettimeofday(&tv1, NULL);
	for (i=0; i<100; i++)
	{
		rs=kvput(key, value);
	}
	gettimeofday(&tv2, NULL);
	printf("kvput ok %d\n", rs);
	printf("time : %f\n",((tv2.tv_sec+tv2.tv_usec*0.000001)-(tv1.tv_sec+tv1.tv_usec*0.000001)));


	gettimeofday(&tv1, NULL);
	for (i=0; i<100; i++)
	{
		rs=kvget(key, buf);
	}
	gettimeofday(&tv2, NULL);
	printf("kvget ok %d\n", rs);
	printf("time : %f\n",((tv2.tv_sec+tv2.tv_usec*0.000001)-(tv1.tv_sec+tv1.tv_usec*0.000001)));


	gettimeofday(&tv1, NULL);
	for (i=0; i<100; i++)
	{
		rs=kvdel(key);
	}
	gettimeofday(&tv2, NULL);
	printf("kvdel ok %d\n", rs);
	printf("time : %f\n",((tv2.tv_sec+tv2.tv_usec*0.000001)-(tv1.tv_sec+tv1.tv_usec*0.000001)));


	gettimeofday(&tv1, NULL);
	rs=kvclose();
	gettimeofday(&tv2, NULL);
	printf("kvclose ok %d\n", rs);
	printf("time : %f\n",((tv2.tv_sec+tv2.tv_usec*0.000001)-(tv1.tv_sec+tv1.tv_usec*0.000001)));
	
	return 0;
}
