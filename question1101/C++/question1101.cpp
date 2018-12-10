#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
	int N;
	scanf("%d", &N);
	int num, beforeSort[N], afterSort[N];
	vector<int> result;
	for (int i = 0; i < N; i++) {
		scanf("%d", &num);
		beforeSort[i] = afterSort[i] = num;
	}
	sort(afterSort, afterSort + N);
	int max = 0;
	for (int i = 0; i < N; i++) {
		if (afterSort[i] == beforeSort[i] && afterSort[i] > max) {
			result.push_back(afterSort[i]);
		}
		if (beforeSort[i] > max) {
			max = beforeSort[i];
		}
	}
	printf("%d\n", result.size());
	for (int i = 0; i < result.size(); i++) {
		printf("%d", result[i]);
		if (i != result.size() - 1) {
			printf(" ");
		}
	}
	printf("\n");
	return 0;
}
