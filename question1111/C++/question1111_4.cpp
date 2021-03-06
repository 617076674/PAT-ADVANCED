#include<iostream>
#include<vector>

using namespace std;

int N, M, source, destination, INF = 1000000000;	//十字路口数量，道路数量，起点，终点，无穷大数
int lenGraph[510][510], timeGraph[510][510];
int dLen[510], dTime[510];
bool visitedLen[510], visitedTime[510];
vector<int> preLen[510], preTime[510];
vector<int> tempPathLen, tempPathTime;
vector<int> pathLen, pathTime;
int minTime = INF, minCross = INF;

void dijkstraLen(int s);
void dfsLen(int nowVisit);
void dijkstraTime(int s);
void dfsTime(int nowVisit);

int main() {
	fill(visitedLen, visitedLen + 510, false);
	fill(visitedTime, visitedTime + 510, false);
	scanf("%d %d", &N, &M);	//读取十字路口数量和路径数量
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			lenGraph[i][j] = timeGraph[i][j] = INF;
		}
	}
	int V1, V2, one_way, length, time;
	for(int i = 0; i < M; i++) {
		scanf("%d %d %d %d %d", &V1, &V2, &one_way, &length, &time);	//读取每条道路的信息
		lenGraph[V1][V2] = length;
		timeGraph[V1][V2] = time;
		if(one_way != 1) {
			lenGraph[V2][V1] = length;
			timeGraph[V2][V1] = time;
		}
	}
	scanf("%d %d", &source, &destination);
	dijkstraLen(source);
	dfsLen(destination);
	dijkstraTime(source);
	dfsTime(destination);
	if(pathLen == pathTime) {
		printf("Distance = %d; Time = %d:", dLen[destination], dTime[destination]);
		for(int i = pathLen.size() - 1; i >= 0; i--) {
			printf(" %d", pathLen[i]);
			if(i != 0) {
				printf(" ->");
			}
		}
		printf("\n");
	} else {
		printf("Distance = %d:", dLen[destination]);
		for(int i = pathLen.size() - 1; i >= 0; i--) {
			printf(" %d", pathLen[i]);
			if(i != 0) {
				printf(" ->");
			}else{
				printf("\n");
			}
		}
		printf("Time = %d:", dTime[destination]);
		for(int i = pathTime.size() - 1; i >= 0; i--) {
			printf(" %d", pathTime[i]);
			if(i != 0) {
				printf(" ->");
			}else{
				printf("\n");				
			}
		}
	}
	return 0;
}

void dijkstraLen(int s) {
	for(int i = 0; i < N; i++) {
		dLen[i] = INF;
	}
	dLen[s] = 0;
	for(int i = 0; i < N; i++) {
		int u = -1, min = INF;
		for(int j = 0; j < N; j++) {
			if(!visitedLen[j] && dLen[j] < min) {
				min = dLen[j];
				u = j;
			}
		}
		if(u == -1) {
			return;
		}
		visitedLen[u] = true;
		for(int v = 0; v < N; v++) {
			if(!visitedLen[v] && lenGraph[u][v] != INF) {
				if(dLen[u] + lenGraph[u][v] < dLen[v]) {
					dLen[v] = dLen[u] + lenGraph[u][v];
					preLen[v].clear();
					preLen[v].push_back(u);
				} else if(dLen[u] + lenGraph[u][v] == dLen[v]) {
					preLen[v].push_back(u);
				}
			}
		}
	}
}

void dfsLen(int nowVisit) {
	tempPathLen.push_back(nowVisit);
	if(nowVisit == source) {
		int time = 0;
		for(int i = tempPathLen.size() - 1; i > 0; i--) {
			time += timeGraph[tempPathLen[i]][tempPathLen[i - 1]];
		}
		if(time < minTime) {
			pathLen = tempPathLen;
			minTime = time;
		}
		tempPathLen.pop_back();
		return;	//递归终止条件 
	}
	for(int i = 0; i < preLen[nowVisit].size(); i++) {
		dfsLen(preLen[nowVisit][i]);
	}
	tempPathLen.pop_back();
}

void dijkstraTime(int s) {
	for(int i = 0; i < N; i++) {
		dTime[i] = INF;
	}
	dTime[s] = 0;
	for(int i = 0; i < N; i++) {
		int u = -1, min = INF;
		for(int j = 0; j < N; j++) {
			if(!visitedTime[j] && dTime[j] < min) {
				min = dTime[j];
				u = j;
			}
		}
		if(u == -1) {
			return;
		}
		visitedTime[u] = true;
		for(int v = 0; v < N; v++) {
			if(!visitedTime[v] && timeGraph[u][v] != INF) {
				if(dTime[u] + timeGraph[u][v] < dTime[v]) {
					dTime[v] = dTime[u] + timeGraph[u][v];
					preTime[v].clear();
					preTime[v].push_back(u);
				} else if(dTime[u] + timeGraph[u][v] == dTime[v]) {
					preTime[v].push_back(u);
				}
			}
		}
	}
}

void dfsTime(int nowVisit) {
	tempPathTime.push_back(nowVisit);
	if(nowVisit == source) {
		if(tempPathTime.size() < minCross) {
			pathTime = tempPathTime;
			minCross = tempPathTime.size();
		}
		tempPathTime.pop_back();
		return;	//递归终止条件 
	}
	for(int i = 0; i < preTime[nowVisit].size(); i++) {
		dfsTime(preTime[nowVisit][i]);
	}
	tempPathTime.pop_back();
}
