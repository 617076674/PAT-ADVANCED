#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct node {
	int level;
	vector<int> child;
};

int N;
int M;
node Node[101];
int count[101] = {0};	//第i层有count[i]个成员

void bfs(int nowVisit);

int main() {
	cin >> N >> M;
	int ID, K, num;
	for(int i = 0; i < M; i++) {
		cin >> ID >> K;
		for(int j = 0; j < K; j++) {
			cin >> num;
			Node[ID].child.push_back(num);
		}
	}
	bfs(1);
	for(int i = 1; i <= N; i++) {
		count[Node[i].level]++;
	}
	int maxGeneration = 0;
	for(int i = 1; i <= N; i++) {
		if(count[i] > count[maxGeneration]) {
			maxGeneration = i;
		}
	}
	cout << count[maxGeneration] << " " << maxGeneration << endl;
	return 0;
}


void bfs(int nowVisit) {
	queue<int> q;
	Node[nowVisit].level = 1;
	q.push(nowVisit);
	while(!q.empty()) {
		int now = q.front();
		q.pop();
		for(int i = 0; i < Node[now].child.size(); i++) {
			Node[Node[now].child[i]].level = Node[now].level + 1;
			q.push(Node[now].child[i]);
		}
	}
}
