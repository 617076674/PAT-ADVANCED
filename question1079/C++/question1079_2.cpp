#include<iostream>
#include<vector>
#include<math.h>
#include<queue>

using namespace std;

struct node{
	int sales;
	int level;
	vector<int> child;
};

int N;
double P;
double r;
node Node[100000];
double totalSales = 0.0;

void bfs(int nowVisit);

int main(){
	cin >> N >> P >> r;
	int K, num;
	for(int i = 0; i < N; i++){
		cin >> K;
		if(K == 0){
			cin >> num;
			Node[i].sales = num; 
		}else{
			for(int j = 0; j < K; j++){
				cin >> num;
				Node[i].child.push_back(num);
			}
		}
	}
	bfs(0);
	printf("%.1lf\n", totalSales);	//自动四舍五入 
	return 0;
}

void bfs(int nowVisit){
	queue<int> q;
	Node[nowVisit].level = 0;
	q.push(nowVisit);
	while(!q.empty()){
		int now = q.front();
		if(Node[now].child.size() == 0){
			totalSales += Node[now].sales * P * pow(1.0 + r / 100, Node[now].level);
		}
		q.pop();
		for(int i = 0; i < Node[now].child.size(); i++){
			Node[Node[now].child[i]].level = Node[now].level + 1;
			q.push(Node[now].child[i]);
		}
	}
}
void dfs(int nowVisit, int level){
	if(Node[nowVisit].child.size() == 0){
		
		return;
	}
	for(int i = 0; i < Node[nowVisit].child.size(); i++){
		dfs(Node[nowVisit].child[i], level + 1);
	}
}
