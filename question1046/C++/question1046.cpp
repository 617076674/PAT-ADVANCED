#include<iostream>

using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	int distances[N];
	for(int i = 0; i < N; i++){
		scanf("%d", &distances[i]);
	}
	int M;
	scanf("%d", &M);
	int num1, num2, distance1, distance2;
	for(int i = 0; i < M; i++){
		scanf("%d %d", &num1, &num2);
		if(num1 > num2){
			int temp = num1;
			num1 = num2;
			num2 = temp;
		}
		distance1 = 0;
		for(int j = num1 - 1; j < num2 - 1; j++){
			distance1 += distances[j];
		}
		distance2 = 0;
		for(int j = num2 - 1; j < N; j++){
			distance2 += distances[j];
		}
		for(int j = 0; j < num1 - 1; j++){
			distance2 += distances[j];
		}
		printf("%d\n", min(distance1, distance2));
	}
	return 0;
}
