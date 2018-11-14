#include<iostream>
#include<cmath>

using namespace std;

int findPrime(int num);	//寻找大于等于num的最小素数
bool isPrime(int num);	//判断一个数是否是素数

int main() {
	int MSize, N;
	scanf("%d %d", &MSize, &N);
	int trueMSize = findPrime(MSize);
	bool flag[trueMSize];
	fill(flag, flag + trueMSize, false);
	int num;
	int temp;
	for(int i = 0; i < N; i++) {
		scanf("%d", &num);
		temp = num % trueMSize;
		if(!flag[temp]) {
			printf("%d", temp);
			flag[temp] = true;
		} else {
			int j = 1;
			for(; j < trueMSize; j++) {
				temp = (j * j + num) % trueMSize;
				if(!flag[temp]) {
					printf("%d", temp);
					flag[temp] = true;
					break;
				}
			}
			if(j >= trueMSize){
				printf("-");
			}
		}
		if(i != N - 1) {
			printf(" ");
		}
	}
	return 0;
}

int findPrime(int num) {
	for(int i = num; ; i++) {
		if(isPrime(i)) {
			return i;
		}
	}
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
