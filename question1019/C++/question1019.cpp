#include<iostream>
#include<vector>

using namespace std;

bool isPalindromic(vector<int> result);

int main(){
	int N, b;
	scanf("%d %d", &N, &b);
	vector<int> result;
	while(N > 0){
		result.push_back(N % b);
		N /= b;
	}
	if(isPalindromic(result)){
		printf("Yes\n");
	}else{
		printf("No\n");
	}
	for(int i = result.size() - 1; i >= 0; i--){
		printf("%d", result[i]);
		if(i != 0){
			printf(" ");
		}else{
			printf("\n");
		}
	}
	return 0;
}

bool isPalindromic(vector<int> result){
	for(int i = 0; i < result.size() / 2; i++){
		if(result[i] != result[result.size() - 1 - i]){
			return false;
		}
	}
	return true;
}
