#include<iostream>
#include<string>
#include<sstream>

using namespace std;

int marToEarth(string s, string* lowStrings, string* highStrings);
string earthToMar(int num, string* lowStrings, string* highStrings);

int main() {
	string lowStrings[13] = { "tret", "jan", "feb", "mar", "apr", "may", "jun", "jly", "aug", "sep", "oct", "nov", "dec" };
	string highStrings[12] = { "tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", "syy", "lok", "mer", "jou" };
	int count;
	cin >> count;
	
	
	string tempNum;
	getline(cin, tempNum);
	int num;

	for (int i = 0; i < count; i++) {
		getline(cin, tempNum);
		if (tempNum[0] >= '0' && tempNum[0] <= '9') {
			stringstream transfer;
			transfer << tempNum;
			transfer >> num;
			cout << earthToMar(num, lowStrings, highStrings);
		} else {
			cout << marToEarth(tempNum, lowStrings, highStrings);
		}
		if (i != count - 1) {
			cout << endl;
		}
	}
}

int marToEarth(string s, string* lowStrings, string* highStrings) {
	int spaceIndex = -1;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			spaceIndex = i;
			break;
		}
	}
	if (spaceIndex == -1) {
		for (int i = 0; i < 13; i++) {
			if (s.compare(lowStrings[i]) == 0) {
				return i;
			}
		}
		for (int i = 0; i < 12; i++) {
			if (s.compare(highStrings[i]) == 0) {
				return (i + 1) * 13;
			}
		}
	} else {
		string s1 = s.substr(0, 3);
		string s2 = s.substr(spaceIndex + 1, 3);
		int result = 0;
		for (int i = 0; i < 12; i++) {
			if (s1.compare(highStrings[i]) == 0) {
				result += (i + 1) * 13;
				break;
			}
		}
		for (int i = 0; i < 13; i++) {
			if (s2.compare(lowStrings[i]) == 0) {
				result += i;
				break;
			}
		}
		return result;
	}
}

string earthToMar(int num, string* lowStrings, string* highStrings) {
	if (num <= 12) {
		return lowStrings[num];
	} else {
		string result = "";
		result += highStrings[num / 13 - 1];
		if (num % 13 != 0) {
			result += " ";
			result += lowStrings[num % 13];
		}
		return result;
	}
}