#include<iostream>
#include<vector>

using namespace std;

vector<int> preOrder;
vector<int> inOrder;
int result;

void findResult(int preLeft, int preRight, int inLeft, int inRight);

int main() {
	int N;
	scanf("%d", &N);
	int num;
	for(int i = 0; i < N; i++) {
		scanf("%d", &num);
		preOrder.push_back(num);
	}
	for(int i = 0; i < N; i++) {
		scanf("%d", &num);
		inOrder.push_back(num);
	}
	findResult(0, preOrder.size() - 1, 0, inOrder.size() - 1);
	printf("%d\n", result);
	return 0;
}

void findResult(int preLeft, int preRight, int inLeft, int inRight) {
	if(preLeft == preRight) {
		result = preOrder[preLeft];
		return;
	}
	int k;
	for(int i = inLeft; i <= inRight; i++) {
		if(inOrder[i] == preOrder[preLeft]) {
			k = i;
			break;
		}
	}
	int numLeft = k - inLeft;
	if(numLeft == 0) {
		findResult(preLeft + numLeft + 1, preRight, k + 1, inRight);
	} else {
		findResult(preLeft + 1, preLeft + numLeft, inLeft, k - 1);
	}
}
