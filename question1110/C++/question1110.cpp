#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

struct node{	//�ڵ�ṹ�壬�洢�����Ӻ��Һ��� 
	int lchild, rchild;
};

node Node[20];	//�Ծ�̬�������ʽ�洢���Ľڵ���Ϣ 
vector<int> levelOrder;	//ԭ���Ĳ��������� 
vector<int> inOrder;	//ԭ�������������� 
vector<int> checkInOrder;	//������һ����ȫ����������������ʽ�洢���ڵ��Ŵ�0��ʼ�����õ������������� 

int changeToNum(char* input);	//�������룬������ı��ת��Ϊint�� 
void levelOrderTraversal(int head);	//�������ԭ������ 
void inOrderTraversal(int head);	//�������ԭ������ 
void checkInOrderTraversal(int index);	//������һ����ȫ����������������ʽ�洢���ڵ��Ŵ�0��ʼ�����������֮ 

int main(){
	int N;
	scanf("%d", &N);	//��ȡ�ڵ������Ϣ 
	char left[3], right[3];	//��Ŀ��֤�ڵ����С�ڵ���20������ַ���������2�������ô�СΪ3���ַ����������� 
	bool flag[N];	//���ĳ�ڵ��Ƿ������ĳ���ڵ�ĺ��ӽڵ��� 
	fill(flag, flag + N, true);	//��ʼ��Ϊtrue 
	for(int i = 0; i < N; i++){
		scanf("%s %s", left, right);
		if(strcmp(left, "-") == 0){	//�����"-"���ú��ӽڵ��Ϊ-1 
			Node[i].lchild = -1;
		}else{
			int num = changeToNum(left);
			Node[i].lchild = num;
			flag[num] = false;	//��Ǳ��Ϊnum�Ľڵ�������ĳ���ڵ�ĺ��ӽڵ� 
		}
		if(strcmp(right, "-") == 0){	//�����"-"���ú��ӽڵ��Ϊ-1
			Node[i].rchild = -1;
		}else{
			int num = changeToNum(right);
			Node[i].rchild = num;
			flag[num] = false;	//��Ǳ��Ϊnum�Ľڵ�������ĳ���ڵ�ĺ��ӽڵ� 
		}
	}
	int head = -1;	//Ѱ��ͷ�ڵ� 
	for(int i = 0; i < N; i++){
		if(flag[i]){	//ͷ�ڵ�һ�����������ĳ���ڵ�ĺ��ӽڵ��� 
			head = i;
		}
	}
	levelOrderTraversal(head);	//�������ԭ������ 
	inOrderTraversal(head);	//�������ԭ������
	checkInOrderTraversal(0);	//������һ����ȫ����������������ʽ�洢���ڵ��Ŵ�0��ʼ�����������֮
	if(inOrder == checkInOrder){	//����������ԭ�������Ľ������������ʽ�洢���������������ͬ��˵����һ����ȫ������ 
		printf("YES %d\n", levelOrder[levelOrder.size() - 1]);
	}else{	//���򣬲���һ����ȫ������ 
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
		if(Node[now].lchild != -1){	//�����Ӳ�Ϊ-1����������� 
			q.push(Node[now].lchild);
		}
		if(Node[now].rchild != -1){	//���Һ��Ӳ�Ϊ-1�����Һ������ 
			q.push(Node[now].rchild);
		}
	}
}

void inOrderTraversal(int head){
	if(head == -1){	//�ݹ���ֹ���� 
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
	checkInOrderTraversal(2 * index + 1);	//�����ӱ��Ϊ2 * index + 1 
	checkInOrder.push_back(levelOrder[index]);
	checkInOrderTraversal(2 * index + 2);	//���Һ��ӱ��Ϊ2 * index + 2 
}
