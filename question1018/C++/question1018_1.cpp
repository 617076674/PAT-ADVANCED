#include<iostream>
#include<vector>

using namespace std;

struct node {
	int v;	//�ڵ���
	int time;	//��Ȩ
	node(int _v, int _time) : v(_v), time(_time) {};	//���캯��
};

int Cmax;	//ÿ��վ����������
int N;	//վ������
int Sp;	//Ŀ�ĵ�
int M;	//��·����
int INF = 1000000000;	//�����������
int C[502] = {0};	//���ÿ��վ�㵱ǰ���г�����
vector<node> graph[502];	//����ͼ
bool visited[502] = {false};	//�������
int d[502];	//��¼���·������
vector<int> pre[502];	//��¼ǰһ���ڵ�
vector<int> tempPath;
vector<int> path;
int optValue1 = INF;	//��¼��Ҫ�ṩ�Ĺ������г���������СΪ����
int optValue2 = INF;	//��¼��Ҫ���յĹ������г���������СΪ���� 

void dijkstra(int s);
void dfs(int nowVisit);

int main() {
	cin >> Cmax >> N >> Sp >> M;
	int Ci;
	for(int i = 1; i <= N; i++) {
		cin >> Ci;
		C[i] = Ci;
	}
	int Si, Sj, Tij;
	for(int i = 0; i < M; i++) {
		cin >> Si >> Sj >> Tij;
		graph[Si].push_back(node(Sj, Tij));
		graph[Sj].push_back(node(Si, Tij));
	}
	dijkstra(0);	//PBMC���ڵ�λ��0�ڵ������� 
	dfs(Sp);
	cout << optValue1 << " ";
	for(int i = path.size() - 1; i >= 0; i--) {
		cout << path[i];
		if(i != 0) {
			cout << "->";
		}
	}
	cout << " " << optValue2 << endl;
	return 0;
}

void dijkstra(int s) {
	for(int i = 0; i <= N; i++) {
		d[i] = INF;
	}
	d[s] = 0;
	for(int i = 0; i <= N; i++) {
		int u = -1, min = INF;
		for(int j = 0; j <= N; j++) {
			if(!visited[j] && d[j] < min) {	//j��Ҫ��δ��ǵ�Ԫ�� 
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
			int time = graph[u][j].time;
			if(!visited[v]) {
				if(time + d[u] < d[v]) {
					d[v] = time + d[u];
					pre[v].clear();
					pre[v].push_back(u);
				} else if(time + d[u] == d[v]) {
					pre[v].push_back(u);
				}
			}
		}
	}
}

void dfs(int nowVisit) {
	if(nowVisit == 0) {
		tempPath.push_back(nowVisit);
		int provide = 0, recycle = 0;	//provide��Ҫ�ṩ�Ĺ������г�������recycle��Ҫ���յĹ������г����� 
		for(int i = tempPath.size() - 2; i >= 0; i--){
			if(C[tempPath[i]] - Cmax / 2 >= 0){
				recycle += C[tempPath[i]] - Cmax / 2;
			}else{
				if(recycle >= Cmax / 2 - C[tempPath[i]]){
					recycle -= Cmax / 2 - C[tempPath[i]];
				}else{
					provide += Cmax / 2 - C[tempPath[i]] - recycle;
					recycle = 0;
				}
			} 
		} 
		if(provide < optValue1){
			optValue1 = provide;
			optValue2 = recycle;	//�˴�ҲҪ����optValue2��ֵ 
			path = tempPath;
		}else if(provide == optValue1 && recycle < optValue2){
			optValue2 = recycle;
			path = tempPath;
		}
		tempPath.pop_back();
		return; 	//�����ǵݹ���ֹ������ֱ�ӷ��� 
	}
	tempPath.push_back(nowVisit);
	for(int i = 0; i < pre[nowVisit].size(); i++) {
		dfs(pre[nowVisit][i]);
	}
	tempPath.pop_back();
}
