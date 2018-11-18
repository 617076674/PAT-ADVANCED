#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<queue>

using namespace std;

struct node {
	int v;
	int lineFlag;	//���������ڵڼ�����·
	node(int _v, int _lineFlag) : v(_v), lineFlag(_lineFlag) {};
};

vector<node> graph[10000];	//����ͼ
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
		int from = path.size() - 1;	//�洢ĳ�������Ŀ�ʼ�ڵ���·��path�е����� 
		int lastLine;
		for(int k = 0; k < graph[path[path.size() - 1]].size(); k++) {
			//�������ڽӾ������ʽ�洢ͼ����Ϣ����֪ͼ��һ�����㣬����һ������ʱ��������Ҫ�����ö���������ڱ� 
			if(graph[path[path.size() - 1]][k].v == path[path.size() - 2]) {	 
				lastLine = graph[path[path.size() - 1]][k].lineFlag;	//��¼��һ���������ĵ������ 
			}
		}
		for(int j = path.size() - 2; j > 0; j--) {
			for(int k = 0; k < graph[path[j]].size(); k++) {
				if(graph[path[j]][k].v == path[j - 1]) {
					if(lastLine != graph[path[j]][k].lineFlag) {	//�ҵ��˱������ĵ�����ź�ǰһ���߲�ͬ 
						//ĳ�������ı��ΪlastLine����ʼ�ڵ�Ϊpath[from]�������ڵ�Ϊpath[j] 
						printf("Take Line#%d from %04d to %04d.\n", lastLine, path[from], path[j]);
						from = j;	//����fromֵ 
						lastLine = graph[path[j]][k].lineFlag;	//����ǰһ��������ŵ�ֵ  
					}
					break;	//ֻҪ�ҵ�����һ������Ϳ���break 
				}
			}
		}
		printf("Take Line#%d from %04d to %04d.\n", lastLine, path[from], path[0]);	//��Ҫ��ӡ��path[from]���յ�path[0]����Ϣ 
	}
	return 0;
}

void init() {	//ÿ��SPFA֮ǰ��ʼ�����ּ�¼���� 
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
			if(d[now] + 1 < d[v]) {	//ͼ����Ȩͼ�����Ǽٶ�ÿ���߳���Ϊ1 
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
		set<int> lineFlags;	//��set������ȥ���������ظ�����վ��� 
		for(int i = tempPath.size() - 1; i > 0; i--) {
			for(int j = 0; j < graph[tempPath[i]].size(); j++) {
				if(graph[tempPath[i]][j].v == tempPath[i - 1]) {
					lineFlags.insert(graph[tempPath[i]][j].lineFlag);
				}
			}
		}
		if(lineFlags.size() < minTransfer) {	//·�������б���������վ�Ĳ�ͬ�����Ŀ������Ҫת�����Ĵ��� + 1 
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
