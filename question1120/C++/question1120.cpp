#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

int main(){
	int friendID[37];
	fill(friendID, friendID + 37, 0);
	int N;
	scanf("%d", &N);
	char num[5];
	for(int i = 0; i < N; i++){
		scanf("%s", num);
		int temp = 0;
		for(int i = 0; i < strlen(num); i++){
			temp += num[i] - '0';
		}
		friendID[temp] = 1;
	}
	int count = 0;
	vector<int> result;
	for(int i = 0; i < 37; i++){
		if(friendID[i] == 1){
			count++;
			result.push_back(i);
		}
	}
	printf("%d\n", count);
	for(int i = 0; i < result.size(); i++){
		printf("%d", result[i]);
		if(i != result.size() - 1){
			printf(" ");
		}else{
			printf("\n");
		}
	}
	return 0;
} 
