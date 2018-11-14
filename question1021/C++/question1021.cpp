#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct node {
	int v;	//�ڵ���
	int level;	//����
	node(int _v, int _level) : v(_v), level(_level) {};	//���캯��
};

int n;	//�ڵ����
vector<int> graph[10001];	//����ͼ
bool visited[10001] = {false};	//�������
int level[10001] = {0};	//��¼������ȱ����Ĳ���

void dfs(int nowVisit);
void bfs(int nowVisit, int index);

int main() {
	cin >> n;
	int v1, v2;
	for(int i = 0; i < n - 1; i++) {
		cin >> v1 >> v2;
		graph[v1 - 1].push_back(v2 - 1);
		graph[v2 - 1].push_back(v1 - 1);
	}
	int count = 0;
	for(int i = 0; i < n; i++) {
		if(!visited[i]) {
			dfs(i);
			count++;
		}
	}
	if(count > 1) {
		printf("Error: %d components\n", count);
		return 0;
	}
	for(int i = 0; i < 10001; i++) {
		visited[i] = false;
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < 10001; j++) {
			visited[j] = false;
		}
		if(!visited[i]) {
			bfs(i, i);
		}
	}
	int max = level[0];
	for(int i = 1; i < n; i++) {
		if(level[i] > max) {
			max = level[i];
		}
	}
	for(int i = 0; i < n; i++) {
		if(level[i] == max) {
			cout << i + 1 << endl;
		}
	}
	return 0;
}

void dfs(int nowVisit) {
	visited[nowVisit] = true;
	for(int i = 0; i < graph[nowVisit].size(); i++) {
		if(!visited[graph[nowVisit][i]]) {
			dfs(graph[nowVisit][i]);
		}
	}
}

void bfs(int nowVisit, int index) {
	queue<node> q;
	q.push(node(nowVisit, 0));
	visited[nowVisit] = true;
	while(!q.empty()) {
		node uNode = q.front();
		if(uNode.level > level[index]) {
			level[index] = uNode.level;
		}
		int u = uNode.v;
		q.pop();
		for(int i = 0; i < graph[u].size(); i++) {
			int v = graph[u][i];
			if(!visited[v]) {
				q.push(node(v, uNode.level + 1));
				visited[v] = true;
			}
		}
	}
}
