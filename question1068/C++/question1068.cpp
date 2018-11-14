#include<iostream>
#include<algorithm>

using namespace std;

bool cmp(int a, int b);

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	int nums[N];
	for(int i = 0; i < N; i++){
		scanf("%d", &nums[i]);
	}
	sort(nums, nums + N, cmp);
	int dp[N][M + 1];
	bool choice[N][M + 1];
	for(int i = 0; i < M + 1; i++){
		if(nums[0] <= i){
			dp[0][i] = nums[0];
			choice[0][i] = true;	//选择了索引为0的硬币 
		}else{
			dp[0][i] = 0;
			choice[0][i] = false;	//不选择索引为0的硬币 
		}
	}
	for(int i = 1; i < N; i++){
		for(int j = 0; j < M + 1; j++){
			if(j - nums[i] >= 0 && dp[i - 1][j - nums[i]] + nums[i] >= dp[i - 1][j]){
				dp[i][j] = dp[i - 1][j - nums[i]] + nums[i];
				choice[i][j] = true;	//选择索引为i的硬币 
			}else{
				dp[i][j] = dp[i - 1][j];
				choice[i][j] = false; 
			}
		}
	}
	if(dp[N - 1][M] != M){
		printf("No Solution\n");
		return 0;
	}
	bool flag[N];
	int value = M, count = 0;
	for(int i = N - 1; i >= 0; i--){
		if(choice[i][value]){
			flag[i] = true;
			value -= nums[i];
			count++;
		}else{
			flag[i] = false;
		}
	}
	for(int i = N - 1; i >= 0; i--){
		if(flag[i]){
			printf("%d", nums[i]);
			count--;
			if(count > 0){
				printf(" ");
			}
		}
	}
	return 0;
} 

bool cmp(int a, int b){
	return a > b;
}
