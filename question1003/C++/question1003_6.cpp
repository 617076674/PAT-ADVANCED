#include<iostream>
#include<set>
#include<vector>
#include<queue>

using namespace std;

struct node {
	int v;	//邻接边的目标顶点
	int dis;	//邻接边的边权
	node(int _v, int _dis) : v(_v), dis(_dis) {} //构造函数
};

int n;	//城市数量
int m;	//路径数量
int c1;	//你所在的城市
int c2;	//需要去急救的城市
int INF = 1000000000;	//无穷大数
vector<node> graph[501];	//无向图
int teams[501] = {0};	//每个城市的急救队数量
int d[501];	//d[i]表示从起点c1到达城市i的最短路径长度
int num[501];	//num[i]表示从起点c1到达点i的最短路径条数
int weight[501];	//weight[i]表示从起点c1到达点i所能搜集到的最大急救队数量
set<int> pre[501];	//存储前一节点列表
bool inQueue[501] = {false};	//inQueue[i]用以判断节点i是否在队列中 
int countInQueue[501] = {0};	//countInQueue[i]表示节点i的入队次数 

bool spfa(int s);

int main() {
	cin >> n >> m >> c1 >> c2;
	for(int i = 0; i < n; i++) {
		cin >> teams[i];
	}
	int city1, city2, len;
	for(int i = 0; i < m; i++) {
		cin >> city1 >> city2 >> len;
		graph[city1].push_back(node(city2, len));
		graph[city2].push_back(node(city1, len));
	}
	spfa(c1);
	cout << num[c2] << " " << weight[c2] << endl;
	return 0;
}

bool spfa(int s) {
	for(int i = 0; i < n; i++) {
		d[i] = INF;
		num[i] = 0;
		weight[i] = 0;
	}
	d[s] = 0;
	num[s] = 1;
	weight[s] = teams[s];
	queue<int> q;
	q.push(s);	//源点入队
	inQueue[s] = true;
	countInQueue[s]++;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inQueue[u] = false;	//设置u为不在队列中 
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;	//邻接边的顶点
			int dis = graph[u][j].dis;	//邻接边的边权
			if(dis + d[u] < d[v]) {
				d[v] = dis + d[u];
				if(!inQueue[v]){	//如果v不在队列中 
					q.push(v);	//v入队 
					inQueue[v] = true;	//设置v为在队列中
					countInQueue[v]++;
					if(countInQueue[v] >= n){
						return false;	//当某个顶点的入队次数超过n - 1次时，说明图中存在从源点可达的负环 
					} 
				}
				num[v] = num[u];
				weight[v] = weight[u] + teams[v];
				pre[v].clear();
				pre[v].insert(u);
			} else if(dis + d[u] == d[v]) {
				if(weight[u] + teams[v] > weight[v]) {
					weight[v] = weight[u] + teams[v];
				}
				pre[v].insert(u);
				num[v] = 0;	//重新统计num[v]
				set<int>::iterator it;
				for(it = pre[v].begin(); it != pre[v].end(); it++) {
					num[v] += num[*it];
				}
				if(!inQueue[v]){	//如果v不在队列中 
					q.push(v);	//v入队 
					inQueue[v] = true;	//设置v为在队列中
					countInQueue[v]++;
					if(countInQueue[v] >= n){
						return false;	//当某个顶点的入队次数超过n - 1次时，说明图中存在从源点可达的负环 
					} 
				}
			}
		}
	}
	return true;
}
