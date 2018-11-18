#include<iostream>
#include<vector>
#include<set>
#include<queue>

using namespace std;

int N, M, source, destination, INF = 1000000000;	//十字路口数量，道路数量，起点，终点，无穷大数
int lenGraph[510][510], timeGraph[510][510];
int dLen[510], dTime[510];
set<int> preLen[510], preTime[510];
vector<int> tempPathLen, tempPathTime;
vector<int> pathLen, pathTime;
int minTime = INF, minCross = INF;
bool inqLen[510], inqTime[510];
int countInqLen[510], countInqTime[510];

bool spfaLen(int s);
void dfsLen(int nowVisit);
bool spfaTime(int s);
void dfsTime(int nowVisit);

int main() {
	fill(inqLen, inqLen + 510, false);
	fill(inqTime, inqTime + 510, false);
	fill(countInqLen, countInqLen + 510, false);
	fill(countInqTime, countInqTime + 510, false);
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
	spfaLen(source);
	dfsLen(destination);
	spfaTime(source);
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

bool spfaLen(int s) {
	for(int i = 0; i < N; i++) {
		dLen[i] = INF;
	}
	dLen[s] = 0;
	queue<int> q;
	q.push(s);
	inqLen[s] = true;
	countInqLen[s]++;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inqLen[u] = false;
		for(int v = 0; v < N; v++) {
			if(lenGraph[u][v] != INF) {
				if(dLen[u] + lenGraph[u][v] < dLen[v]) {
					dLen[v] = dLen[u] + lenGraph[u][v];
					preLen[v].clear();
					preLen[v].insert(u);
					if(!inqLen[v]){
						q.push(v);
						inqLen[v] = true;
						countInqLen[v]++;
						if(countInqLen[v] > N - 1){
							return false;
						}
					}
				}else if(dLen[u] + lenGraph[u][v] == dLen[v]) {
					preLen[v].insert(u);
					if(!inqLen[v]){
						q.push(v);
						inqLen[v] = true;
						countInqLen[v]++;
						if(countInqLen[v] > N - 1){
							return false;
						}
					}
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
		return;	//递归终止条件 
	}
	for(set<int>::iterator it = preLen[nowVisit].begin(); it != preLen[nowVisit].end(); it++) {
		dfsLen(*it);
	}
	tempPathLen.pop_back();
}

bool spfaTime(int s) {
	for(int i = 0; i < N; i++) {
		dTime[i] = INF;
	}
	dTime[s] = 0;
	queue<int> q;
	q.push(s);
	inqTime[s] = true;
	countInqTime[s]++;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		inqTime[u] = false;
		for(int v = 0; v < N; v++) {
			if(timeGraph[u][v] != INF) {
				if(dTime[u] + timeGraph[u][v] < dTime[v]) {
					dTime[v] = dTime[u] + timeGraph[u][v];
					preTime[v].clear();
					preTime[v].insert(u);
					if(!inqTime[v]){
						q.push(v);
						inqTime[v] = true;
						countInqTime[v]++;
						if(countInqTime[v] > N - 1){
							return false;
						}
					}
				}else if(dTime[u] + timeGraph[u][v] == dTime[v]) {
					preTime[v].insert(u);
					if(!inqTime[v]){
						q.push(v);
						inqTime[v] = true;
						countInqTime[v]++;
						if(countInqTime[v] > N - 1){
							return false;
						}
					}
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
		return;	//递归终止条件 
	}
	for(set<int>::iterator it = preTime[nowVisit].begin(); it != preTime[nowVisit].end(); it++) {
		dfsTime(*it);
	}
	tempPathTime.pop_back();
}
