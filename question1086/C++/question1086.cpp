#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

struct node {
	int lchild;
	int rchild;
};

int N;
node Node[31];
int index = 1;
vector<int> preOrder;
vector<int> inOrder;
vector<int> postOrder;

int create(int leftPre, int rightPre, int leftIn, int rightIn);
void postOrderTraversal(int root); 

int main(){
	cin >> N;
	string operate;
	int num;
	stack<int> Stack;
	for(int i = 0; i < 2 * N; i++){
		cin >> operate;
		if(operate.compare("Push") == 0){
			cin >> num;
			preOrder.push_back(num);
			Stack.push(num);
		}else if(operate.compare("Pop") == 0){
			inOrder.push_back(Stack.top());
			Stack.pop();
		}
	}
	int root = create(0, preOrder.size() - 1, 0, inOrder.size() - 1);
	postOrderTraversal(root);
	for(int i = 0; i < postOrder.size(); i++){
		cout << postOrder[i];
		if(i != postOrder.size() - 1){
			cout << " ";
		}
	}
	cout << endl;
	return 0;
}

int create(int leftPre, int rightPre, int leftIn, int rightIn){
	if(leftPre > rightPre){
		return -1;
	}
	int root = preOrder[leftPre];
	int k;
	for(k = leftIn; k <= rightIn; k++){
		if(inOrder[k] == preOrder[leftPre]){
			break;
		}
	}
	int numLeft = k - leftIn;
	Node[root].lchild = create(leftPre + 1, leftPre + numLeft, leftIn, k - 1);
	Node[root].rchild = create(leftPre + numLeft + 1, rightPre, k + 1, rightIn);
	return root;
}

void postOrderTraversal(int root){
	if(root == -1){
		return;
	}
	postOrderTraversal(Node[root].lchild);
	postOrderTraversal(Node[root].rchild);
	postOrder.push_back(root);
}
