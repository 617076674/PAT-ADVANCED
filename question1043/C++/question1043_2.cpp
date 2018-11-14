#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct node {
	int data;
	int lchild;
	int rchild;
};

int N;	//�ڵ����
vector<int> preOrder;	//ǰ�����
node Node[1000];
int index = 0;
vector<int> preOrderBSTree;
vector<int> preOrderBSTreeMirror;
vector<int> postOrderBSTree;
vector<int> postOrderBSTreeMirror;

int newNode(int v);	//����һ��Node�����еĽڵ���½ڵ㣬indexΪ���±�
void insert(int &root, int x);	//���룬rootΪ���ڵ��������е��±꣬Ҫ������
int createBinarySearchTree();	//���������ǰ�������������������
void preOrderTraversal(int root);	//����������ǰ�����
void preOrderTraversalMirror(int root);	//�������������ǰ�����
void postOrderTraversal(int root);	//�����������������
void postOrderTraversalMirror(int root);	//��������������������

int main() {
	cin >> N;
	int input;
	for(int i = 0; i < N; i++) {
		cin >> input;
		preOrder.push_back(input);
	}
	int root = createBinarySearchTree();
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

int newNode(int v) {
	Node[index].data = v;
	Node[index].lchild = -1;
	Node[index].rchild = -1;
	return index++;
}

void insert(int &root, int x) {
	if(root == -1) {
		root = newNode(x);
		return;
	}
	if(x < Node[root].data) {
		insert(Node[root].lchild, x);
	} else {
		insert(Node[root].rchild, x);
	}
}

int createBinarySearchTree() {
	int root = -1;	//�½������
	for(int i = 0; i < N; i++) {
		insert(root, preOrder[i]);
	}
	return root;
}

void preOrderTraversal(int root) {
	if(root == -1) {
		return;
	}
	preOrderBSTree.push_back(Node[root].data);
	preOrderTraversal(Node[root].lchild);
	preOrderTraversal(Node[root].rchild);
}

void preOrderTraversalMirror(int root) {
	if(root == -1) {
		return;
	}
	preOrderBSTreeMirror.push_back(Node[root].data);
	preOrderTraversalMirror(Node[root].rchild);
	preOrderTraversalMirror(Node[root].lchild);
}

void postOrderTraversal(int root) {
	if(root == -1) {
		return;
	}
	postOrderTraversal(Node[root].lchild);
	postOrderTraversal(Node[root].rchild);
	postOrderBSTree.push_back(Node[root].data);
}

void postOrderTraversalMirror(int root) {
	if(root == -1) {
		return;
	}
	postOrderTraversalMirror(Node[root].rchild);
	postOrderTraversalMirror(Node[root].lchild);
	postOrderBSTreeMirror.push_back(Node[root].data);
}
