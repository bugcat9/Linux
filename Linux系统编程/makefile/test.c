#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

int add(int , int);
int sub(int , int);
int main(int argc, char *argv[]){
	int a = 9, b = 3;
	printf("%d + %d = %d\n", a, b, add(a, b));
	printf("%d - %d = %d\n", a, b, sub(a, b));
	return 0;	
}
