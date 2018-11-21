#include<iostream>
#include<vector>
#include<set>

using namespace std;

vector<int> preOrder;
vector<int> inOrder;
int num1, num2;

int findAncestor(int preLeft, int preRight, int inLeft, int inRight, int num1, int num2);

int main() {
	int M, N;
	scanf("%d %d", &M, &N);
	int num;
	set<int> numSet;
	for(int i = 0; i < N; i++) {
		scanf("%d", &num);
		preOrder.push_back(num);
		numSet.insert(num);
	}
	for(set<int>::iterator it = numSet.begin(); it != numSet.end(); it++){
		inOrder.push_back(*it);
	}
	set<int>::iterator it1, it2;
	for(int i = 0; i < M; i++) {
		scanf("%d %d", &num1, &num2);
		it1 = numSet.find(num1);
		it2 = numSet.find(num2);
		if(it1 != numSet.end() && it2 != numSet.end()) {
			int ancestor = findAncestor(0, N - 1, 0, N - 1, num1, num2);
			if(ancestor == num1){
				printf("%d is an ancestor of %d.\n", ancestor, num2);
			}else if(ancestor == num2){
				printf("%d is an ancestor of %d.\n", ancestor, num1);
			}else{
				printf("LCA of %d and %d is %d.\n", num1, num2, ancestor);
			}
		} else if(it1 == numSet.end() && it2 != numSet.end()) {
			printf("ERROR: %d is not found.\n", num1);
		} else if(it1 != numSet.end() && it2 == numSet.end()) {
			printf("ERROR: %d is not found.\n", num2);
		} else {
			printf("ERROR: %d and %d are not found.\n", num1, num2);
		}
	}
	return 0;
}

int findAncestor(int preLeft, int preRight, int inLeft, int inRight, int num1, int num2) {
	int k;
	int left = inLeft, right = inRight;	//二分查找法 
	while(left <= right){
		int mid = left + (right - left) / 2;
		if(inOrder[mid] == preOrder[preLeft]){
			k = mid;
			break;
		}else if(inOrder[mid] < preOrder[preLeft]){
			left = mid + 1;
		}else{
			right = mid - 1;
		}
	}
	int numLeft = k - inLeft; 
	if(num1 < preOrder[preLeft] && num2 < preOrder[preLeft]){
		return findAncestor(preLeft + 1, preLeft + numLeft, inLeft, k - 1, num1, num2);
	}else if(num1 > preOrder[preLeft] && num2 > preOrder[preLeft]){
		return findAncestor(preLeft + numLeft + 1, preRight, k + 1, inRight, num1, num2);
	}else{
		return preOrder[preLeft];
	}
}
