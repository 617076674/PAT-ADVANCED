#include<iostream>
#include<set>

using namespace std;

int n;	//城市数量
int m;	//路径数量
int c1;	//你所在的城市
int c2;	//需要去急救的城市
int INF = 1000000000;	//无穷大数
int graph[501][501];	//无向图
int teams[501] = {0};	//每个城市的急救队数量
int d[501];	//d[i]表示从起点c1到达城市i的最短路径长度
int num[501];	//num[i]表示从起点c1到达点i的最短路径条数
int weight[501];	//weight[i]表示从起点c1到达点i所能搜集到的最大急救队数量 
set<int> pre[501];	//存储前一节点列表

bool bellmanFord(int s);

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
	cout << num[c2] << " " << weight[c2] << endl;
	return 0;
}

bool bellmanFord(int s) {
	for(int i = 0; i < n; i++) {
		d[i] = INF;
		num[i] = 0;
		weight[i] = 0;
	}
	d[s] = 0;
	num[s] = 1;
	weight[s] = teams[s];
	for(int i = 0; i < n - 1; i++) {
		for(int u = 0; u < n; u++) {
			for(int v = 0; v < n; v++) {
				if(graph[u][v] != INF) {
					if(graph[u][v] + d[u] < d[v]) {
						d[v] = graph[u][v] + d[u];
						num[v] = num[u];
						weight[v] = weight[u] + teams[v];
						pre[v].clear();
						pre[v].insert(u);
					}else if(graph[u][v] + d[u] == d[v]){
						if(weight[u] + teams[v] > weight[v]){
							weight[v] = weight[u] + teams[v];
						}
						pre[v].insert(u);
						num[v] = 0;	//重新统计num[v] 
						set<int>::iterator it;
						for(it = pre[v].begin(); it != pre[v].end(); it++){
							num[v] += num[*it];
						}
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
