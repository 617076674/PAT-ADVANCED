#include<iostream>
#include<cmath>

using namespace std;

int main() {
	int N;
	scanf("%d", &N);
	int left = 0, right = -1;	//[left, right]为连续整数区间 
	for(int i = 2; i < sqrt(N); i++){
		if(N % i != 0){
			continue;
		}
		int j = i;
		int multiply = i;
		while(true){
			if(multiply >= N){
				break;
			}
			if(N % ((j + 1) * multiply) == 0){
				multiply *= (j + 1);
			}else{
				break;
			}
			j++;
		}
		if(j - i > right - left){
			right = j;
			left = i;
		}
	}
	if(right - left + 1 == 0){
		printf("1\n%d", N);
		return 0;
	}
	printf("%d\n", right - left + 1);
	for(int i = left; i <= right; i++){
		printf("%d", i);
		if(i != right){
			printf("*");
		}
	}
	return 0;
}
