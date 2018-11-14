#include<iostream>
#include<vector>
#include<set>

using namespace std;

struct node {
	int v;	//邻接边的目标顶点
	int dis;	//邻接边的边权
	node(int _v, int _dis) : v(_v), dis(_dis) {};	//构造函数
};

int n;	//城市数量
int m;	//高速公路数量
int	s;	//起始城市
int d;	//目的地城市
int INF = 1000000000;	//定义无穷大数
vector<node> graph[501];	//无向图
int price[501][501];	//记录两城市间的价格
set<int> pre[501];
vector<int> path;
vector<int> tempPath;
int optValue = INF;
int distances[501];

bool bellmanFord(int s);
void dfs(int nowVisit);

int main() {
	cin >> n >> m >> s >> d;
	int city1, city2, distance, cost;
	for(int i = 0; i < m; i++) {
		cin >> city1 >> city2 >> distance >> cost;
		graph[city1].push_back(node(city2, distance));
		graph[city2].push_back(node(city1, distance));
		price[city1][city2] = cost;
		price[city2][city1] = cost;
	}
	bellmanFord(s);
	dfs(d);
	for(int i = path.size() - 1; i >= 0; i--) {
		cout << path[i] << " ";
	}
	cout << distances[d] << " " << optValue << endl;
	return 0;
}

bool bellmanFord(int s) {
	for(int i = 0; i < n; i++) {
		distances[i] = INF;
	}
	distances[s] = 0;
	for(int i = 0; i < n - 1; i++) {	//执行n - 1轮操作，n为定点数
		for(int u = 0; u < n; u++) {	//每轮操作都遍历所有顶点
			for(int j = 0; j < graph[u].size(); j++) {
				int v = graph[u][j].v;
				int dis = graph[u][j].dis;
				if(distances[u] + dis < distances[v]) {
					distances[v] = distances[u] + dis;	//松弛操作
					pre[v].clear();
					pre[v].insert(u);
				} else if(distances[u] + dis == distances[v]) {
					pre[v].insert(u);
				}
			}
		}
	}
	for(int u = 0; u < n; u++) {	//每轮操作都遍历所有顶点
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;
			int dis = graph[u][j].dis;
			if(distances[u] + dis < distances[v]) {
				return false;
			}
		}
	}
	return true;
}

void dfs(int nowVisit) {
	if(nowVisit == s) {
		tempPath.push_back(nowVisit);
		int value = 0;
		for(int i = tempPath.size() - 1; i > 0; i--) {
			value += price[tempPath[i]][tempPath[i - 1]];
		}
		if(value < optValue) {
			path = tempPath;
			optValue = value;
		}
		tempPath.pop_back();
		return;
	}
	tempPath.push_back(nowVisit);
	set<int>::iterator it;
	for(it = pre[nowVisit].begin(); it != pre[nowVisit].end(); it++) {
		dfs(*it);
	}
	tempPath.pop_back();
}
