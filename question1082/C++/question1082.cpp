#include<iostream>
#include<cstring>

char num[10][5] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
char wei[5][5] = {"Shi", "Bai", "Qian", "Wan", "Yi"};

int main(){
	char str[15];
	scanf("%[^\n]", str);	//按字符串方式输入数字 
	int len = strlen(str);	//字符串长度
	int left = 0, right = len - 1;	//left与right分别指向字符串首尾元素
	if(str[0] == '-'){	//如果是负数，则输出"Fu"，并把left右移1位 
		printf("Fu");
		left++;
	} 
	while(left + 4 <= right){
		right -= 4;	//将right每次左移4位，直到left与right在同一节 
	}
	while(left < len){	//循环每次处理数字的一节（4位或小于4位） 
		bool flag = false;	//flag == false表示没有累积的0
		bool isPrint = false;	//isPrint == false表示该节没有输出过其中的位
		while(left <= right){	//从左至右处理数字中某节的每一位 
			if(left > 0 && str[left] == '0'){	//如果当前位为0且当前位不是首位，即对输入是0的情况做了特殊处理 
				flag = true;	//令标记flag为true 
			}else{	//如果当前位不为0 
				if(flag){	//如果存在累积的0 
					printf(" ling");
					flag = false; 
				}
				//只要不是首位（包括负号），后面的每一位前都要输出空格
				if(left > 0){
					printf(" ");
				}
				printf("%s", num[str[left] - '0']);	//输出当前位数字
				isPrint = true;	//该节至少有一位被输出
				if(left != right){	//某节中除了各位外，都需要输出十百千 
					printf(" %s", wei[right - left - 1]);
				} 
			}
			left++;	//left右移1位 
		}
		if(isPrint && right != len - 1){	//只要不是个位，就输出万或亿 
			printf(" %s", wei[(len - 1 - right) / 4 + 2]);
		}
		right += 4;	//right右移4位，输出下一节 
	}
	return 0;
}
