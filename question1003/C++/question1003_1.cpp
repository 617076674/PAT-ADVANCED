#include<iostream>
#include<queue>

using namespace std;

int n;	//��������
int m;	//��·����
int c1;	//���
int c2;	//�յ� 
int graph[501][501];	//����ͼ 
int teams[501] = {0};	//���ȶ����� 
int d[501];	//d[i]��ʾ�����c1�����i�����·������ 
int num[501];	//num[i]��ʾ�����c1�����i�����·������
int weight[501];	//weight[i]��ʾ�����c1�����i�����Ѽ�������󼱾ȶ����� 
bool visited[501] = {false};

void dijkstra(int s); 

int main(){
	cin >> n >> m >> c1 >> c2;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			graph[i][j] = 1000000000;
		}
	}
	for(int i = 0; i < n; i++){
		cin >> teams[i];
	}
	int city1, city2, len;
	for(int i = 0; i < m; i++){
		cin >> city1 >> city2 >> len;
		graph[city1][city2] = len;
		graph[city2][city1] = len;
	}
	dijkstra(c1);
	cout << num[c2] << " " << weight[c2] << endl;	
	return 0;
}

void dijkstra(int s){
	for(int i = 0; i < 501; i++){
		d[i] = 1000000000;
		num[i] = 0;
		weight[i] = 0;
	}
	weight[s] = teams[s];
	num[s] = 1;
	d[s] = 0;	//���s��������ľ���Ϊ0
	for(int i = 0; i < n; i++){
		int u = -1, min = 1000000000;
		for(int j = 0; j < n; j++){	//Ѱ��δ���ʵĶ�����d[]��С�� 
			if(!visited[j] && d[j] < min){
				u = j;
				min = d[j];
			}
		}
		if(u == -1){	//�Ҳ���С��1000000000��d[u]��˵��ʣ�µĶ������㲻��ͨ 
			return;
		}	
		visited[u] = true;
		for(int j = 0; j < n; j++){
			if(!visited[j] && graph[u][j] != 1000000000){
				if(d[u] + graph[u][j] < d[j]){
					d[j] = d[u] + graph[u][j];	//�Ż�d[v]
					weight[j] = weight[u] + teams[j];
					num[j] = num[u];
				}else if(d[u] + graph[u][j] == d[j]){
					if(weight[u] + teams[j] > weight[j]){
						weight[j] = weight[u] + teams[j];						
					}
					num[j] += num[u];
				}  
			}
		}
	} 
} 

