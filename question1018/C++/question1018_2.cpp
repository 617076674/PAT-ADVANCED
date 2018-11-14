#include<iostream>
#include<vector>
#include<set>

using namespace std;

struct node {
	int v;	//节点编号
	int time;	//边权值
	node(int _v, int _time) : v(_v), time(_time) {};	//构造函数
};

int Cmax;	//每站最大容量
int N;	//总站数
int Sp;	//目的地
int M;	//道路总数
int INF = 1000000000;	//无穷大数
int C[502];	//每站现有公共自行车数量
vector<node> graph[502];	//无向图
int d[502];	//存储最短路径长度
set<int> pre[502]; 	//记录前一节点
vector<int> path;
vector<int> tempPath;
int optValue1 = INF;
int optValue2 = INF;

bool bellmanFord(int s);
void dfs(int nowVisit);

int main() {
	cin >> Cmax >> N >> Sp >> M;
	for(int i = 1; i <= N; i++) {
		cin >> C[i];
	}
	int Si, Sj, Tij;
	for(int i = 0; i < M; i++) {
		cin >> Si >> Sj >> Tij;
		graph[Si].push_back(node(Sj, Tij));
		graph[Sj].push_back(node(Si, Tij));
	}
	bellmanFord(0);
	dfs(Sp);
	cout << optValue1 << " ";
	for(int i = path.size() - 1; i >= 0; i--){
		cout << path[i];
		if(i != 0){
			cout << "->";
		}
	}
	cout << " " << optValue2 << endl;
	return 0;
}

bool bellmanFord(int s) {
	for(int i = 0; i <= N; i++) {
		d[i] = INF;
	}
	d[s] = 0;
	for(int i = 0; i < N; i++) {
		for(int u = 0; u <= N; u++) {
			for(int k = 0; k < graph[u].size(); k++) {
				int v = graph[u][k].v;
				int time = graph[u][k].time;
				if(d[u] + time < d[v]) {
					d[v] = d[u] + time;
					pre[v].clear();
					pre[v].insert(u);
				} else if(d[u] + time == d[v]) {
					pre[v].insert(u);
				}
			}
		}
	}
	for(int u = 0; u <= N; u++) {
		for(int k = 0; k < graph[u].size(); k++) {
			int v = graph[u][k].v;
			int time = graph[u][k].time;
			if(d[u] + time < d[v]) {
				return false;
			} 
		}
	}
	return true;
}

void dfs(int nowVisit){
	if(nowVisit == 0){
		tempPath.push_back(nowVisit);
		int provide = 0, recycle = 0;
		for(int i = tempPath.size() - 2; i >= 0; i--){
			if(C[tempPath[i]] - Cmax / 2 >= 0){
				recycle += C[tempPath[i]] - Cmax / 2;
			}else{
				if(recycle >= -C[tempPath[i]] + Cmax / 2){
					recycle -= -C[tempPath[i]] + Cmax / 2;
				}else{
					provide += -C[tempPath[i]] + Cmax / 2 - recycle;
					recycle = 0;
				}
			}
		}
		if(provide < optValue1){
			optValue1 = provide;
			optValue2 = recycle;
			path = tempPath;
		}else if(provide = optValue1 && recycle < optValue2){
			optValue2 = recycle;
			path = tempPath;
		}
		tempPath.pop_back();
		return;
	}
	tempPath.push_back(nowVisit);
	set<int>::iterator it;
	for(it = pre[nowVisit].begin(); it != pre[nowVisit].end(); it++){
		dfs(*it);
	}
	tempPath.pop_back();
}
