#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct node {
	int data;
	int height;
	int lchild;
	int rchild;
};

int N;
vector<int> input;
node Node[20];
int index = 0;

int newNode(int num);
int getHeight(int root);
int getBalanceFactor(int root);
void updateHeight(int root);
void leftTurn(int &root);
void rightTurn(int &root);
void insert(int &root, int num);
int create();

int main(){
	cin >> N;
	int num;
	for(int i = 0; i < N; i++){
		cin >> num;
		input.push_back(num);
	}
	int root = create();
	cout << Node[root].data << endl;
	return 0;
}

int newNode(int num){
	int root = index++;
	Node[root].data = num;
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

int getBalanceFactor(int root){
	return getHeight(Node[root].lchild) - getHeight(Node[root].rchild);
}

void updateHeight(int root) {
	Node[root].height = max(getHeight(Node[root].lchild), getHeight(Node[root].rchild)) + 1;
}

void leftTurn(int &root) {
	int temp = Node[root].rchild;
	Node[root].rchild = Node[temp].lchild;
	Node[temp].lchild = root;
	updateHeight(root);
	updateHeight(temp);
	root = temp;
}

void rightTurn(int &root) {
	int temp = Node[root].lchild;
	Node[root].lchild = Node[temp].rchild;
	Node[temp].rchild = root;
	updateHeight(root);
	updateHeight(temp);
	root = temp;
}

void insert(int &root, int num) {
	if(root == -1){
		root = newNode(num);
		return;
	}
	if(num < Node[root].data){
		insert(Node[root].lchild, num);
		updateHeight(root);
		if(getBalanceFactor(root) == 2){
			if(getBalanceFactor(Node[root].lchild) == 1){
				rightTurn(root);
			}else if(getBalanceFactor(Node[root].lchild) == -1){
				leftTurn(Node[root].lchild);
				rightTurn(root);
			}
		}
	}else{
		insert(Node[root].rchild, num);
		updateHeight(root);
		if(getBalanceFactor(root) == -2){
			if(getBalanceFactor(Node[root].rchild) == -1){
				leftTurn(root);
			}else if(getBalanceFactor(Node[root].rchild) == 1){
				rightTurn(Node[root].rchild);
				leftTurn(root);
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
