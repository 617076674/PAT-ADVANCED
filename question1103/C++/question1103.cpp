#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

int N;
int K;
int P;
vector<int> nums;
vector<int> sequence;
vector<int> result;
int optValue = 0;

void dfs(int sum, int value, int size, int index);

int main() {
	cin >> N >> K >> P;
	for(int i = 0; ; i++) {
		int num = (int)pow(i, P);
		if(num > N) {
			break;
		}
		nums.push_back(num);
	}
	dfs(0, 0, 0, nums.size() - 1);
	if(result.size() == 0) {
		cout << "Impossible" << endl;
	} else {
		cout << N << " = ";
		for(int i = 0; i < result.size(); i++) {
			cout << result[i] << "^" << P;
			if(i != result.size() - 1) {
				cout << " + ";
			}
		}
		cout << endl;
	}
	return 0;
}

void dfs(int sum, int value, int size, int index) {
	if(sum >= N || size >= K) {
		if(size == K && sum == N) {
			if(value > optValue) {
				optValue = value;
				result = sequence;
			}
		}
		return;
	}
	if(index - 1 >= 0){
		sequence.push_back(index);
		dfs(sum + nums[index], value + index, size + 1, index);
		sequence.pop_back();
		dfs(sum, value, size, index - 1);
	}
}
