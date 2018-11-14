#include<iostream>
#include<vector>
#include<map>
#include<string>

using namespace std;

struct node {
	int v;	//�ڵ���
	int cost;	//��Ȩֵ
	node(int _v, int _cost) : v(_v), cost(_cost) {}	//���캯��
};

int N;	//��������
int K;	//��·����
int INF = 1000000000;	//������� 
string start;	//��ʼ���������
int happy[201];	//��Ÿ������еĿ���ֵ
map<string, int> stringToInt;	//��������->���
map<int, string> intToString; 	//���->��������
vector<node> graph[201];	//����ͼ
int d[201];	//��¼����ʼ���е����i�����ٻ���ֵ 
bool visited[201];	//�������
vector<int> pre[201];	//��¼ǰһ���ڵ� 
vector<int> path;
vector<int> tempPath;
int optHappy = 0;
double optAverageHappy = 0.0;
int count = 0;	//��¼���·������ 

void dijkstra(int s);
void dfs(int nowVisit);

int main() {
	cin >> N >> K >> start;
	stringToInt[start] = 0;	//��ʼ���б��Ϊ0
	intToString[0] = start;
	string city;
	int happyness;
	for(int i = 1; i <= N - 1; i++) {
		cin >> city >> happyness;
		stringToInt[city] = i;
		intToString[i] = city;
		happy[i] = happyness;
	}
	string city1, city2;
	int cost;
	for(int i = 0; i < K; i++) {
		cin >> city1 >> city2 >> cost;
		int id1 = stringToInt[city1];
		int id2 = stringToInt[city2];
		graph[id1].push_back(node(id2, cost));
		graph[id2].push_back(node(id1, cost));
	}
	int destination = stringToInt["ROM"];
	dijkstra(0);
	dfs(destination);
	cout << count << " " << d[destination] << " " << optHappy << " " << (int)optAverageHappy << endl;
	for(int i = path.size() - 1; i >= 0; i--){
		cout << intToString[path[i]];
		if(i != 0){
			cout << "->";
		}
	}
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
			int cost = graph[u][j].cost;
			if(!visited[v]){
				if(d[u] + cost < d[v]){
					d[v] = d[u] + cost;
					pre[v].clear();
					pre[v].push_back(u);
				}else if(d[u] + cost == d[v]){
					pre[v].push_back(u);
				}
			}
		}
	}
} 

void dfs(int nowVisit){
	if(nowVisit == 0){
		count++;
		tempPath.push_back(nowVisit);
		int happyValue = 0;
		for(int i = tempPath.size() - 2; i >= 0; i--){
			happyValue += happy[tempPath[i]];
		}
		double averageHappyValue = 1.0 * happyValue / (tempPath.size() - 1);
		if(happyValue > optHappy){
			optHappy = happyValue;
			optAverageHappy = averageHappyValue;	//Ҳ��Ҫ����optAverageHappy��ֵ 
			path = tempPath;
		}else if(happyValue == optHappy && averageHappyValue > optAverageHappy){
			optAverageHappy = averageHappyValue;
			path = tempPath;
		}
		tempPath.pop_back();
		return;
	} 
	tempPath.push_back(nowVisit);
	for(int i = 0; i < pre[nowVisit].size(); i++){
		dfs(pre[nowVisit][i]);
	}
	tempPath.pop_back();
} 
