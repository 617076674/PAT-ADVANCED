#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int n;	//城市数量
int m;	//高速公路数量
int k;	//需要检查的城市数量
int graph[1001][1001] = {0};	//无向图
bool inq[1001];

void bfs(int nowVisit, int city);

int main() {
	cin >> n >> m >> k;
	int city1, city2;
	for(int i = 0; i < m; i++) {
		cin >> city1 >> city2;
		graph[city1 - 1][city2 - 1] = 1;
		graph[city2 - 1][city1 - 1] = 1;
	}
	int city;
	for(int i = 0; i < k; i++) {
		cin >> city;
		int count = 0;
		fill(inq, inq + 1001, false);
		for(int j = 0; j < n; j++) {
			if(j == city - 1) {
				continue;
			}
			if(!inq[j]) {
				bfs(j, city);
				count++;
			}
		}
		cout << count - 1 << endl;
	}
}

void bfs(int nowVisit, int city) {
	queue<int> q;
	q.push(nowVisit);
	while(!q.empty()) {
		int now = q.front();
		inq[now] = true;
		q.pop();
		for(int i = 0; i < n; i++) {
			if(i != city - 1 && !inq[i] && graph[i][now] != 0) {
				q.push(i);
			}
		}
	}
}
