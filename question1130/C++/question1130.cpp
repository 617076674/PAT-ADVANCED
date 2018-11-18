#include<iostream>

using namespace std;

struct node {
	char data[11];
	int lchild, rchild;
};

node Node[21];
int index = 1;
int root;

void inOrderTraversal(int head);

int main() {
	int N;
	scanf("%d", &N);
	bool flag[N + 1];
	fill(flag + 1, flag + N + 1, false);
	int lchild, rchild;
	for(int i = 0; i < N; i++) {
		scanf("%s %d %d", Node[index].data, &lchild, &rchild);
		Node[index].lchild = lchild;
		Node[index].rchild = rchild;
		if(lchild != -1) {
			flag[lchild] = true;
		}
		if(rchild != -1) {
			flag[rchild] = true;
		}
		index++;
	}
	for(int i = 1; i <= N; i++) {
		if(!flag[i]) {
			root = i;
			break;
		}
	}
	inOrderTraversal(root);
	return 0;
}

void inOrderTraversal(int head) {
	if(head == -1) {
		return;
	}
	if(!(Node[head].lchild == -1 && Node[head].rchild == -1) && !(head == root)) {	//如果没有左右孩子或是根节点，则不输出左括号 
		printf("(");
	}
	inOrderTraversal(Node[head].lchild);
	printf("%s", Node[head].data);
	inOrderTraversal(Node[head].rchild);
	if(!(Node[head].lchild == -1 && Node[head].rchild == -1) && !(head == root)) {	//如果没有左右孩子或是根节点，也不输出右括号 
		printf(")");
	}
}
