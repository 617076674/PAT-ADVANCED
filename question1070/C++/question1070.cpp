#include<iostream>
#include<algorithm>

using namespace std;

int main(){
	int N;
	cin >> N;
	
	int lengths[N];
	int tempLength;
	for(int i = 0; i < N; i++){
		cin >> tempLength;
		lengths[i] = tempLength;
	}
	
	sort(lengths, lengths + N);
	
	double result = (lengths[0] + lengths[1]) / 2.0;
	for(int i = 2; i < N; i++){
		result = (result + lengths[i]) / 2;
	}
	
	cout << (int)result << endl;
	
	return 0;
}

