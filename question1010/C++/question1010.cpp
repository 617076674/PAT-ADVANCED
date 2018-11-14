#include<iostream>
#include<string>

using namespace std;

string N1, N2;
int tag, radix;

int main() {
	cin >> N1 >> N2 >> tag >> radix;
	//���tagΪ2���򽻻�N1��N2��ֵ 
	if(tag == 2) {
		string temp = N1;
		N1 = N2;
		N2 = temp;
	}
	//��N1ת��Ϊ10�������ݣ���Ŀ����������֤��10��������long long��Χ�ڣ� 
	long long num1 = 0;
	for(int i = 0; i < N1.length(); i++) {
		if(N1[i] >= 'a' && N1[i] <= 'z') {
			num1 = num1 * radix + N1[i] - 'a' + 10;
		} else {
			num1 = num1 * radix + N1[i] - '0';
		}
	}
	//left����ΪN2����С���� 
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
	//right����ΪN2�������� 
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
		} else if(num2 < 0) {	//���num2������long long�ķ�Χ���϶���num1Ҫ�� 
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
