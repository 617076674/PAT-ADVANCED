#include<iostream>

using namespace std;

int N, M;
bool graph[501][501];
int count[501];	//计算每个顶点连接的边数
bool visited[501];

void dfs(int nowVisit);

int main() {
	for(int i = 0; i < 501; i++) {
		for(int j = 0; j < 501; j++) {
			graph[i][j] = false;
		}
	}
	fill(count, count + 501, 0);
	fill(visited, visited + 501, false);
	scanf("%d %d", &N, &M);
	int v1, v2;
	for(int i = 0; i < M; i++) {
		scanf("%d %d", &v1, &v2);
		graph[v1][v2] = graph[v2][v1] = true;
		count[v1]++;
		count[v2]++;
	}
	int countOdd = 0;
	int blocks = 0;	//计算连通分量个数
	for(int i = 1; i <= N; i++) {
		printf("%d", count[i]);
		if(count[i] % 2 == 1) {
			countOdd++;
		}
		if(i != N) {
			printf(" ");
		} else {
			printf("\n");
		}
		if(!visited[i]) {
			dfs(i);
			blocks++;
		}
	}
	if(blocks == 1 && countOdd == 0) {
		printf("Eulerian\n");
	} else if(blocks == 1 && countOdd == 2) {
		printf("Semi-Eulerian\n");
	} else {
		printf("Non-Eulerian\n");
	}
	return 0;
}

void dfs(int nowVisit) {
	visited[nowVisit] = true;	//设置nowVisit已访问 
	for(int i = 1; i <= N; i++) {
		if(graph[nowVisit][i] && !visited[i]) {
			dfs(i);
		}
	}
}
