#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int result = 1;
int 
fibo(int n){
	if(n == 0|| n == 1)
		return 1;
	result *= n;

	return n*fibo(n-1);

}
int
main(int argc, char *argv[]){
	int res = fibo(6);
	printf("%i\n",res);
	return EXIT_SUCCESS;
}
