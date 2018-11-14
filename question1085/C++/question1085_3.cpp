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

	int result = 0;
	for (int i = 0; i < nums.size(); i++) {
		for (int j = i + result; j < nums.size(); j++) {
			if (nums[j] <= nums[i] * p) {
				if (j - i + 1 > result) {
					result = j - i + 1;
				}
			} else {
				break;
			}
		}
	}

	cout << result;
}
