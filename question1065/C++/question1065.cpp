#include<iostream>

using namespace std;

bool judge(long long A, long long B, long long C);

int main() {
	int T;
	long long A, B, C;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++) {
		scanf("%lld %lld %lld", &A, &B, &C);
		if(judge(A, B, C)) {
			printf("Case #%d: true\n", i);
		} else {
			printf("Case #%d: false\n", i);
		}
	}
}

bool judge(long long A, long long B, long long C) {
	if(A > 0 && B > 0) {
		if(C < 0) {
			return true;
		} else {
			if(A + B > C || A + B < 0) {
				return true;
			} else {
				return false;
			}
		}
	} else if(A < 0 && B < 0) {
		if(C > 0) {
			return false;
		} else {
			if(A + B > C && A + B < 0) {
				return true;
			} else {
				return false;
			}
		}
	} else {
		if(A + B > C) {
			return true;
		} else {
			return false;
		}
	}
}
