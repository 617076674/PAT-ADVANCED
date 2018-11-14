#include<iostream>
#include<set>
#include<vector>

using namespace std;

struct node{
	int data;
	int lchild, rchild;
};

node Node[30];
int index = 0;
bool flag = true;
int preOrder[30];
int postOrder[30];
vector<int> inOrder; 

int create(int preLeft, int preRight, int postLeft, int postRight);
void inOrderTraversal(int head);

int main(){
	int N;
	scanf("%d", &N);
	for(int i = 0; i < N; i++){
		scanf("%d", &preOrder[i]);
	}
	for(int i = 0; i < N; i++){
		scanf("%d", &postOrder[i]);
	}
	int head = create(0, N - 1, 0, N - 1);
	if(flag){
		printf("Yes\n");
	}else{
		printf("No\n");
	}
	inOrderTraversal(head);
	for(int i = 0; i < inOrder.size(); i++){
		printf("%d", inOrder[i]);
		if(i != inOrder.size() - 1){
			printf(" ");
		}else{
			printf("\n");
		}
	}
	return 0;
}

int create(int preLeft, int preRight, int postLeft, int postRight){
	if(preLeft > preRight){
		return -1;
	}
	if(preLeft + 1 == preRight){
		flag = false;
	}
	int head = index++;
	Node[head].data = preOrder[preLeft];
	int numLeft = 0;
	for(int i = postLeft; i <= postRight - 1; i++){
		if(postOrder[i] == preOrder[preLeft + 1]){
			numLeft = i - postLeft + 1;
			break;
		}
	}
	Node[head].lchild = create(preLeft + 1, preLeft + numLeft, postLeft, postLeft + numLeft - 1);
	Node[head].rchild = create(preLeft + numLeft + 1, preRight, postLeft + numLeft, postRight - 1);
	return head;
}

void inOrderTraversal(int head){
	if(head == -1){
		return; 
	}
	inOrderTraversal(Node[head].lchild);
	inOrder.push_back(Node[head].data);
	inOrderTraversal(Node[head].rchild);
}
