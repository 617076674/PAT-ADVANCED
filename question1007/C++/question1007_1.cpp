#include<iostream>

int main() {
	int K;
	scanf("%d", &K);
	long long nums[K];
	for(int i = 0; i < K; i++) {
		scanf("%lld", &nums[i]);
	}
	long long sum[K];	//sum[i] = nums[0] + ... + nums[i]
	sum[0] = nums[0];
	for(int i = 1; i < K; i++) {
		sum[i] = sum[i - 1] + nums[i];
	}
	long long max = -1;
	int left = -1, right = -1;
	for(int i = 0; i < K; i++) {
		if(i == 0) {
			for(int j = i; j < K; j++) {
				if(sum[j] > max) {
					max = sum[j];
					left = 0;
					right = j;
				}
			}
		} else {
			for(int j = i; j < K; j++) {
				if(sum[j] - sum[i - 1] > max) {
					max = sum[j] - sum[i - 1];
					left = i;
					right = j;
				}
			}
		}
	}
	if(max < 0) {
		printf("0 %lld %lld\n", nums[0], nums[K - 1]);
	} else {
		printf("%lld %lld %lld\n", max, nums[left], nums[right]);
	}
	return 0;
}
