#include<iostream>
#include<cmath>
 
using namespace std;
 
int ranks[10000];
 
bool isPrime(int num);
 
int main() {
	fill(ranks, ranks + 10000, 0);
	int N;
	scanf("%d", &N);
	int num;
	for(int i = 1; i <= N; i++) {
		scanf("%d", &num);
		ranks[num] = i;
	}
	int K;
	scanf("%d", &K);
	for(int i = 0; i < K; i++) {
		scanf("%d", &num);
		printf("%04d: ", num);
		if(ranks[num] == -1){
			printf("Checked\n");
		}else if(ranks[num] == 1) {
			printf("Mystery Award\n");
			ranks[num] = -1;
		} else if(ranks[num] == 0) {
			printf("Are you kidding?\n");
		} else if(isPrime(ranks[num])) {
			printf("Minion\n");
			ranks[num] = -1;
		} else {
			printf("Chocolate\n");
			ranks[num] = -1;
		}
	}
	return 0;
}
 
bool isPrime(int num) {
	if(num == 1) {
		return false;
	}
	for(int i = 2; i <= sqrt(num); i++) {
		if(num % i == 0) {
			return false;
		}
	}
	return true;
}

