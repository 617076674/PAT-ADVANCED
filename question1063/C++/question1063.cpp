#include<iostream>
#include<set>
#include<algorithm>

using namespace std;

int main(){
	int N, M, num, K, num1, num2, Nc, Nt;
	scanf("%d", &N);
	set<int> nums[N + 1];
	set<int>::iterator it;
	for(int i = 1; i <= N; i++){
		scanf("%d", &M);
		for(int j = 0; j < M; j++){
			scanf("%d", &num);
			nums[i].insert(num);
		}
	}
	scanf("%d", &K);
	for(int i = 0; i < K; i++){
		Nc = 0;
		scanf("%d %d", &num1, &num2);
		for(it = nums[num1].begin(); it != nums[num1].end(); it++){
			if(nums[num2].find(*it) != nums[num2].end()){
				Nc++;
			}
		}
		Nt = nums[num1].size() + nums[num2].size() - Nc;
		printf("%.1f%\n", Nc * 100.0 / Nt);
	}
}
