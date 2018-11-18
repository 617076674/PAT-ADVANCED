#include<iostream>
#include<algorithm>

using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	double nums[N];
	for(int i = 0; i < N; i++){
		scanf("%lf", &nums[i]);
	}
	sort(nums, nums + N);
	double result = nums[0];
	for(int i = 1; i < N; i++){
		result = (result + nums[i]) / 2;
	}
	printf("%d\n", (int)result);
	return 0; 
}
