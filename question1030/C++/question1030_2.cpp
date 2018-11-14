#include<iostream>
#include<vector>

using namespace std;

int n;	//城市数量
int m;	//高速公路数量
int s;	//起始城市
int d;	//目的地城市
int INF = 1000000000;	//无穷大数
int graph[501][501];	//无向图
int price[501][501] = {0};	//存储高速公路价格信息
int visited[501] = {false};	//标记数组
vector<int> pre[501];	//前一节点列表
int distances[501];	//distances[i]代表从起点s到达点i的最短路径长度
vector<int> path;	//最优路径
vector<int> tempPath;	//临时路径
int optValue = INF; //一开始将最优费用设为无穷大 

void dijkstra(int s);
void dfs(int nowVisit);

int main() {
	cin >> n >> m >> s >> d;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			graph[i][j] = INF;
		}
	}
	int city1, city2, distance, cost;
	for(int i = 0; i < m; i++) {
		cin >> city1 >> city2 >> distance >> cost;
		graph[city1][city2] = distance;
		graph[city2][city1] = distance;
		price[city1][city2] = cost;
		price[city2][city1] = cost;
	}
	dijkstra(s);
	dfs(d);
	for(int i = path.size() - 1; i >= 0; i--){
		cout << path[i] << " ";
	}
	cout << distances[d] << " " << optValue << endl;
	return 0;
}

void dijkstra(int s) {
	for(int i = 0; i < n; i++){
		distances[i] = INF;
	}
	distances[s] = 0;
	for(int i = 0; i < n; i++){
		int u = -1, min = INF;
		for(int j = 0; j < n; j++){
			if(!visited[j] && distances[j] < min){
				min = distances[j];
				u = j;
			}
		}
		if(u == -1){
			return;
		}
		visited[u] = true;
		for(int v = 0; v < n; v++){
			if(!visited[v] && graph[u][v] != INF){
				if(distances[u] + graph[u][v] < distances[v]){
					distances[v] = distances[u] + graph[u][v];
					pre[v].clear();
					pre[v].push_back(u);
				}else if(distances[u] + graph[u][v] == distances[v]){
					pre[v].push_back(u);
				}
			}
		}
	}
}

void dfs(int nowVisit){
	if(nowVisit == s){
		tempPath.push_back(nowVisit);
		int value = 0;
		for(int i = tempPath.size() - 1; i > 0; i--){
			value += price[tempPath[i]][tempPath[i - 1]];
		}
		if(value < optValue){
			optValue = value;
			path = tempPath;
		}
		tempPath.pop_back();	//将刚加入的节点删除
		return; 
	}
	tempPath.push_back(nowVisit);
	for(int i = 0; i < pre[nowVisit].size(); i++){
		dfs(pre[nowVisit][i]);
	}
	tempPath.pop_back();
}
