#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M, K;
vector<int> graph[1001];	//ÎÞÏòÍ¼
bool inq[1001];
int lost_city, count;

void bfs(int nowVisit);

int main() {
	scanf("%d %d %d", &N, &M, &K);
	int city1, city2;
	for(int i = 0; i < M; i++) {
		scanf("%d %d", &city1, &city2);
		graph[city1].push_back(city2);
		graph[city2].push_back(city1);
	}
	for(int i = 0; i < K; i++) {
		scanf("%d", &lost_city);
		count = 0;
		fill(inq + 1, inq + N + 1, false);
		for(int j = 1; j < N + 1; j++) {
			if(j == lost_city) {
				continue;
			}
			if(!inq[j]) {
				bfs(j);
				count++;
			}
		}
		printf("%d\n", count - 1);
	}
	return 0;
}

void bfs(int nowVisit) {
	queue<int> q;
	q.push(nowVisit);
	inq[nowVisit] = true;
	while(!q.empty()) {
		int now = q.front();
		q.pop();
		for(int i = 0; i < graph[now].size(); i++) {
			if(graph[now][i] != lost_city && !inq[graph[now][i]]) {
				q.push(graph[now][i]);
				inq[graph[now][i]] = true;
			}
		}
	}
}
