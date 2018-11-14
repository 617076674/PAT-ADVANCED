#include<iostream>
#include<algorithm>

using namespace std;

int main() {
	int N;
	scanf("%d", &N);
	int nums[N];
	for(int i = 0; i < N; i++) {
		scanf("%d", &nums[i]);
	}
	sort(nums, nums + N);
	int sum1 = 0, sum2 = 0;
	if(N % 2 == 0) {
		printf("0 ");
	} else {
		printf("1 ");
	}
	for(int i = 0; i < N / 2; i++) {
		sum1 += nums[i];
	}
	for(int i = N / 2; i < N; i++) {
		sum2 += nums[i];
	}
	printf("%d\n", sum2 - sum1);
	return 0;
}
