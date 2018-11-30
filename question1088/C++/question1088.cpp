#include<iostream>

using namespace std;

long long numerator1, numerator2, denominator1, denominator2, newDenominator, newNumerator;

long long gcd(long long num1, long long num2);
void showFraction(long long numerator, long long denominator);
void showResults(long long numerator1, long long numerator2, long long denominator1, long long denominator2, char c);

int main() {
	scanf("%lld/%lld %lld/%lld", &numerator1, &denominator1, &numerator2, &denominator2); 
	showResults(numerator1, numerator2, denominator1, denominator2, '+');
	printf("\n");
	showResults(numerator1, numerator2, denominator1, denominator2, '-');
	printf("\n");
	showResults(numerator1, numerator2, denominator1, denominator2, '*');
	printf("\n");
	showResults(numerator1, numerator2, denominator1, denominator2, '/');
	printf("\n");
	return 0;
}

long long gcd(long long num1, long long num2){
	if(num1 < num2){
		long long temp = num1;
		num1 = num2;
		num2 = temp;
	}
	if(num2 == 0)
        return num1;
    return gcd(num2, num1 % num2);
}

void showFraction(long long numerator, long long denominator){
	bool flag = false;
	if(numerator < 0){
		numerator *= -1;
		flag = true;
	}
	if(flag) {
		printf("(");
	}
	if(numerator % denominator == 0) {
		if(flag){
			printf("-");
		}
		printf("%lld", numerator / denominator);
	} else {
		long long maxGCD = gcd(numerator, denominator);
		if(flag){
			printf("-");
		}
		if(numerator < denominator){
			printf("%lld/%lld", numerator / maxGCD, denominator / maxGCD);
		}else{
			long long merchant = numerator / denominator;
			printf("%lld %lld/%lld", merchant, (numerator - merchant * denominator) / maxGCD, denominator / maxGCD);
		}	
	}
	if(flag) {
		printf(")");
	}
}

void showResults(long long numerator1, long long numerator2, long long denominator1, long long denominator2, char c) {
	showFraction(numerator1, denominator1);
	printf(" %c ", c); 
	showFraction(numerator2, denominator2);
	printf(" = ");
	if(c == '+') {
		newDenominator = denominator1 * denominator2;
		newNumerator = numerator1 * denominator2 + numerator2 * denominator1;
		showFraction(newNumerator, newDenominator);
	}else if(c == '-'){
		newDenominator = denominator1 * denominator2;
		newNumerator = numerator1 * denominator2 - numerator2 * denominator1;
		showFraction(newNumerator, newDenominator);
	}else if(c == '*'){
		newDenominator = denominator1 * denominator2;
		newNumerator = numerator1 * numerator2;
		showFraction(newNumerator, newDenominator);
	}else if(c == '/'){
		newDenominator = denominator1 * numerator2;
		newNumerator = numerator1 * denominator2;
		if(newDenominator < 0){
			newNumerator *= -1;
			newDenominator *= -1;
		}
		if(newDenominator == 0){
			printf("Inf");
		}else{
			showFraction(newNumerator, newDenominator);
		}
	}
}
