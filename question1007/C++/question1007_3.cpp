#include<iostream>

int main() {
	int K;
	scanf("%d", &K);
	long long nums[K];
	for(int i = 0; i < K; i++) {
		scanf("%lld", &nums[i]);
	}
	long long dp[K];	//dp[i]表示以nums[i]结尾的最大序列和
	int left[K];	//left[i]表示以nums[i]结尾的最大序列的左端索引 
	dp[0] = nums[0];
	left[0] = 0; 
	for(int i = 1; i < K; i++){
		if(nums[i] > nums[i] + dp[i - 1]){
			dp[i] = nums[i];
			left[i] = i;
		}else{
			dp[i] = nums[i] + dp[i - 1];
			left[i] = left[i - 1];
		}
	}
	int max = 0;
	for(int i = 1; i < K; i++){
		if(dp[i] > dp[max]){
			max = i;
		}
	}
	if(dp[max] < 0){
		printf("0 %lld %lld\n", nums[0], nums[K - 1]);
	}else{
		printf("%lld %lld %lld\n", dp[max], nums[left[max]], nums[max]);
	} 
	return 0;
}
