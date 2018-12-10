#include<iostream>

using namespace std;

int N, index = -1;

bool isInsertionSort(int input1[], int input2[]);
void nextInsertionSort(int* input);
void nextHeapSort(int* input);
void print(int* input);

int main() {
	scanf("%d", &N);
	int input1[N];
	for(int i = 0; i < N; i++) {
		scanf("%d", &input1[i]);
	}
	int input2[N];
	for(int i = 0; i < N; i++) {
		scanf("%d", &input2[i]);
	}
	if(isInsertionSort(input1, input2)) {
		printf("Insertion Sort\n");
		nextInsertionSort(input2);
	} else {
		printf("Heap Sort\n");
		nextHeapSort(input2);
	}
	print(input2);
	return 0;
}

bool isInsertionSort(int input1[], int input2[]) {
	for(int i = 0; i < N; i++) {
		if(input2[i + 1] < input2[i]) {
			index = i + 1;
			break;
		}
	}
	for(int i = index; i < N; i++) {
		if(input1[i] != input2[i]) {
			return false;
		}
	}
	return true;
}

void nextInsertionSort(int* input) {
	int temp = input[index];
	int j = index - 1;
	for(; input[j] > temp && j >= 0; j--) {
		input[j + 1] = input[j];
	}
	input[j + 1] = temp;
}

void nextHeapSort(int* input) {
	int range;
	for(int i = 1; i < N; i++){
		if(input[i] > input[0]){
			range = i - 1;
			break;
		}
	}
	swap(input[0], input[range]);
	int i = 0, j = 2 * i + 1;
	while(j <= range - 1) {
		if(j + 1 <= range - 1 && input[j + 1] > input[j]) {
			j++;
		}
		if(input[j] > input[i]) {
			swap(input[i], input[j]);
			i = j;
			j = 2 * i + 1;
		} else {
			break;
		}
	}
}

void print(int* input) {
	for(int i = 0; i < N; i++) {
		printf("%d", input[i]);
		if(i != N - 1) {
			printf(" ");
		} else {
			printf("\n");
		}
	}
}
