// Name:Minjie Shen
// lab for module 8: recursion
#include <stdio.h>

long long int factorial(long long int n){
	long long int result = 1;
	if (n <= 1) {
		return result;
	}
	for(int i = 2; i <= n; i++) {
		result *= i;
	}
	return result;
};

long long int factorial_rec(int n){
	if (n == 0 || n == 1) {
		return 1;
	}
	long long int result = factorial_rec(n - 1) * n;
	return result;
}

int main(){

  // Both of these should print the same result!
  printf("factorial(20) = %lld\n",factorial(20));
  printf("factorial_rec(21) = %lld\n",factorial_rec(21));


  return 0;
}
