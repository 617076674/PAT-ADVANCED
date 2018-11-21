#include<iostream>
#include<vector>

using namespace std;

struct node{
	int data;
	node* lchild;
	node* rchild;
};

bool isMaxHeap(vector<int> levelOrder);	//判断是否是最大堆 
bool isMinHeap(vector<int> levelOrder);	//判断是否是最小堆 
node* newNode(int num);	//新建节点 
node* create(vector<int> levelOrder);	//根据层序遍历建立树，返回树的根节点 
void postOrderTraversal(node* head, vector<int> &postOrder);	//后序遍历 

int main(){
	int M, N;
	scanf("%d %d", &N, &M);
	for(int i = 0; i < N; i++){
		vector<int> levelOrder;
		int num;
		for(int j = 0; j < M; j++){
			scanf("%d", &num);
			levelOrder.push_back(num);
		}
		if(isMaxHeap(levelOrder)){
			printf("Max Heap\n");
		}else if(isMinHeap(levelOrder)){
			printf("Min Heap\n");
		}else{
			printf("Not Heap\n");
		}
		node* head = create(levelOrder);
		vector<int> postOrder;
		postOrderTraversal(head, postOrder);
		for(int j = 0; j < postOrder.size(); j++){
			printf("%d", postOrder[j]);
			if(j != postOrder.size() - 1){
				printf(" ");
			}else{
				printf("\n");
			}
		}
	}
	return 0;
}

bool isMaxHeap(vector<int> levelOrder){
	for(int i = 0; i < levelOrder.size(); i++){
		if(2 * i + 1 < levelOrder.size()){
			if(levelOrder[2 * i + 1] > levelOrder[i]){
				return false;
			}
		}
		if(2 * i + 2 < levelOrder.size()){
			if(levelOrder[2 * i + 2] > levelOrder[i]){
				return false;
			}
		}
	}
	return true;
}

bool isMinHeap(vector<int> levelOrder){
	for(int i = 0; i < levelOrder.size(); i++){
		if(2 * i + 1 < levelOrder.size()){
			if(levelOrder[2 * i + 1] < levelOrder[i]){
				return false;
			}
		}
		if(2 * i + 2 < levelOrder.size()){
			if(levelOrder[2 * i + 2] < levelOrder[i]){
				return false;
			}
		}
	}
	return true;
}

node* newNode(int num){
	node* head = new node();
	head->data = num;
	head->lchild = NULL;
	head->rchild = NULL;
	return head;
}

node* create(vector<int> levelOrder){
	vector<node*> nodes;
	for(int i = 0; i < levelOrder.size(); i++){
		nodes.push_back(newNode(levelOrder[i]));
	}
	for(int i = 0; i < nodes.size(); i++){
		if(2 * i + 1 < nodes.size()){
			nodes[i]->lchild = nodes[2 * i + 1];
		}
		if(2 * i + 2 < nodes.size()){
			nodes[i]->rchild = nodes[2 * i + 2];
		}
	}
	return nodes[0];
}

void postOrderTraversal(node* head, vector<int> &postOrder){
	if(head == NULL){
		return;
	}
	postOrderTraversal(head->lchild, postOrder);
	postOrderTraversal(head->rchild, postOrder);
	postOrder.push_back(head->data);
}
