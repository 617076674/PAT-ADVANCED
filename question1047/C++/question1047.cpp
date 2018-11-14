#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool cmp(char* s1, char* s2);

int main(){
	int N, K;
	scanf("%d %d", &N, &K);
	vector<char*> courses[K + 1];	//第i门课程的学生为courses[i]
	char name[N][5];
	int id;
	int count;
	int course;
	for(int i = 0; i < N; i++){
		scanf("%s %d", name[i], &count);
		for(int j = 0; j < count; j++){
			scanf("%d", &course);
			courses[course].push_back(name[i]);
		}
	}
	for(int i = 1; i <= K; i++){
		printf("%d %d\n", i, courses[i].size());
		sort(courses[i].begin(), courses[i].end(), cmp);
		for(int j = 0; j < courses[i].size(); j++){
			printf("%s\n", courses[i][j]);
		}
	} 
	return 0;
}

bool cmp(char* s1, char* s2){
	for(int i = 0; i < 4; i++){
		if(*(s1 + i) != *(s2 + i)){
			return *(s1 + i) < *(s2 + i);
		}
	}
} 
