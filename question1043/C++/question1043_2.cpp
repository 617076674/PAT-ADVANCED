#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct node {
	int data;
	int lchild;
	int rchild;
};

int N;	//节点个数
vector<int> preOrder;	//前序遍历
node Node[1000];
int index = 0;
vector<int> preOrderBSTree;
vector<int> preOrderBSTreeMirror;
vector<int> postOrderBSTree;
vector<int> postOrderBSTreeMirror;

int newNode(int v);	//分配一个Node数组中的节点给新节点，index为其下标
void insert(int &root, int x);	//插入，root为根节点在数组中的下标，要加引用
int createBinarySearchTree();	//根据输入的前序遍历构建二分搜索树
void preOrderTraversal(int root);	//二叉搜索树前序遍历
void preOrderTraversalMirror(int root);	//镜像二叉搜索树前序遍历
void postOrderTraversal(int root);	//二叉搜索树后序遍历
void postOrderTraversalMirror(int root);	//镜像二叉搜索树后序遍历

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
	int root = -1;	//新建根结点
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
