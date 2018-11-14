#include<iostream>
#include<cstring>

void reverse(char* str, int N);

int main() {
	int N;
	scanf("%d", &N);
	getchar();
	char input[N][257];
	for(int i = 0; i < N; i++) {
		scanf("%[^\n]", input[i]);
		reverse(input[i], strlen(input[i]));
		getchar();
	}
	char result[257];
	int index = 0;
	while(true) {
		bool flag = true;
		for(int i = 0; i < N - 1; i++) {
			if(index >= strlen(input[i]) || index >= strlen(input[i + 1]) || input[i][index] != input[i + 1][index]) {
				flag = false;
			}
		}
		if(!flag){
			break;
		}
		result[index] = input[0][index];
		index++;
	}
	result[index] = '\0';
	reverse(result, strlen(result));
	if(strlen(result) == 0){
		printf("nai\n");
	}else{
		printf("%s\n", result);
	} 
	return 0;
}

void reverse(char* str, int N){
	for(int i = 0; i < N / 2; i++){
		char temp = *(str + i);
		*(str + i) = *(str + N - i - 1);
		*(str + N - i - 1) = temp;
	}
}
