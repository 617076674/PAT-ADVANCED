#include<iostream>
#include<string>

using namespace std;

int main() {
	string s1;
	string s2;
	string s3;
	string s4;
	string weeks[] = { "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN" };

	cin >> s1 >> s2 >> s3 >> s4;

	int index = -1;
	for (int i = 0; i < s1.length(); i++) {
		if (i >= s2.length()) {
			break;
		}
		if (s1[i] >= 'A' && s1[i] <= 'G' && s1[i] == s2[i]) {
			index = i;
			cout << weeks[s1[i] - 'A'] << " ";
			break;
		}
	}

	for (int i = index + 1; i < s1.length(); i++) {
		if (i >= s2.length()) {
			break;
		}
		if (((s1[i] >= '0' && s1[i] <= '9') || (s1[i] >= 'A' && s1[i] <= 'N')) && s1[i] == s2[i]){
			if ((s1[i] >= '0' && s1[i] <= '9')) {
				cout << "0" << s1[i] << ":";
				break;
			} else {
				int hour = s1[i] - 'A' + 10;
				cout << hour << ":";
			}
			break;
		}
	}
	for (int i = 0; i < s3.length(); i++) {
		if (i >= s4.length()) {
			break;
		}
		if (((s3[i] >= 'a' && s3[i] <= 'z') || (s3[i] >= 'A' && s3[i] <= 'Z')) && s3[i] == s4[i]) {
			if (i <= 9) {
				cout << "0" << i;
			} else {
				cout << i;
			}
			break;
		}
	}
}