#include<iostream>
#include<vector>

using namespace std;

int n, m, c1, c2, INF = 1000000000;	//城市数量，道路数量，起点，终点，无穷大数
int graph[501][501];	//无向图
int teams[501];	//每个城市的急救队数量
int d[501];	//d[i]表示从起点c1到达城市i的最短路径长度
vector<int> pre[501];	//存储前一节点列表
bool visited[501];	//dijkstra算法的标记数组，用以标记该位置是否已被访问
vector<int> path;	//存储能搜集到最多急救队数量的最短路径
vector<int> tempPath; //存储深度优先遍历过程中的当前路径
int optValue = 0;	//能搜集到的最多急救队数量，初始化为0
int count = 0;	//最短路径条数，初始化为0

void dijkstra(int s);
void dfs(int nowVisit);

int main() {
	scanf("%d %d %d %d", &n, &m, &c1, &c2);	//读取城市数量，道路数量，起点，终点
	fill(visited, visited + 501, false);	//初始化该标记数组全部为false，所有节点均未被访问
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			graph[i][j] = INF;	//初始化图，任意两点的距离都为无穷大，即图中不存在任何路径
		}
	}
	for(int i = 0; i < n; i++) {
		scanf("%d", &teams[i]); //读取每个城市急救队数量
	}
	int city1, city2, len;
	for(int i = 0; i < m; i++) {
		scanf("%d %d %d", &city1, &city2, &len);
		graph[city1][city2] = graph[city2][city1] = len;	//读取城市间的路径信息
	}
	dijkstra(c1);	////以c1为起点利用dijkstra算法求到其余点的最短距离
	dfs(c2);	//从终点开始根据记录的前一节点列表pre寻找出能搜集到的最多急救队数量以及最短路径条数
	printf("%d %d\n", count, optValue);	//输出结果
	return 0;
}

void dijkstra(int s) {
	fill(d, d + 501, INF);	//初始化源点s到其余点的最短距离均为无穷大
	d[s] = 0;	//起点s到达自身的距离为0
	for(int i = 0; i < n; i++) {
		int u = -1, min = INF;
		for(int j = 0; j < n; j++) {	//寻找未访问的顶点中d[]最小的
			if(!visited[j] && d[j] < min) {
				min = d[j];
				u = j;
			}
		}
		if(u == -1) {	//找不到小于INF的d[u]，说明剩下的顶点和起点不连通
			return;
		}
		visited[u] = true;	////将该最小的d[u]的u点标记为已被访问过
		for(int v = 0; v < n; v++) {
			if(!visited[v] && graph[u][v] != INF) {
				if(graph[u][v] + d[u] < d[v]) {	//如果通过u点到达v比直接到达v要更小
					d[v] = graph[u][v] + d[u];	//优化d[v]
					pre[v].clear();	//清空之前存储的v的前一个节点
					pre[v].push_back(u);	//将u当成v的前一个节点存储进pre[v]中
				} else if(graph[u][v] + d[u] == d[v]) {	//如果通过u点到达v与直接到达v点的路径相等
					pre[v].push_back(u);	//将u加入pre[v]中
				}
			}
		}
	}
}

void dfs(int nowVisit) {
	tempPath.push_back(nowVisit);	//将当前节点加入当前路径中 
	if(nowVisit == c1) {	//如果当前节点就是起点c1，这是递归的终止条件 
		count++;	//最短路径条数加1 
		int value = 0;	//计算当前路径所能搜集到的急救队数量 
		for(int i = tempPath.size() - 1; i >= 0; i--) {
			value += teams[tempPath[i]];
		}
		if(value > optValue) {	//如果当前路径所能搜集到的急救队数量大于最大数量optValue 
			optValue = value;	//更新最大急救队数量的值 
			path = tempPath;	//将当前路径作为能搜集到最大急救队数量的路径保存下来 
		}
		tempPath.pop_back();	//弹出当前节点，变量的手动回溯过程 
		return;
	}
	for(int i = 0; i < pre[nowVisit].size(); i++) {
		dfs(pre[nowVisit][i]);	//深度优先遍历当前节点的所有前一个节点 
	}
	tempPath.pop_back();	//弹出当前节点，变量的手动回溯过程 
}
