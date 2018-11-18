#include<iostream>
#include<vector>

using namespace std;

int n, m, c1, c2, INF = 1000000000;	//������������·��������㣬�յ㣬�������
int graph[501][501];	//����ͼ
int teams[501];	//ÿ�����еļ��ȶ�����
int d[501];	//d[i]��ʾ�����c1�������i�����·������
vector<int> pre[501];	//�洢ǰһ�ڵ��б�
bool visited[501];	//dijkstra�㷨�ı�����飬���Ա�Ǹ�λ���Ƿ��ѱ�����
vector<int> path;	//�洢���Ѽ�����༱�ȶ����������·��
vector<int> tempPath; //�洢������ȱ��������еĵ�ǰ·��
int optValue = 0;	//���Ѽ�������༱�ȶ���������ʼ��Ϊ0
int count = 0;	//���·����������ʼ��Ϊ0

void dijkstra(int s);
void dfs(int nowVisit);

int main() {
	scanf("%d %d %d %d", &n, &m, &c1, &c2);	//��ȡ������������·��������㣬�յ�
	fill(visited, visited + 501, false);	//��ʼ���ñ������ȫ��Ϊfalse�����нڵ��δ������
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			graph[i][j] = INF;	//��ʼ��ͼ����������ľ��붼Ϊ����󣬼�ͼ�в������κ�·��
		}
	}
	for(int i = 0; i < n; i++) {
		scanf("%d", &teams[i]); //��ȡÿ�����м��ȶ�����
	}
	int city1, city2, len;
	for(int i = 0; i < m; i++) {
		scanf("%d %d %d", &city1, &city2, &len);
		graph[city1][city2] = graph[city2][city1] = len;	//��ȡ���м��·����Ϣ
	}
	dijkstra(c1);	////��c1Ϊ�������dijkstra�㷨����������̾���
	dfs(c2);	//���յ㿪ʼ���ݼ�¼��ǰһ�ڵ��б�preѰ�ҳ����Ѽ�������༱�ȶ������Լ����·������
	printf("%d %d\n", count, optValue);	//������
	return 0;
}

void dijkstra(int s) {
	fill(d, d + 501, INF);	//��ʼ��Դ��s����������̾����Ϊ�����
	d[s] = 0;	//���s��������ľ���Ϊ0
	for(int i = 0; i < n; i++) {
		int u = -1, min = INF;
		for(int j = 0; j < n; j++) {	//Ѱ��δ���ʵĶ�����d[]��С��
			if(!visited[j] && d[j] < min) {
				min = d[j];
				u = j;
			}
		}
		if(u == -1) {	//�Ҳ���С��INF��d[u]��˵��ʣ�µĶ������㲻��ͨ
			return;
		}
		visited[u] = true;	////������С��d[u]��u����Ϊ�ѱ����ʹ�
		for(int v = 0; v < n; v++) {
			if(!visited[v] && graph[u][v] != INF) {
				if(graph[u][v] + d[u] < d[v]) {	//���ͨ��u�㵽��v��ֱ�ӵ���vҪ��С
					d[v] = graph[u][v] + d[u];	//�Ż�d[v]
					pre[v].clear();	//���֮ǰ�洢��v��ǰһ���ڵ�
					pre[v].push_back(u);	//��u����v��ǰһ���ڵ�洢��pre[v]��
				} else if(graph[u][v] + d[u] == d[v]) {	//���ͨ��u�㵽��v��ֱ�ӵ���v���·�����
					pre[v].push_back(u);	//��u����pre[v]��
				}
			}
		}
	}
}

void dfs(int nowVisit) {
	tempPath.push_back(nowVisit);	//����ǰ�ڵ���뵱ǰ·���� 
	if(nowVisit == c1) {	//�����ǰ�ڵ�������c1�����ǵݹ����ֹ���� 
		count++;	//���·��������1 
		int value = 0;	//���㵱ǰ·�������Ѽ����ļ��ȶ����� 
		for(int i = tempPath.size() - 1; i >= 0; i--) {
			value += teams[tempPath[i]];
		}
		if(value > optValue) {	//�����ǰ·�������Ѽ����ļ��ȶ����������������optValue 
			optValue = value;	//������󼱾ȶ�������ֵ 
			path = tempPath;	//����ǰ·����Ϊ���Ѽ�����󼱾ȶ�������·���������� 
		}
		tempPath.pop_back();	//������ǰ�ڵ㣬�������ֶ����ݹ��� 
		return;
	}
	for(int i = 0; i < pre[nowVisit].size(); i++) {
		dfs(pre[nowVisit][i]);	//������ȱ�����ǰ�ڵ������ǰһ���ڵ� 
	}
	tempPath.pop_back();	//������ǰ�ڵ㣬�������ֶ����ݹ��� 
}
