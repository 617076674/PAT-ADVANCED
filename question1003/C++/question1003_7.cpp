#include<iostream>
#include<set>
#include<vector>
#include<queue>

using namespace std;

struct node {
	int v;	//�ڽӱߵ�Ŀ�궥��
	int dis;	//�ڽӱߵı�Ȩ
	node(int _v, int _dis) : v(_v), dis(_dis) {} //���캯��
};

int n;	//��������
int m;	//·������
int c1;	//�����ڵĳ���
int c2;	//��Ҫȥ���ȵĳ���
int INF = 1000000000;	//�������
vector<node> graph[501];	//����ͼ
int teams[501] = {0};	//ÿ�����еļ��ȶ�����
int d[501];	//d[i]��ʾ�����c1�������i�����·������
set<int> pre[501];	//�洢ǰһ�ڵ��б�
bool inQueue[501] = {false};	//inQueue[i]�����жϽڵ�i�Ƿ��ڶ����� 
int countInQueue[501] = {0};	//countInQueue[i]��ʾ�ڵ�i����Ӵ��� 
vector<int> path;
vector<int> tempPath; 
int optValue = 0;
int count = 0;

bool spfa(int s);
void dfs(int nowVisit);

int main() {
	cin >> n >> m >> c1 >> c2;
	for(int i = 0; i < n; i++) {
		cin >> teams[i];
	}
	int city1, city2, len;
	for(int i = 0; i < m; i++) {
		cin >> city1 >> city2 >> len;
		graph[city1].push_back(node(city2, len));
		graph[city2].push_back(node(city1, len));
	}
	spfa(c1);
	dfs(c2);
	cout << count << " " << optValue << endl;
	return 0;
}

bool spfa(int s) {
	for(int i = 0; i < n; i++) {
		d[i] = INF;
	}
	d[s] = 0;
	queue<int> q;
	q.push(s);	//Դ�����
	inQueue[s] = true;
	countInQueue[s]++;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inQueue[u] = false;	//����uΪ���ڶ����� 
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;	//�ڽӱߵĶ���
			int dis = graph[u][j].dis;	//�ڽӱߵı�Ȩ
			if(dis + d[u] < d[v]) {
				d[v] = dis + d[u];
				if(!inQueue[v]){	//���v���ڶ����� 
					q.push(v);	//v��� 
					inQueue[v] = true;	//����vΪ�ڶ�����
					countInQueue[v]++;
					if(countInQueue[v] >= n){
						return false;	//��ĳ���������Ӵ�������n - 1��ʱ��˵��ͼ�д��ڴ�Դ��ɴ�ĸ��� 
					} 
				}
				pre[v].clear();
				pre[v].insert(u);
			} else if(dis + d[u] == d[v]) {
				pre[v].insert(u);
				if(!inQueue[v]){	//���v���ڶ����� 
					q.push(v);	//v��� 
					inQueue[v] = true;	//����vΪ�ڶ�����
					countInQueue[v]++;
					if(countInQueue[v] >= n){
						return false;	//��ĳ���������Ӵ�������n - 1��ʱ��˵��ͼ�д��ڴ�Դ��ɴ�ĸ��� 
					} 
				}
			}
		}
	}
	return true;
}

void dfs(int nowVisit){
	if(nowVisit == c1){
		count++;
		tempPath.push_back(nowVisit);
		int value = 0;
		for(int i = tempPath.size() - 1; i >= 0; i--){
			value += teams[tempPath[i]];
		}
		if(value > optValue){
			optValue = value;
			path = tempPath;
		}
		tempPath.pop_back();
	}
	tempPath.push_back(nowVisit);
	set<int>::iterator it;
	for(it = pre[nowVisit].begin(); it != pre[nowVisit].end(); it++){
		dfs(*it);
	}
	tempPath.pop_back();
}
