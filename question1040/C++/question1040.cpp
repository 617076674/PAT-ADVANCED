#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

int main() {
	char input[1001];
	scanf("%[^\n]", input);
	int len = strlen(input);
	bool dp[len][len];
	for(int i = 0; i < len; i++) {
		dp[i][i] = true;
	}
	int result = 1;
	for(int k = -1; k >= -len + 1; k--) {
		for(int i = len + k - 1; i >= 0; i--) {
			if(input[i] == input[i - k]) {
				if(i + 1 > i - k - 1) {	//��ʱ˵�����Ӵ��ĳ��ȵ���2��ֱ����Ϊ�����Ӵ� 
					dp[i][i - k] = true;
				} else {
					dp[i][i - k] = dp[i + 1][i - k - 1]; 
				}
			} else {
				dp[i][i - k] = false;
			}
			if(dp[i][i - k] && 1 - k > result) {
				result = 1 - k;
			}
		}
	}
	printf("%d\n", result);
	return 0;
}
