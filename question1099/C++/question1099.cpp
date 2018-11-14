#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

struct node {
	int data;
	int lchild;
	int rchild;
};

int N;
node Node[100];
vector<int> inOrder;
int index = 0;
vector<int> levelOrder;

void inOrderTraversal(int root);
void levelOrderTraversal(int root);
void print();

int main(){
	cin >> N;
	int left, right;
	for(int i = 0; i < N; i++){
		cin >> left >> right;
		Node[i].lchild = left;
		Node[i].rchild = right;
	}
	int num;
	for(int i = 0; i < N; i++){
		cin >> num;
		inOrder.push_back(num);
	}
	sort(inOrder.begin(), inOrder.end());
	inOrderTraversal(0);
	levelOrderTraversal(0);
	print();
	return 0;
} 

void inOrderTraversal(int root) {
	if(root == -1){
		return;
	}
	inOrderTraversal(Node[root].lchild);
	Node[root].data = inOrder[index++];
	inOrderTraversal(Node[root].rchild);
}

void levelOrderTraversal(int root){
	queue<int> q;
	q.push(root);
	while(!q.empty()){
		int now = q.front();
		levelOrder.push_back(Node[now].data);
		q.pop();
		if(Node[now].lchild != -1){
			q.push(Node[now].lchild);
		}
		if(Node[now].rchild != -1){
			q.push(Node[now].rchild);
		}
	}
}

void print() {
	for(int i = 0; i < levelOrder.size(); i++){
		cout << levelOrder[i];
		if(i != levelOrder.size() - 1){
			cout << " ";
		}
	}
}
