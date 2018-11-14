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
int preOrder[1000];	//前序遍历
vector<int> postOrder;	//后序遍历结果
node Node[1000];
int index = 0;

int createBinarySearchTree(int leftPre, int rightPre);	//根据前序遍历构建二叉搜索树
int createMirrorBinarySearchTree(int leftPre, int rightPre);	//根据前序遍历构建镜像二叉搜索树
void postOrderTraversal(int root);

int main() {
	cin >> N;
	for(int i = 0; i < N; i++) {
		cin >> preOrder[i];
	}
	int root = createBinarySearchTree(0, N - 1);
	postOrderTraversal(root);
	if(postOrder.size() == N) {
		cout << "YES" << endl;
		for(int i = 0; i < N; i++) {
			cout << postOrder[i];
			if(i != N - 1) {
				cout << " ";
			}
		}
		cout << endl;
	} else {
		postOrder.clear();
		index = 0;
		root = createMirrorBinarySearchTree(0, N - 1);
		postOrderTraversal(root);
		if(postOrder.size() == N) {
			cout << "YES" << endl;
			for(int i = 0; i < N; i++) {
				cout << postOrder[i];
				if(i != N - 1) {
					cout << " ";
				}
			}
			cout << endl;
		} else {
			cout << "NO" << endl;
		}
	}
	return 0;
}

int createBinarySearchTree(int leftPre, int rightPre) {
	if(leftPre > rightPre) {
		return -1;
	}
	int root = index++;
	Node[root].data = preOrder[leftPre];
	int k;
	for(k = leftPre + 1; k <= rightPre; k++) {
		if(preOrder[k] >= preOrder[leftPre]) {
			break;
		}
	}
	int l;
	for(l = k; l <= rightPre; l++) {
		if(preOrder[l] < preOrder[leftPre]) {
			break;
		}
	}
	Node[root].lchild = createBinarySearchTree(leftPre + 1, k - 1);
	Node[root].rchild = createBinarySearchTree(k, l - 1);
	return root;
}

int createMirrorBinarySearchTree(int leftPre, int rightPre) {
	if(leftPre > rightPre) {
		return -1;
	}
	int root = index++;
	Node[root].data = preOrder[leftPre];
	int k;
	for(k = leftPre + 1; k <= rightPre; k++) {
		if(preOrder[k] < preOrder[leftPre]) {
			break;
		}
	}
	int l;
	for(l = k; l <= rightPre; l++) {
		if(preOrder[l] >= preOrder[leftPre]) {
			break;
		}
	}
	Node[root].lchild = createMirrorBinarySearchTree(leftPre + 1, k - 1);
	Node[root].rchild = createMirrorBinarySearchTree(k, l - 1);
	return root;
}

void postOrderTraversal(int root) {
	if(root == -1) {
		return;
	}
	postOrderTraversal(Node[root].lchild);
	postOrderTraversal(Node[root].rchild);
	postOrder.push_back(Node[root].data);
}


