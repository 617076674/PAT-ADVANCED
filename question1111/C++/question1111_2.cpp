#include<iostream>
#include<vector>
#include<set>

using namespace std;

struct node {
	int v;	//�˵���
	int length;	//��·����
	int time;	//��·ʱ��
	node(int _v, int _length, int _time) : v(_v), length(_length), time(_time) {};	//���캯��
};

int N, M, source, destination, INF = 1000000000;	//ʮ��·����������·��������㣬�յ㣬�������
vector<node> graph[501];	//���ڽӱ���ʽ�洢����ͼ
int d1[501], d2[501];	//d1[]��d2[]�ֱ��¼����㵽��������̳��Ⱥ����ʱ��
set<int> pre1[501], pre2[501];	//pre1[]��pre2[]�ֱ����Գ���Ϊ��Ȩ��bellmanFord����ʱ��Ϊ��Ȩ��bellmanFordʱ�ļ�¼ǰһ���ڵ������
vector<int> tempPath1, tempPath2;	//tempPath1��tempPath2�ֱ��Ƕ���̳��Ⱥ����ʱ���·����������ȱ���ʱ�ĵ�ǰ·��
vector<int> path1, path2;	//path1��path2�ֱ�����̳��������ʱ���·�������ʱ����·��ʮ��·���������ٵ�·��
int optValue1 = INF, optValue2 = INF;	//optValue1��optValue2�ֱ�����̳����е����ʱ������ʱ���е�����ʮ��·������

bool bellmanFord1(int s);	//�Գ���Ϊ��Ȩ��bellmanFord
void dfs1(int nowVisit);	//����̳��ȵ�·����������ȱ�������������ʱ���·��
bool bellmanFord2(int s);	//��ʱ��Ϊ��Ȩ��bellmanFord
void dfs2(int nowVisit);	//�����ʱ���·����������ȱ��������������ʮ��·��������·�� 

int main() {
	scanf("%d %d", &N, &M);	//��ȡʮ��·��������·������
	int V1, V2, one_way, length, time;
	for(int i = 0; i < M; i++) {
		scanf("%d %d %d %d %d", &V1, &V2, &one_way, &length, &time);	//��ȡÿ����·����Ϣ
		graph[V1].push_back(node(V2, length, time));
		if(one_way == 0) {	//���one_way��0��˵��������·��˫��ͨ�е�
			graph[V2].push_back(node(V1, length, time));
		}
	}
	scanf("%d %d", &source, &destination);
	bellmanFord1(source);	//�Գ���Ϊ��Ȩ��bellmanFord
	dfs1(destination);	//����̳��ȵ�·����������ȱ�������������ʱ���·��
	bellmanFord2(source);	//��ʱ��Ϊ��Ȩ��bellmanFord
	dfs2(destination);	//�����ʱ���·����������ȱ��������������ʮ��·��������·��
	if(path1 == path2) {	//����Գ���Ϊ��Ȩ��õ�����·������ʱ��Ϊ��Ȩ��õ�����·����ͬ
		printf("Distance = %d; Time = %d: ", d1[destination], d2[destination]);
		for(int i = path1.size() - 1; i >= 0; i--) {
			printf("%d", path1[i]);
			if(i != 0) {
				printf(" -> ");
			} else {
				printf("\n");
			}
		}
	} else {	//����Գ���Ϊ��Ȩ��õ�����·������ʱ��Ϊ��Ȩ��õ�����·����ͬ
		printf("Distance = %d: ", d1[destination]);
		for(int i = path1.size() - 1; i >= 0; i--) {
			printf("%d", path1[i]);
			if(i != 0) {
				printf(" -> ");
			} else {
				printf("\n");
			}
		}
		printf("Time = %d: ", d2[destination]);
		for(int i = path2.size() - 1; i >= 0; i--) {
			printf("%d", path2[i]);
			if(i != 0) {
				printf(" -> ");
			} else {
				printf("\n");
			}
		}
	}
	return 0;
}

bool bellmanFord1(int s) {
	for(int i = 0; i < N; i++) {	//��ʼ����ʼ�㵽�����ľ����Ϊ�����
		d1[i] = INF;
	}
	d1[s] = 0;	//��ʼ�㵽��ʼ��ľ�����0
	for(int i = 0; i < N - 1; i++) {	//ִ��N - 1���ɳڲ��� 
		for(int u = 0; u < N; u++) {
			for(int j = 0; j < graph[u].size(); j++) {
				int v = graph[u][j].v;
				int length = graph[u][j].length;
				if(d1[u] + length < d1[v]) {	//���ͨ��u����v�ľ������ 
					d1[v] = d1[u] + length;	//���µ���v�ľ���
					pre1[v].clear();	//���v��ǰһ���ڵ�
					pre1[v].insert(u);	//��u����v��ǰһ���ڵ��б���
				} else if(d1[u] + length == d1[v]) {	//���ͨ��u����v�ľ����ԭ������v�ľ���һ��
					pre1[v].insert(u);	//��u����v��ǰһ���ڵ��б���
				}
			}
		}
	}
	for(int u = 0; u < N; u++) {	 
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;
			int length = graph[u][j].length;
			if(d1[u] + length < d1[v]) {	//�������N - 1���ɳڲ������ܼ��������ɳڲ�����˵�����ڸ�Ȩ��������false 
				return false;
			}
		}
	}
	return true;	//�����ڸ�Ȩ��������true 
}

void dfs1(int nowVisit) {
	tempPath1.push_back(nowVisit);	//��ǰ�ڵ���뵱ǰ·�� 
	if(nowVisit == source) {	//�����ǰ�ڵ�����ʼ��
		int value1 = 0;
		for(int i = tempPath1.size() - 1; i > 0; i--) {	//���㵱ǰ·����ʱ��
			//�����ڽӱ����Ȩ����Ҫ�����õ����ӵ����е����Ѱ�ҵ���Ҫ��������ߵı�Ȩ
			for(int j = 0; j < graph[tempPath1[i]].size(); j++) {
				if(graph[tempPath1[i]][j].v == tempPath1[i - 1]) {
					value1 += graph[tempPath1[i]][j].time;
					break;
				}
			}
		}
		if(value1 < optValue1) {	//�����ǰ·����ʱ��С����Сʱ�� 
			optValue1 = value1;	//������Сʱ���ֵ 
			path1 = tempPath1;	//ѡȡ��ǰ·��Ϊ���·���е�����·�� 
		}
		tempPath1.pop_back();	//�������ֶ����� 
		return;
	}
	for(set<int>::iterator it = pre1[nowVisit].begin(); it != pre1[nowVisit].end(); it++) {	//�Ե�ǰ�ڵ������ǰһ���ڵ���������ȱ��� 
		dfs1(*it);
	}
	tempPath1.pop_back();	//�������ֶ����� 
}

bool bellmanFord2(int s) {
	for(int i = 0; i < N; i++) {	//��ʼ����ʼ�㵽������ʱ���Ϊ�����
		d2[i] = INF;
	}
	d2[s] = 0;	//��ʼ�㵽��ʼ���ʱ����0
	for(int i = 0; i < N - 1; i++) {	//ִ��N - 1���ɳڲ���
		for(int u = 0; u < N; u++) {
			for(int j = 0; j < graph[u].size(); j++) {
				int v = graph[u][j].v;
				int time = graph[u][j].time;
				if(d2[u] + time < d2[v]) {	//���ͨ��u����v��ʱ�����
					d2[v] = d2[u] + time;	//���µ���v��ʱ�� 
					pre2[v].clear();	//���v��ǰһ���ڵ�
					pre2[v].insert(u);	//��u����v��ǰһ���ڵ��б���
				} else if(d2[u] + time == d2[v]) {	//���ͨ��u����v��ʱ���ԭ������v��ʱ��һ��
					pre2[v].insert(u);	//��u����v��ǰһ���ڵ��б���
				}
			}
		}
	}
	for(int u = 0; u < N; u++) {
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;
			int time = graph[u][j].time;
			if(d2[u] + time < d2[v]) {	//�������N - 1���ɳڲ������ܼ��������ɳڲ�����˵�����ڸ�Ȩ��������false
				return false;
			}
		}
	}
	return true;	//�����ڸ�Ȩ��������true 
}

void dfs2(int nowVisit) {
	tempPath2.push_back(nowVisit);	//��ǰ�ڵ���뵱ǰ·��
	if(nowVisit == source) {	//�����ǰ�ڵ�����ʼ��
		int value2 = tempPath2.size();
		if(value2 < optValue2) {	//�����ǰ·��ͨ����ʮ��·������С�����ٵ�ʮ��·������
			optValue2 = value2;	//�������ٵ�ʮ��·������ 
			path2 = tempPath2;	//ѡȡ��ǰ·��Ϊ���ʱ��·���е�����·�� 
		}
		tempPath2.pop_back();	//�������ֶ�����
		return;
	}
	for(set<int>::iterator it = pre2[nowVisit].begin(); it != pre2[nowVisit].end(); it++) {	//�Ե�ǰ�ڵ������ǰһ���ڵ���������ȱ���
		dfs2(*it);
	}
	tempPath2.pop_back();	//�������ֶ�����
}
