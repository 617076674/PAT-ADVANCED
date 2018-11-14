#include<iostream>
#include<queue>

using namespace std;

struct node {
	int data;
	int lchild;
	int rchild;
};

int N;	//二叉树的节点个数
int postOrder[31];	//后序遍历数组 
int inOrder[31];	//中序遍历数组
int levelOrder[31];	//层序遍历数组
node Node[31];
int index = 0;
int resultIndex = 0;

int create(int leftPost, int rightPost, int leftIn, int rightIn);
void levelTraversal(int root); 

int main(){
	cin >> N;
	for(int i = 0; i < N; i++){
		cin >> postOrder[i];
	}
	for(int i = 0; i < N; i++){
		cin >> inOrder[i];
	}
	int root = create(0, N - 1, 0, N - 1);
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

int create(int leftPost, int rightPost, int leftIn, int rightIn){
	if(leftPost > rightPost){
		return -1;
	}
	int root = index++;
	Node[root].data = postOrder[rightPost];
	int k;
	for(k = leftIn; k <= rightIn; k++){
		if(inOrder[k] == postOrder[rightPost]){
			break;
		}
	}
	int numLeft = k - leftIn; 
	Node[root].lchild = create(leftPost, leftPost + numLeft - 1, leftIn, k - 1);
	Node[root].rchild = create(leftPost + numLeft, rightPost - 1, k + 1, rightIn);
	return root ;
}

void levelTraversal(int root){
	if(root == -1){
		return;
	}
	queue<int> q;
	q.push(root);
	while(!q.empty()){
		int now = q.front();
		q.pop();
		levelOrder[resultIndex++] = Node[now].data;
		if(Node[now].lchild != -1){
			q.push(Node[now].lchild);
		}
		if(Node[now].rchild != -1){
			q.push(Node[now].rchild);
		}
	}
}
