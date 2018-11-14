#include<iostream>
#include<string>

using namespace std;

string reverse(string s);
string add(string s1, string s2);
bool judge(string s1, string s2);

int main() {
	string input;
	cin >> input;
	string sum = add(input, input);
	if(judge(input, sum)) {
		cout << "Yes" << endl;
	} else {
		cout << "No" << endl;
	}
	cout << sum << endl;
	return 0;
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

bool judge(string s1, string s2) {
	int count1[10];	//count1[i]表示s1字符串中字符i出现的次数
	fill(count1, count1 + 10, 0);
	for(int i = 0; i < s1.length(); i++) {
		count1[s1[i] - '0']++;
	}
	int count2[10];	//count2[i]表示s2字符串中字符i出现的次数
	fill(count2, count2 + 10, 0);
	for(int i = 0; i < s2.length(); i++) {
		count2[s2[i] - '0']++;
	}
	for(int i = 0; i < 10; i++) {
		if(count1[i] != count2[i]) {
			return false;
		}
	}
	return true;
}
