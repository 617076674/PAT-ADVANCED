#include<iostream>

using namespace std;

string reverse(string s);
string add(string s1, string s2);
bool isPalindromicNumber(string s);

int main(){
	string N, tempN;
	int K;
	cin >> N >> K;
	int step = 0;
	while(!isPalindromicNumber(N)){
		tempN = add(N, reverse(N));
		N = tempN;
		step++;
		if(step >= K){
			break;
		}
	}
	cout << N << endl;
	cout << step << endl;
}

string reverse(string s) {
	string result = "";
	for(int i = s.length() - 1; i >= 0; i--) {
		result += s[i];
	}
	return result;
}

string add(string s1, string s2) {
	int flag = 0;
	s1 = reverse(s1);
	s2 = reverse(s2);
	string result = "";
	int index1 = 0;
	int index2 = 0;
	while(true) {
		if(index1 >= s1.length() && index2 >= s2.length()) {
			if(flag != 0) {
				result += flag + '0';
			}
			break;
		} else {
			int num = s1[index1] - '0' + s2[index2] - '0' + flag;
			if(num >= 10) {
				num -= 10;
				flag = 1;
			} else {
				flag = 0;
			}
			result += num + '0';
			index1++;
			index2++;
		}
	}
	return reverse(result);
}

bool isPalindromicNumber(string s){
	for(int i = 0; i < s.length() / 2; i++){
		if(s[i] != s[s.length() - 1 - i]){
			return false;
		}
	}
	return true;
}
