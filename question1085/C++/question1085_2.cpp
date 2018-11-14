#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
	int n;
	long p;
	cin >> n >> p;

	long temp;
	vector<long> nums;
	for (int i = 0; i < n; i++) {
		cin >> temp;
		nums.push_back(temp);
	}
	sort(nums.begin(), nums.end());

	int **dp = new int*[n];
	for (int i = 0; i < n; i++) {
		dp[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		dp[i][i] = 1;
	}

	for (int k = -1; k >= 1 - n; k--) {
		for (int i = 0; i <= n + k - 1; i++) {
			if (nums[i - k] <= nums[i] * p) {
				dp[i][i - k] = 1 - k;
			} else {
				dp[i][i - k] = dp[i + 1][i - k];
				if (dp[i][i - k - 1] > dp[i][i - k]) {
					dp[i][i - k] = dp[i][i - k - 1];
				}
			}
		}
		delete dp[n + k];
	}

	int result;

	result = dp[0][n - 1];
	delete dp;

	cout << result;
}
