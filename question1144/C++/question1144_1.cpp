#include<iostream>

using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	int nums[N + 1];	//������Ҫ��N + 1��С������num[i]�洢i 
	fill(nums, nums + N, -1);
	int num;
	for(int i = 0; i < N; i++){
		scanf("%d", &num);
		if(num >= 0 && num <= N){
			nums[num] = num;
		}
	}
	int i = 1;
	for(; i <= N; i++){
		if(nums[i] == -1){	//һ���ҵ���ȱʧ��ĳ������i,����� 
			printf("%d\n", i);
			break;
		}
	}
	if(i > N){	//�������1 ~ N�������������ڣ�ȱʧ�ĵ�һ������һ����N + 1 
		printf("%d\n", i);
	} 
	return 0;
} 
