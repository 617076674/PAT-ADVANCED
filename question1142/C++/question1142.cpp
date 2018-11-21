#include<iostream>
#include<set>

using namespace std;

set<int> graph[201];	

int main(){
	int Nv, Ne;
	scanf("%d %d", &Nv, &Ne);
	int v1, v2;
	for(int i = 0; i < Ne; i++){
		scanf("%d %d", &v1, &v2);
		graph[v1].insert(v2);
		graph[v2].insert(v1);
	}
	int M;
	scanf("%d", &M);
	for(int i = 0; i < M; i++){
		int K;
		scanf("%d", &K);
		int nums[K];
		set<int> numSet;
		for(int j = 0; j < K; j++){
			scanf("%d", &nums[j]);
			numSet.insert(nums[j]);
		}
		bool flag = true;	//判断其是否是一个clique 
		for(int j = 0; j < K; j++){
			for(int k = j + 1; k < K; k++){
				if(graph[nums[j]].find(nums[k]) == graph[nums[j]].end()){
					flag = false;
					break;
				}
			}
			if(!flag){
				break;
			}
		}
		if(!flag){
			printf("Not a Clique\n");
		}else{
			bool flag2 = true;	//判断是否是最大clique 
			for(int j = 1; j <= Nv; j++){
				if(numSet.find(j) != numSet.end()){
					continue;
				}
				bool flag3 = true;	//判断该点j能否加入到clique中 
				for(int k = 0; k < K; k++){
					if(graph[j].find(nums[k]) == graph[j].end()){
						flag3 = false;
						break;
					}
				}
				if(flag3){	//一旦发现还有额外的顶点可以加入clique中 
					flag2 = false;	//说明当前clique并不是一个最大clique 
					break;
				}
			}
			if(!flag2){
				printf("Not Maximal\n");
			}else{
				printf("Yes\n");
			}
		}
	}
	return 0;
}
