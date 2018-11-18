#include<iostream>
#include<vector>
#include<set>

using namespace std;

struct node {
	int v;	//端点编号
	int length;	//道路长度
	int time;	//道路时间
	node(int _v, int _length, int _time) : v(_v), length(_length), time(_time) {};	//构造函数
};

int N, M, source, destination, INF = 1000000000;	//十字路口数量，道路数量，起点，终点，无穷大数
vector<node> graph[501];	//用邻接表形式存储有向图
int d1[501], d2[501];	//d1[]和d2[]分别记录从起点到其余点的最短长度和最短时间
set<int> pre1[501], pre2[501];	//pre1[]和pre2[]分别是以长度为边权做bellmanFord和以时间为边权做bellmanFord时的记录前一个节点的数组
vector<int> tempPath1, tempPath2;	//tempPath1和tempPath2分别是对最短长度和最短时间的路径做深度优先遍历时的当前路径
vector<int> path1, path2;	//path1和path2分别是最短长度中最短时间的路径和最短时间中路过十字路口数量最少的路径
int optValue1 = INF, optValue2 = INF;	//optValue1和optValue2分别是最短长度中的最短时间和最短时间中的最少十字路口数量

bool bellmanFord1(int s);	//以长度为边权做bellmanFord
void dfs1(int nowVisit);	//对最短长度的路径做深度优先遍历求得其中最短时间的路径
bool bellmanFord2(int s);	//以时间为边权做bellmanFord
void dfs2(int nowVisit);	//对最短时间的路径做深度优先遍历求得其中最少十字路口数量的路径 

int main() {
	scanf("%d %d", &N, &M);	//读取十字路口数量和路径数量
	int V1, V2, one_way, length, time;
	for(int i = 0; i < M; i++) {
		scanf("%d %d %d %d %d", &V1, &V2, &one_way, &length, &time);	//读取每条道路的信息
		graph[V1].push_back(node(V2, length, time));
		if(one_way == 0) {	//如果one_way是0，说明这条道路是双向通行的
			graph[V2].push_back(node(V1, length, time));
		}
	}
	scanf("%d %d", &source, &destination);
	bellmanFord1(source);	//以长度为边权做bellmanFord
	dfs1(destination);	//对最短长度的路径做深度优先遍历求得其中最短时间的路径
	bellmanFord2(source);	//以时间为边权做bellmanFord
	dfs2(destination);	//对最短时间的路径做深度优先遍历求得其中最少十字路口数量的路径
	if(path1 == path2) {	//如果以长度为边权求得的最优路径与以时间为边权求得的最优路径相同
		printf("Distance = %d; Time = %d: ", d1[destination], d2[destination]);
		for(int i = path1.size() - 1; i >= 0; i--) {
			printf("%d", path1[i]);
			if(i != 0) {
				printf(" -> ");
			} else {
				printf("\n");
			}
		}
	} else {	//如果以长度为边权求得的最优路径与以时间为边权求得的最优路径不同
		printf("Distance = %d: ", d1[destination]);
		for(int i = path1.size() - 1; i >= 0; i--) {
			printf("%d", path1[i]);
			if(i != 0) {
				printf(" -> ");
			} else {
				printf("\n");
			}
		}
		printf("Time = %d: ", d2[destination]);
		for(int i = path2.size() - 1; i >= 0; i--) {
			printf("%d", path2[i]);
			if(i != 0) {
				printf(" -> ");
			} else {
				printf("\n");
			}
		}
	}
	return 0;
}

bool bellmanFord1(int s) {
	for(int i = 0; i < N; i++) {	//初始化起始点到其余点的距离均为无穷大
		d1[i] = INF;
	}
	d1[s] = 0;	//起始点到起始点的距离是0
	for(int i = 0; i < N - 1; i++) {	//执行N - 1轮松弛操作 
		for(int u = 0; u < N; u++) {
			for(int j = 0; j < graph[u].size(); j++) {
				int v = graph[u][j].v;
				int length = graph[u][j].length;
				if(d1[u] + length < d1[v]) {	//如果通过u到达v的距离更短 
					d1[v] = d1[u] + length;	//更新到达v的距离
					pre1[v].clear();	//清空v的前一个节点
					pre1[v].insert(u);	//将u插入v的前一个节点列表中
				} else if(d1[u] + length == d1[v]) {	//如果通过u到达v的距离和原来到达v的距离一样
					pre1[v].insert(u);	//将u插入v的前一个节点列表中
				}
			}
		}
	}
	for(int u = 0; u < N; u++) {	 
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;
			int length = graph[u][j].length;
			if(d1[u] + length < d1[v]) {	//如果经过N - 1轮松弛操作还能继续进行松弛操作，说明存在负权环，返回false 
				return false;
			}
		}
	}
	return true;	//不存在负权环，返回true 
}

void dfs1(int nowVisit) {
	tempPath1.push_back(nowVisit);	//当前节点加入当前路径 
	if(nowVisit == source) {	//如果当前节点是起始点
		int value1 = 0;
		for(int i = tempPath1.size() - 1; i > 0; i--) {	//计算当前路径的时间
			//对于邻接表求边权，需要遍历该点连接的所有点才能寻找到所要求的那条边的边权
			for(int j = 0; j < graph[tempPath1[i]].size(); j++) {
				if(graph[tempPath1[i]][j].v == tempPath1[i - 1]) {
					value1 += graph[tempPath1[i]][j].time;
					break;
				}
			}
		}
		if(value1 < optValue1) {	//如果当前路径的时间小于最小时间 
			optValue1 = value1;	//更新最小时间的值 
			path1 = tempPath1;	//选取当前路径为最短路径中的最优路径 
		}
		tempPath1.pop_back();	//变量的手动回溯 
		return;
	}
	for(set<int>::iterator it = pre1[nowVisit].begin(); it != pre1[nowVisit].end(); it++) {	//对当前节点的所有前一个节点做深度优先遍历 
		dfs1(*it);
	}
	tempPath1.pop_back();	//变量的手动回溯 
}

bool bellmanFord2(int s) {
	for(int i = 0; i < N; i++) {	//初始化起始点到其余点的时间均为无穷大
		d2[i] = INF;
	}
	d2[s] = 0;	//起始点到起始点的时间是0
	for(int i = 0; i < N - 1; i++) {	//执行N - 1轮松弛操作
		for(int u = 0; u < N; u++) {
			for(int j = 0; j < graph[u].size(); j++) {
				int v = graph[u][j].v;
				int time = graph[u][j].time;
				if(d2[u] + time < d2[v]) {	//如果通过u到达v的时间更短
					d2[v] = d2[u] + time;	//更新到达v的时间 
					pre2[v].clear();	//清空v的前一个节点
					pre2[v].insert(u);	//将u插入v的前一个节点列表中
				} else if(d2[u] + time == d2[v]) {	//如果通过u到达v的时间和原来到达v的时间一样
					pre2[v].insert(u);	//将u插入v的前一个节点列表中
				}
			}
		}
	}
	for(int u = 0; u < N; u++) {
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;
			int time = graph[u][j].time;
			if(d2[u] + time < d2[v]) {	//如果经过N - 1轮松弛操作还能继续进行松弛操作，说明存在负权环，返回false
				return false;
			}
		}
	}
	return true;	//不存在负权环，返回true 
}

void dfs2(int nowVisit) {
	tempPath2.push_back(nowVisit);	//当前节点加入当前路径
	if(nowVisit == source) {	//如果当前节点是起始点
		int value2 = tempPath2.size();
		if(value2 < optValue2) {	//如果当前路径通过的十字路口数量小于最少的十字路口数量
			optValue2 = value2;	//更新最少的十字路口数量 
			path2 = tempPath2;	//选取当前路径为最短时间路径中的最优路径 
		}
		tempPath2.pop_back();	//变量的手动回溯
		return;
	}
	for(set<int>::iterator it = pre2[nowVisit].begin(); it != pre2[nowVisit].end(); it++) {	//对当前节点的所有前一个节点做深度优先遍历
		dfs2(*it);
	}
	tempPath2.pop_back();	//变量的手动回溯
}
