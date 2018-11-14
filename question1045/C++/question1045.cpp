#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
	int N;
	scanf("%d", &N);
	int M;
	scanf("%d", &M);
	int position[N + 1];
	fill(position, position + N + 1, -1);
	int num;
	for(int i = 0; i < M; i++) {
		scanf("%d", &num);
		position[num] = i;
	}
	int L;
	scanf("%d", &L);
	vector<int> nums;
	for(int i = 0; i < L; i++) {
		scanf("%d", &num);
		if(position[num] == -1) {
			continue;
		}
		nums.push_back(position[num]);
	}
	int dp[nums.size()];
	fill(dp, dp + nums.size(), 1);
	int maxIndex = 0;
	for(int i = 1; i < nums.size(); i++) {
		for(int j = 0; j < i; j++) {
			if(nums[i] >= nums[j]) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
		if(dp[i] > dp[maxIndex]) {
			maxIndex = i;
		}
	}
	printf("%d\n", dp[maxIndex]);
	return 0;
}
