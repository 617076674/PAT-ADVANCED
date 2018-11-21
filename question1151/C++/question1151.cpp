#include<iostream>
#include<vector>
#include<set>

using namespace std;

set<int> numSet;	//存储 
vector<int> inOrder;	//中序遍历序列 
vector<int> preOrder;	//前序遍历序列 

int findLCA(int preLeft, int preRight, int inLeft, int inRight, int num1, int num2);

int main() {
	int M, N;
	scanf("%d %d", &M, &N);
	int num;
	for(int i = 0; i < N; i++) {
		scanf("%d", &num);
		inOrder.push_back(num);
		numSet.insert(num);	//用set集合存储键值，方便判断某节点是否存在 
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
	for(int i = 0; i <= (inRight - inLeft) / 2; i++) {	//双指针两边同时向中间逼近 
		left = inLeft + i;	//left指针从左边开始逼近中间 
		if(inOrder[left] == preOrder[preLeft]) {	//如果left指针找到了preOrder[preLeft]
			k = left;	//令k = left 
			break;	//跳出循环 
		}
		if(inOrder[left] == num1 || inOrder[left] == num2) {	//如果left指针发现了num1或num2 
			countLeft++;	//在左子树中发现的num1或num2的次数加1 
		}
		right = inRight - i;	//right指针从右边开始逼近中间 
		if(inOrder[right] == preOrder[preLeft]){	//如果right指针发现了num1或num2 
			k = right;	//令k = right 
			break;	//跳出循环 
		}
		if(inOrder[right] == num1 || inOrder[right] == num2){	//如果right指针发现了num1或num2 
			countRight++;	//在右子树中发现的num1或num2的次数加1
		}
	}
	int numLeft = k - inLeft;	//左子树中的节点个数 
	if(num1 == preOrder[preLeft] || num2 == preOrder[preLeft]){	//如果num1或num2和当前根节点相等 
		return preOrder[preLeft];	//当前根节点就是num1和num2的最近公共祖先 
	}
	if(countLeft == 2){	//在左子树中发现num1或num2的次数为2次，说明num1和num2都在左子树中，递归地在左子树中寻找 
		return findLCA(preLeft + 1, preLeft + numLeft, inLeft, k - 1, num1, num2);
	}else if(countLeft == 1){	//在左子树中发现num1或num2的次数为1次 
		if(countRight == 1){	//在右子树中发现num1或num2的次数为1次 
			return preOrder[preLeft];	//当前根节点就是num1和num2的最近公共祖先 
		}else if(countRight == 0){	//在右子树中发现num1或num2的次数为0次 
			if(k == left){	//如果k == left，说明左子树中确实只包含num1或num2中的一个，另一个在右子树中 
				return preOrder[preLeft];	//当前根节点就是num1和num2的最近公共祖先 	
			}else if(k == right){	//如果k == right，说明右子树中确实不包含num1或num2，num1和num2都在左子树中 
				return findLCA(preLeft + 1, preLeft + numLeft, inLeft, k - 1, num1, num2);	//说明num1和num2都在左子树中，递归地在左子树中寻找 
			}
		}
	}else if(countLeft == 0){	//在左子树中发现num1或num2的次数为0次  
		if(countRight == 2){	//在右子树中发现num1或num2的次数为2次，说明num1和num2都在右子树中，递归地在右子树中寻找
			return findLCA(preLeft + numLeft + 1, preRight, k + 1, inRight, num1, num2);
		}else if(countRight == 1){	//在右子树中发现num1或num2的次数为1次 
			if(k == right){	//如果k == right，说明右子树中确实只包含num1或num2中的一个，另一个在左子树中 
				return preOrder[preLeft];	//当前根节点就是num1和num2的最近公共祖先
			}else if(k == left){	//如果k == left，说明左子树中确实不包含num1或num2，num1和num2都在右子树中 
				return findLCA(preLeft + numLeft + 1, preRight, k + 1, inRight, num1, num2);	//递归地在右子树中寻找
			}
		}else if(countRight == 0){	//在右子树中发现num1或num2的次数为0次
			if(k == right){	//如果k == right，说明右子树中确实不包含num1或num2，num1和num2都在左子树中 
				return findLCA(preLeft + 1, preLeft + numLeft, inLeft, k - 1, num1, num2);
			}else if(k == left){	//如果k == left，说明左子树中确实不包含num1或num2，num1和num2都在右子树中
				return findLCA(preLeft + numLeft + 1, preRight, k + 1, inRight, num1, num2);
			}
		}
	}
}
