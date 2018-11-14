#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

struct message{
	char user[11];
	char password[11];
};

bool needModified(char* password, int N);

int main(){
	int N;
	scanf("%d", &N);
	char user[11], password[11];
	vector<message> result;
	message tempMessage;
	for(int i = 0; i < N; i++){
		scanf("%s %s", user, password);
		if(needModified(password, strlen(password))){
			for(int i = 0; i < strlen(password); i++){
				if(password[i] == '1'){
					password[i] = '@';
				}else if(password[i] == '0'){
					password[i] = '%';
				}else if(password[i] == 'l'){
					password[i] = 'L';
				}else if(password[i] == 'O'){
					password[i] = 'o';
				}
			}
			strcpy(tempMessage.user, user);
			strcpy(tempMessage.password, password);
			result.push_back(tempMessage);
		}
	}
	if(result.size() == 0 && N == 1){
		printf("There is 1 account and no account is modified\n");
	}else if(result.size() == 0 && N > 1){
		printf("There are %d accounts and no account is modified\n", N);
	}else{
		printf("%d\n", result.size());
		for(int i = 0; i < result.size(); i++){
			printf("%s %s\n", result[i].user, result[i].password);
		}
	}
	return 0;
}

bool needModified(char* password, int N){
	for(int i = 0; i < N; i++){
		char temp = *(password + i);
		if(temp == '1' || temp == 'l' || temp == '0' || temp == 'O'){
			return true;
		}
	}
	return false;
}
