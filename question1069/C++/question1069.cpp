#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

bool compareNum(int num1, int num2);
int noRisingArray(int num);
int noDownArray(int num);

int main() {
	int num;
	cin >> num;
	while (true) {
		int num1 = noRisingArray(num);
		int num2 = noDownArray(num);
		num = num1 - num2;
		if (num == 6174) {
			printf("%04d - %04d = %04d\n", num1, num2, num);
			break;
		} else {
			if (num1 == num2) {
				printf("%04d - %04d = 0000", num1, num2);
				break;
			} else {
				printf("%04d - %04d = %04d\n", num1, num2, num);
			}
		}
	}
}

bool compareNum(int num1, int num2) {
	if (num1 <= num2) {
		return false;
	} else {
		return true;
	}
}

int noRisingArray(int num) {
	vector<int> nums;
	while (num > 0) {
		nums.push_back(num % 10);
		num /= 10;
	}
	while (nums.size() < 4) {
		nums.push_back(0);
	}
	sort(nums.begin(), nums.end(), compareNum);
	int result = 0;
	for (int i = 0; i < nums.size(); i++) {
		result = result * 10 + nums[i];
	}
	return result;
}

int noDownArray(int num) {
	vector<int> nums;
	while (num > 0) {
		nums.push_back(num % 10);
		num /= 10;
	}
	while (nums.size() < 4) {
		nums.push_back(0);
	}
	sort(nums.begin(), nums.end());
	int result = 0;
	for (int i = 0; i < nums.size(); i++) {
		result = result * 10 + nums[i];
	}
	return result;
}