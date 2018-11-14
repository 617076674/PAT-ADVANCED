#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct node {
	int num;
	int weight;
	vector<int> child;
};

int N;	//节点个数 
int M;	//非叶子节点个数 
int S;	//路径权值 
node Node[100];	//建立一个大小为结点上限个数的node型数组
vector<int> path;	//存放路径 

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
		sort(Node[ID].child.begin(), Node[ID].child.end(), cmp);	//对每个节点的子节点进行排序 
	}
	dfs(0, 0);	//从0节点开始深度优先遍历 
	return 0;
}

bool cmp(int a, int b){
	return Node[a].weight > Node[b].weight;	//用大于等于号会出现段错误 
}

void dfs(int nowVisit, int sum){
	path.push_back(nowVisit);
	if(sum + Node[nowVisit].weight > S){
		path.pop_back();
		return;
	}
	if(sum + Node[nowVisit].weight == S){
		if(Node[nowVisit].child.size() == 0){	//判断当前节点是否是叶子节点 
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
