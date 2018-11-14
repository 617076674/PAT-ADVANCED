#include<iostream>
#include<cstring>

using namespace std;

int main() {
	int k;
	scanf("%d", &k);
	char input[1001];
	scanf("%s", input);
	int flag[37];	//flag[0] ~ flag[25]代表a-z,flag[26] ~ flag[35]代表0~9,flag[36]代表_
	fill(flag, flag + 37, 0);	//0表示没出现过，1表示没破，2表示破了
	for(int i = 0; i < strlen(input); i++) {
		int count = 1;	//记录当前字符的出现次数 
		while(i + 1 < strlen(input) && input[i + 1] == input[i]) {
			count++;
			i++;
		}
		if(count % k == 0) {	//如果当前字符的出现次数是k的整数倍	
			if(input[i] >= 'a' && input[i] <= 'z') {
				if(flag[input[i] - 'a'] == 0){	//如果该字符没有出现过，则将其flag位置置为2表示破损 
					flag[input[i] - 'a'] = 2;	//如果该字符出现过其flag值是1，那么即使这里出现的次数是k的整数倍，也不应该认为该键破损 
				}
			} else if(input[i] >= '0' && input[i] <= '9') {
				if(flag[input[i] - '0' + 26] == 0){
					flag[input[i] - '0' + 26] = 2;
				}
			} else if(input[i] == '_') {
				if(flag[36] == 0){
					flag[36] = 2;
				}
			}
		} else {
			if(input[i] >= 'a' && input[i] <= 'z') {	//不管之前flag值怎么样，只要出现了不是k的整数倍的次数，该键就不是破损的 
				flag[input[i] - 'a'] = 1;
			} else if(input[i] >= '0' && input[i] <= '9') {
				flag[input[i] - '0' + 26] = 1;
			} else if(input[i] == '_') {
				flag[36] = 1;
			}
		}
	}
	bool output[37];	//表示该键是否已输出过，一个键只输出一次 
	fill(output, output + 37, false);
	for(int i = 0; i < strlen(input); i++) {
		if(input[i] >= 'a' && input[i] <= 'z') {
			if(flag[input[i] - 'a'] == 2 && !output[input[i] - 'a']){
				printf("%c", input[i]);
				output[input[i] - 'a'] = true;
			}
		} else if(input[i] >= '0' && input[i] <= '9') {
			if(flag[input[i] - '0' + 26] == 2 && !output[input[i] - '0' + 26]){
				printf("%c", input[i]);
				output[input[i] - '0' + 26] = true;
			}
		} else if(input[i] == '_') {
			if(flag[36] == 2 && !output[36]){
				printf("%c", input[i]);
				output[36] = true;
			}
		}
	}
	printf("\n");
	for(int i = 0; i < strlen(input); i++) {
		if(input[i] >= 'a' && input[i] <= 'z') {
			if(flag[input[i] - 'a'] == 1) {	//如果当前键不破损，直接打印该字符即可 
				printf("%c", input[i]);
			} else {	
				int count = 1;
				while(i + 1 < strlen(input) && input[i + 1] == input[i]) {
					count++;
					i++;
				}
				for(int j = 0; j < count / k; j++) {	//如果当前键是破损的，打印次数应该是其出现次数除以k 
					printf("%c", input[i]);
				}
			}
		} else if(input[i] >= '0' && input[i] <= '9') {
			if(flag[input[i] - '0' + 26] == 1) {	//如果当前键不破损，直接打印该字符即可 
				printf("%c", input[i]);
			} else {
				int count = 1;
				while(i + 1 < strlen(input) && input[i + 1] == input[i]) {
					count++;
					i++;
				}
				for(int j = 0; j < count / k; j++) {	//如果当前键是破损的，打印次数应该是其出现次数除以k  
					printf("%c", input[i]);
				}
			}
		} else if(input[i] == '_') {
			if(flag[36] == 1) {	//如果当前键不破损，直接打印该字符即可
				printf("%c", input[i]);
			} else {
				int count = 1;
				while(i + 1 < strlen(input) && input[i + 1] == input[i]) {
					count++;
					i++;
				}
				for(int j = 0; j < count / k; j++) {	//如果当前键是破损的，打印次数应该是其出现次数除以k 
					printf("%c", input[i]);
				}
			}
		}
	}
}
