#include<iostream>

using namespace std;

struct node{
	int data, height, lchild, rchild;
};

node Node[20];
int N, nums[20], index = 0;

int newNode(int num);
int getHeight(int root);
int getBalanceFactor(int root);
void updateHeight(int root);
void turnLeft(int &root);
void turnRight(int &root);
void insert(int &root, int num);
int create();

int main(){
	scanf("%d", &N);
	for(int i = 0; i < N; i++){
		scanf("%d", &nums[i]);
	}
	int root = create();
	printf("%d\n", Node[root].data);
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

void updateHeight(int root){
	Node[root].height = max(getHeight(Node[root].lchild), getHeight(Node[root].rchild)) + 1;
}

void turnLeft(int &root){
	int temp = Node[root].rchild;
	Node[root].rchild = Node[temp].lchild;
	Node[temp].lchild = root;
	updateHeight(root);
	updateHeight(temp);
	root = temp;
}

void turnRight(int &root){
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
	if(Node[root].data < num){
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
	}else{
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
	}
}

int create(){
	int root = -1;
	for(int i = 0; i < N; i++){
		insert(root, nums[i]);
	}
	return root;
}
