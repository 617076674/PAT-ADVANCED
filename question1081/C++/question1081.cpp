#include<iostream>
#include<cmath>

using namespace std;

struct digit {
	long long numerator;
	long long denominator;
	digit() {};
	digit(long long _numerator, long long _denominator) : numerator(_numerator), denominator(_denominator) {};
};

long long gcd(long long a, long long b);
digit add(digit d1, digit d2);

int main() {
	int N;
	scanf("%d", &N);
	digit result = digit(0, 1);
	digit tempDigit;
	for(int i = 0; i < N; i++) {
		scanf("%lld/%lld", &tempDigit.numerator, &tempDigit.denominator);
		result = add(result, tempDigit);
	}
	if(result.numerator == 0){
		printf("0\n");
		return 0;
	}
	if(result.numerator / result.denominator != 0) {
		printf("%lld", result.numerator / result.denominator);
	}
	if(result.numerator % result.denominator != 0) {
		if(result.numerator / result.denominator != 0) {
			printf(" ");
		}
		printf("%lld/%lld\n", result.numerator % result.denominator, result.denominator);
	}
	return 0;
}

long long gcd(long long a, long long b) {
	if(a < b) {
		return gcd(b, a);
	}
	if(b == 0) {
		return a;
	}
	return gcd(b, a % b);
}

digit add(digit d1, digit d2) {
	long long newDenominator = d1.denominator * d2.denominator;
	long long newNumerator = d1.numerator * d2.denominator + d2.numerator * d1.denominator;
	long long common = gcd(abs(newDenominator), abs(newNumerator));	//防止负数传进去 
	return digit(newNumerator / common, newDenominator / common);
}
