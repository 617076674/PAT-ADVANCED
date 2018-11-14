#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct node {
	int data;
	node* lchild;
	node* rchild;
};

int N;	//�ڵ����
vector<int> preOrder;	//ǰ�����
vector<int> preOrderBSTree;
vector<int> preOrderBSTreeMirror;
vector<int> postOrderBSTree;
vector<int> postOrderBSTreeMirror;

node* newNode(int v);	//����һ��Node�����еĽڵ���½ڵ㣬indexΪ���±�
void insert(node* &root, int x);	//���룬rootΪ���ڵ��������е��±꣬Ҫ������
node* createBinarySearchTree();	//���������ǰ�������������������
void preOrderTraversal(node* root);	//����������ǰ�����
void preOrderTraversalMirror(node* root);	//�������������ǰ�����
void postOrderTraversal(node* root);	//�����������������
void postOrderTraversalMirror(node* root);	//��������������������

int main() {
	cin >> N;
	int input;
	for(int i = 0; i < N; i++) {
		cin >> input;
		preOrder.push_back(input);
	}
	node* root = createBinarySearchTree();
	preOrderTraversal(root);
	preOrderTraversalMirror(root);
	postOrderTraversal(root);
	postOrderTraversalMirror(root);
	if(preOrder == preOrderBSTree){
		cout << "YES" << endl;
		for(int i = 0; i < postOrderBSTree.size(); i++){
			cout << postOrderBSTree[i];
			if(i != postOrderBSTree.size() - 1){
				cout << " ";
			}
		}
	}else if(preOrder == preOrderBSTreeMirror){
		cout << "YES" << endl;
		for(int i = 0; i < postOrderBSTreeMirror.size(); i++){
			cout << postOrderBSTreeMirror[i];
			if(i != postOrderBSTreeMirror.size() - 1){
				cout << " ";
			}
		}
	}else{
		cout << "NO" << endl;
	}
	return 0;
}

node* newNode(int v) {
	node* root = new node;
	root->data = v;
	root->lchild = NULL;
	root->rchild = NULL;
	return root;
}

void insert(node* &root, int x) {
	if(root == NULL) {
		root = newNode(x);
		return;
	}
	if(x < root->data) {
		insert(root->lchild, x);
	} else {
		insert(root->rchild, x);
	}
}

node* createBinarySearchTree() {
	node* root = NULL;	//�½������
	for(int i = 0; i < N; i++) {
		insert(root, preOrder[i]);
	}
	return root;
}

void preOrderTraversal(node* root) {
	if(root == NULL) {
		return;
	}
	preOrderBSTree.push_back(root->data);
	preOrderTraversal(root->lchild);
	preOrderTraversal(root->rchild);
}

void preOrderTraversalMirror(node* root) {
	if(root == NULL) {
		return;
	}
	preOrderBSTreeMirror.push_back(root->data);
	preOrderTraversalMirror(root->rchild);
	preOrderTraversalMirror(root->lchild);
}

void postOrderTraversal(node* root) {
	if(root == NULL) {
		return;
	}
	postOrderTraversal(root->lchild);
	postOrderTraversal(root->rchild);
	postOrderBSTree.push_back(root->data);
}

void postOrderTraversalMirror(node* root) {
	if(root == NULL) {
		return;
	}
	postOrderTraversalMirror(root->rchild);
	postOrderTraversalMirror(root->lchild);
	postOrderBSTreeMirror.push_back(root->data);
}
