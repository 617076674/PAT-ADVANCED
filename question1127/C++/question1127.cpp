#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct node {
	int data;
	int lchild, rchild;
};

node Node[30];
int index = 0;
vector<int> inOrder;
vector<int> postOrder;
vector<int> zigZagOrder;

int create(int inLeft, int inRight, int postLeft, int postRight);
void zigZagOrderTraversal(int head);

int main() {
	int N;
	scanf("%d", &N);
	int num;
	for(int i = 0; i < N; i++) {
		scanf("%d", &num);
		inOrder.push_back(num);
	}
	for(int i = 0; i < N; i++) {
		scanf("%d", &num);
		postOrder.push_back(num);
	}
	int head = create(0, inOrder.size() - 1, 0, postOrder.size() - 1);
	zigZagOrderTraversal(head);
	for(int i = 0; i < zigZagOrder.size(); i++) {
		printf("%d", zigZagOrder[i]);
		if(i != zigZagOrder.size() - 1) {
			printf(" ");
		} else {
			printf("\n");
		}
	}
	return 0;
}

int create(int inLeft, int inRight, int postLeft, int postRight) {
	if(inLeft > inRight) {
		return - 1;
	}
	int head = index++;
	Node[head].data = postOrder[postRight];
	int k;
	for(int i = inLeft; i <= inRight; i++) {
		if(inOrder[i] == postOrder[postRight]) {
			k = i;
			break;
		}
	}
	int numLeft = k - inLeft;
	Node[head].lchild = create(inLeft, k - 1, postLeft, postLeft + numLeft - 1);
	Node[head].rchild = create(k + 1, inRight, postLeft + numLeft, postRight - 1);
	return head;
}

void zigZagOrderTraversal(int head) {
	queue<int> q;
	q.push(head);
	bool flag = true;
	while(!q.empty()) {
		int qSize = q.size();
		vector<int> level;
		for(int i = 0; i < qSize; i++) {
			int now = q.front();
			level.push_back(Node[now].data);
			q.pop();
			if(Node[now].lchild != -1){
				q.push(Node[now].lchild);
			}
			if(Node[now].rchild != -1){
				q.push(Node[now].rchild);
			}
		}
		if(flag){
			for(int i = level.size() - 1; i >= 0; i--){
				zigZagOrder.push_back(level[i]);
			}
			flag = false;
		}else{
			for(int i = 0; i < level.size(); i++){
				zigZagOrder.push_back(level[i]);
			}
			flag = true;
		}
	}
}
