#include<iostream>
#include<cstring>

using namespace std;

int main() {
	int k;
	scanf("%d", &k);
	char input[1001];
	scanf("%s", input);
	int flag[37];	//flag[0] ~ flag[25]����a-z,flag[26] ~ flag[35]����0~9,flag[36]����_
	fill(flag, flag + 37, 0);	//0��ʾû���ֹ���1��ʾû�ƣ�2��ʾ����
	for(int i = 0; i < strlen(input); i++) {
		int count = 1;	//��¼��ǰ�ַ��ĳ��ִ��� 
		while(i + 1 < strlen(input) && input[i + 1] == input[i]) {
			count++;
			i++;
		}
		if(count % k == 0) {	//�����ǰ�ַ��ĳ��ִ�����k��������	
			if(input[i] >= 'a' && input[i] <= 'z') {
				if(flag[input[i] - 'a'] == 0){	//������ַ�û�г��ֹ�������flagλ����Ϊ2��ʾ���� 
					flag[input[i] - 'a'] = 2;	//������ַ����ֹ���flagֵ��1����ô��ʹ������ֵĴ�����k����������Ҳ��Ӧ����Ϊ�ü����� 
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
			if(input[i] >= 'a' && input[i] <= 'z') {	//����֮ǰflagֵ��ô����ֻҪ�����˲���k���������Ĵ������ü��Ͳ�������� 
				flag[input[i] - 'a'] = 1;
			} else if(input[i] >= '0' && input[i] <= '9') {
				flag[input[i] - '0' + 26] = 1;
			} else if(input[i] == '_') {
				flag[36] = 1;
			}
		}
	}
	bool output[37];	//��ʾ�ü��Ƿ����������һ����ֻ���һ�� 
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
			if(flag[input[i] - 'a'] == 1) {	//�����ǰ��������ֱ�Ӵ�ӡ���ַ����� 
				printf("%c", input[i]);
			} else {	
				int count = 1;
				while(i + 1 < strlen(input) && input[i + 1] == input[i]) {
					count++;
					i++;
				}
				for(int j = 0; j < count / k; j++) {	//�����ǰ��������ģ���ӡ����Ӧ��������ִ�������k 
					printf("%c", input[i]);
				}
			}
		} else if(input[i] >= '0' && input[i] <= '9') {
			if(flag[input[i] - '0' + 26] == 1) {	//�����ǰ��������ֱ�Ӵ�ӡ���ַ����� 
				printf("%c", input[i]);
			} else {
				int count = 1;
				while(i + 1 < strlen(input) && input[i + 1] == input[i]) {
					count++;
					i++;
				}
				for(int j = 0; j < count / k; j++) {	//�����ǰ��������ģ���ӡ����Ӧ��������ִ�������k  
					printf("%c", input[i]);
				}
			}
		} else if(input[i] == '_') {
			if(flag[36] == 1) {	//�����ǰ��������ֱ�Ӵ�ӡ���ַ�����
				printf("%c", input[i]);
			} else {
				int count = 1;
				while(i + 1 < strlen(input) && input[i + 1] == input[i]) {
					count++;
					i++;
				}
				for(int j = 0; j < count / k; j++) {	//�����ǰ��������ģ���ӡ����Ӧ��������ִ�������k 
					printf("%c", input[i]);
				}
			}
		}
	}
}
