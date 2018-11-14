#include<iostream>
#include<stack>

using namespace std;

int n;	//���д���
int m;	//���ٹ�·����
int s;	//��ʼ����
int d;	//Ŀ�ĵس���
int INF = 1000000000;	//�����������
int graph[501][501]; //����ͼ
int price[501][501] = {0};	//�洢���ٹ�·�۸���Ϣ
int visited[501] = {false};	//��ǽڵ��Ƿ��Ѿ������ʵ�����
int pre[501];	//�洢ǰһ���ڵ���Ϣ
int distances[501];	//distances[i]�洢�����s����ڵ�i�����·������
int costs[501];	//costs[i]�洢�����s����ڵ�i�����ٻ���

void dijkstra(int s);

int main() {
	cin >> n >> m >> s >> d;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			graph[i][j] = INF;
		}
	}
	int city1, city2, distance, cost;
	for(int i = 0; i < m; i++) {
		cin >> city1 >> city2 >> distance >> cost;
		graph[city1][city2] = distance;
		graph[city2][city1] = distance;
		price[city1][city2] = cost;
		price[city2][city1] = cost;
	}
	dijkstra(s);
	stack<int> showPathStack;
	int tempD = d;
	showPathStack.push(tempD);
	while(tempD != s) {
		showPathStack.push(pre[tempD]);
		tempD = pre[tempD];
	}
	while(!showPathStack.empty()) {
		cout << showPathStack.top() << " ";
		showPathStack.pop();
	}
	cout << distances[d] << " " << costs[d] << endl;
	return 0;
}

void dijkstra(int s) {
	for(int i = 0; i < n; i++){
		distances[i] = INF;
		costs[i] = INF;
	}
	costs[s] = 0;
	distances[s] = 0;
	for(int i = 0; i < n; i++){
		int u = -1, min = INF;
		for(int j = 0; j < n; j++){
			if(distances[j] < min && !visited[j]){
				u = j;
				min = distances[j];
			}
		}
		if(u == -1){
			return;
		}
		visited[u] = true;
		for(int v = 0; v < n; v++){
			if(!visited[v] && graph[u][v] != INF){
				if(distances[u] + graph[u][v] < distances[v]){
					distances[v] = distances[u] + graph[u][v];
					pre[v] = u;
					costs[v] = price[u][v] + costs[u];
				}else if(distances[u] + graph[u][v] == distances[v]){
					if(price[u][v] + costs[u] < costs[v]){
						costs[v] = price[u][v] + costs[u];
						pre[v] = u;
					}
				}
			}
		}
	}
}
