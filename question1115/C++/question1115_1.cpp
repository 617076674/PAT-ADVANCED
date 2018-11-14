#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct node {
	int data;
	int lchild, rchild;
};

node Node[1001];
int index = 0;
vector<int> nums;
vector<int> sizes;

int newNode(int num);
void insert(int &head, int num);
int create();
void levelOrderTraversal(int head);

int main() {
	int N;
	scanf("%d", &N);
	int num;
	for(int i = 0; i < N; i++) {
		scanf("%d", &num);
		nums.push_back(num);
	}
	int head = create();
	levelOrderTraversal(head);
	int n1 = sizes[sizes.size() - 1];
	int n2 = sizes[sizes.size() - 2];
	printf("%d + %d = %d\n", n1, n2, n1 + n2);
	return 0;
}

int newNode(int num) {
	int head = index++;
	Node[head].data = num;
	Node[head].lchild = -1;
	Node[head].rchild = -1;
	return head;
}

void insert(int &head, int num) {
	if(head == -1) {
		head = newNode(num);
		return;
	}
	if(num > Node[head].data) {
		insert(Node[head].rchild, num);
	} else {
		insert(Node[head].lchild, num);
	}
}

int create() {
	int head = -1;
	for(int i = 0; i < nums.size(); i++) {
		insert(head, nums[i]);
	}
	return head;
}

void levelOrderTraversal(int head) {
	queue<int> q;
	q.push(head);
	while(!q.empty()) {
		int size = q.size();
		sizes.push_back(size);
		for(int i = 0; i < size; i++) {
			int now = q.front();
			q.pop();
			if(Node[now].lchild != -1) {
				q.push(Node[now].lchild);
			}
			if(Node[now].rchild != -1) {
				q.push(Node[now].rchild);
			}
		}
	}
}
