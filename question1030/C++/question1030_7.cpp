#include<iostream>
#include<vector>
#include<set>
#include<queue>

using namespace std;

int N;
int M;
int S;
int D;
int INF = 1000000000;
int graph[500][500];
int price[500][500];
int d[500];
set<int> pre[500];
vector<int> path;
vector<int> tempPath;
int minCost = INF;
bool inq[500] = {false};
int countInq[500] = {0};

bool spfa(int s);
void dfs(int nowVisit);

int main() {
	cin >> N >> M >> S >> D;
	int city1, city2, distance, cost;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			graph[i][j] = graph[j][i] = INF;
		}
	}
	for(int i = 0; i < M; i++) {
		cin >> city1 >> city2 >> distance >> cost;
		graph[city1][city2] = graph[city2][city1] = distance;
		price[city1][city2] = price[city2][city1] = cost;
	}
	spfa(S);
	dfs(D);
	for(int i = path.size() - 1; i >= 0; i--) {
		cout << path[i] << " ";
	}
	cout << d[D] << " " << minCost << endl;
	return 0;
}

bool spfa(int s) {
	for(int i = 0; i < N; i++) {
		d[i] = INF;
	}
	d[s] = 0;
	queue<int> q;
	q.push(s);
	inq[s] = true;
	countInq[s]++;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(int v = 0; v < N; v++) {
			int distance = graph[u][v];
			if(distance != INF) {
				if(d[u] + distance < d[v]) {
					d[v] = d[u] + distance;
					pre[v].clear();
					pre[v].insert(u);
					if(!inq[v]){
						q.push(v);
						inq[v] = true;
						countInq[v]++;
						if(countInq[v] >= N){
							return false;
						}
					}
				} else if(d[u] + distance == d[v]) {
					pre[v].insert(u);
					if(!inq[v]){
						q.push(v);
						inq[v] = true;
						countInq[v]++;
						if(countInq[v] >= N){
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

void dfs(int nowVisit) {
	tempPath.push_back(nowVisit);
	if(nowVisit == S) {
		int value = 0;
		for(int i = tempPath.size() - 1; i > 0; i--) {
			value += price[tempPath[i]][tempPath[i - 1]];
		}
		if(value < minCost) {
			minCost = value;
			path = tempPath;
		}
		tempPath.pop_back();
		return;
	}
	set<int>::iterator it;
	for(it = pre[nowVisit].begin(); it != pre[nowVisit].end(); it++) {
		dfs(*it);
	}
	tempPath.pop_back();
}
