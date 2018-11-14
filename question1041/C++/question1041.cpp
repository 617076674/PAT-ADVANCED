#include<iostream>
#include<vector>

using namespace std;

int main(){
	int flag[10001];
	fill(flag, flag + 10001, 0); 
	int N;
	scanf("%d", &N);
	int num;
	vector<int> nums;
	for(int i = 0; i < N; i++){
		scanf("%d", &num);
		nums.push_back(num);
		flag[num]++;
	}
	int i = 0;
	for(; i < N; i++){
		if(flag[nums[i]] == 1){
			printf("%d\n", nums[i]);
			break;
		}
	}
	if(i >= N){
		printf("None\n");
	}
	return 0;
}
