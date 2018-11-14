#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N;
vector<int> input1;
vector<int> input2;

bool isInsertionSort();
void nextInsertionSort();
void nextHeapSort();
void print();

int main() {
	cin >> N;
	int num;
	for(int i = 0; i < N; i++) {
		cin >> num;
		input1.push_back(num);
	}
	for(int i = 0; i < N; i++) {
		cin >> num;
		input2.push_back(num);
	}
	if(isInsertionSort()) {
		cout << "Insertion Sort" << endl;
		nextInsertionSort();
	} else {
		cout << "Heap Sort" << endl;
		nextHeapSort();
	}
	print();
	return 0;
}

bool isInsertionSort() {
	int k = 0;
	for(int i = 0; i < N - 1; i++) {
		if(input2[i] > input2[i + 1]) {
			k = i + 1;
			break;
		}
	}
	for(int i = k; i < N; i++) {
		if(input1[i] != input2[i]) {
			return false;
		}
	}
	return true;
}

void nextInsertionSort() {
	int k = 0;
	for(int i = 0; i < N - 1; i++) {
		if(input2[i] > input2[i + 1]) {
			k = i + 1;
			break;
		}
	}
	int j = k - 1;
	int temp = input2[k];
	for(; input2[j] > temp; j--) {
		input2[j + 1] = input2[j];
	}
	input2[j + 1] = temp;
}

void nextHeapSort() {
	int k;
	for(int i = N - 1; i >= 0; i--) {
		bool flag = true;
		for(int j = 0; j < i; j++) {
			if(input2[j] > input2[i]) {
				flag = false;
			}
		}
		if(!flag) {
			k = i;
			break;
		}
	}
	swap(input2[0], input2[k]);
	int i = 0;
	int j = 2 * i + 1;
	while(j <= k - 1) {
		if(j + 1 <= k - 1 && input2[j + 1] > input2[j]) {
			j = j + 1;
		}
		if(input2[j] > input2[i]) {
			swap(input2[i], input2[j]);
			i = j;
			j = 2 * i + 1;
		}else{
			break;
		}
	}
}

void print() {
	for(int i = 0; i < input2.size(); i++) {
		cout << input2[i];
		if(i != input2.size() - 1) {
			cout << " ";
		}
	}
	cout << endl;
}
