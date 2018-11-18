#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int n;	//城市数量
int m;	//高速公路数量
int k;	//需要检查的城市数量
vector<int> graph[1001];	//无向图
bool inq[1001];

void bfs(int nowVisit, int city);

int main() {
	scanf("%d %d %d", &n, &m, &k);
	int city1, city2;
	for(int i = 0; i < m; i++) {
		scanf("%d %d", &city1, &city2);
		graph[city1 - 1].push_back(city2 - 1);
		graph[city2 - 1].push_back(city1 - 1);
	}
	int city;
	for(int i = 0; i < k; i++) {
		scanf("%d", &city);
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
		printf("%d\n", count - 1);
	}
}

void bfs(int nowVisit, int city) {
	queue<int> q;
	q.push(nowVisit);
	while(!q.empty()) {
		int now = q.front();
		inq[now] = true;
		q.pop();
		for(int i = 0; i < graph[now].size(); i++){
			if(graph[now][i] != city - 1 && !inq[graph[now][i]]) {
				q.push(graph[now][i]);
			}
		}
	}
}
