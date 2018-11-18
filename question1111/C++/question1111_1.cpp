#include<iostream>
#include<vector>

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
bool visited1[501], visited2[501];	//visited1[]��visited2[]�ֱ����Գ���Ϊ��Ȩ��dijkstra����ʱ��Ϊ��Ȩ��dijkstraʱ�ı������
vector<int> pre1[501], pre2[501];	//pre1[]��pre2[]�ֱ����Գ���Ϊ��Ȩ��dijkstra����ʱ��Ϊ��Ȩ��dijkstraʱ�ļ�¼ǰһ���ڵ������
vector<int> tempPath1, tempPath2;	//tempPath1��tempPath2�ֱ��Ƕ���̳��Ⱥ����ʱ���·����������ȱ���ʱ�ĵ�ǰ·��
vector<int> path1, path2;	//path1��path2�ֱ�����̳��������ʱ���·�������ʱ����·��ʮ��·���������ٵ�·��
int optValue1 = INF, optValue2 = INF;	//optValue1��optValue2�ֱ�����̳����е����ʱ������ʱ���е�����ʮ��·������

void dijkstra1(int s);	//�Գ���Ϊ��Ȩ��dijkstra
void dfs1(int nowVisit);	//����̳��ȵ�·����������ȱ�������������ʱ���·��
void dijkstra2(int s);	//��ʱ��Ϊ��Ȩ��dijkstra
void dfs2(int nowVisit);	//�����ʱ���·����������ȱ��������������ʮ��·��������·��

int main() {
	fill(visited1, visited1 + 501, false);	//��ʼ���������
	fill(visited2, visited2 + 501, false);
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
	dijkstra1(source);	//�Գ���Ϊ��Ȩ��dijkstra
	dfs1(destination);	//����̳��ȵ�·����������ȱ�������������ʱ���·��
	dijkstra2(source);	//��ʱ��Ϊ��Ȩ��dijkstra
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

void dijkstra1(int s) {
	for(int i = 0; i < N; i++) {	//��ʼ����ʼ�㵽�����ľ����Ϊ����� 
		d1[i] = INF;
	}
	d1[s] = 0;	//��ʼ�㵽��ʼ��ľ�����0 
	for(int i = 0; i < N; i++) {
		int u = -1, min = INF;
		for(int j = 0; j < N; j++) {
			if(!visited1[j] && d1[j] < min) {	//Ѱ��δ���ʹ��Ľڵ��еľ�����С�Ľڵ� 
				min = d1[j];
				u = j;
			}
		}
		if(u == -1) {
			return;
		}
		visited1[u] = true;	//��Ǹýڵ�Ϊ�ѷ��� 
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;
			int length = graph[u][j].length;
			if(!visited1[v]) {	//����ڵ�vδ������ 
				if(d1[u] + length < d1[v]) {	//���ͨ��u����v�ľ������ 
					d1[v] = d1[u] + length;	//���µ���v�ľ��� 
					pre1[v].clear();	//���v��ǰһ���ڵ� 
					pre1[v].push_back(u);	//��uѹ��v��ǰһ���ڵ��б��� 
				} else if(d1[u] + length == d1[v]) {	//���ͨ��u����v�ľ����ԭ������v�ľ���һ�� 
					pre1[v].push_back(u);	//��uѹ��v��ǰһ���ڵ��б���
				}
			}
		}
	}
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
	for(int i = 0; i < pre1[nowVisit].size(); i++) {	//�Ե�ǰ�ڵ������ǰһ���ڵ���������ȱ��� 
		dfs1(pre1[nowVisit][i]);
	}
	tempPath1.pop_back();	//�������ֶ�����
}

void dijkstra2(int s) {
	for(int i = 0; i < N; i++) {	//��ʼ����ʼ�㵽������ʱ���Ϊ�����
		d2[i] = INF;
	}
	d2[s] = 0;	//��ʼ�㵽��ʼ���ʱ����0 
	for(int i = 0; i < N; i++) {
		int u = -1, min = INF;
		for(int j = 0; j < N; j++) {
			if(!visited2[j] && d2[j] < min) {	//Ѱ��δ���ʹ��Ľڵ��е�ʱ����С�Ľڵ�	
				min = d2[j];
				u = j;
			}
		}
		if(u == -1) {
			return;
		}
		visited2[u] = true;	//��Ǹýڵ�Ϊ�ѷ���
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;
			int time = graph[u][j].time;
			if(!visited2[v]) {	//����ڵ�vδ������ 
				if(d2[u] + time < d2[v]) {	//���ͨ��u����v��ʱ�����
					d2[v] = d2[u] + time;	//���µ���v��ʱ�� 
					pre2[v].clear();	//���v��ǰһ���ڵ�
					pre2[v].push_back(u);	//��uѹ��v��ǰһ���ڵ��б���
				} else if(d2[u] + time == d2[v]) {	//���ͨ��u����v��ʱ���ԭ������v��ʱ��һ�� 
					pre2[v].push_back(u);	//��uѹ��v��ǰһ���ڵ��б���
				}
			}
		}
	}
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
	for(int i = 0; i < pre2[nowVisit].size(); i++) {	//�Ե�ǰ�ڵ������ǰһ���ڵ���������ȱ��� 
		dfs2(pre2[nowVisit][i]);
	}
	tempPath2.pop_back();	//�������ֶ�����
}
