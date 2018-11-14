#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int change(char* name);

int main(){
	int N, K, courseId, courseCapacity;
	scanf("%d %d", &N, &K);
	char name[5];
	vector<int> students[175761];
	for(int i = 0; i < K; i++){
		scanf("%d %d", &courseId, &courseCapacity);
		for(int j = 0; j < courseCapacity; j++){
			scanf("%s", name);
			int id = change(name);
			students[id].push_back(courseId);
		}
	}
	for(int i = 0; i < N; i++){
		scanf("%s", name);
		int id = change(name);
		printf("%s ", name);
		printf("%d", students[id].size());
		sort(students[id].begin(), students[id].end());
		for(int j = 0; j < students[id].size(); j++){
			printf(" %d", students[id][j]);
		}
		printf("\n");
	}
	return 0;
}

int change(char* name){
	int result = 0;
	for(int i = 0; i < 3; i++){
		result = result * 26 + *(name + i) - 'A';
	}
	result = result * 10 + *(name + 3) - '0';
	return result;
}
