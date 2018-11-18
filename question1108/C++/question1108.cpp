#include<iostream>
#include<cstring>
#include<cmath>

bool isValid(char* input);	//判断输入的数字是否有效 
double changeToNum(char* input);	//将输入的数字转换成double类型 

int main() {
	int N;
	scanf("%d", &N);	//读取数字总数N	 
	char input[100];	//用char数组来记录每一个输入的数字 
	int count = 0;	//统计有效数字出现的个数 
	double sum = 0.0;	//统计有效数字总和 
	for(int i = 0; i < N; i++) {
		scanf("%s", input);
		if(isValid(input)) {	//如果输入的数字是有效的 
			count++;	//有效数字个数加1 
			sum += changeToNum(input);	//更新有效数字和 
		} else {
			printf("ERROR: %s is not a legal number\n", input);	//如果输入的数字是无效的，输出错误信息 
		}
	}
	if(count == 0) {	//如果没有有效数字出现 
		printf("The average of 0 numbers is Undefined\n");
	} else if(count == 1) {	//如果有效数字出现的次数是1 
		printf("The average of 1 number is %.2f\n", sum);
	} else {	//如果有效数字出现的次数大于等于2 
		printf("The average of %d numbers is %.2f\n", count, sum / count);
	}
	return 0;
}

bool isValid(char* input) {
	int len = strlen(input);
	int countPoint = 0;	//统计输入数字中小数点的个数 
	for(int i = 0; i < len; i++) {
		if(i == 0 && input[i] == '-') {	//对于输入数字中的第一个字符，允许是"-" 
			continue;
		}
		if(input[i] == '.') {	//遇到小数点 
			countPoint++;	//小数点个数加1 
		} else if(!(input[i] >= '0' && input[i] <= '9')) {	//如果遇到了0 ~ 9之外的字符，该数字一定不合法 
			return false;
		}
	}
	if(countPoint >= 2) {	//如果出现了2个及以上的小数点，该数字一定不合法 
		return false;
	}
	if(countPoint == 1) {	//如果小数点出现了一次 
		int pointIndex = strstr(input, ".") - input;	//寻找小数点的索引 
		if(len - 1 - pointIndex > 2) {	//如果小数点之后的字符数量大于2，说明该数字由大于2位的小数部分，该数字不合法 
			return false;
		}
	}
	double num = changeToNum(input);	//将该数字转换成double类型 
	if(num >= -1000 && num <= 1000) {	//如果该数字在[-1000, 1000]范围内，合法 
		return true;
	} else {	//如果该数字不在[-1000, 1000]范围内，不合法 
		return false;
	}
}

double changeToNum(char* input) {
	int len = strlen(input);
	if(strstr(input, ".")) {	//如果该数字中有小数点 
		int pointIndex = strstr(input, ".") - input;	//获得小数点的索引 
		if(input[0] == '-') {	//如果该数字第一个符号是"-" 
			double result = 0.0;
			for(int i = 1; i < pointIndex; i++) {	//从该数字的第二个符号，即索引1开始计算该数字整数部分的值 
				result = result * 10 + input[i] - '0';
			}
			for(int i = pointIndex + 1; i < len; i++) {	//从小数点索引后一位开始计算小数部分的值 
				result += (input[i] - '0') / (pow(10, i - pointIndex));
			}
			return -result;	//返回负的结果，因为该数字的第一个符号是"-" 
		} else {	 //如果该数字第一个符号不是"-" 
			double result = 0.0;
			for(int i = 0; i < pointIndex; i++) {	//从该数字的第一个符号，即索引0开始计算该数字整数部分的值 
				result = result * 10 + input[i] - '0';
			}
			for(int i = pointIndex + 1; i < len; i++) {	//从小数点索引后一位开始计算小数部分的值
				result += (input[i] - '0') / (pow(10, i - pointIndex));
			}
			return result;	//返回结果
		}
	} else {	//如果该数字中没有小数点，即没有小数部分 
		if(input[0] == '-') {	//如果该数字第一个符号是"-"
			double result = 0.0;
			for(int i = 1; i < len; i++) {	//从该数字的第二个符号，即索引1开始计算该数字的值 
				result = result * 10 + input[i] - '0';
			}
			return -result;	//返回负的结果，因为该数字的第一个符号是"-"
		} else {	//如果该数字第一个符号不是"-"
			double result = 0.0;
			for(int i = 0; i < len; i++) {	//从该数字的第一个符号，即索引0开始计算该数字的值 
				result = result * 10 + input[i] - '0';
			}
			return result;	//返回结果 
		}
	}
}
