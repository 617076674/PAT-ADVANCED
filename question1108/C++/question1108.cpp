#include<iostream>
#include<cstring>
#include<cmath>

bool isValid(char* input);	//�ж�����������Ƿ���Ч 
double changeToNum(char* input);	//�����������ת����double���� 

int main() {
	int N;
	scanf("%d", &N);	//��ȡ��������N	 
	char input[100];	//��char��������¼ÿһ����������� 
	int count = 0;	//ͳ����Ч���ֳ��ֵĸ��� 
	double sum = 0.0;	//ͳ����Ч�����ܺ� 
	for(int i = 0; i < N; i++) {
		scanf("%s", input);
		if(isValid(input)) {	//����������������Ч�� 
			count++;	//��Ч���ָ�����1 
			sum += changeToNum(input);	//������Ч���ֺ� 
		} else {
			printf("ERROR: %s is not a legal number\n", input);	//����������������Ч�ģ����������Ϣ 
		}
	}
	if(count == 0) {	//���û����Ч���ֳ��� 
		printf("The average of 0 numbers is Undefined\n");
	} else if(count == 1) {	//�����Ч���ֳ��ֵĴ�����1 
		printf("The average of 1 number is %.2f\n", sum);
	} else {	//�����Ч���ֳ��ֵĴ������ڵ���2 
		printf("The average of %d numbers is %.2f\n", count, sum / count);
	}
	return 0;
}

bool isValid(char* input) {
	int len = strlen(input);
	int countPoint = 0;	//ͳ������������С����ĸ��� 
	for(int i = 0; i < len; i++) {
		if(i == 0 && input[i] == '-') {	//�������������еĵ�һ���ַ���������"-" 
			continue;
		}
		if(input[i] == '.') {	//����С���� 
			countPoint++;	//С���������1 
		} else if(!(input[i] >= '0' && input[i] <= '9')) {	//���������0 ~ 9֮����ַ���������һ�����Ϸ� 
			return false;
		}
	}
	if(countPoint >= 2) {	//���������2�������ϵ�С���㣬������һ�����Ϸ� 
		return false;
	}
	if(countPoint == 1) {	//���С���������һ�� 
		int pointIndex = strstr(input, ".") - input;	//Ѱ��С��������� 
		if(len - 1 - pointIndex > 2) {	//���С����֮����ַ���������2��˵���������ɴ���2λ��С�����֣������ֲ��Ϸ� 
			return false;
		}
	}
	double num = changeToNum(input);	//��������ת����double���� 
	if(num >= -1000 && num <= 1000) {	//�����������[-1000, 1000]��Χ�ڣ��Ϸ� 
		return true;
	} else {	//��������ֲ���[-1000, 1000]��Χ�ڣ����Ϸ� 
		return false;
	}
}

double changeToNum(char* input) {
	int len = strlen(input);
	if(strstr(input, ".")) {	//�������������С���� 
		int pointIndex = strstr(input, ".") - input;	//���С��������� 
		if(input[0] == '-') {	//��������ֵ�һ��������"-" 
			double result = 0.0;
			for(int i = 1; i < pointIndex; i++) {	//�Ӹ����ֵĵڶ������ţ�������1��ʼ����������������ֵ�ֵ 
				result = result * 10 + input[i] - '0';
			}
			for(int i = pointIndex + 1; i < len; i++) {	//��С����������һλ��ʼ����С�����ֵ�ֵ 
				result += (input[i] - '0') / (pow(10, i - pointIndex));
			}
			return -result;	//���ظ��Ľ������Ϊ�����ֵĵ�һ��������"-" 
		} else {	 //��������ֵ�һ�����Ų���"-" 
			double result = 0.0;
			for(int i = 0; i < pointIndex; i++) {	//�Ӹ����ֵĵ�һ�����ţ�������0��ʼ����������������ֵ�ֵ 
				result = result * 10 + input[i] - '0';
			}
			for(int i = pointIndex + 1; i < len; i++) {	//��С����������һλ��ʼ����С�����ֵ�ֵ
				result += (input[i] - '0') / (pow(10, i - pointIndex));
			}
			return result;	//���ؽ��
		}
	} else {	//�����������û��С���㣬��û��С������ 
		if(input[0] == '-') {	//��������ֵ�һ��������"-"
			double result = 0.0;
			for(int i = 1; i < len; i++) {	//�Ӹ����ֵĵڶ������ţ�������1��ʼ��������ֵ�ֵ 
				result = result * 10 + input[i] - '0';
			}
			return -result;	//���ظ��Ľ������Ϊ�����ֵĵ�һ��������"-"
		} else {	//��������ֵ�һ�����Ų���"-"
			double result = 0.0;
			for(int i = 0; i < len; i++) {	//�Ӹ����ֵĵ�һ�����ţ�������0��ʼ��������ֵ�ֵ 
				result = result * 10 + input[i] - '0';
			}
			return result;	//���ؽ�� 
		}
	}
}
