#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct node {
	int data;
	node* lchild;
	node* rchild;
};

vector<int> nums;
vector<int> sizes;

node* newNode(int num);
void insert(node* &head, int num);
node* create();
void levelOrderTraversal(node* head);

int main() {
	int N;
	scanf("%d", &N);
	int num;
	for(int i = 0; i < N; i++) {
		scanf("%d", &num);
		nums.push_back(num);
	}
	node* head = create();
	levelOrderTraversal(head);
	int n1 = sizes[sizes.size() - 1];
	int n2 = sizes[sizes.size() - 2];
	printf("%d + %d = %d\n", n1, n2, n1 + n2);
	return 0;
}

node* newNode(int num) {
	node* head = new node();
	head->data = num;
	head->lchild = NULL;
	head->rchild = NULL;
	return head;
}

void insert(node* &head, int num) {
	if(head == NULL) {
		head = newNode(num);
		return;
	}
	if(num > head->data) {
		insert(head->rchild, num);
	} else {
		insert(head->lchild, num);
	}
}

node* create() {
	node* head = NULL;
	for(int i = 0; i < nums.size(); i++) {
		insert(head, nums[i]);
	}
	return head;
}

void levelOrderTraversal(node* head) {
	queue<node*> q;
	q.push(head);
	while(!q.empty()) {
		int size = q.size();
		sizes.push_back(size);
		for(int i = 0; i < size; i++) {
			node* now = q.front();
			q.pop();
			if(now->lchild != NULL) {
				q.push(now->lchild);
			}
			if(now->rchild != NULL) {
				q.push(now->rchild);
			}
		}
	}
}
