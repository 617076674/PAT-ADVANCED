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
	fill(hashTable, hashTable + MSize, -1);	//��ʼ��Ϊ-1��˵����λ�û�δ����ֵ 
	int num;
	for(int i = 0; i < N; i++) {
		scanf("%d", &num);
		if(hashTable[num % MSize] == -1) {	//���δ������ͻ 
			hashTable[num % MSize] = num;
		} else {	//��������˳�ͻ 
			bool flag = false;
			for(int j = 1; j < MSize; j++) {	//��ƽ��̽�ⷨѰ�ҿ�λ����ֵ 
				if(hashTable[(num + j * j) % MSize] == -1) {
					hashTable[(num + j * j) % MSize] = num;
					flag = true;	//flag = true��ʾ����ɹ� 
					break;
				}
			}
			if(!flag) {	//���û�в���ɹ� 
				printf("%d cannot be inserted.\n", num);
			}
		}
	}
	int totalTime = M;	//����Ҫ���ҵ�ÿһ�����֣���ʹһ����λ���ҵ���Ҳ��Ҫ����1 
	for(int i = 0; i < M; i++) {
		scanf("%d", &num);
		for(int j = 0; j < MSize; j++) {	//����ƽ��̽�ⷨѰ��ֵ 
			if(hashTable[(num + j * j) % MSize] == num || hashTable[(num + j * j) % MSize] == -1) {	//����ҵ��˸�ֵ 
				break;
			}else{
				totalTime++;	//�������̽��û���ҵ���ֵ�����ͻ����totaltime��1 
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
