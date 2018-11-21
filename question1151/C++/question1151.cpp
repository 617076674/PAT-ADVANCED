#include<iostream>
#include<vector>
#include<set>

using namespace std;

set<int> numSet;	//�洢 
vector<int> inOrder;	//����������� 
vector<int> preOrder;	//ǰ��������� 

int findLCA(int preLeft, int preRight, int inLeft, int inRight, int num1, int num2);

int main() {
	int M, N;
	scanf("%d %d", &M, &N);
	int num;
	for(int i = 0; i < N; i++) {
		scanf("%d", &num);
		inOrder.push_back(num);
		numSet.insert(num);	//��set���ϴ洢��ֵ�������ж�ĳ�ڵ��Ƿ���� 
	}
	for(int i = 0; i < N; i++) {
		scanf("%d", &num);
		preOrder.push_back(num);
	}
	int num1, num2;
	for(int i = 0; i < M; i++) {
		scanf("%d %d", &num1, &num2);
		set<int>::iterator it1 = numSet.find(num1);
		set<int>::iterator it2 = numSet.find(num2);
		if(it1 != numSet.end() && it2 != numSet.end()) {
			int lca = findLCA(0, N - 1, 0, N - 1, num1, num2);
			if(num1 == lca) {
				printf("%d is an ancestor of %d.\n", lca, num2);
			} else if(num2 == lca) {
				printf("%d is an ancestor of %d.\n", lca, num1);
			} else {
				printf("LCA of %d and %d is %d.\n", num1, num2, lca);
			}
		} else if(it1 == numSet.end() && it2 != numSet.end()) {
			printf("ERROR: %d is not found.\n", num1);
		} else if(it1 != numSet.end() && it2 == numSet.end()) {
			printf("ERROR: %d is not found.\n", num2);
		} else {
			printf("ERROR: %d and %d are not found.\n", num1, num2);
		}
	}
}

int findLCA(int preLeft, int preRight, int inLeft, int inRight, int num1, int num2) {
	int k, countLeft = 0, countRight = 0;
	int left, right;
	for(int i = 0; i <= (inRight - inLeft) / 2; i++) {	//˫ָ������ͬʱ���м�ƽ� 
		left = inLeft + i;	//leftָ�����߿�ʼ�ƽ��м� 
		if(inOrder[left] == preOrder[preLeft]) {	//���leftָ���ҵ���preOrder[preLeft]
			k = left;	//��k = left 
			break;	//����ѭ�� 
		}
		if(inOrder[left] == num1 || inOrder[left] == num2) {	//���leftָ�뷢����num1��num2 
			countLeft++;	//���������з��ֵ�num1��num2�Ĵ�����1 
		}
		right = inRight - i;	//rightָ����ұ߿�ʼ�ƽ��м� 
		if(inOrder[right] == preOrder[preLeft]){	//���rightָ�뷢����num1��num2 
			k = right;	//��k = right 
			break;	//����ѭ�� 
		}
		if(inOrder[right] == num1 || inOrder[right] == num2){	//���rightָ�뷢����num1��num2 
			countRight++;	//���������з��ֵ�num1��num2�Ĵ�����1
		}
	}
	int numLeft = k - inLeft;	//�������еĽڵ���� 
	if(num1 == preOrder[preLeft] || num2 == preOrder[preLeft]){	//���num1��num2�͵�ǰ���ڵ���� 
		return preOrder[preLeft];	//��ǰ���ڵ����num1��num2������������� 
	}
	if(countLeft == 2){	//���������з���num1��num2�Ĵ���Ϊ2�Σ�˵��num1��num2�����������У��ݹ������������Ѱ�� 
		return findLCA(preLeft + 1, preLeft + numLeft, inLeft, k - 1, num1, num2);
	}else if(countLeft == 1){	//���������з���num1��num2�Ĵ���Ϊ1�� 
		if(countRight == 1){	//���������з���num1��num2�Ĵ���Ϊ1�� 
			return preOrder[preLeft];	//��ǰ���ڵ����num1��num2������������� 
		}else if(countRight == 0){	//���������з���num1��num2�Ĵ���Ϊ0�� 
			if(k == left){	//���k == left��˵����������ȷʵֻ����num1��num2�е�һ������һ������������ 
				return preOrder[preLeft];	//��ǰ���ڵ����num1��num2������������� 	
			}else if(k == right){	//���k == right��˵����������ȷʵ������num1��num2��num1��num2������������ 
				return findLCA(preLeft + 1, preLeft + numLeft, inLeft, k - 1, num1, num2);	//˵��num1��num2�����������У��ݹ������������Ѱ�� 
			}
		}
	}else if(countLeft == 0){	//���������з���num1��num2�Ĵ���Ϊ0��  
		if(countRight == 2){	//���������з���num1��num2�Ĵ���Ϊ2�Σ�˵��num1��num2�����������У��ݹ������������Ѱ��
			return findLCA(preLeft + numLeft + 1, preRight, k + 1, inRight, num1, num2);
		}else if(countRight == 1){	//���������з���num1��num2�Ĵ���Ϊ1�� 
			if(k == right){	//���k == right��˵����������ȷʵֻ����num1��num2�е�һ������һ������������ 
				return preOrder[preLeft];	//��ǰ���ڵ����num1��num2�������������
			}else if(k == left){	//���k == left��˵����������ȷʵ������num1��num2��num1��num2������������ 
				return findLCA(preLeft + numLeft + 1, preRight, k + 1, inRight, num1, num2);	//�ݹ������������Ѱ��
			}
		}else if(countRight == 0){	//���������з���num1��num2�Ĵ���Ϊ0��
			if(k == right){	//���k == right��˵����������ȷʵ������num1��num2��num1��num2������������ 
				return findLCA(preLeft + 1, preLeft + numLeft, inLeft, k - 1, num1, num2);
			}else if(k == left){	//���k == left��˵����������ȷʵ������num1��num2��num1��num2������������
				return findLCA(preLeft + numLeft + 1, preRight, k + 1, inRight, num1, num2);
			}
		}
	}
}
