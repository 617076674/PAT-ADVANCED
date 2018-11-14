#include<iostream>
#include<vector>

using namespace std;

int n;	//城市数量
int m;	//高速公路数量
int k;	//需要检查的城市数量
vector<int> graph[1001];	//无向图
int father[1001];	//并查集数组
bool visited[1001]; //标记数组 

int findFather(int x);
bool isConnected(int x, int y); 
void unionTwo(int x, int y);
void init();

int main(){
	cin >> n >> m >> k;
	int city1, city2;
	for(int i = 0; i < m; i++){
		cin >> city1 >> city2;
		graph[city1 - 1].push_back(city2 - 1);
		graph[city2 - 1].push_back(city1 - 1);
	}
	int city;
	for(int i = 0; i < k; i++){
		cin >> city;
		init();
		for(int j = 0; j < n; j++){
			for(int l = 0; l < graph[j].size(); l++){
				int u = j, v = graph[j][l];
				if(u == city - 1 || v == city - 1){
					continue;
				}
				unionTwo(u, v);
			}
		}
		int count = 0;
		for(int j = 0; j < n; j++){
			if(j == city - 1){
				continue;
			}
			int jFather = findFather(j);
			if(!visited[jFather]){
				count++;
				visited[jFather] = true;
			}
		}
		cout << count - 1 << endl;
	} 
	return 0; 
}

int findFather(int x){
	int a = x;
	while(x != father[x]){
		x = father[x];	
	}
	while(a != father[a]){	//路径压缩 
		int z = a;
		a = father[a];
		father[z] = x;
	}
	return x;
}

bool isConnected(int x, int y){
	int xFather = findFather(x);
	int yFather = findFather(y);
	if(xFather != yFather){
		return false;
	}
	return true;
}

void unionTwo(int x, int y){
	if(!isConnected(x, y)){
		father[father[x]] = father[y];
	}
} 

void init(){
	for(int i = 0; i < n; i++){
		father[i] = i;
		visited[i] = false; 
	}
}
