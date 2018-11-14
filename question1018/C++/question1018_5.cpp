#include<iostream>
#include<vector>
#include<set>

using namespace std;

int Cmax;	//站点最大容量
int N;	//站点总数
int Sp;	//目的地
int M;	//道路数量
int INF = 1000000000;
int C[510];	//记录每站点当期自行车数量
int graph[510][510];	//无向图
int d[510];
vector<int> tempPath;
vector<int> path;
int optValue1 = INF;
int optValue2 = INF;
set<int> pre[510];

bool bellmanFord(int s);
void dfs(int nowVisit);

int main() {
	cin >> Cmax >> N >> Sp >> M;
	for(int i = 1; i <= N; i++) {
		cin >> C[i];
	}
	int Si, Sj, Tij;
	for(int i = 0; i <= N; i++) {
		for(int j = 0; j <= N; j++) {
			graph[i][j] = INF;
		}
	}
	for(int i = 0; i < M; i++) {
		cin >> Si >> Sj >> Tij;
		graph[Si][Sj] = Tij;
		graph[Sj][Si] = Tij;
	}
	bellmanFord(0);
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

bool bellmanFord(int s) {
	for(int i = 0; i <= N; i++) {
		d[i] = INF;
	}
	d[s] = 0;
	for(int i = 0; i < N; i++) {
		for(int u = 0; u <= N; u++) {
			for(int v = 0; v <= N; v++) {
				if(graph[u][v] != INF) {
					if(d[u] + graph[u][v] < d[v]) {
						d[v] = d[u] + graph[u][v];
						pre[v].clear();
						pre[v].insert(u);
					} else if(d[u] + graph[u][v] == d[v]) {
						pre[v].insert(u);
					}
				}
			}
		}
	}
	for(int u = 0; u <= N; u++) {
		for(int v = 0; v <= N; v++) {
			if(graph[u][v] != INF) {
				if(d[u] + graph[u][v] < d[v]) {
					return false;
				}
			}
		}
	}
	return true;
}

void dfs(int nowVisit) {
	tempPath.push_back(nowVisit);
	if(nowVisit == 0) {
		int provide = 0, recycle = 0;
		for(int i = tempPath.size() - 2; i >= 0; i--) {	//0位置的点是PBMC，不需要计算
			int diff = C[tempPath[i]] - Cmax / 2;	//这里的点索引不是i，而是tempPath[i]
			if(diff >= 0) {
				recycle += diff;
			} else {
				if(recycle >= -diff) {
					recycle += diff;
				} else {
					provide += -diff - recycle;
					recycle = 0;
				}
			}
		}
		if(provide < optValue1) {
			path = tempPath;
			optValue1 = provide;
			optValue2 = recycle;
		} else if(provide == optValue1 && recycle < optValue2) {
			path = tempPath;
			optValue2 = recycle;
		}
		tempPath.pop_back();
		return;
	}
	set<int>::iterator it;
	for(it = pre[nowVisit].begin(); it != pre[nowVisit].end(); it++){
		dfs(*it);
	}
	tempPath.pop_back();
}
