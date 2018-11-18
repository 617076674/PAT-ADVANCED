#include<iostream>
#include<cstring>

long long changeToNum(char* input, int left, int right);

int main(){
	int N;
	scanf("%d", &N);
	char input[15];
	long long Z, A, B;
	for(int i = 0; i < N; i++){
		scanf("%s", input);
		Z = changeToNum(input, 0, strlen(input) - 1);
		A = changeToNum(input, 0, strlen(input) / 2 - 1);
		B = changeToNum(input, strlen(input) / 2, strlen(input) - 1);
		if(A * B != 0 && Z % (A * B) == 0){	//注意A * B如果是0，需要输出"No" 
			printf("Yes\n");
		}else{
			printf("No\n");
		}
	}
	return 0;
} 

long long changeToNum(char* input, int left, int right){
	long long result = 0;
	for(int i = left; i <= right; i++){
		result = result * 10 + input[i] - '0';
	}
	return result;
}
