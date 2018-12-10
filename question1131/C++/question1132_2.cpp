#include<iostream>
#include<vector>
#include<queue>
#include<set>

using namespace std;

struct node {
	int v;
	int lineFlag;	//���������ڵڼ�����·
	node(int _v, int _lineFlag) : v(_v), lineFlag(_lineFlag) {};
};

vector<node> graph[10000];
int start, destination, INF = 1000000;
bool visited[10000];	//������ȱ����ı�����飬���ĳ�ڵ��Ƿ��ѱ����ʹ� 
set<int> pre[10000];	//��¼ǰһ���ڵ�
vector<int> tempPath, path;
int minLength, minTransfer;

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
		for(int k = 0; k < graph[path[from]].size(); k++) {
			if(graph[path[from]][k].v == path[from - 1]) {
				lastLine = graph[path[from]][k].lineFlag;
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
	path.clear();
	for(int i = 0; i < 10000; i++) {
		pre[i].clear();
	}
	minLength = minTransfer = INF;
	fill(visited, visited + 10000, false);
}

void bfs(int nowVisit) {
	queue<int> q;
	q.push(nowVisit);
	visited[nowVisit] = true;
	while(!q.empty()) {
		int qSize = q.size();
		set<int> tempVisited;
		for(int i = 0; i < qSize; i++) {
			int now = q.front();
			q.pop();
			for(int i = 0; i < graph[now].size(); i++) {
				int v = graph[now][i].v;
				if(!visited[v]) {
					q.push(v);
					pre[v].insert(now);
					tempVisited.insert(v);
				}
			}
		}
		for(set<int>::iterator it = tempVisited.begin(); it != tempVisited.end(); it++){	 
			visited[*it] = true;	//�ڱ�����ͬһ������нڵ����ȥ��Ƿ�������
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
					break; 
				}
			}
		}
		if(tempPath.size() < minLength) {	 //�ҵ��˸��̵�·��
			minLength = tempPath.size();
			minTransfer = lineFlags.size();	//ҲҪ������Сת��������
			path = tempPath;
		} else if(tempPath.size() == minLength && lineFlags.size() < minTransfer) {	//���·����ȣ�����ת����������С
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
