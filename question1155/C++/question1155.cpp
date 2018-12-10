#include<iostream>
#include<vector>

using namespace std;

int N, levelOrder[1000];
bool flag1 = true, flag2 = true;	//flag1用于判别最大堆，flag2用于判别最小堆 
vector<int> path;

void dfs(int now);

int main(){
	scanf("%d", &N);
	for(int i = 0; i < N; i++){
		scanf("%d", &levelOrder[i]);
	}
	dfs(0);
	if(flag1){
		printf("Max Heap\n");
	}else if(flag2){
		printf("Min Heap\n");
	}else{
		printf("Not Heap\n");
	}
	return 0;
}

void dfs(int now){
	path.push_back(levelOrder[now]);
	int lchild = now * 2 + 1, rchild = now * 2 + 2;
	if(lchild >= N){
		for(int i = 0; i < path.size(); i++){
			printf("%d", path[i]);
			if(i != path.size() - 1){
				printf(" ");
			}else{
				printf("\n");
			}
		}
		path.pop_back();
		return;
	}
	if(rchild < N){
		if(levelOrder[now] > levelOrder[rchild]){
			flag2 = false;
		}
		if(levelOrder[now] < levelOrder[rchild]){
			flag1 = false;
		}
		dfs(rchild);
	}
	if(lchild < N){
		if(levelOrder[now] > levelOrder[lchild]){
			flag2 = false;
		}
		if(levelOrder[now] < levelOrder[lchild]){
			flag1 = false;
		}
		dfs(lchild);
	}
	path.pop_back();
}
