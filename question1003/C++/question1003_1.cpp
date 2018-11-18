#include<iostream>
#include<queue>

using namespace std;

int n, m, c1, c2, INF = 1000000000;	//������������·��������㣬�յ㣬������� 
int graph[501][501];	//����ͼ 
int teams[501];	//���ȶ����� 
int d[501];	//d[i]��ʾ�����c1�����i�����·������ 
int num[501];	//num[i]��ʾ�����c1�����i�����·������
int weight[501];	//weight[i]��ʾ�����c1�����i�����Ѽ�������󼱾ȶ����� 
bool visited[501];	//dijkstra�㷨�ı�����飬���Ա�Ǹ�λ���Ƿ��ѱ����� 

void dijkstra(int s); 

int main(){
	scanf("%d %d %d %d", &n, &m, &c1, &c2);	//��ȡ������������·��������㣬�յ� 
	fill(visited, visited + 501, false);	//��ʼ���ñ������ȫ��Ϊfalse�����нڵ��δ������ 
	for(int i = 0; i < n; i++){	
		for(int j = 0; j < n; j++){
			graph[i][j] = INF;	//��ʼ��ͼ����������ľ��붼Ϊ����󣬼�ͼ�в������κ�·�� 
		}
	}
	for(int i = 0; i < n; i++){
		scanf("%d", &teams[i]); //��ȡÿ�����м��ȶ����� 
	}
	int city1, city2, len;
	for(int i = 0; i < m; i++){
		scanf("%d %d %d", &city1, &city2, &len);
		graph[city1][city2] = graph[city2][city1] = len;	//��ȡ���м��·����Ϣ 
	}
	dijkstra(c1);	//��c1Ϊ�������dijkstra�㷨����������̾��� 
	printf("%d %d\n", num[c2], weight[c2]);	//������ 
	return 0;
}

void dijkstra(int s){
	fill(d, d + 501, INF);	//��ʼ��Դ��s����������̾����Ϊ����� 
	fill(num, num + 501, 0);	//��ʼ�����s�������������·��������Ϊ0�� 
	fill(weight, weight + 501, 0);	//��ʼ�������s��������������Ѽ�������󼱾ȶ�������Ϊ0 
	weight[s] = teams[s];	//���s���������������Ѽ����ļ��ȶ���������������ӵ�еļ��ȶ����� 
	num[s] = 1;	//���s��������������·������Ϊ1 
	d[s] = 0;	//���s��������ľ���Ϊ0
	for(int i = 0; i < n; i++){
		int u = -1, min = INF;
		for(int j = 0; j < n; j++){	//Ѱ��δ���ʵĶ�����d[]��С�� 
			if(!visited[j] && d[j] < min){
				u = j;
				min = d[j];
			}
		}
		if(u == -1){	//�Ҳ���С��INF��d[u]��˵��ʣ�µĶ������㲻��ͨ 
			return;
		}	
		visited[u] = true;	//������С��d[u]��u����Ϊ�ѱ����ʹ� 
		for(int j = 0; j < n; j++){
			if(!visited[j] && graph[u][j] != INF){	//���jδ�����ʹ���u��j֮����·�� 
				if(d[u] + graph[u][j] < d[j]){	//���ͨ��u�㵽��j��ֱ�ӵ���jҪ��С 
					d[j] = d[u] + graph[u][j];	//�Ż�d[v]
					weight[j] = weight[u] + teams[j];	//����j���Ԯ�ӵ��������ڵ���u���Ԯ�ӵ���������j�������Ԯ�ӵ����� 
					num[j] = num[u];	//����j������·���������ڵ���u������·������ 
				}else if(d[u] + graph[u][j] == d[j]){	//���ͨ��u�㵽��j��ֱ�ӵ���j���·����� 
					if(weight[u] + teams[j] > weight[j]){	//���ͨ��u�㵽��j�������Ѽ����ļ��ȶ��������� 
						weight[j] = weight[u] + teams[j];	//���µ���j�����󼱾ȶ����� 
					}
					num[j] += num[u];	//����j������·��������Ҫ���ϵ���u������·������ 
				}  
			}
		}
	} 
} 

