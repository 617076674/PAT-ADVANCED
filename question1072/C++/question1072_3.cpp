#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<queue>

using namespace std;

struct node {
	int v;	//节点编号
	int len;	//道路长度
	node(int _v, int _len) : v(_v), len(_len) {}	//构造函数
};

int N;	//房子数量
int M;	//加油站数量
int K;	//道路数量
int Ds;	//加油站服务范围
int INF = 1000000000;	//无穷大数
vector<node> graph[1020]; //无向图，房子的编号为1 ~ N，加油站的编号为N + 1 ~ N + M
int d[1020];	//记录最短长度
bool inq[1020];
int countInq[1020];

int totalDistance();
bool validPosition();
int minDistance();
void init();
int change(string s);
bool spfa(int s);

int main() {
	cin >> N >> M >> K >> Ds;
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
		spfa(i);
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
	if(result == 0) {
		cout << "No Solution" << endl;
		return 0;
	}
	cout << "G" << result - N << endl;
	double average = minTotalLen * 10.0 / N;
	int averageResult = minTotalLen * 10 / N;
	if(average - averageResult >= 0.5) {
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
		inq[i] = false;
		countInq[i] = 0; 
	}
}

int change(string s) {
	if(s[0] == 'G') {
		if(s.length() == 3) {
			return 10 + N;
		} else {
			int num = s[1] - '0';
			return num + N;
		}
	} else {
		stringstream ss;
		ss << s;
		int result;
		ss >> result;
		return result;
	}
}

bool spfa(int s) {
	init();
	d[s] = 0;
	queue<int> q;
	q.push(s);
	inq[s] = true;
	countInq[s]++;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		inq[u] = false;
		for(int j = 0; j < graph[u].size(); j++){
			int v = graph[u][j].v;
			int len = graph[u][j].len;
			if(len + d[u] < d[v]){
				d[v] = len + d[u];
				if(!inq[v]){
					q.push(v);
					inq[v] = true;
					countInq[v]++;
					if(countInq[v] > M + N){
						return false;
					}
				}
			}
		}
	}
	return true;
}
