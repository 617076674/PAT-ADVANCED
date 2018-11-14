#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>

using namespace std;

struct node {
	int data;
	int lchild;
	int rchild;
};

int N;
node Node[1000];
int index = 0;
vector<int> inOrder;
vector<int> levelOrder;

int create(int left, int right);
void levelOrderTraversal(int root);
void print();

int main() {
	cin >> N;
	int num;
	for(int i = 0; i < N; i++) {
		cin >> num;
		inOrder.push_back(num);
	}
	sort(inOrder.begin(), inOrder.end());
	int root = create(0, inOrder.size() - 1);
	levelOrderTraversal(root);
	print();
	return 0;
}

int create(int left, int right) {
	if(left > right) {
		return -1;
	}
	int root = index++;
	int count = right - left + 1;	//总共有count个节点
	int level;	//层数 
	for(int i = 1;; i++) {
		if((int)pow(2, i) - 1 >= count) {
			level = i;
			break;
		}
	}
	int countLastLevel = count - (int)pow(2, level - 1) + 1;	//最后一层的节点数 
	int numLeft;	//根节点左边的节点数 
	if(countLastLevel <= (int)pow(2, level - 2)) {	//(int)pow(2, level - 2)是最后一层节点数的一半 
		numLeft = countLastLevel + (count - 1 - countLastLevel) / 2;
	} else {
		numLeft = (int)pow(2, level - 2) + (count - 1 - countLastLevel) / 2;
	}
	Node[root].data = inOrder[left + numLeft];
	Node[root].lchild = create(left, left + numLeft - 1);
	Node[root].rchild = create(left + numLeft + 1, right);
	return root;
}

void levelOrderTraversal(int root) {
	queue<int> q;
	q.push(root);
	while(!q.empty()) {
		int now = q.front();
		levelOrder.push_back(Node[now].data);
		q.pop();
		if(Node[now].lchild != -1) {
			q.push(Node[now].lchild);
		}
		if(Node[now].rchild != -1) {
			q.push(Node[now].rchild);
		}
	}
}

void print() {
	for(int i = 0; i < levelOrder.size(); i++) {
		cout << levelOrder[i];
		if(i != levelOrder.size() - 1) {
			cout << " ";
		}
	}
	cout << endl;
}
