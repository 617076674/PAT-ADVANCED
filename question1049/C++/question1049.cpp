#include<iostream>
#include<string>
#include<cmath>
 
using namespace std;
 
int main() {
	string input;
	cin >> input;
	int result = 0;
	for(int i = 0; i < input.length(); i++) {
		if(i == 0) {
			if(input[i] == '1') {
				int right = 0;
				for(int j = 1; j < input.length(); j++) {
					right = right * 10 + input[j] - '0';
				}
				result += right + 1;
			} else {
				result += (int)pow(10, input.length() - 1);
			}
		} else if(i == input.length() - 1) {
			int left = 0;
			for(int j = 0; j < input.length() - 1; j++) {
				left = left * 10 + input[j] - '0';
			}
			result += left + 1;
			if(input[i] == '0') {
				result--;
			}
		} else {
			int left = 0, right = 0;
			for(int j = 0; j < i; j++){
				left = left * 10 + input[j] - '0';
			}
			for(int j = i + 1; j < input.length(); j++){
				right = right * 10 + input[j] - '0';
			}
			if(input[i] == '0'){
				result += left * (int)pow(10, input.length() - i - 1);
			}else if(input[i] == '1'){
				result += left * (int)pow(10, input.length() - i - 1) + right + 1;
			}else{
				result += (left + 1) * (int)pow(10, input.length() - i - 1);
			}
		}
	}
	printf("%d\n", result);
	return 0;
}

