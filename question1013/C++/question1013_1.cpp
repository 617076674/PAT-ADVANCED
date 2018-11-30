#include<iostream>
#include<vector>

using namespace std;

int N, M, K;
vector<int> graph[1001];
int lost_city, count;
bool visited[1001];

void dfs(int nowVisit);

int main(){
	scanf("%d %d %d", &N, &M, &K);
	int city1, city2;
	for(int i = 0; i < M; i++){
		scanf("%d %d", &city1, &city2);
		graph[city1].push_back(city2);
		graph[city2].push_back(city1);
	}
	for(int i = 0; i < K; i++){
		fill(visited + 1, visited + N + 1, false);
		count = 0;
		scanf("%d", &lost_city);
		for(int j = 1; j <= N; j++){
			if(j == lost_city){
				continue;
			}
			if(!visited[j]){
				dfs(j);
				count++;
			}
		}
		printf("%d\n", count - 1);
	}
	return 0;
} 

void dfs(int nowVisit){
	visited[nowVisit] = true;
	for(int i = 0; i < graph[nowVisit].size(); i++){
		int v = graph[nowVisit][i];
		if(!visited[v] && v != lost_city){
			dfs(v);
		}
	}
}
