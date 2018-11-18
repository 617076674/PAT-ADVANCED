#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<queue>

using namespace std;

struct node {
	int v;
	int lineFlag;	//该条边属于第几条线路
	node(int _v, int _lineFlag) : v(_v), lineFlag(_lineFlag) {};
};

vector<node> graph[10000];	//无向图
int start, destination;
int INF = 1000000000;
int d[10000];
int countInq[10000];
bool inq[10000];
set<int> pre[10000];
vector<int> tempPath;
vector<int> path;
int minTransfer = INF;

void init();
bool spfa(int s);
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
		scanf("%d %d", &start, &destination);
		init();
		spfa(start);
		dfs(destination);
		printf("%d\n", path.size() - 1);
		int from = path.size() - 1;	//存储某条地铁的开始节点在路径path中的索引 
		int lastLine;
		for(int k = 0; k < graph[path[path.size() - 1]].size(); k++) {
			//由于用邻接矩阵的形式存储图的信息，已知图的一个顶点，求另一个顶点时，我们需要遍历该顶点的所有邻边 
			if(graph[path[path.size() - 1]][k].v == path[path.size() - 2]) {	 
				lastLine = graph[path[path.size() - 1]][k].lineFlag;	//记录第一条边所属的地铁编号 
			}
		}
		for(int j = path.size() - 2; j > 0; j--) {
			for(int k = 0; k < graph[path[j]].size(); k++) {
				if(graph[path[j]][k].v == path[j - 1]) {
					if(lastLine != graph[path[j]][k].lineFlag) {	//找到了边所属的地铁编号和前一条边不同 
						//某条地铁的编号为lastLine，开始节点为path[from]，结束节点为path[j] 
						printf("Take Line#%d from %04d to %04d.\n", lastLine, path[from], path[j]);
						from = j;	//更新from值 
						lastLine = graph[path[j]][k].lineFlag;	//更新前一条地铁编号的值  
					}
					break;	//只要找到了另一个顶点就可以break 
				}
			}
		}
		printf("Take Line#%d from %04d to %04d.\n", lastLine, path[from], path[0]);	//还要打印从path[from]到终点path[0]的信息 
	}
	return 0;
}

void init() {	//每次SPFA之前初始化各种记录变量 
	fill(countInq, countInq + 10000, 0);
	fill(inq, inq + 10000, false);
	tempPath.clear();
	path.clear();
	for(int i = 0; i < 10000; i++) {
		pre[i].clear();
	}
	minTransfer = INF;
}

bool spfa(int s) {
	fill(d, d + 10000, INF);
	d[s] = 0;
	queue<int> q;
	q.push(s);
	inq[s] = true;
	countInq[s]++;
	while(!q.empty()){
		int now = q.front();
		q.pop();
		inq[now] = false;
		for(int j = 0; j < graph[now].size(); j++){
			int v = graph[now][j].v;
			if(d[now] + 1 < d[v]) {	//图是无权图，我们假定每条边长度为1 
				d[v] = d[now] + 1;
				pre[v].clear();
				pre[v].insert(now);
				if(!inq[v]){
					q.push(v);
					inq[v] = true;
					countInq[v]++;
					if(countInq[v] > 9999){
						return false;
					}
				}
			} else if(d[now] + 1 == d[v]) {
				pre[v].insert(now);
				if(!inq[v]){
					q.push(v);
					inq[v] = true;
					countInq[v]++;
					if(countInq[v] > 9999){
						return false;
					}
				}
			}
		}
	}
	return true;
}

void dfs(int nowVisit) {
	tempPath.push_back(nowVisit);
	if(nowVisit == start) {
		set<int> lineFlags;	//用set集合来去除边所属重复地铁站编号 
		for(int i = tempPath.size() - 1; i > 0; i--) {
			for(int j = 0; j < graph[tempPath[i]].size(); j++) {
				if(graph[tempPath[i]][j].v == tempPath[i - 1]) {
					lineFlags.insert(graph[tempPath[i]][j].lineFlag);
				}
			}
		}
		if(lineFlags.size() < minTransfer) {	//路径中所有边所属地铁站的不同编号数目就是需要转地铁的次数 + 1 
			minTransfer = lineFlags.size();
			path = tempPath;
		}
		tempPath.pop_back();
		return;
	}
	for(set<int>::iterator it = pre[nowVisit].begin(); it != pre[nowVisit].end(); it++){
		dfs(*it);
	}
	tempPath.pop_back();
}
