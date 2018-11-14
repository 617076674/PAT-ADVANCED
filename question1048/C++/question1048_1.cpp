#include<iostream>
#include<algorithm>

using namespace std;

int main(){
	int N, M;
	scanf("%d%d", &N, &M);
	int nums[N];
	for(int i = 0; i < N; i++){
		scanf("%d", &nums[i]);
	}
	sort(nums, nums + N);
	int left = 0;
	int right = N - 1;
	while(left < right){
		if(nums[left] + nums[right] == M){
			printf("%d %d\n", nums[left], nums[right]);
			break;
		}else if(nums[left] + nums[right] < M){
			left++;
		}else{
			right--;
		}
	}
	if(left >= right){
		printf("No Solution\n");
	}
	return 0;
}
