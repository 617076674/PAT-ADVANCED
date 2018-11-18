#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

bool isSolution(vector<int> nums);	//判断给出的N皇后解决方案是否正确 

int main(){
	int K;
	scanf("%d", &K);
	vector<int> nums;
	int num;
	for(int i = 0; i < K; i++){
		nums.clear();
		int N;
		scanf("%d", &N);
		for(int j = 0; j < N; j++){
			scanf("%d", &num);
			nums.push_back(num);
		}
		if(isSolution(nums)){
			printf("YES\n");
		}else{
			printf("NO\n");
		}
	}
	return 0;
}

bool isSolution(vector<int> nums){
	for(int i = 0; i < nums.size(); i++){
		for(int j = i + 1; j < nums.size(); j++){
			if(nums[i] == nums[j] || abs(i - j) == abs(nums[i] - nums[j])){	//如果两个皇后出现的同一行或出现在对角线，说明不正确 
				return false;
			}
		}
	}
	return true;
}
