#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	int nums[N];
	for(int i = 0; i < N; i++){
		scanf("%d", &nums[i]);
	}
	sort(nums, nums + N);
	vector<int> result;
	for(int i = 0; i < N; i++){
		int find = M - nums[i];
		int j = lower_bound(nums + i + 1, nums + N, find) - nums;
		if(j == N){
			continue;
		}
		if(nums[j] + nums[i] == M){
			result.push_back(nums[i]);
			result.push_back(nums[j]);
			break;
		}
	}
	if(result.size() == 0){
		printf("No Solution\n");
	}else{
		printf("%d %d", result[0], result[1]);
	}
	return 0;
} 
