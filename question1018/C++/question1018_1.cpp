#include<iostream>
#include<vector>

using namespace std;

struct node {
	int v;	//节点编号
	int time;	//边权
	node(int _v, int _time) : v(_v), time(_time) {};	//构造函数
};

int Cmax;	//每个站点的最大容量
int N;	//站点数量
int Sp;	//目的地
int M;	//道路数量
int INF = 1000000000;	//定义无穷大数
int C[502] = {0};	//存放每个站点当前自行车数量
vector<node> graph[502];	//无向图
bool visited[502] = {false};	//标记数组
int d[502];	//记录最短路径长度
vector<int> pre[502];	//记录前一个节点
vector<int> tempPath;
vector<int> path;
int optValue1 = INF;	//记录需要提供的公共自行车数量，最小为最优
int optValue2 = INF;	//记录需要回收的公共自行车数量，最小为最优 

void dijkstra(int s);
void dfs(int nowVisit);

int main() {
	cin >> Cmax >> N >> Sp >> M;
	int Ci;
	for(int i = 1; i <= N; i++) {
		cin >> Ci;
		C[i] = Ci;
	}
	int Si, Sj, Tij;
	for(int i = 0; i < M; i++) {
		cin >> Si >> Sj >> Tij;
		graph[Si].push_back(node(Sj, Tij));
		graph[Sj].push_back(node(Si, Tij));
	}
	dijkstra(0);	//PBMC所在的位置0节点就是起点 
	dfs(Sp);
	cout << optValue1 << " ";
	for(int i = path.size() - 1; i >= 0; i--) {
		cout << path[i];
		if(i != 0) {
			cout << "->";
		}
	}
	cout << " " << optValue2 << endl;
	return 0;
}

void dijkstra(int s) {
	for(int i = 0; i <= N; i++) {
		d[i] = INF;
	}
	d[s] = 0;
	for(int i = 0; i <= N; i++) {
		int u = -1, min = INF;
		for(int j = 0; j <= N; j++) {
			if(!visited[j] && d[j] < min) {	//j需要是未标记的元素 
				min = d[j];
				u = j;
			}
		}
		if(u == -1) {
			return;
		}
		visited[u] = true;
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;
			int time = graph[u][j].time;
			if(!visited[v]) {
				if(time + d[u] < d[v]) {
					d[v] = time + d[u];
					pre[v].clear();
					pre[v].push_back(u);
				} else if(time + d[u] == d[v]) {
					pre[v].push_back(u);
				}
			}
		}
	}
}

void dfs(int nowVisit) {
	if(nowVisit == 0) {
		tempPath.push_back(nowVisit);
		int provide = 0, recycle = 0;	//provide需要提供的公共自行车数量，recycle需要回收的公共自行车数量 
		for(int i = tempPath.size() - 2; i >= 0; i--){
			if(C[tempPath[i]] - Cmax / 2 >= 0){
				recycle += C[tempPath[i]] - Cmax / 2;
			}else{
				if(recycle >= Cmax / 2 - C[tempPath[i]]){
					recycle -= Cmax / 2 - C[tempPath[i]];
				}else{
					provide += Cmax / 2 - C[tempPath[i]] - recycle;
					recycle = 0;
				}
			} 
		} 
		if(provide < optValue1){
			optValue1 = provide;
			optValue2 = recycle;	//此处也要更新optValue2的值 
			path = tempPath;
		}else if(provide == optValue1 && recycle < optValue2){
			optValue2 = recycle;
			path = tempPath;
		}
		tempPath.pop_back();
		return; 	//这里是递归终止条件，直接返回 
	}
	tempPath.push_back(nowVisit);
	for(int i = 0; i < pre[nowVisit].size(); i++) {
		dfs(pre[nowVisit][i]);
	}
	tempPath.pop_back();
}
