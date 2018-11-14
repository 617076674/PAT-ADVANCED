#include<iostream>
#include<string>

using namespace std;

int main() {
	string input;

	cin >> input;

	int flag = 0;
	int indexE = 0;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == 'E') {
			indexE = i;
			if (input[i + 1] == '+') {
				flag = 1;
			} else if (input[i + 1] == '-') {
				flag = 0;
			}
			break;
		}
	}

	int expr = 0;
	for (int i = indexE + 2; i < input.length(); i++) {
		expr = expr * 10 + input[i] - '0';
	}
	if (expr == 0) {
		for (int i = 0; i < indexE; i++) {
			if (input[i] == '+') {
				continue;
			}
			cout << input[i];
		}
		return 0;
	}

	if (flag) {
		if (expr >= indexE - 3) {
			for (int i = 0; i < indexE; i++) {
				if (input[i] == '.' || input[i] == '+') {
					continue;
				}
				cout << input[i];
			}
			for (int i = 0; i < expr - indexE + 3; i++) {
				cout << "0";
			}
		} else {
			for (int i = 0; i <= 2 + expr; i++) {
				if (input[i] == '.' || input[i] == '+') {
					continue;
				}
				cout << input[i];
			}
			cout << ".";
			for (int i = 3 + expr; i < indexE; i++) {
				cout << input[i];
			}
		}
	} else {
		if (input[0] == '-') {
			cout << "-";
		}
		for (int i = 0; i <= expr; i++) {
			if (i == 1) {
				cout << ".";
			} else {
				cout << "0";
			}
		}
		for (int i = 1; i < indexE; i++) {
			if (input[i] == '.') {
				continue;
			}
			cout << input[i];
		}
	}
}