#include<iostream>
#include<string>
#include<vector>
#include<queue>

using namespace std;

struct node {
	int lchild;
	int rchild;
};

int N;
node Node[10];
bool flag[10] = {false};
vector<int> levelOrder;
vector<int> inOrder;

int inverseTree(int root);
void levelOrderTraversal(int root);
void inOrderTraversal(int root);

int main() {
	cin >> N;
	string lchild, rchild;
	for(int i = 0; i < N; i++) {
		cin >> lchild >> rchild;
		if(lchild.compare("-") == 0) {
			Node[i].lchild = -1;
		} else {
			int num = lchild[0] - '0';
			Node[i].lchild = num;
			flag[num] = true;
		}
		if(rchild.compare("-") == 0) {
			Node[i].rchild = -1;
		} else {
			int num = rchild[0] - '0';
			Node[i].rchild = num;
			flag[num] = true;
		}
	}
	int root = -1;
	for(int i = 0; i < N; i++) {
		if(!flag[i]) {
			root = i;
			break;
		}
	}
	root = inverseTree(root);
	levelOrderTraversal(root);
	inOrderTraversal(root);
	for(int i = 0; i < levelOrder.size(); i++) {
		cout << levelOrder[i];
		if(i != levelOrder.size() - 1) {
			cout << " ";
		}
	}
	cout << endl;
	for(int i = 0; i < inOrder.size(); i++) {
		cout << inOrder[i];
		if(i != inOrder.size() - 1) {
			cout << " ";
		}
	}
	cout << endl;
	return 0;
}

int inverseTree(int root) {
	if(root == -1) {
		return root;
	}
	int rootLeft = inverseTree(Node[root].rchild);
	int rootRight = inverseTree(Node[root].lchild);
	Node[root].lchild = rootLeft;
	Node[root].rchild = rootRight;
	return root;
}

void levelOrderTraversal(int root) {
	queue<int> q;
	q.push(root);
	while(!q.empty()) {
		int now = q.front();
		levelOrder.push_back(now);
		q.pop();
		if(Node[now].lchild != -1) {
			q.push(Node[now].lchild);
		}
		if(Node[now].rchild != -1) {
			q.push(Node[now].rchild);
		}
	}
}

void inOrderTraversal(int root) {
	if(root == -1) {
		return;
	}
	inOrderTraversal(Node[root].lchild);
	inOrder.push_back(root);
	inOrderTraversal(Node[root].rchild);
}
