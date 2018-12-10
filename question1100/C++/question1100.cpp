#include<iostream>
#include<string>
#include<sstream>
 
using namespace std;
 
int N; 
string lowStrings[13] = {"tret", "jan", "feb", "mar", "apr", "may", "jun", "jly", "aug", "sep", "oct", "nov", "dec"};
string highStrings[12] = {"tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", "syy", "lok", "mer", "jou"};
	
int marToEarth(string s);
string earthToMar(int num);
 
int main() {
	scanf("%d", &N);
	getchar();	//¶ÁÈ¡»»ÐÐ·û 
	string tempNum;
	int num;
	for (int i = 0; i < N; i++) {
		getline(cin, tempNum);
		if (tempNum[0] >= '0' && tempNum[0] <= '9') {
			stringstream transfer;
			transfer << tempNum;
			transfer >> num;
			cout << earthToMar(num) << endl;
		} else {
			cout << marToEarth(tempNum) << endl;
		}
	}
}
 
int marToEarth(string s) {
	if (s.length() <= 4) {
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
		int result = 0;
		for (int i = 0; i < 12; i++) {
			if (s.substr(0, 3).compare(highStrings[i]) == 0) {
				result += (i + 1) * 13;
				break;
			}
		}
		for (int i = 0; i < 13; i++) {
			if (s.substr(4, 3).compare(lowStrings[i]) == 0) {
				result += i;
				break;
			}
		}
		return result;
	}
}
 
string earthToMar(int num) {
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

