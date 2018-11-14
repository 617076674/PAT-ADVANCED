#include<iostream>
#include<algorithm>

using namespace std;

bool isInsertionSort(int* nums1, int* nums2, int N);
void nextInsertionSort(int* nums1, int* nums2, int N);
void nextMergeSort(int* nums1, int* nums2, int N);

int main() {
	int N;
	scanf("%d", &N);
	int nums1[N];
	int nums2[N];
	for(int i = 0; i < N; i++) {
		scanf("%d", &nums1[i]);
	}
	for(int i = 0; i < N; i++) {
		scanf("%d", &nums2[i]);
	}
	if(isInsertionSort(nums1, nums2, N)) {
		printf("Insertion Sort\n");
		nextInsertionSort(nums1, nums2, N);
	} else {
		printf("Merge Sort\n");
		nextMergeSort(nums1, nums2, N);
	}
	for(int i = 0; i < N; i++){
		printf("%d", nums2[i]);
		if(i != N - 1){
			printf(" ");
		}else{
			printf("\n");
		}
	}
	return 0;
}

bool isInsertionSort(int* nums1, int* nums2, int N) {
	int k = -1;
	for(int i = 0; i < N; i++) {
		if(*(nums2 + i + 1) < *(nums2 + i)) {
			k = i + 1;
			break;
		}
	}
	for(int i = k; i < N; i++) {
		if(*(nums1 + i) != *(nums2 + i)) {
			return false;
		}
	}
	return true;
}

void nextInsertionSort(int* nums1, int* nums2, int N) {
	int k = -1;
	for(int i = 0; i < N; i++) {
		if(*(nums2 + i + 1) < *(nums2 + i)) {
			k = i + 1;
			break;
		}
	}
	int temp = *(nums2 + k);
	int i = k;
	for(; *(nums2 + i - 1) > temp; i--){
		*(nums2 + i) = *(nums2 + i - 1);
	}
	*(nums2 + i) = temp;
}

void nextMergeSort(int* nums1, int* nums2, int N){
	int size = 2;
	bool flag = true;
	while(true){
		for(int i = 0; i < N; i += size){
			for(int j = i; j < i + size - 1 && j < N - 1; j++){	//j < N - 1±ðÂäÁË 
				if(*(nums2 + j + 1) < *(nums2 + j)){
					flag = false;
				}
			}
		}
		if(!flag){
			break;
		}
		size *= 2;
	}
	for(int i = 0; i < N; i += size){
		sort(nums2 + i, nums2 + min(i + size, N));
	}
}
