#include<iostream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;

struct node {
	int v;	//节点编号
	int len;	//道路长度
	node(int _v, int _len) : v(_v), len(_len) {}	
};

int N, M, K, Ds, INF = 1000000000;	//房子数量，加油站数量，道路数量，加油站服务范围，无穷大数 
vector<node> graph[1020]; //无向图，房子的编号为1 ~ N，加油站的编号为N + 1 ~ N + M
int d[1020];	//记录最短长度
bool visited[1020];	//标记数组

int totalDistance();
bool validPosition();
int minDistance();
void init();
int change(string s);
void dijkstra(int s);

int main() {
	scanf("%d %d %d %d", &N, &M, &K, &Ds); 
	string P1, P2;
	int Dist;
	for(int i = 0; i < K; i++) {
		cin >> P1 >> P2 >> Dist;
		int id1 = change(P1);
		int id2 = change(P2);
		graph[id1].push_back(node(id2, Dist));
		graph[id2].push_back(node(id1, Dist));
	}
	int minLen = 0;
	int minTotalLen = INF;
	int result = 0;
	for(int i = N + 1; i <= N + M; i++) {
		dijkstra(i);
		if(validPosition()) {
			if(minDistance() > minLen) {
				result = i;
				minLen = minDistance();
				minTotalLen = totalDistance();	//此处也要更新minTotalLen 
			} else if(minDistance() == minLen) {
				if(minTotalLen > totalDistance()) {
					result = i;
					minTotalLen = totalDistance();
				}
			}
		}
	}
	if(result == 0){
		cout << "No Solution" << endl;
		return 0;
	}
	cout << "G" << result - N << endl;
	double average = minTotalLen * 10.0 / N;
	int averageResult = minTotalLen * 10 / N;
	if(average - averageResult >= 0.5){
		averageResult++;
	}
	printf("%.1lf %.1lf\n", minLen * 1.0, averageResult * 1.0 / 10);
	return 0;
}

int totalDistance() {
	int sum = 0;
	for(int i = 1; i <= N; i++) {
		sum += d[i];
	}
	return sum;
}

bool validPosition() {
	for(int i = 1; i <= N; i++) {
		if(d[i] > Ds) {
			return false;
		}
	}
	return true;
}

int minDistance() {
	int min = 1;
	for(int i = 2; i <= N; i++) {
		if(d[i] < d[min]) {
			min = i;
		}
	}
	return d[min];
}

void init() {
	for(int i = 1; i <= N + M; i++) {
		d[i] = INF;
		visited[i] = false;
	}
}

int change(string s) {
	if(s[0] == 'G'){
		if(s.length() == 3){
			return 10 + N;
		}else{
			int num = s[1] - '0';
			return num + N;
		}
	}else{
		stringstream ss;
		ss << s;
		int result;
		ss >> result;
		return result;
	}
}

void dijkstra(int s) {
	init();
	d[s] = 0;
	for(int i = 0; i < N + M; i++) {
		int u = -1, min = INF;
		for(int j = 1; j <= N + M; j++) {
			if(!visited[j] && min > d[j]) {
				min = d[j];
				u = j;
			}
		}
		if(u == -1) {
			return;
		}
		visited[u] = true;
		for(int j = 0; j < graph[u].size(); j++) {
			int v = graph[u][j].v;
			int len = graph[u][j].len;
			if(!visited[v]) {
				if(d[u] + len < d[v]) {
					d[v] = d[u] + len;
				}
			}
		}
	}
}
