#include<iostream>
#include<vector>

using namespace std;

struct node {
	vector<int> child;
};

int N;
int M;
node Node[101];
int count[101] = {0};	//第i层有count[i]个成员

void dfs(int nowVisit, int level); 

int main(){
	cin >> N >> M;
	int ID, K, num;
	for(int i = 0; i < M; i++){
		cin >> ID >> K;
		for(int j = 0; j < K; j++){
			cin >> num;
			Node[ID].child.push_back(num); 
		}
	}
	dfs(1, 1);
	int maxGeneration = 0;
	for(int i = 1; i <= N; i++){
		if(count[i] > count[maxGeneration]){
			maxGeneration = i;
		}
	}
	cout << count[maxGeneration] << " " << maxGeneration << endl;
	return 0;
}

void dfs(int nowVisit, int level){
	count[level]++;
	if(Node[nowVisit].child.size() == 0){
		return;
	}
	for(int i = 0; i < Node[nowVisit].child.size(); i++){
		dfs(Node[nowVisit].child[i], level + 1);
	}
}
