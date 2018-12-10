 #include<iostream>
#include<cmath>
#include<cstring>

using namespace std;

int L, K;

bool isPrime(int num);

int main(){
	scanf("%d %d", &L, &K);
	char input[L + 1];
	scanf("%s", input);
	if(K == 0){
		printf("404\n");
		return 0;
	}
	for(int i = 0; i + K <= strlen(input); i++){
		int result = 0;
		char temp[K + 1];
		for(int j = i; j < i + K; j++){
			result = input[j] - '0' + result * 10;
			temp[j - i] = input[j];
		}
		temp[K] = '\0';
		if(isPrime(result)){
			printf("%s\n", temp);
			return 0;
		}
	}
	printf("404\n");
	return 0;
} 

bool isPrime(int num){
	if(num == 1){
		return false;
	}
	for(int i = 2; i <= sqrt(num); i++){
		if(num % i == 0){
			return false;
		}
	}
	return true;
}
