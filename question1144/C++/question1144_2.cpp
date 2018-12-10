#include<iostream>

using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	int nums[N + 1];
	for(int i = 0; i < N; i++){
		scanf("%d", &nums[i]);
	}
	nums[N] = -1;
	for(int i = 0; i <= N; i++){
		while(nums[i] >= 0 && nums[i] <= N && nums[i] != i){
			if(nums[nums[i]] == nums[i]){
				break;
			}
			swap(nums[i], nums[nums[i]]);
		}
	}
	for(int i = 1; i <= N; i++){
		if(nums[i] != i){
			printf("%d\n", i);
			return 0;
		}
	}
	printf("%d\n", N + 1);
	return 0;
}
