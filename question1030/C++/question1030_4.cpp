#include<iostream>
#include<vector>
#include<queue>
#include<set>

using namespace std;

struct node{
	int v;	//邻接边的顶点编号
	int dis;	//邻接边的边权
	node(int _v, int _dis) : v(_v), dis(_dis) {}	//构造函数 
};

int n;	//城市数量
int m;	//高速公路数量
int s;	//起始城市
int d;	//目的地城市
int INF = 1000000000;	//无穷大数 
vector<node> graph[501];	//无向图
int price[501][501];	//记录两地高速公路间的价格 
set<int> pre[501];	//前一个节点set集合
bool inq[501] = {false};	//记录节点是否在队列中
int num[501] = {0};	//记录每个节点的入队次数 
int distances[501];	//记录最短路径长度
vector<int> path;	//记录最优路径
vector<int> tempPath;	//记录当前路径
int optValue = INF;

bool spfa(int s);
void dfs(int nowVisit); 

int main(){
	cin >> n >> m >> s >> d;
	int city1, city2, distance, cost;
	for(int i = 0; i < m; i++){
		cin >> city1 >> city2 >> distance >> cost;
		graph[city1].push_back(node(city2, distance));
		graph[city2].push_back(node(city1, distance));
		price[city1][city2] = cost;
		price[city2][city1] = cost; 
	}
	spfa(s);
	dfs(d);
	for(int i = path.size() - 1; i >= 0; i--){
		cout << path[i] << " ";
	}
	cout << distances[d] << " " << optValue << endl;
	return 0;
} 

bool spfa(int s){
	for(int i = 0; i < n; i++){
		distances[i] = INF;
	}
	distances[s] = 0;
	queue<int> q;
	q.push(s);
	inq[s] = true; 
	num[s]++;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(int i = 0; i < graph[u].size(); i++){
			int v = graph[u][i].v;
			int dis = graph[u][i].dis;
			if(dis + distances[u] < distances[v]){
				distances[v] = dis + distances[u];
				pre[v].clear();
				pre[v].insert(u);
				if(!inq[v]){
					q.push(v);
					inq[v] = true;
					num[v]++;
					if(num[v] > n - 1){
						return false;
					}
				}
			}else if(dis + distances[u] == distances[v]){
				pre[v].insert(u);
				if(!inq[v]){
					q.push(v);
					inq[v] = true;
					num[v]++;
					if(num[v] > n - 1){
						return false;
					}
				}
			}
		}
	}
	return true;
}

void dfs(int nowVisit){
	if(nowVisit == s){
		tempPath.push_back(nowVisit);
		int value = 0;
		for(int i = tempPath.size() - 1; i > 0; i--){
			value += price[tempPath[i]][tempPath[i - 1]];
		}
		if(value < optValue){
			optValue = value;
			path = tempPath;
		}
		tempPath.pop_back();
		return;
	}
	tempPath.push_back(nowVisit);
	set<int>::iterator it;
	for(it = pre[nowVisit].begin(); it != pre[nowVisit].end(); it++){
		dfs(*it);
	}
	tempPath.pop_back();
}
