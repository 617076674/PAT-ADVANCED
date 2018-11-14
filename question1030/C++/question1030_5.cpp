#include<iostream>
#include<vector>

using namespace std;

struct node {
	int v;
	int distance;
	int cost;
	node(int _v, int _distance, int _cost) : v(_v), distance(_distance), cost(_cost) {};
};

int N;
int M;
int S;
int D;
int INF = 1000000000;
vector<node> graph[500];
bool visited[500] = {false};
int d[500];
vector<int> pre[500];
vector<int> path;
vector<int> tempPath;
int minCost = INF;

void dijkstra(int s);
void dfs(int nowVisit);

int main(){
	cin >> N >> M >> S >> D;
	int city1, city2, distance, cost;
	for(int i = 0; i < M; i++){
		cin >> city1 >> city2 >> distance >> cost;
		graph[city1].push_back(node(city2, distance, cost));
		graph[city2].push_back(node(city1, distance, cost));
	}
	dijkstra(S);
	dfs(D);
	for(int i = path.size() - 1; i >= 0; i--){
		cout << path[i] << " ";
	}
	cout << d[D] << " " << minCost << endl;
	return 0; 
} 

void dijkstra(int s){
	for(int i = 0; i < N; i++){
		d[i] = INF;
	}
	d[s] = 0;
	for(int i = 0; i < N; i++){
		int u = -1, min = INF;
		for(int j = 0; j < N; j++){
			if(!visited[j] && d[j] < min){
				min = d[j];
				u = j;
			}
		}
		if(u == -1){
			return;
		}
		visited[u] = true;
		for(int j = 0; j < graph[u].size(); j++){
			int v = graph[u][j].v;
			int distance = graph[u][j].distance;
			if(!visited[v]){
				if(d[u] + distance < d[v]){
					d[v] = d[u] + distance;
					pre[v].clear();
					pre[v].push_back(u);
				}else if(d[u] + distance == d[v]){
					pre[v].push_back(u);
				}
			}
		}
	}
}

void dfs(int nowVisit){
	tempPath.push_back(nowVisit);
	if(nowVisit == S){
		int value = 0;
		for(int i = tempPath.size() - 1; i > 0; i--){
			for(int j = 0; j < graph[tempPath[i]].size(); j++){	//用邻接表实现求边权时需要遍历其所有邻边 
				if(graph[tempPath[i]][j].v == tempPath[i - 1]){
					value += graph[tempPath[i]][j].cost;
					break;
				}
			}
		}
		if(value < minCost){
			minCost = value;
			path = tempPath;
		}
		tempPath.pop_back();
		return;
	} 
	for(int i = 0; i < pre[nowVisit].size(); i++){
		dfs(pre[nowVisit][i]);
	}
	tempPath.pop_back();
}
