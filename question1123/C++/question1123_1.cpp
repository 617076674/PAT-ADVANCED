#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

struct node{
	int data;
	int height;
	int lchild;
	int rchild;
};

int N;
vector<int> input;
node Node[20];
int index = 0;
vector<int> levelOrder;
vector<int> inOrder;

int newNode(int data);
int getHeight(int root);
int getBalanceFactor(int root);
void updateHeight(int root);
void turnLeft(int &root);
void turnRight(int &root);
void insert(int &root, int num);
int create();
void levelOrderTraversal(int root);
void print();
void inOrderTraversal(int root);

int main(){
	cin >> N;
	int num;
	for(int i = 0; i < N; i++){
		cin >> num;
		input.push_back(num);
	}
	int root = create();
	if(root == -1){
		cout << "YES" << endl;
		return 0;
	}
	levelOrderTraversal(root);
	print();
	inOrderTraversal(0);
	for(int i = 0; i < inOrder.size() - 1; i++){
		if(inOrder[i + 1] < inOrder[i]){
			cout << "NO" << endl;
			return 0;
		}
	}
	cout << "YES" << endl;
	return 0; 
}

int newNode(int data){
	int root = index++;
	Node[root].data = data;
	Node[root].height = 1;
	Node[root].lchild = Node[root].rchild = -1;
	return root;
}

int getHeight(int root){
	if(root == -1){
		return 0;
	}
	return Node[root].height;
}

int getBalanceFactor(int root) {
	return getHeight(Node[root].lchild) - getHeight(Node[root].rchild);
}

void updateHeight(int root){
	Node[root].height = max(getHeight(Node[root].lchild), getHeight(Node[root].rchild)) + 1;
}

void turnLeft(int &root) {
	int temp = Node[root].rchild;
	Node[root].rchild = Node[temp].lchild;
	Node[temp].lchild = root;
	updateHeight(root);
	updateHeight(temp);
	root = temp;
}

void turnRight(int &root) {
	int temp = Node[root].lchild;
	Node[root].lchild = Node[temp].rchild;
	Node[temp].rchild = root;
	updateHeight(root);
	updateHeight(temp);
	root = temp;
}

void insert(int &root, int num){
	if(root == -1){
		root = newNode(num);
		return; 
	}
	if(num < Node[root].data){
		insert(Node[root].lchild, num);
		updateHeight(root);
		if(getBalanceFactor(root) == 2){
			if(getBalanceFactor(Node[root].lchild) == 1){
				turnRight(root);
			}else if(getBalanceFactor(Node[root].lchild) == -1){
				turnLeft(Node[root].lchild);
				turnRight(root);
			}
		}
	}else{
		insert(Node[root].rchild, num);
		updateHeight(root);
		if(getBalanceFactor(root) == -2){
			if(getBalanceFactor(Node[root].rchild) == -1){
				turnLeft(root);
			}else if(getBalanceFactor(Node[root].rchild) == 1){
				turnRight(Node[root].rchild);
				turnLeft(root);
			}
		}
	}
}

int create(){
	int root = -1;
	for(int i = 0; i < N; i++){
		insert(root, input[i]);
	}
	return root;
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

void print(){
	for(int i = 0; i < levelOrder.size(); i++){
		cout << levelOrder[i];
		if(i != levelOrder.size() - 1){
			cout << " ";
		}
	}
	cout << endl;
}

void inOrderTraversal(int root){
	if(root >= levelOrder.size()){
		return;
	}
	inOrderTraversal(root * 2 + 1);
	inOrder.push_back(levelOrder[root]);
	inOrderTraversal(root * 2 + 2);
}
