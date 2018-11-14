#include<iostream>

using namespace std;

int main(){
	char result[3] = {'W', 'T', 'L'};
	double max, num;
	int index;
	double profit = 1.0;
	for(int i = 0; i < 3; i++){
		max = 0.0;
		index = -1;
		for(int j = 0; j < 3; j++){
			scanf("%lf", &num);
			if(num > max){
				max = num;
				index = j;
			}
		}
		printf("%c ", result[index]);
		profit *= max;
	}
	printf("%.2f\n", (profit * 0.65 - 1) * 2);
} 
