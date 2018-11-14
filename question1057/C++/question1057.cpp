#include<iostream>
#include<stack>
#include<cstring>

using namespace std;

int table[100001];
int block[317];
stack<int> numStack;

void printMedian();

int main() {
	fill(table, table + 100001, 0);
	fill(block, block + 317, 0);
	int N;
	scanf("%d", &N);
	char operation[11];
	for(int i = 0; i < N; i++) {
		scanf("%s", operation);
		if(strcmp(operation, "Pop") == 0) {
			if(numStack.empty()) {
				printf("Invalid\n");
			} else {
				int num = numStack.top();
				table[num]--;
				block[num / 316]--;
				printf("%d\n", num);
				numStack.pop();
			}
		} else if(strcmp(operation, "PeekMedian") == 0) {
			if(numStack.empty()) {
				printf("Invalid\n");
			} else {
				printMedian();
			}
		} else if(strcmp(operation, "Push") == 0) {
			int num;
			scanf("%d", &num);
			table[num]++;
			block[num / 316]++;
			numStack.push(num);
		}
	}
	return 0;
}

void printMedian() {
	int k = (numStack.size() + 1) / 2;
	int sum = 0;
	int index = 0;
	for(int i = 0; i < 317; i++){
		sum += block[i];
		if(sum >= k){
			index = i;
			sum -= block[i];
			break;
		}
	}
	k -= sum;
	for(int i = index * 316; i < (index + 1) * 316 && i < 100001; i++){
		if(table[i] == 0){
			continue;
		}
		k -= table[i];
		if(k <= 0){
			printf("%d\n", i);
			break;
		}
	}
}
