#include<iostream>
#include<vector>
#include<cmath>
#include<queue>

using namespace std;

struct node {
	int level;
	vector<int> child;
};

int N;
double P;
double r;
node Node[100000];
int countLevel[100000] = {0};	//第i层有countLevel[i]个叶子节点

void bfs(int nowVisit);

int main() {
	cin >> N >> P >> r;
	int K, ID;
	for(int i = 0; i < N; i++) {
		cin >> K;
		if(K != 0) {
			for(int j = 0; j < K; j++) {
				cin >> ID;
				Node[i].child.push_back(ID);
			}
		}
	}
	bfs(0);
	for(int i = 0; i < N; i++) {
		if(Node[i].child.size() == 0) {
			countLevel[Node[i].level]++;
		}
	}
	int minLevel;
	for(int i = 0; i < N; i++) {
		if(countLevel[i] != 0) {
			minLevel = i;
			break;
		}
	}
	printf("%.4lf %d\n", pow(1 + r / 100, minLevel) * P, countLevel[minLevel]);
}

void bfs(int nowVisit) {
	queue<int> q;
	Node[nowVisit].level = 0;
	q.push(nowVisit);
	while(!q.empty()){
		int now = q.front();
		q.pop();
		for(int i = 0; i < Node[now].child.size(); i++){
			Node[Node[now].child[i]].level = Node[now].level + 1;
			q.push(Node[now].child[i]);
		}
	}
}
