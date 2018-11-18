#include<iostream>
#include<vector>
#include<queue>
#include<set>

using namespace std;

struct node {
	int v;
	int lineFlag;	//该条边属于第几条线路
	node(int _v, int _lineFlag) : v(_v), lineFlag(_lineFlag) {};
};

vector<node> graph[10000];
int start, destination, INF = 1000000;
bool visited[10000];	//广度优先遍历的标记数组，标记某节点是否已经入过队并出队 
set<int> pre[10000];	//记录前一个节点
vector<int> tempPath;
vector<int> path;
int minLength = INF;
int minTransfer = INF;

void init();
void bfs(int nowVisit);
void dfs(int nowVisit);

int main() {
	int N;
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) {
		int M;
		scanf("%d", &M);
		int station[M];
		for(int j = 0; j < M; j++) {
			scanf("%d", &station[j]);
		}
		for(int j = 0; j < M - 1; j++) {
			graph[station[j]].push_back(node(station[j + 1], i));
			graph[station[j + 1]].push_back(node(station[j], i));
		}
	}
	int K;
	scanf("%d", &K);
	for(int i = 0; i < K; i++) {
		init();
		scanf("%d %d", &start, &destination);
		bfs(start);
		dfs(destination);
		printf("%d\n", path.size() - 1);
		int from = path.size() - 1;
		int lastLine;
		for(int k = 0; k < graph[path[path.size() - 1]].size(); k++) {
			if(graph[path[path.size() - 1]][k].v == path[path.size() - 2]) {
				lastLine = graph[path[path.size() - 1]][k].lineFlag;
			}
		}
		for(int j = path.size() - 2; j > 0; j--) {
			for(int k = 0; k < graph[path[j]].size(); k++) {
				if(graph[path[j]][k].v == path[j - 1]) {
					if(lastLine != graph[path[j]][k].lineFlag) {
						printf("Take Line#%d from %04d to %04d.\n", lastLine, path[from], path[j]);
						from = j;
						lastLine = graph[path[j]][k].lineFlag;
						break;
					}
				}
			}
		}
		printf("Take Line#%d from %04d to %04d.\n", lastLine, path[from], path[0]);
	}
}

void init() {
	tempPath.clear();
	path.clear();
	for(int i = 0; i < 10000; i++) {
		pre[i].clear();
	}
	minLength = INF;
	minTransfer = INF;
	fill(visited, visited + 10000, false);
}

void bfs(int nowVisit) {
	queue<int> q;
	q.push(nowVisit);
	while(!q.empty()) {
		int now = q.front();
		visited[now] = true;
		q.pop();
		for(int i = 0; i < graph[now].size(); i++) {
			int v = graph[now][i].v;
			if(visited[v]) {
				continue;
			}
			q.push(v);
			pre[v].insert(now);
		}
	}
}

void dfs(int nowVisit) {
	tempPath.push_back(nowVisit);
	if(nowVisit == start) {
		set<int> lineFlags;
		for(int i = tempPath.size() - 1; i > 0; i--) {
			for(int j = 0; j < graph[tempPath[i]].size(); j++) {
				if(graph[tempPath[i]][j].v == tempPath[i - 1]) {
					lineFlags.insert(graph[tempPath[i]][j].lineFlag);
				}
			}
		}
		if(tempPath.size() < minLength){	 //找到了更短的路径 
			minLength = tempPath.size();
			minTransfer = lineFlags.size();	//也要更新最小转地铁次数 
			path = tempPath;
		}else if(tempPath.size() == minLength && lineFlags.size() < minTransfer) {	//如果路径相等，但是转地铁次数更小 
			minTransfer = lineFlags.size();
			path = tempPath;
		}
		tempPath.pop_back();
		return;
	}
	for(set<int>::iterator it = pre[nowVisit].begin(); it != pre[nowVisit].end(); it++) {
		dfs(*it);
	}
	tempPath.pop_back();
}
