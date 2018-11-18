#include<iostream>
#include<cstring>

int main() {
	int a, b;	//读取输入数据a和b 
	scanf("%d %d", &a, &b);
	int sum = a + b;	//计算和 
	if(sum == 0) {	//对和为0的情况做特殊处理 
		printf("0\n");
		return 0;
	}
	bool flag = true;	//flag用以标记和是否是负数 
	if(sum < 0) {
		flag = false;
		sum *= -1;	//将负数转变为正数 
	}
	char result[15];
	int index = 0;	//记录char数组result的下标 
	int circle = 0;	//记录循环，每3个数字添加一个"," 
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
			result[index - 1] = '-';//如果末位是","，且和是负数，将","替换为"-"，并添加"\0"结束标记	 
			result[index] = '\0';
		} else {
			result[index - 1] = '\0';//如果末位是","，且和不是负数，将","替换为"\0"结束标记
		}
	} else {
		if(!flag) {	//如果末位不是","，且和是负数，添加"-" 
			result[index++] = '-';
		}
		result[index] = '\0';	//在末位添加"\0"结束标记 
	}
	for(int i = strlen(result) - 1; i >= 0; i--) {
		printf("%c", result[i]);
	}
	printf("\n");
	return 0;
}
