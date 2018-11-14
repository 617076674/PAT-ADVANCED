#include<iostream>

using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	int pre = 0;
	int now;
	int result = N * 5;
	for(int i = 0; i < N; i++){
		scanf("%d", &now);
		if(now > pre){
			result += (now - pre) * 6;
		}else if(now < pre){
			result += (pre - now) * 4;
		}
		pre = now;
	}
	printf("%d\n", result);
	return 0;
}
