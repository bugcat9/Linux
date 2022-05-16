#include"mymath.h"

int main(int argc, char *argv[]){
	int a = 9, b = 3;
	printf("%d + %d = %d\n", a, b, add(a, b));
	printf("%d - %d = %d\n", a, b, sub(a, b));

	printf("finish!!!\n");
	return 0;	
}


