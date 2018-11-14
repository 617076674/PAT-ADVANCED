#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct node{
	int data;
	int height;
	node* lchild;
	node* rchild;
};

int N;
vector<int> input;
vector<int> levelOrder;
vector<int> inOrder;

node* newNode(int data);
int getHeight(node* root);
int getBalanceFactor(node* root);
void updateHeight(node* root);
void leftTurn(node* &root);
void rightTurn(node* &root);
void insert(node* &root, int num);
node* create();
void levelOrderTraversal(node* root);
void inOrderTraversal(int root);
void print();

int main(){
	cin >> N;
	int num;
	for(int i = 0; i < N; i++){
		cin >> num;
		input.push_back(num);
	}
	node* root = create();
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

node* newNode(int data){
	node* root = new node;	//此处需要new一个node 
	root->data = data;
	root->height = 1;
	root->lchild = NULL;
	root->rchild = NULL;
	return root;
}

int getHeight(node* root){
	if(root == NULL){
		return 0;
	}
	return root->height;
}

int getBalanceFactor(node* root){
	return getHeight(root->lchild) - getHeight(root->rchild);
}

void updateHeight(node* root){
	root->height = max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
}

void leftTurn(node* &root){
	node* temp = root->rchild;
	root->rchild = temp->lchild;
	temp->lchild = root;
	updateHeight(root);
	updateHeight(temp);
	root = temp;
}

void rightTurn(node* &root){
	node* temp = root->lchild;
	root->lchild = temp->rchild;
	temp->rchild = root;
	updateHeight(root);
	updateHeight(temp);
	root = temp;
}

void insert(node* &root, int num){
	if(root == NULL){
		root = newNode(num);
		return;
	}
	if(num < root->data){
		insert(root->lchild, num);
		updateHeight(root);
		if(getBalanceFactor(root) == 2){
			if(getBalanceFactor(root->lchild) == 1){
				rightTurn(root); 
			}else if(getBalanceFactor(root->lchild) == -1){
				leftTurn(root->lchild);
				rightTurn(root);
			}
		}
	}else{
		insert(root->rchild, num);
		updateHeight(root);
		if(getBalanceFactor(root) == -2){
			if(getBalanceFactor(root->rchild) == -1){
				leftTurn(root); 
			}else if(getBalanceFactor(root->rchild) == 1){
				rightTurn(root->rchild);
				leftTurn(root);
			}
		}
	}
}

node* create(){
	node* root = NULL;
	for(int i = 0; i < N; i++){
		insert(root, input[i]);
	}
	return root;
}

void levelOrderTraversal(node* root){
	queue<node*> q;
	q.push(root);
	while(!q.empty()){
		node* now = q.front();
		levelOrder.push_back(now->data);
		q.pop();
		if(now->lchild != NULL){
			q.push(now->lchild);
		}
		if(now->rchild != NULL){
			q.push(now->rchild);
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
	if(root >= N){
		return;
	}
	inOrderTraversal(root * 2 + 1);
	inOrder.push_back(levelOrder[root]);
	inOrderTraversal(root * 2 + 2);
}
