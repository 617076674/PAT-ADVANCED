#include<iostream>

using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	int nums[N + 1];	//数组需要开N + 1大小，其中num[i]存储i 
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
		if(nums[i] == -1){	//一旦找到了缺失的某个正数i,就输出 
			printf("%d\n", i);
			break;
		}
	}
	if(i > N){	//如果所有1 ~ N的所有正数都在，缺失的第一个正数一定是N + 1 
		printf("%d\n", i);
	} 
	return 0;
} 
