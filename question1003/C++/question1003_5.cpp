#include<iostream>
#include<set>
#include<vector>

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
int num[501];	//num[i]��ʾ�����c1�����i�����·������
int weight[501];	//weight[i]��ʾ�����c1�����i�����Ѽ�������󼱾ȶ�����
set<int> pre[501];	//�洢ǰһ�ڵ��б�

bool bellmanFord(int s);

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
	bellmanFord(c1);
	cout << num[c2] << " " << weight[c2] << endl;
	return 0;
}

bool bellmanFord(int s) {
	for(int i = 0; i < n; i++) {
		d[i] = INF;
		num[i] = 0;
		weight[i] = 0;
	}
	d[s] = 0;
	num[s] = 1;
	weight[s] = teams[s];
	for(int i = 0; i < n - 1; i++) {
		for(int u = 0; u < n; u++) {
			for(int j = 0; j < graph[u].size(); j++) {
				int v = graph[u][j].v;	//�ڽӱߵĶ���
				int dis = graph[u][j].dis;	//�ڽӱߵı�Ȩ
				if(dis + d[u] < d[v]) {
					d[v] = dis + d[u];
					num[v] = num[u];
					weight[v] = weight[u] + teams[v];
					pre[v].clear();
					pre[v].insert(u);
				} else if(dis + d[u] == d[v]) {
					if(weight[u] + teams[v] > weight[v]) {
						weight[v] = weight[u] + teams[v];
					}
					pre[v].insert(u);
					num[v] = 0;	//����ͳ��num[v]
					set<int>::iterator it;
					for(it = pre[v].begin(); it != pre[v].end(); it++) {
						num[v] += num[*it];
					}
				}
			}
		}
	}
	for(int u = 0; u < n; u++) {
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;	//�ڽӱߵĶ���
			int dis = graph[u][j].dis;	//�ڽӱߵı�Ȩ
			if(dis + d[u] < d[v]) {
				return false;
			}
		}
	}
	return true;
}
