#include<iostream>
#include<vector>
#include<set>
#include<queue>

using namespace std;

struct node {
	int v;	//�ڵ���
	int time;	//��Ȩֵ
	node(int _v, int _time) : v(_v), time(_time) {};	//���캯��
};

int Cmax;	//ÿվ�������
int N;	//��վ��
int Sp;	//Ŀ�ĵ�
int M;	//��·����
int INF = 1000000000;	//�������
int C[502];	//ÿվ���й������г�����
vector<node> graph[502];	//����ͼ
int d[502];	//�洢���·������
set<int> pre[502]; 	//��¼ǰһ�ڵ�
vector<int> path;
vector<int> tempPath;
int optValue1 = INF;
int optValue2 = INF;
bool inq[502] = {false};	//��ǽڵ��Ƿ��ڶ�����
int countInq[502] = {0};	//��¼�ڵ����Ӵ��� 

bool spfa(int s);
void dfs(int nowVisit);

int main() {
	cin >> Cmax >> N >> Sp >> M;
	for(int i = 1; i <= N; i++) {
		cin >> C[i];
	}
	int Si, Sj, Tij;
	for(int i = 0; i < M; i++) {
		cin >> Si >> Sj >> Tij;
		graph[Si].push_back(node(Sj, Tij));
		graph[Sj].push_back(node(Si, Tij));
	}
	spfa(0);
	dfs(Sp);
	cout << optValue1 << " ";
	for(int i = path.size() - 1; i >= 0; i--){
		cout << path[i];
		if(i != 0){
			cout << "->";
		}
	}
	cout << " " << optValue2 << endl;
	return 0;
}

bool spfa(int s) {
	for(int i = 0; i <= N; i++){
		d[i] = INF;
	}
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
			int time = graph[u][j].time;
			if(d[u] + time < d[v]){
				d[v] = d[u] + time;
				pre[v].clear();
				pre[v].insert(u);
				if(!inq[v]){
					q.push(v);
					inq[v] = true;
					countInq[v]++;
					if(countInq[v] >= N + 1){
						return false;
					}
				}
			}else if(d[u] + time == d[v]){
				pre[v].insert(u);
				if(!inq[v]){
					q.push(v);
					inq[v] = true;
					countInq[v]++;
					if(countInq[v] >= N + 1){
						return false;
					}
				}
			}
		}
	}
	return true; 
}

void dfs(int nowVisit){
	if(nowVisit == 0){
		tempPath.push_back(nowVisit);
		int provide = 0, recycle = 0;
		for(int i = tempPath.size() - 2; i >= 0; i--){
			if(C[tempPath[i]] - Cmax / 2 >= 0){
				recycle += C[tempPath[i]] - Cmax / 2;
			}else{
				if(recycle >= -C[tempPath[i]] + Cmax / 2){
					recycle -= -C[tempPath[i]] + Cmax / 2;
				}else{
					provide += -C[tempPath[i]] + Cmax / 2 - recycle;
					recycle = 0;
				}
			}
		}
		if(provide < optValue1){
			optValue1 = provide;
			optValue2 = recycle;
			path = tempPath;
		}else if(provide = optValue1 && recycle < optValue2){
			optValue2 = recycle;
			path = tempPath;
		}
		tempPath.pop_back();
		return;
	}
	tempPath.push_back(nowVisit);
	set<int>::iterator it;
	for(it = pre[nowVisit].begin(); it != pre[nowVisit].end(); it++){
		dfs(*it);
	}
	tempPath.pop_back();
}
