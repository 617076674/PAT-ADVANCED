#include<iostream>
#include<string>

using namespace std;

int findIndexSlash(string s);
long calculateNumerator(string s);
long calculateDenominator(string s);
long gcd(long num1, long num2);
void showFraction(long numerator, long denominator);
void showResults(long numerator1, long numerator2, long denominator1, long denominator2, char c);

int main() {

	string s1;
	string s2;

	cin >> s1 >> s2;

	int n1 = s1.length();
	int n2 = s2.length();

	long numerator1 = calculateNumerator(s1);
	long numerator2 = calculateNumerator(s2);

	long denominator1 = calculateDenominator(s1);
	long denominator2 = calculateDenominator(s2);

	showResults(numerator1, numerator2, denominator1, denominator2, '+');
	printf("\n");
	showResults(numerator1, numerator2, denominator1, denominator2, '-');
	printf("\n");
	showResults(numerator1, numerator2, denominator1, denominator2, '*');
	printf("\n");
	showResults(numerator1, numerator2, denominator1, denominator2, '/');
}

int findIndexSlash(string s) {
	int indexSlash = -1;
	for(int i = 0; i < s.length(); i++) {
		if(s[i] == '/') {
			indexSlash = i;
			break;
		}
	}
	return indexSlash;
}

long calculateNumerator(string s) {
	int indexSlash = findIndexSlash(s);
	if(s[0] == '-') {
		long result = 0;
		for(int i = 1; i < indexSlash; i++) {
			result = result * 10 + (s[i] - '0');
		}
		return -result;
	} else {
		long result = 0;
		for(int i = 0; i < indexSlash; i++) {
			result = result * 10 + (s[i] - '0');
		}
		return result;
	}
}

long calculateDenominator(string s) {
	int indexSlash = findIndexSlash(s);
	long result = 0;
	for(int i = indexSlash + 1; i < s.length(); i++) {
		result = result * 10 + (s[i] - '0');
	}
	return result;
}

long gcd(long num1, long num2){
	if(num1 < num2){
		long temp = num1;
		num1 = num2;
		num2 = temp;
	}
	if(num2 == 0)
        return num1;
    return gcd(num2, num1 % num2);
}

void showFraction(long numerator, long denominator){
	bool flag = false;
	if(numerator < 0){
		numerator *= -1;
		flag = true;
	}
	if(flag) {
		cout << "(";
	}
	if(numerator % denominator == 0) {
		if(flag){
			cout << "-";
		}
		cout << (numerator / denominator);
	} else {
		long maxGCD = gcd(numerator, denominator);
		if(flag){
			cout << "-";
		}
		if(numerator < denominator){
			cout << (numerator / maxGCD) << "/" << (denominator / maxGCD);
		}else{
			long merchant = numerator / denominator;
			cout << merchant << " " << ((numerator - merchant * denominator) / maxGCD) << "/" << (denominator / maxGCD);
		}
		
	}
	if(flag) {
		cout << ")";
	}
}

void showResults(long numerator1, long numerator2, long denominator1, long denominator2, char c) {
	showFraction(numerator1, denominator1);
	cout << " " << c << " ";
	showFraction(numerator2, denominator2);
	cout << " = ";

	if(c == '+') {
		long newNumerator1 = numerator1 * denominator2;
		long newNumerator2 = numerator2 * denominator1;
		long newDenominator = denominator1 * denominator2;
		long newNumerator = newNumerator1 + newNumerator2;
		showFraction(newNumerator, newDenominator);
	}else if(c == '-'){
		long newNumerator1 = numerator1 * denominator2;
		long newNumerator2 = numerator2 * denominator1;
		long newDenominator = denominator1 * denominator2;
		long newNumerator = newNumerator1 - newNumerator2;
		showFraction(newNumerator, newDenominator);
	}else if(c == '*'){
		long newDenominator = denominator1 * denominator2;
		long newNumerator = numerator1 * numerator2;
		showFraction(newNumerator, newDenominator);
	}else if(c == '/'){
		long newDenominator = denominator1 * numerator2;
		long newNumerator = numerator1 * denominator2;
		if(newDenominator < 0){
			newNumerator *= -1;
			newDenominator *= -1;
		}
		if(newDenominator == 0){
			cout << "Inf";
		}else{
			showFraction(newNumerator, newDenominator);
		}
	}
}
