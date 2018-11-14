#include<iostream>
#include<queue> 

using namespace std;

struct node {
	int data;
	node* lchild;
	node* rchild;
};

int N;	//二叉树的节点个数
int postOrder[31];	//后序遍历数组 
int inOrder[31];	//中序遍历数组
int levelOrder[31];
int index = 0; 

/*
	当前后序序列区间为[leftPost, rightPost]，中序序列区间为[leftIn, rightIn]，返回根节点地址 
*/ 
node* create(int leftPost, int rightPost, int leftIn, int rightIn);

/*
	层序遍历二叉树 
*/
void levelTraversal(node* root);

int main(){
	cin >> N;
	for(int i = 0; i < N; i++){
		cin >> postOrder[i];
	}
	for(int i = 0; i < N; i++){
		cin >> inOrder[i];
	}
	node* root = create(0, N - 1, 0, N - 1);	//这里右边界是N - 1，而不是N，在函数的定义中，左右边界都是闭区间 
	levelTraversal(root);
	for(int i = 0; i < N; i++){
		cout << levelOrder[i];
		if(i != N - 1){
			cout << " ";
		}
	}
	cout << endl;
	return 0;
}

node* create(int leftPost, int rightPost, int leftIn, int rightIn){
	if(leftPost > rightPost){
		return NULL;	//后序序列的长度小于等于0时，直接返回 
	}
	node* root = new node;
	root->data = postOrder[rightPost];	//新节点的数据域为根结点的值
	int k;
	for(k = leftIn; k <= rightIn; k++){
		if(inOrder[k] == postOrder[rightPost]){
			break;
		}
	}
	int numLeft = k - leftIn;	//左子树的节点个数
	root->lchild = create(leftPost, leftPost + numLeft - 1, leftIn, k - 1);
	root->rchild = create(leftPost + numLeft, rightPost - 1, k + 1, rightIn);
	return root; 
}

void levelTraversal(node* root){
	if(root == NULL){
		return;
	}
	queue<node*> q;
	q.push(root);
	while(!q.empty()){
		node* now = q.front();
		q.pop();
		levelOrder[index++] = now->data;
		if(now->lchild != NULL){
			q.push(now->lchild);
		}
		if(now->rchild != NULL){
			q.push(now->rchild);
		}
	}
}
