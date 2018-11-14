#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int perfectArrays(vector<long> nums, int left, int right, int p);

int main(){
	int n, p;
	
	cin >> n >> p;
	
	vector<long> nums;
	long tempNum;
	for(int i = 0; i < n; i++){
		cin >> tempNum;
		nums.push_back(tempNum);
	}
	
	sort(nums.begin(), nums.end());
	
	cout << perfectArrays(nums, 0, n - 1, p);
	
	return 0;
}

int perfectArrays(vector<long> nums, int left, int right, int p){
	if(left >= right){
		return 1;
	}
	if(nums[right] <= nums[left] * p){
		return right - left + 1;
	}else{
		int result1 = perfectArrays(nums, left + 1, right, p);
		int result2 = perfectArrays(nums, left, right - 1, p);
		if(result1 >= result2){
			return result1;
		}
		return result2;
	}
}
