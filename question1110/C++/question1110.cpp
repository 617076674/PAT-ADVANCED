#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

struct node{	//节点结构体，存储其左孩子和右孩子 
	int lchild, rchild;
};

node Node[20];	//以静态数组的形式存储树的节点信息 
vector<int> levelOrder;	//原树的层序遍历结果 
vector<int> inOrder;	//原树的中序遍历结果 
vector<int> checkInOrder;	//假设是一棵完全二叉树，以数组形式存储（节点编号从0开始），得到的中序遍历结果 

int changeToNum(char* input);	//处理输入，将输入的编号转换为int型 
void levelOrderTraversal(int head);	//层序遍历原二叉树 
void inOrderTraversal(int head);	//中序遍历原二叉树 
void checkInOrderTraversal(int index);	//假设是一棵完全二叉树，以数组形式存储（节点编号从0开始），中序遍历之 

int main(){
	int N;
	scanf("%d", &N);	//读取节点个数信息 
	char left[3], right[3];	//题目保证节点个数小于等于20，因此字符数不超过2，可以用大小为3的字符数组来保存 
	bool flag[N];	//标记某节点是否出现在某个节点的孩子节点中 
	fill(flag, flag + N, true);	//初始化为true 
	for(int i = 0; i < N; i++){
		scanf("%s %s", left, right);
		if(strcmp(left, "-") == 0){	//如果是"-"，该孩子节点记为-1 
			Node[i].lchild = -1;
		}else{
			int num = changeToNum(left);
			Node[i].lchild = num;
			flag[num] = false;	//标记编号为num的节点曾经是某个节点的孩子节点 
		}
		if(strcmp(right, "-") == 0){	//如果是"-"，该孩子节点记为-1
			Node[i].rchild = -1;
		}else{
			int num = changeToNum(right);
			Node[i].rchild = num;
			flag[num] = false;	//标记编号为num的节点曾经是某个节点的孩子节点 
		}
	}
	int head = -1;	//寻找头节点 
	for(int i = 0; i < N; i++){
		if(flag[i]){	//头节点一定不会出现在某个节点的孩子节点中 
			head = i;
		}
	}
	levelOrderTraversal(head);	//层序遍历原二叉树 
	inOrderTraversal(head);	//中序遍历原二叉树
	checkInOrderTraversal(0);	//假设是一棵完全二叉树，以数组形式存储（节点编号从0开始），中序遍历之
	if(inOrder == checkInOrder){	//如果中序遍历原二叉树的结果和以数组形式存储后的中序遍历结果相同，说明是一棵完全二叉树 
		printf("YES %d\n", levelOrder[levelOrder.size() - 1]);
	}else{	//否则，不是一棵完全二叉树 
		printf("NO %d\n", head);
	}
	return 0;
}

int changeToNum(char* input){
	int result = 0;
	for(int i = 0; i < strlen(input); i++){
		result = result * 10 + input[i] - '0';
	}
	return result;
}

void levelOrderTraversal(int head){
	queue<int> q;
	q.push(head);
	while(!q.empty()){
		int now = q.front();
		levelOrder.push_back(now);
		q.pop();
		if(Node[now].lchild != -1){	//其左孩子不为-1，则左孩子入队 
			q.push(Node[now].lchild);
		}
		if(Node[now].rchild != -1){	//其右孩子不为-1，则右孩子入队 
			q.push(Node[now].rchild);
		}
	}
}

void inOrderTraversal(int head){
	if(head == -1){	//递归终止条件 
		return;
	}
	inOrderTraversal(Node[head].lchild);
	inOrder.push_back(head);
	inOrderTraversal(Node[head].rchild);
}

void checkInOrderTraversal(int index){
	if(index >= levelOrder.size()){
		return;
	}
	checkInOrderTraversal(2 * index + 1);	//其左孩子编号为2 * index + 1 
	checkInOrder.push_back(levelOrder[index]);
	checkInOrderTraversal(2 * index + 2);	//其右孩子编号为2 * index + 2 
}
