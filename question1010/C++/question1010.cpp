#include<iostream>
#include<string>

using namespace std;

string N1, N2;
int tag, radix;

int main() {
	cin >> N1 >> N2 >> tag >> radix;
	//如果tag为2，则交换N1和N2的值 
	if(tag == 2) {
		string temp = N1;
		N1 = N2;
		N2 = temp;
	}
	//将N1转换为10进制数据（题目测试用例保证该10进制数在long long范围内） 
	long long num1 = 0;
	for(int i = 0; i < N1.length(); i++) {
		if(N1[i] >= 'a' && N1[i] <= 'z') {
			num1 = num1 * radix + N1[i] - 'a' + 10;
		} else {
			num1 = num1 * radix + N1[i] - '0';
		}
	}
	//left定义为N2的最小进制 
	long long left = -1;
	for(int i = 0; i < N2.length(); i++) {
		if(N2[i] >= 'a' && N2[i] <= 'z') {
			if(N2[i] - 'a' + 10 > left - 1) {
				left = N2[i] - 'a' + 10 + 1;
			}
		} else {
			if(N2[i] - '0' > left - 1) {
				left = N2[i] - '0' + 1;
			}
		}
	}
	//right定义为N2的最大进制 
	long long right = max(left, num1 + 1);
	while(left <= right) {
		long long mid = left + (right - left) / 2;
		long long num2 = 0;
		for(int i = 0; i < N2.length(); i++) {
			if(N2[i] >= 'a' && N2[i] <= 'z') {
				num2 = num2 * mid + N2[i] - 'a' + 10;
			} else {
				num2 = num2 * mid + N2[i] - '0';
			}

		}
		if(num1 == num2) {
			printf("%lld\n", mid);
			break;
		} else if(num2 < 0) {	//如果num2超过了long long的范围，肯定比num1要大 
			right = mid - 1;
		} else if(num1 < num2) {
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}
	if(left > right) {
		printf("Impossible\n");
	}
	return 0;
}
