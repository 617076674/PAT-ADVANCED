#include<iostream>
#include<string>

using namespace std;

int main() {
	string input;
	cin >> input;
	int countP = 0;
	int countPA = 0;
	int countPAT = 0;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == 'P') {
			countP++;
			countP %= 1000000007;
		} else if (input[i] == 'A') {
			countPA += countP;
			countPA %= 1000000007;
		} else {
			countPAT += countPA;
			countPAT %= 1000000007;
		}
	}
	cout << countPAT;
	return 0;
}