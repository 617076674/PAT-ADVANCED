#include<iostream>
#include<cstring>

int main() {
	int a, b;	//��ȡ��������a��b 
	scanf("%d %d", &a, &b);
	int sum = a + b;	//����� 
	if(sum == 0) {	//�Ժ�Ϊ0����������⴦�� 
		printf("0\n");
		return 0;
	}
	bool flag = true;	//flag���Ա�Ǻ��Ƿ��Ǹ��� 
	if(sum < 0) {
		flag = false;
		sum *= -1;	//������ת��Ϊ���� 
	}
	char result[15];
	int index = 0;	//��¼char����result���±� 
	int circle = 0;	//��¼ѭ����ÿ3���������һ��"," 
	while(sum > 0) {
		result[index++] = sum % 10 + '0';
		circle++;
		sum /= 10;
		if(circle % 3 == 0) {
			result[index++] = ',';
			circle = 0;
		}
	}
	if(result[index - 1] == ',') {	 
		if(!flag) {		
			result[index - 1] = '-';//���ĩλ��","���Һ��Ǹ�������","�滻Ϊ"-"�������"\0"�������	 
			result[index] = '\0';
		} else {
			result[index - 1] = '\0';//���ĩλ��","���ҺͲ��Ǹ�������","�滻Ϊ"\0"�������
		}
	} else {
		if(!flag) {	//���ĩλ����","���Һ��Ǹ��������"-" 
			result[index++] = '-';
		}
		result[index] = '\0';	//��ĩλ���"\0"������� 
	}
	for(int i = strlen(result) - 1; i >= 0; i--) {
		printf("%c", result[i]);
	}
	printf("\n");
	return 0;
}
