#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

struct node{
	vector<int> child;
};

int N;
double P;
double r;
node Node[100000];
int countLevel[100000] = {0};	//第i层有countLevel[i]个叶子节点

void dfs(int nowVisit, int level);

int main(){
	cin >> N >> P >> r;
	int K, ID;
	for(int i = 0; i < N; i++){
		cin >> K;
		if(K != 0){
			for(int j = 0; j < K; j++){
				cin >> ID;
				Node[i].child.push_back(ID);
			}
		}
	}
	dfs(0, 0);
	int minLevel;
	for(int i = 0; i < N; i++){
		if(countLevel[i] != 0){
			minLevel = i;
			break;
		}
	}
	printf("%.4lf %d\n", pow(1 + r / 100, minLevel) * P, countLevel[minLevel]);
}

void dfs(int nowVisit, int level){
	if(Node[nowVisit].child.size() == 0){
		countLevel[level]++;
		return;
	}
	for(int i = 0; i < Node[nowVisit].child.size(); i++){
		dfs(Node[nowVisit].child[i], level + 1);
	}
} 
