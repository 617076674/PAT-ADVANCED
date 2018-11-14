#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

int main(){
	char numEnglish[10][6] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	char input[101];
	scanf("%s", input);
	int sum = 0;
	for(int i = 0; i < strlen(input); i++){
		sum += input[i] - '0';
	}
	vector<int> result;
	if(sum == 0){
		printf("zero\n");
		return 0;
	}
	while(sum > 0){
		result.push_back(sum % 10);
		sum /= 10;
	}
	for(int i = result.size() - 1; i >= 0; i--){
		printf("%s", numEnglish[result[i]]);
		if(i != 0){
			printf(" ");
		}else{
			printf("\n");
		}
	}
	return 0;
}
 
