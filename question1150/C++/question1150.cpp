#include<iostream>
#include<set>

using namespace std;

int INF = 1000000000;
int graph[201][201];

int main() {
	for(int i = 0; i < 201; i++) {
		for(int j = 0; j < 201; j++) {
			graph[i][j] = INF;
		}
	}
	int N, M;
	scanf("%d %d", &N, &M);
	int city1, city2, dist;
	for(int i = 0; i < M; i++) {
		scanf("%d %d %d", &city1, &city2, &dist);
		graph[city1][city2] = graph[city2][city1] = dist;
	}
	int K;
	scanf("%d", &K);
	int minIndex, min = INF;
	for(int i = 1; i <= K; i++) {
		int n;
		scanf("%d", &n);
		int nums[n];
		set<int> numSet;
		for(int j = 0; j < n; j++) {
			scanf("%d", &nums[j]);
			numSet.insert(nums[j]);
		}
		int distance = 0;
		bool flag = true;
		for(int j = 0; j < n - 1; j++) {
			if(graph[nums[j]][nums[j + 1]] == INF) {
				flag = false;
				break;
			}
			distance += graph[nums[j]][nums[j + 1]];
		}
		if(numSet.size() == N && nums[0] == nums[n - 1] && flag) {
			if(n == N + 1) {
				printf("Path %d: %d (TS simple cycle)\n", i, distance);
			} else {
				printf("Path %d: %d (TS cycle)\n", i, distance);
			}
			if(distance < min) {
				min = distance;
				minIndex = i;
			}
		} else {
			if(flag) {
				printf("Path %d: %d (Not a TS cycle)\n", i, distance);
			} else {
				printf("Path %d: NA (Not a TS cycle)\n", i);
			}
		}
	}
	printf("Shortest Dist(%d) = %d\n", minIndex, min);
	return 0;
}
