#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct node {
	int num;
	int weight;
	vector<int> child;
};

int N;	//�ڵ���� 
int M;	//��Ҷ�ӽڵ���� 
int S;	//·��Ȩֵ 
node Node[100];	//����һ����СΪ������޸�����node������
vector<int> path;	//���·�� 

bool cmp(int a, int b);
void dfs(int nowVisit, int sum); 
void printPath();

int main(){
	cin >> N >> M >> S;
	for(int i = 0; i < N; i++){
		cin >> Node[i].weight;
	}
	int ID, K, childID;
	for(int i = 0; i < M; i++){
		cin >> ID >> K;
		for(int j = 0; j < K; j++){
			cin >> childID;
			Node[ID].child.push_back(childID);
		}
		sort(Node[ID].child.begin(), Node[ID].child.end(), cmp);	//��ÿ���ڵ���ӽڵ�������� 
	}
	dfs(0, 0);	//��0�ڵ㿪ʼ������ȱ��� 
	return 0;
}

bool cmp(int a, int b){
	return Node[a].weight > Node[b].weight;	//�ô��ڵ��ںŻ���ֶδ��� 
}

void dfs(int nowVisit, int sum){
	path.push_back(nowVisit);
	if(sum + Node[nowVisit].weight > S){
		path.pop_back();
		return;
	}
	if(sum + Node[nowVisit].weight == S){
		if(Node[nowVisit].child.size() == 0){	//�жϵ�ǰ�ڵ��Ƿ���Ҷ�ӽڵ� 
			printPath();
		}
		path.pop_back();
		return;
	}
	for(int i = 0; i < Node[nowVisit].child.size(); i++){
		dfs(Node[nowVisit].child[i], sum + Node[nowVisit].weight);
	}
	path.pop_back();
}

void printPath(){
	for(int i = 0; i < path.size(); i++){
		cout << Node[path[i]].weight;
		if(i != path.size() - 1){
			cout << " ";
		}
	}
	cout << endl;
}
