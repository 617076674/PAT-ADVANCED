#include<iostream>
#include<vector>
#include<set>

using namespace std;

struct edge{
	int v1, v2;
};

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	edge edges[M];
	for(int i = 0; i < M; i++){
		scanf("%d %d", &edges[i].v1, &edges[i].v2);
	}
	int K;
	scanf("%d", &K);
	for(int i = 0; i < K; i++){
		int Nv;
		scanf("%d", &Nv);
		int num;
		set<int> nums;
		for(int j = 0; j < Nv; j++){
			scanf("%d", &num);
			nums.insert(num);
		}
		bool flag = true;
		for(int j = 0; j < M; j++){	//对每一条边都需要查询其两个端点是否至少有一个在set集合中 
			if(nums.find(edges[j].v1) == nums.end() && nums.find(edges[j].v2) == nums.end()){	//如果两个都不在 
				flag = false;
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
