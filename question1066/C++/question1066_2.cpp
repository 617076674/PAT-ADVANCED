#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct node {
	int data;
	int height;
	node* lchild;
	node* rchild;
};

int N;
vector<int> input;

node* newNode(int num);
int getHeight(node* root);
int getBalanceFactor(node* root);
void updateHeight(node* root);
void leftTurn(node* &root);
void rightTurn(node* &root);
void insert(node* &root, int num);
node* create();

int main(){
	cin >> N;
	int num;
	for(int i = 0; i < N; i++){
		cin >> num;
		input.push_back(num);
	}
	node* root = create();
	cout << root->data << endl;
	return 0;
}

node* newNode(int num){
	node* root = new node;
	root->data = num;
	root->height = 1;
	root->lchild = root->rchild = NULL;
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
