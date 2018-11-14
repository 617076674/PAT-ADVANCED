#include<iostream>
#include<vector>
#include<queue> 

using namespace std;

struct node {
	int num;
	vector<int> child;
};

int N;	//节点总数
int M;	//非叶子节点数
node Node[100];
vector<int> leaves;	//存放每一层的叶子节点数 

void levelTraversal(int root); 

int main(){
	cin >> N >> M;
	int ID, K, childID;
	for(int i = 0; i < M; i++){
		cin >> ID >> K;
		for(int j = 0; j < K; j++){
			cin >> childID;
			Node[ID].child.push_back(childID);
		}
	}
	levelTraversal(1);
	for(int i = 0; i < leaves.size(); i++){
		cout << leaves[i];
		if(i != leaves.size() - 1){
			cout << " ";
		}
	}
	cout << endl;
	return 0; 
}

void levelTraversal(int root){
	queue<int> q;
	q.push(root);
	while(!q.empty()){
		int qSize = q.size();
		int levelLeaves = 0;
		for(int i = 0; i < qSize; i++){
			int now = q.front();
			q.pop();
			if(Node[now].child.size() == 0){
				levelLeaves++;
			}
			for(int j = 0; j < Node[now].child.size(); j++){
				q.push(Node[now].child[j]);
			}
		}
		leaves.push_back(levelLeaves);
	} 
} 
