#include<iostream>
#include<set>
#include<map>

using namespace std;

set<int> goodsMap[100000];	//不相容的物品 

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	int num1, num2;
	for(int i = 0; i < N; i++){
		scanf("%d %d", &num1, &num2);
		goodsMap[num1].insert(num2);
		goodsMap[num2].insert(num1); 
	}
	for(int i = 0; i < M; i++){
		int K;
		scanf("%d", &K);
		int nums[K];
		for(int j = 0; j < K; j++){
			scanf("%d", &nums[j]);
		}
		bool flag = true;
		for(int j = 0; j < K; j++){
			for(int k = j + 1; k < K; k++){
				if(goodsMap[nums[j]].find(nums[k]) != goodsMap[nums[j]].end()){
					flag = false;
					break;
				}
			}
			if(!flag){
				break;
			}
		}
		if(flag){
			printf("Yes\n");
		}else{
			printf("No\n");
		}
	}
	return 0;
}
