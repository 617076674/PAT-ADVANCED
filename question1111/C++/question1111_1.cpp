#include<iostream>
#include<vector>

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
bool visited1[501] = {false};
bool visited2[501] = {false};
vector<int> pre1[501];
vector<int> pre2[501];
vector<int> tempPath1;
vector<int> tempPath2;
vector<int> path1;
vector<int> path2;
int optValue1 = INF;
int optValue2 = INF;

void dijkstra1(int s);
void dfs1(int nowVisit);
void dijkstra2(int s);
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
	dijkstra1(source);
	dfs1(destination);
	dijkstra2(source);
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

void dijkstra1(int s) {
	for(int i = 0; i < N; i++) {
		d1[i] = INF;
	}
	d1[s] = 0;
	for(int i = 0; i < N; i++) {
		int u = -1, min = INF;
		for(int j = 0; j < N; j++) {
			if(!visited1[j] && d1[j] < min) {
				min = d1[j];
				u = j;
			}
		}
		if(u == -1) {
			return;
		}
		visited1[u] = true;
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;
			int length = graph[u][j].length;
			if(!visited1[v]) {
				if(d1[u] + length < d1[v]) {
					d1[v] = d1[u] + length;
					pre1[v].clear();
					pre1[v].push_back(u);
				} else if(d1[u] + length == d1[v]) {
					pre1[v].push_back(u);
				}
			}
		}
	}
}

void dfs1(int nowVisit) {
	tempPath1.push_back(nowVisit);
	if(nowVisit == source) {
		int value1 = 0;
		for(int i = tempPath1.size() - 1; i > 0; i--) {
			//对于邻接表求边权，需要遍历该点连接的所有点才能寻找到所要求的那条边的边权
			for(int j = 0; j < graph[tempPath1[i]].size(); j++){	
				if(graph[tempPath1[i]][j].v == tempPath1[i - 1]){
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
	for(int i = 0; i < pre1[nowVisit].size(); i++) {
		dfs1(pre1[nowVisit][i]);
	}
	tempPath1.pop_back();
}

void dijkstra2(int s) {
	for(int i = 0; i < N; i++) {
		d2[i] = INF;
	}
	d2[s] = 0;
	for(int i = 0; i < N; i++) {
		int u = -1, min = INF;
		for(int j = 0; j < N; j++) {
			if(!visited2[j] && d2[j] < min) {
				min = d2[j];
				u = j;
			}
		}
		if(u == -1) {
			return;
		}
		visited2[u] = true;
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;
			int time = graph[u][j].time;
			if(!visited2[v]) {
				if(d2[u] + time < d2[v]) {
					d2[v] = d2[u] + time;
					pre2[v].clear();
					pre2[v].push_back(u);
				} else if(d2[u] + time == d2[v]) {
					pre2[v].push_back(u);
				}
			}
		}
	}
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
	for(int i = 0; i < pre2[nowVisit].size(); i++) {
		dfs2(pre2[nowVisit][i]);
	}
	tempPath2.pop_back();
}
