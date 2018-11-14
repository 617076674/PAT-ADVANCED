#include<iostream>
#include<algorithm>

using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	int array[N];	//存放各数字当前所处的位置编号 
	int unOrdered = 0;	//unOrdered记录除0以外不在本位上的数的个数 
	int num; 
	for(int i = 0; i < N; i++){
		scanf("%d", &num);
		array[num] = i;
		if(array[i] != i && i != 0){
			unOrdered++;
		}
	}
	int k = 1;	//k存放除0以为当前不在本位上的最小数
	int result = 0;
	while(unOrdered > 0){
		//如果0在本位上，则寻找一个当前不在本位上的数与0交换 
		if(array[0] == 0){
			while(k < N){
				if(array[k] != k){
					swap(array[k], array[0]);
					result++;
					break;
				}
				k++;
			}
		}
		//只要0不在本位，就将0所在位置的数的当前所处位置与0的位置交换 
		while(array[0] != 0){
			swap(array[0], array[array[0]]);	//将0与array[0]交换 
			result++;	//交换次数加1 
			unOrdered--;	//不在本位上的数的个数减1 
		}
	} 
	printf("%d\n", result);
	return 0;
}
