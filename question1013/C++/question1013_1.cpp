#include<iostream>
#include<vector>

using namespace std;

int n;	//城市数量
int m;	//高速公路数量
int k;	//需要检查的城市数量
int graph[1001][1001] = {0};	//无向图
bool visited[1001]; 

void dfs(int nowVisit, int city);

int main(){
	cin >> n >> m >> k;
	int city1, city2;
	for(int i = 0; i < m; i++){
		cin >> city1 >> city2;
		graph[city1 - 1][city2 - 1] = 1;
		graph[city2 - 1][city1 - 1] = 1;
	}
	int city;
	for(int i = 0; i < k; i++){
		cin >> city;
		int count = 0;
		for(int j = 0; j < n; j++){
			visited[j] = false;
		}
		for(int j = 0; j < n; j++){
			if(j == city - 1){
				continue;
			}
			if(!visited[j]){
				dfs(j, city);
				count++;
			}
		}
		cout << count - 1 << endl;
	} 
}

void dfs(int nowVisit, int city){
	visited[nowVisit] = true;
	for(int i = 0; i < n; i++){
		if(i != city - 1 && !visited[i] && graph[i][nowVisit] != 0){
			dfs(i, city);
		}
	}
}
