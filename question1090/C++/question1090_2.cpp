#include<iostream>
#include<vector>
#include<cmath>
#include<queue>

using namespace std;

struct node{
	int level;
	vector<int> child;
};

int N;
double P;
double r;
node Node[100000];

void bfs(int nowVisit); 

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
	bfs(root);
	int maxLevel = 0;
	for(int i = 0; i < N ; i++){
		if(Node[i].level > maxLevel){
			maxLevel = Node[i].level;
		}
	}
	int countMaxLevel = 0;
	for(int i = 0; i < N; i++){
		if(Node[i].level == maxLevel){
			countMaxLevel++;
		}
	}
	printf("%.2lf %d\n", pow(1 + r / 100, maxLevel) * P, countMaxLevel);
	return 0;
} 

void bfs(int nowVisit){
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
