#include<iostream>
#include<cstring>

char num[10][5] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
char wei[5][5] = {"Shi", "Bai", "Qian", "Wan", "Yi"};

int main(){
	char str[15];
	scanf("%[^\n]", str);	//���ַ�����ʽ�������� 
	int len = strlen(str);	//�ַ�������
	int left = 0, right = len - 1;	//left��right�ֱ�ָ���ַ�����βԪ��
	if(str[0] == '-'){	//����Ǹ����������"Fu"������left����1λ 
		printf("Fu");
		left++;
	} 
	while(left + 4 <= right){
		right -= 4;	//��rightÿ������4λ��ֱ��left��right��ͬһ�� 
	}
	while(left < len){	//ѭ��ÿ�δ������ֵ�һ�ڣ�4λ��С��4λ�� 
		bool flag = false;	//flag == false��ʾû���ۻ���0
		bool isPrint = false;	//isPrint == false��ʾ�ý�û����������е�λ
		while(left <= right){	//�������Ҵ���������ĳ�ڵ�ÿһλ 
			if(left > 0 && str[left] == '0'){	//�����ǰλΪ0�ҵ�ǰλ������λ������������0������������⴦�� 
				flag = true;	//����flagΪtrue 
			}else{	//�����ǰλ��Ϊ0 
				if(flag){	//��������ۻ���0 
					printf(" ling");
					flag = false; 
				}
				//ֻҪ������λ���������ţ��������ÿһλǰ��Ҫ����ո�
				if(left > 0){
					printf(" ");
				}
				printf("%s", num[str[left] - '0']);	//�����ǰλ����
				isPrint = true;	//�ý�������һλ�����
				if(left != right){	//ĳ���г��˸�λ�⣬����Ҫ���ʮ��ǧ 
					printf(" %s", wei[right - left - 1]);
				} 
			}
			left++;	//left����1λ 
		}
		if(isPrint && right != len - 1){	//ֻҪ���Ǹ�λ������������ 
			printf(" %s", wei[(len - 1 - right) / 4 + 2]);
		}
		right += 4;	//right����4λ�������һ�� 
	}
	return 0;
}
