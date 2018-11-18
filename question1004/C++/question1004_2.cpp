#include<iostream>
#include<vector>
#include<queue> 

using namespace std;

struct node {
	int num;
	vector<int> child;
};

int N, M;	//节点总数，非叶子节点数
node Node[100];
int leaves[100];//存放每一层的叶子节点数
int depth; 

void dfs(int root, int level); 

int main(){
	fill(leaves, leaves + 100, 0);
	scanf("%d %d", &N, &M);
	int ID, K, childID;
	for(int i = 0; i < M; i++){
		scanf("%d %d", &ID, &K);
		for(int j = 0; j < K; j++){
			scanf("%d", &childID);
			Node[ID].child.push_back(childID);
		}
	}
	dfs(1, 0);
	for(int i = 0; i <= depth; i++){
		printf("%d", leaves[i]);
		if(i != depth){
			printf(" "); 
		}else{
			printf("\n");
		}
	}
	return 0; 
}

void dfs(int root, int level){
	if(Node[root].child.size() == 0){
		leaves[level]++;
		depth = max(depth, level);
		return;
	}
	for(int i = 0; i < Node[root].child.size(); i++){
		dfs(Node[root].child[i], level + 1);
	}
}
