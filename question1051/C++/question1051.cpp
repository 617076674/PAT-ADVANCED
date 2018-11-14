#include<iostream>
#include<stack>

using namespace std;

int main() {
	int M, N, K;
	scanf("%d %d %d", &M, &N, &K);
	int nums[N];
	stack<int> numStack;
	for(int i = 0; i < K; i++) {
		while(!numStack.empty()) {
			numStack.pop();
		}
		for(int j = 0; j < N; j++) {
			scanf("%d", &nums[j]);
		}
		int index = 0;
		bool flag = true;
		for(int j = 1; j <= N; j++) {
			numStack.push(j);
			if(numStack.size() > M) {
				flag = false;
				break;
			}
			while(!numStack.empty() && numStack.top() == nums[index]) {
				index++;
				numStack.pop();
			}
		}
		if(flag && numStack.empty()) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
}
