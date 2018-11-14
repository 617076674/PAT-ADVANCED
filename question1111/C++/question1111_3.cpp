#include<iostream>
#include<vector>
#include<set>
#include<queue>

using namespace std;

struct node {
	int v;	//端点编号
	int length;	//道路长度
	int time;	//道路时间
	node(int _v, int _length, int _time) : v(_v), length(_length), time(_time) {};	//构造函数
};

int N;	//十字路口数量
int M;	//道路数量
int source;
int destination;
int INF = 1000000000;
vector<node> graph[501];	//有向图
int d1[501];
int d2[501];
set<int> pre1[501];
set<int> pre2[501];
vector<int> tempPath1;
vector<int> tempPath2;
vector<int> path1;
vector<int> path2;
int optValue1 = INF;
int optValue2 = INF;
bool inq1[501] = {false};
bool inq2[501] = {false};
int countInq1[501] = {0};
int countInq2[501] = {0};

bool spfa1(int s);
void dfs1(int nowVisit);
bool spfa2(int s);
void dfs2(int nowVisit);

int main() {
	cin >> N >> M;
	int V1, V2, one_way, length, time;
	for(int i = 0; i < M; i++) {
		cin >> V1 >> V2 >> one_way >> length >> time;
		graph[V1].push_back(node(V2, length, time));
		if(one_way == 0) {
			graph[V2].push_back(node(V1, length, time));
		}
	}
	cin >> source >> destination;
	spfa1(source);
	dfs1(destination);
	spfa2(source);
	dfs2(destination);
	bool flag = true;
	if(path1.size() != path2.size()) {
		flag = false;
	} else {
		for(int i = 0; i < path1.size(); i++) {
			if(path1[i] != path2[i]) {
				flag = false;
				break;
			}
		}
	}
	if(flag) {
		cout << "Distance = " << d1[destination] << "; Time = " << d2[destination] << ": ";
		for(int i = path1.size() - 1; i >= 0; i--) {
			cout << path1[i];
			if(i != 0) {
				cout << " -> ";
			}
		}
		cout << endl;
	} else {
		cout <<"Distance = " << d1[destination] << ": ";
		for(int i = path1.size() - 1; i >= 0; i--) {
			cout << path1[i];
			if(i != 0) {
				cout << " -> ";
			}
		}
		cout << endl;
		cout <<"Time = " << d2[destination] << ": ";
		for(int i = path2.size() - 1; i >= 0; i--) {
			cout << path2[i];
			if(i != 0) {
				cout << " -> ";
			}
		}
		cout << endl;
	}
	return 0;
}

bool spfa1(int s) {
	for(int i = 0; i < N; i++) {
		d1[i] = INF;
	}
	d1[s] = 0;
	queue<int> q;
	q.push(s);
	inq1[s] = true;
	countInq1[s]++;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq1[u] = false;
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;
			int length = graph[u][j].length;
			if(d1[u] + length < d1[v]) {
				d1[v] = d1[u] + length;
				pre1[v].clear();
				pre1[v].insert(u);
				if(!inq1[v]) {
					q.push(v);
					inq1[v] = true;
					countInq1[v]++;
					if(countInq1[v] >= N) {
						return false;
					}
				}
			} else if(d1[u] + length == d1[v]) {
				pre1[v].insert(u);
				if(!inq1[v]) {
					q.push(v);
					inq1[v] = true;
					countInq1[v]++;
					if(countInq1[v] >= N) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

void dfs1(int nowVisit) {
	tempPath1.push_back(nowVisit);
	if(nowVisit == source) {
		int value1 = 0;
		for(int i = tempPath1.size() - 1; i > 0; i--) {
			//对于邻接表求边权，需要遍历该点连接的所有点才能寻找到所要求的那条边的边权
			for(int j = 0; j < graph[tempPath1[i]].size(); j++) {
				if(graph[tempPath1[i]][j].v == tempPath1[i - 1]) {
					value1 += graph[tempPath1[i]][j].time;
					break;
				}
			}
		}
		if(value1 < optValue1) {
			optValue1 = value1;
			path1 = tempPath1;
		}
		tempPath1.pop_back();
		return;
	}
	set<int>::iterator it;
	for(it = pre1[nowVisit].begin(); it != pre1[nowVisit].end(); it++) {
		dfs1(*it);
	}
	tempPath1.pop_back();
}

bool spfa2(int s) {
	for(int i = 0; i < N; i++) {
		d2[i] = INF;
	}
	d2[s] = 0;
	queue<int> q;
	q.push(s);
	inq2[s] = true;
	countInq2[s]++;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inq2[u] = false;
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;
			int time = graph[u][j].time;
			if(d2[u] + time < d2[v]) {
				d2[v] = d2[u] + time;
				pre2[v].clear();
				pre2[v].insert(u);
				if(!inq2[v]){
					q.push(v);
					inq2[v] = true;
					countInq2[v]++;
					if(countInq2[v] > N){
						return false;
					}
				}
			} else if(d2[u] + time == d2[v]) {
				pre2[v].insert(u);
				if(!inq2[v]){
					q.push(v);
					inq2[v] = true;
					countInq2[v]++;
					if(countInq2[v] > N){
						return false;
					}
				}
			}
		}
	}
	return true;
}

void dfs2(int nowVisit) {
	tempPath2.push_back(nowVisit);
	if(nowVisit == source) {
		int value2 = tempPath2.size();
		if(value2 < optValue2) {
			optValue2 = value2;
			path2 = tempPath2;
		}
		tempPath2.pop_back();
		return;
	}
	set<int>::iterator it;
	for(it = pre2[nowVisit].begin(); it != pre2[nowVisit].end(); it++) {
		dfs2(*it);
	}
	tempPath2.pop_back();
}
