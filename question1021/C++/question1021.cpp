#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int n;	//节点个数
vector<int> graph[10000];	//无向图
bool visited[10000];	//标记数组
int level[10000];	//记录广度优先遍历的层数
int index;

void dfs(int nowVisit);
void bfs(int nowVisit);

int main() {
	scanf("%d", &n);
	fill(level, level + n, 0);
	fill(visited, visited + n, false);
	int v1, v2;
	for(int i = 0; i < n - 1; i++) {
		scanf("%d %d", &v1, &v2);
		graph[v1 - 1].push_back(v2 - 1);
		graph[v2 - 1].push_back(v1 - 1);
	}
	int count = 0;
	for(int i = 0; i < n; i++) {
		if(!visited[i]) {
			dfs(i);
			count++;
		}
	}
	if(count > 1) {
		printf("Error: %d components\n", count);
		return 0;
	}
	for(int i = 0; i < n; i++) {
		fill(visited, visited + n, false);
		if(!visited[i]) {
			index = i;
			bfs(i);
		}
	}
	int max = level[0];
	for(int i = 1; i < n; i++) {
		if(level[i] > max) {
			max = level[i];
		}
	}
	for(int i = 0; i < n; i++) {
		if(level[i] == max) {
			printf("%d\n", i + 1);
		}
	}
	return 0;
}

void dfs(int nowVisit) {
	visited[nowVisit] = true;
	for(int i = 0; i < graph[nowVisit].size(); i++) {
		if(!visited[graph[nowVisit][i]]) {
			dfs(graph[nowVisit][i]);
		}
	}
}

void bfs(int nowVisit) {
	queue<int> q;
	q.push(nowVisit);
	visited[nowVisit] = true;
	while(!q.empty()) {
		int qSize = q.size();
		for(int i = 0; i < qSize; i++) {
			int u = q.front();
			q.pop();
			for(int j = 0; j < graph[u].size(); j++){
				int v = graph[u][j];
				if(!visited[v]){
					q.push(v);
					visited[v] = true;
				}
			}
		}
		level[index]++;
	}
}
