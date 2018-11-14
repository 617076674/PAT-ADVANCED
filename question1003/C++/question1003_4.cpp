#include<iostream>
#include<set>
#include<vector>

using namespace std;

int n;	//城市数量
int m;	//路径数量
int c1;	//你所在的城市
int c2;	//需要去急救的城市
int INF = 1000000000;	//无穷大数
int graph[501][501];	//无向图
int teams[501] = {0};	//每个城市的急救队数量
int d[501];	//d[i]表示从起点c1到达城市i的最短路径长度
set<int> pre[501];	//存储前一节点列表
vector<int> path;
vector<int> tempPath; 
int optValue = 0;
int count = 0;

bool bellmanFord(int s);
void dfs(int nowVisit);

int main() {
	cin >> n >> m >> c1 >> c2;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			graph[i][j] = INF;
		}
	}
	for(int i = 0; i < n; i++) {
		cin >> teams[i];
	}
	int city1, city2, len;
	for(int i = 0; i < m; i++) {
		cin >> city1 >> city2 >> len;
		graph[city1][city2] = len;
		graph[city2][city1] = len;
	}
	bellmanFord(c1);
	dfs(c2);
	cout << count << " " << optValue << endl;
	return 0;
}

bool bellmanFord(int s) {
	for(int i = 0; i < n; i++) {
		d[i] = INF;
	}
	d[s] = 0;
	for(int i = 0; i < n - 1; i++) {
		for(int u = 0; u < n; u++) {
			for(int v = 0; v < n; v++) {
				if(graph[u][v] != INF) {
					if(graph[u][v] + d[u] < d[v]) {
						d[v] = graph[u][v] + d[u];
						pre[v].clear();
						pre[v].insert(u);
					}else if(graph[u][v] + d[u] == d[v]){
						pre[v].insert(u);
					}
				}
			}
		}
	}
	for(int u = 0; u < n; u++) {
		for(int v = 0; v < n; v++) {
			if(graph[u][v] != INF) {
				if(graph[u][v] + d[u] < d[v]) {
					return false;
				}
			}
		}
	}
	return true;
}

void dfs(int nowVisit){
	if(nowVisit == c1){
		count++;
		tempPath.push_back(nowVisit);
		int value = 0;
		for(int i = tempPath.size() - 1; i >= 0; i--){
			value += teams[tempPath[i]];
		}
		if(value > optValue){
			optValue = value;
			path = tempPath;
		}
		tempPath.pop_back();
	}
	tempPath.push_back(nowVisit);
	set<int>::iterator it;
	for(it = pre[nowVisit].begin(); it != pre[nowVisit].end(); it++){
		dfs(*it);
	}
	tempPath.pop_back();
}
