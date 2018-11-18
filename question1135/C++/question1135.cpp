#include<iostream>
#include<vector>
#include<set>
#include<cmath>

using namespace std;

struct node {
	int data;
	node* lchild;
	node* rchild;
};

set<int> countBlack;
vector<int> tempPath;

node* create(vector<int> levelOrder);
void dfs(node* nowVisit, bool &flag);
bool isRBTree(node* head);

int main() {
	int K;
	scanf("%d", &K);
	for(int i = 0; i < K; i++) {
		int N;
		scanf("%d", &N);
		vector<int> levelOrder;
		int num;
		for(int j = 0; j < N; j++) {
			scanf("%d", &num);
			levelOrder.push_back(num);
		}
		node* head = create(levelOrder);
		if(isRBTree(head)) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	return 0;
}

node* create(vector<int> levelOrder) {
	if(levelOrder.size() <= 0) {
		return NULL;
	}
	node* head = new node();
	head->data = levelOrder[0];
	vector<int> left;
	vector<int> right;
	for(int i = 1; i < levelOrder.size(); i++) {
		if(abs(levelOrder[i]) < abs(levelOrder[0])) {
			left.push_back(levelOrder[i]);
		} else {
			right.push_back(levelOrder[i]);
		}
	}
	head->lchild = create(left);
	head->rchild = create(right);
	return head;
}

void dfs(node* nowVisit, bool &flag) {
	if(nowVisit == NULL) {
		int count = 0;
		for(int i = 0; i < tempPath.size(); i++) {
			if(tempPath[i] > 0) {
				count++;
			}
		}
		countBlack.insert(count);
		return;
	}
	if(nowVisit->data < 0) {
		if(nowVisit->lchild != NULL) {
			if(nowVisit->lchild->data < 0) {
				flag = false;
			}
		}
		if(nowVisit->rchild != NULL) {
			if(nowVisit->rchild->data < 0) {
				flag = false;
			}
		}
	}
	tempPath.push_back(nowVisit->data);
	dfs(nowVisit->lchild, flag);
	dfs(nowVisit->rchild, flag);
	tempPath.pop_back();
}

bool isRBTree(node* head) {
	if(head->data < 0) {
		return false;
	}
	bool flag = true;
	countBlack.clear();
	tempPath.clear();
	dfs(head, flag);
	if(countBlack.size() != 1 || !flag) {
		return false;
	}
	return true;
}
