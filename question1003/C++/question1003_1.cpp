#include<iostream>
#include<queue>

using namespace std;

int n, m, c1, c2, INF = 1000000000;	//城市数量，道路数量，起点，终点，无穷大数 
int graph[501][501];	//无向图 
int teams[501];	//急救队数量 
int d[501];	//d[i]表示从起点c1到达点i的最短路径长度 
int num[501];	//num[i]表示从起点c1到达点i的最短路径条数
int weight[501];	//weight[i]表示从起点c1到达点i所能搜集到的最大急救队数量 
bool visited[501];	//dijkstra算法的标记数组，用以标记该位置是否已被访问 

void dijkstra(int s); 

int main(){
	scanf("%d %d %d %d", &n, &m, &c1, &c2);	//读取城市数量，道路数量，起点，终点 
	fill(visited, visited + 501, false);	//初始化该标记数组全部为false，所有节点均未被访问 
	for(int i = 0; i < n; i++){	
		for(int j = 0; j < n; j++){
			graph[i][j] = INF;	//初始化图，任意两点的距离都为无穷大，即图中不存在任何路径 
		}
	}
	for(int i = 0; i < n; i++){
		scanf("%d", &teams[i]); //读取每个城市急救队数量 
	}
	int city1, city2, len;
	for(int i = 0; i < m; i++){
		scanf("%d %d %d", &city1, &city2, &len);
		graph[city1][city2] = graph[city2][city1] = len;	//读取城市间的路径信息 
	}
	dijkstra(c1);	//以c1为起点利用dijkstra算法求到其余点的最短距离 
	printf("%d %d\n", num[c2], weight[c2]);	//输出结果 
	return 0;
}

void dijkstra(int s){
	fill(d, d + 501, INF);	//初始化源点s到其余点的最短距离均为无穷大 
	fill(num, num + 501, 0);	//初始化起点s到达其余点的最短路径条数均为0条 
	fill(weight, weight + 501, 0);	//初始化从起点s到达其余点所能搜集到的最大急救队数量均为0 
	weight[s] = teams[s];	//起点s到达其自身所能搜集到的急救队数量就是其自身拥有的急救队数量 
	num[s] = 1;	//起点s到达其自身的最短路径条数为1 
	d[s] = 0;	//起点s到达自身的距离为0
	for(int i = 0; i < n; i++){
		int u = -1, min = INF;
		for(int j = 0; j < n; j++){	//寻找未访问的顶点中d[]最小的 
			if(!visited[j] && d[j] < min){
				u = j;
				min = d[j];
			}
		}
		if(u == -1){	//找不到小于INF的d[u]，说明剩下的顶点和起点不连通 
			return;
		}	
		visited[u] = true;	//将该最小的d[u]的u点标记为已被访问过 
		for(int j = 0; j < n; j++){
			if(!visited[j] && graph[u][j] != INF){	//如果j未被访问过且u与j之间有路径 
				if(d[u] + graph[u][j] < d[j]){	//如果通过u点到达j比直接到达j要更小 
					d[j] = d[u] + graph[u][j];	//优化d[v]
					weight[j] = weight[u] + teams[j];	//到达j点救援队的数量等于到达u点救援队的数量加上j点自身救援队的数量 
					num[j] = num[u];	//到达j点的最短路径条数等于到达u点的最短路径条数 
				}else if(d[u] + graph[u][j] == d[j]){	//如果通过u点到达j与直接到达j点的路径相等 
					if(weight[u] + teams[j] > weight[j]){	//如果通过u点到达j点所能搜集到的急救队数量更多 
						weight[j] = weight[u] + teams[j];	//更新到达j点的最大急救队数量 
					}
					num[j] += num[u];	//到达j点的最短路径条数需要加上到达u点的最短路径条数 
				}  
			}
		}
	} 
} 

