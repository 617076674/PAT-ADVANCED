#include<iostream>
#include<cmath>

using namespace std;

bool isPrime(int num);

int main() {
	int MSize, N, M;
	scanf("%d %d %d", &MSize, &N, &M);
	while(!isPrime(MSize)) {
		MSize++;
	}
	int hashTable[MSize];
	fill(hashTable, hashTable + MSize, -1);	//初始化为-1，说明该位置还未插入值 
	int num;
	for(int i = 0; i < N; i++) {
		scanf("%d", &num);
		if(hashTable[num % MSize] == -1) {	//如果未发生冲突 
			hashTable[num % MSize] = num;
		} else {	//如果发生了冲突 
			bool flag = false;
			for(int j = 1; j < MSize; j++) {	//正平方探测法寻找空位插入值 
				if(hashTable[(num + j * j) % MSize] == -1) {
					hashTable[(num + j * j) % MSize] = num;
					flag = true;	//flag = true表示插入成功 
					break;
				}
			}
			if(!flag) {	//如果没有插入成功 
				printf("%d cannot be inserted.\n", num);
			}
		}
	}
	int totalTime = M;	//对需要查找的每一个数字，即使一步到位就找到，也需要计数1 
	for(int i = 0; i < M; i++) {
		scanf("%d", &num);
		for(int j = 0; j < MSize; j++) {	//用正平方探测法寻找值 
			if(hashTable[(num + j * j) % MSize] == num || hashTable[(num + j * j) % MSize] == -1) {	//如果找到了该值 
				break;
			}else{
				totalTime++;	//如果本次探测没有找到该值，则冲突次数totaltime加1 
			}
		}
	}
	printf("%.1f\n", totalTime * 1.0 / M);
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
