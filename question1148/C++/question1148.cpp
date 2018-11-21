#include<iostream>
#include<vector>

using namespace std;

int main() {
	int N;
	scanf("%d", &N);
	int nums[N + 1];
	for(int i = 1; i < N + 1; i++) {
		scanf("%d", &nums[i]);
	}
	int wolf1, wolf2;
	for(wolf1 = 1; wolf1 <= N; wolf1++) {
		for(wolf2 = wolf1 + 1; wolf2 <= N; wolf2++) {
			vector<int> lie;
			for(int i = 1; i < N + 1; i++) {
				if(nums[i] < 0 && -nums[i] != wolf1 && -nums[i] != wolf2) {
					lie.push_back(i);
				} else if(nums[i] > 0 && (nums[i] == wolf1 || nums[i] == wolf2)) {
					lie.push_back(i);
				}
			}
			if(lie.size() == 2) {
				if(lie[0] == wolf1 || lie[0] == wolf2) {
					if(lie[1] != wolf1 && lie[1] != wolf2) {
						printf("%d %d\n", wolf1, wolf2);
						return 0;
					}
				} else if(lie[1] == wolf1 || lie[1] == wolf2) {
					if(lie[0] != wolf1 && lie[0] != wolf2) {
						printf("%d %d\n", wolf1, wolf2);
						return 0;
					}
				}
			}
		}
	}
	printf("No Solution\n");
	return 0;
}
