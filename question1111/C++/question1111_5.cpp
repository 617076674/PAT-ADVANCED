#include<iostream>
#include<vector>
#include<set>

using namespace std;

int N, M, source, destination, INF = 1000000000;	//十字路口数量，道路数量，起点，终点，无穷大数
int lenGraph[510][510], timeGraph[510][510];
int dLen[510], dTime[510];
set<int> preLen[510], preTime[510];
vector<int> tempPathLen, tempPathTime;
vector<int> pathLen, pathTime;
int minTime = INF, minCross = INF;

bool bellmanFordLen(int s);
void dfsLen(int nowVisit);
bool bellmanFordTime(int s);
void dfsTime(int nowVisit);

int main() {
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
	bellmanFordLen(source);
	dfsLen(destination);
	bellmanFordTime(source);
	dfsTime(destination);
	if(pathLen == pathTime) {
		printf("Distance = %d; Time = %d:", dLen[destination], dTime[destination]);
		for(int i = pathLen.size() - 1; i >= 0; i--) {
			printf(" %d", pathLen[i]);
			if(i != 0) {
				printf(" ->");
			}else{
				printf("\n");
			}
		}
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

bool bellmanFordLen(int s) {
	for(int i = 0; i < N; i++) {
		dLen[i] = INF;
	}
	dLen[s] = 0;
	for(int i = 0; i < N - 1; i++) {
		for(int u = 0; u < N; u++) {
			for(int v = 0; v < N; v++) {
				if(lenGraph[u][v] != INF) {
					if(dLen[u] + lenGraph[u][v] < dLen[v]) {
						dLen[v] = dLen[u] + lenGraph[u][v];
						preLen[v].clear();
						preLen[v].insert(u);
					} else if(dLen[u] + lenGraph[u][v] == dLen[v]) {
						preLen[v].insert(u);
					}
				}
			}
		}
	}
	for(int u = 0; u < N; u++) {
		for(int v = 0; v < N; v++) {
			if(lenGraph[u][v] != INF) {
				if(dLen[u] + lenGraph[u][v] < dLen[v]) {
					return false;
				}
			}
		}
	}
	return true;
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
		return;
	}
	for(set<int>::iterator it = preLen[nowVisit].begin(); it != preLen[nowVisit].end(); it++){
		dfsLen(*it);
	}
	tempPathLen.pop_back();
}

bool bellmanFordTime(int s) {
	for(int i = 0; i < N; i++) {
		dTime[i] = INF;
	}
	dTime[s] = 0;
	for(int i = 0; i < N - 1; i++) {
		for(int u = 0; u < N; u++) {
			for(int v = 0; v < N; v++) {
				if(timeGraph[u][v] != INF) {
					if(dTime[u] + timeGraph[u][v] < dTime[v]) {
						dTime[v] = dTime[u] + timeGraph[u][v];
						preTime[v].clear();
						preTime[v].insert(u);
					} else if(dTime[u] + timeGraph[u][v] == dTime[v]) {
						preTime[v].insert(u);
					}
				}
			}
		}
	}
	for(int u = 0; u < N; u++) {
		for(int v = 0; v < N; v++) {
			if(lenGraph[u][v] != INF) {
				if(dLen[u] + lenGraph[u][v] < dLen[v]) {
					return false;
				}
			}
		}
	}
	return true;
}

void dfsTime(int nowVisit) {
	tempPathTime.push_back(nowVisit);
	if(nowVisit == source) {
		if(tempPathTime.size() < minCross) {
			pathTime = tempPathTime;
			minCross = tempPathTime.size();
		}
		tempPathTime.pop_back();
		return;
	}
	for(set<int>::iterator it = preTime[nowVisit].begin(); it != preTime[nowVisit].end(); it++){
		dfsTime(*it);
	}
	tempPathTime.pop_back();
}
