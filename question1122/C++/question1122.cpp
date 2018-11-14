#include<iostream>
#include<set>

using namespace std;

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	bool graph[N + 1][N + 1];
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= N; j++){
			graph[i][j] = false;
		}
	}
	int vertex1, vertex2;
	for(int i = 0; i < M; i++){
		scanf("%d %d", &vertex1, &vertex2);
		graph[vertex1][vertex2] = true;
		graph[vertex2][vertex1] = true;
	}
	int K;
	scanf("%d", &K);
	for(int i = 0; i < K; i++){
		int n;
		scanf("%d", &n);
		int nums[n];
		set<int> numSet;
		for(int j = 0; j < n; j++){
			scanf("%d", &nums[j]);
			numSet.insert(nums[j]);
		}
		if(nums[0] != nums[n - 1] || n != N + 1 || numSet.size() != N){
			printf("NO\n");
		}else{
			bool flag = true;
			for(int j = 0; j < n - 1; j++){
				if(!graph[nums[j]][nums[j + 1]]){
					flag = false;
					break;
				}
			}
			if(flag){
				printf("YES\n");
			}else{
				printf("NO\n");
			}
		}
	}
	return 0;
}
