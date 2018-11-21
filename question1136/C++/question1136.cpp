#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

string reverseString(string s);
bool isPalindromeNum(string s);
string add(string s1, string s2);

int main(){
	string input;
	getline(cin, input);
	string A = input;
	string B;
	int i = 0;
	for(; i < 10; i++){
		if(isPalindromeNum(A)){
			cout << A << " is a palindromic number." << endl;
			break;
		}
		B = reverseString(A);
		cout << A << " + " << B << " = " << add(A, B) << endl;
		A = add(A, B);
	}
	if(i == 10){
		cout << "Not found in 10 iterations." << endl;
	}
	return 0;
}

string reverseString(string s){
	string result = "";
	for(int i = s.length() - 1; i >= 0; i--){
		result += s[i];
	}
	return result;
}

bool isPalindromeNum(string s){
	for(int i = 0; i <= s.length() / 2; i++){
		if(s[i] != s[s.length() - 1 - i]){
			return false;
		}
	}
	return true;
}

string add(string s1, string s2){
	int index = 0;
	int flag = 0;
	string result = "";
	while(true){
		if(index >= s1.length() && index >= s2.length()){
			if(flag != 0){
				char c = '0' + flag;
				result = c + result;
			}
			break;
		}else if(index < s1.length() && index >= s2.length()){
			int sum = s1[index] - '0' + flag;
			if(sum >= 10){
				sum -= 10;
				char c = '0' + sum;
				result = c + result;
				flag = 1;
			}else{
				char c = '0' + sum;
				result = c + result;
				flag = 0;
			}
		}else if(index >= s1.length() && index < s2.length()){
			int sum = s2[index] - '0' + flag;
			if(sum >= 10){
				sum -= 10;
				char c = '0' + sum;
				result = c + result;
				flag = 1;
			}else{
				char c = '0' + sum;
				result = c + result;
				flag = 0;
			}
		}else if(index < s1.length() && index < s2.length()){
			int sum = s1[index] - '0' + flag + s2[index] - '0';
			if(sum >= 10){
				sum -= 10;
				char c = '0' + sum;
				result = c + result;
				flag = 1;
			}else{
				char c = '0' + sum;
				result = c + result;
				flag = 0;
			}
		}
		index++;
	}
	return result;
}

