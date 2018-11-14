#include<iostream>
#include<queue>

using namespace std;

int n;	//城市数量
int m;	//道路数量
int c1;	//起点
int c2;	//终点 
int graph[501][501];	//无向图 
int teams[501] = {0};	//急救队数量 
int d[501];	//d[i]表示从起点c1到达点i的最短路径长度 
int num[501];	//num[i]表示从起点c1到达点i的最短路径条数
int weight[501];	//weight[i]表示从起点c1到达点i所能搜集到的最大急救队数量 
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
	d[s] = 0;	//起点s到达自身的距离为0
	for(int i = 0; i < n; i++){
		int u = -1, min = 1000000000;
		for(int j = 0; j < n; j++){	//寻找未访问的顶点中d[]最小的 
			if(!visited[j] && d[j] < min){
				u = j;
				min = d[j];
			}
		}
		if(u == -1){	//找不到小于1000000000的d[u]，说明剩下的顶点和起点不连通 
			return;
		}	
		visited[u] = true;
		for(int j = 0; j < n; j++){
			if(!visited[j] && graph[u][j] != 1000000000){
				if(d[u] + graph[u][j] < d[j]){
					d[j] = d[u] + graph[u][j];	//优化d[v]
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

