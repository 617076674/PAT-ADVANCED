#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct node{
	int weight;
	vector<int> children;
};

int N, M, S, ID, K, child;
node Node[100];
vector<int> path;

bool cmp(int num1, int num2);
void dfs(int nowVisit, int sum);

int main(){
	scanf("%d %d %d", &N, &M, &S);
	for(int i = 0; i < N; i++){
		scanf("%d", &Node[i].weight);
	}
	for(int i = 0; i < M; i++){
		scanf("%d %d", &ID, &K);
		for(int j = 0; j < K; j++){
			scanf("%d", &child);
			Node[ID].children.push_back(child);
		}
		sort(Node[ID].children.begin(), Node[ID].children.end(), cmp);
	}
	dfs(0, 0);
	return 0;
}

bool cmp(int num1, int num2){
	return Node[num1].weight > Node[num2].weight;
}

void dfs(int nowVisit, int sum){
	path.push_back(nowVisit);
	if(Node[nowVisit].children.size() == 0){
		sum += Node[nowVisit].weight;
		if(sum == S){
			for(int i = 0; i < path.size(); i++){
				printf("%d", Node[path[i]].weight);
				if(i != path.size() - 1){
					printf(" ");
				}else{
					printf("\n");
				}
			}
		}
		path.pop_back();
		return;
	}
	if(sum > S){
		return;
	}
	for(int i = 0; i < Node[nowVisit].children.size(); i++){
		dfs(Node[nowVisit].children[i], sum + Node[nowVisit].weight);
	}
	path.pop_back();
}
