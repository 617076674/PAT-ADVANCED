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
	int num;
	int root;
	for(int i = 0; i < N; i++){
		cin >> num;
		if(num == -1){
			root = i;
			continue;
		}
		Node[num].child.push_back(i); 
	}
	dfs(root, 0);
	int maxLevel;
	for(int i = N; i >= 0 ; i--){
		if(countLevel[i] != 0){
			maxLevel = i;
			break;
		}
	}
	printf("%.2lf %d\n", pow(1 + r / 100, maxLevel) * P, countLevel[maxLevel]);
	return 0;
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
