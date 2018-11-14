#include<iostream>
#include<algorithm>

using namespace std;

int countSwap(int* array, int N);

int main(){
	int N;
	scanf("%d", &N);
	int array[N];
	for(int i = 0; i < N; i++){
		scanf("%d", &array[i]);
	}
	printf("%d\n", countSwap(array, N));
	return 0;
}

int countSwap(int* array, int N){
	bool flag = true;
	for(int i = 0; i < N; i++){
		if(*(array + i) != i){
			flag = false;
			break;
		}
	}
	//flag = true说明array数组已经已经排好序了 
	if(flag){
		return 0;
	}
	//如果array数组的第一个元素是0 
	if(*array == 0){
		for(int i = 1; i < N; i++){
			if(*(array + i) != i){
				swap(*array, *(array + i));
				break;
			}
		}
		return 1 + countSwap(array, N);
	}else{
		for(int i = 0; i < N; i++){
			if(*(array + i) == 0){
				int another = -1;
				for(int j = 0; j < N; j++){
					if(i == *(array + j)){
						another = j;
						break;
					}
				}
				swap(*(array + i), *(array + another));
				break;
			}
		}
		return 1 + countSwap(array, N);
	} 
} 
