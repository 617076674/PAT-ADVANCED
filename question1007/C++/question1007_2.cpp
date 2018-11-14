#include<iostream>

int main() {
	int K;
	scanf("%d", &K);
	long long nums[K];
	for(int i = 0; i < K; i++) {
		scanf("%lld", &nums[i]);
	}
	long long sum = 0, max = -1;
	int left, right, tempLeft = 0;
	for(int i = 0; i < K; i++) {
		sum += nums[i];
		if(sum > max) {
			max = sum;
			left = tempLeft;
			right = i;
		}
		if(sum < 0) {
			tempLeft = i + 1;
			sum = 0;
		}
	}
	if(max < 0) {
		printf("0 %lld %lld\n", nums[0], nums[K - 1]);
	} else {
		printf("%lld %lld %lld\n", max, nums[left], nums[right]);
	}
	return 0;
}
