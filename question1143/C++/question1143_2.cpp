#include<iostream>
#include<set>

using namespace std;

int M, N;
set<int> numSet;
int num1, num2;

int main() {
	scanf("%d %d", &M, &N);
	int nums[N];
	for(int i = 0; i < N; i++) {
		scanf("%d", &nums[i]);
		numSet.insert(nums[i]);
	}
	for(int i = 0; i < M; i++) {
		scanf("%d %d", &num1, &num2);
		set<int>::iterator it1 = numSet.find(num1);
		set<int>::iterator it2 = numSet.find(num2);
		if(it1 != numSet.end() && it2 != numSet.end()) {
			for(int j = 0; j < N; j++) {
				if((nums[j] >= num1 && nums[j] <= num2) || (nums[j] >= num2 && nums[j] <= num1)) {
					if(num1 != nums[j] && num2 != nums[j]) {
						printf("LCA of %d and %d is %d.\n", num1, num2, nums[j]);
					}else if(num1 == nums[j]){
						printf("%d is an ancestor of %d.\n", num1, num2);
					}else if(num2 == nums[j]){
						printf("%d is an ancestor of %d.\n", num2, num1);
					}
					break;
				}
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
