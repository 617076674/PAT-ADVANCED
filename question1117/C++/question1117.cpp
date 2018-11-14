#include<iostream>
#include<algorithm>

using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	int nums[N];
	for(int i = 0; i < N; i++){
		scanf("%d", &nums[i]);
	}
	sort(nums, nums + N);
	for(int i = nums[N - 1]; i >= 0; i--){
		int index = upper_bound(nums, nums + N, i) - nums;
		if(N - index >= i){
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}
