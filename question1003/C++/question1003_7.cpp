#include<iostream>
#include<queue>
#include<set>
#include<vector>

using namespace std;

struct node{
	int v;
	int length;
	node(int _v, int _length){
		v = _v;
		length = _length;
	}
};

int N, M, C1, C2, INF = 1000000000, teams[500], d[500], countInq[500], count = 0, maxTeams = 0, city1, city2, length;
vector<node> graph[500];
bool inq[500];
set<int> pre[500];
vector<int> tempPath;

bool spfa(int s);
void dfs(int nowVisit);

int main(){
	scanf("%d %d %d %d", &N, &M, &C1, &C2);
	for(int i = 0; i < N; i++){
		scanf("%d", &teams[i]);
	}
	for(int i = 0; i < M; i++){
		scanf("%d %d %d", &city1, &city2, &length);
		graph[city1].push_back(node(city2, length));
		graph[city2].push_back(node(city1, length));
	}
	spfa(C1);
	dfs(C2);
	printf("%d %d\n", count, maxTeams);
	return 0;
}

bool spfa(int s){
	fill(d, d + N, INF);
	fill(countInq, countInq + N, 0);
	fill(inq, inq + N, false);
	d[s] = 0;
	queue<int> q;
	q.push(s);
	countInq[s]++;
	inq[s] = true;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(int j = 0; j < graph[u].size(); j++){
			int v = graph[u][j].v;
			int length = graph[u][j].length;
			if(d[u] + length < d[v]){
				d[v] = d[u] + length;
				pre[v].clear();
				pre[v].insert(u);
				if(!inq[v]){
					q.push(v);
					inq[v] = true;
					countInq[v]++;
					if(countInq[v] > N - 1){
						return false;
					}
				}
			}else if(d[u] + length == d[v]){
				pre[v].insert(u);
				if(!inq[v]){
					q.push(v);
					inq[v] = true;
					countInq[v]++;
					if(countInq[v] > N - 1){
						return false;
					}
				}
			}
		}
	}
	return true;
}

void dfs(int nowVisit){
	tempPath.push_back(nowVisit);
	if(nowVisit == C1){
		count++;
		int countTeams = 0;
		for(int i = 0; i < tempPath.size(); i++){
			countTeams += teams[tempPath[i]];
		}
		if(countTeams > maxTeams){
			maxTeams = countTeams;
		}
		tempPath.pop_back();
		return;
	}
	for(set<int>::iterator it = pre[nowVisit].begin(); it != pre[nowVisit].end(); it++){
		dfs(*it);
	}
	tempPath.pop_back();
}
