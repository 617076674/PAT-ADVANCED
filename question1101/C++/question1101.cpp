#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
	int count;

	cin >> count;

	long tempNum;
	vector<long> beforeSort;
	vector<long> afterSort;
	vector<long> result;

	for (int i = 0; i < count; i++) {
		cin >> tempNum;
		beforeSort.push_back(tempNum);
		afterSort.push_back(tempNum);
	}

	sort(afterSort.begin(), afterSort.end());

	int max = beforeSort[0];
	for (int i = 0; i < afterSort.size(); i++) {
		if (i == 0) {
			if (afterSort[i] == beforeSort[i]) {
				result.push_back(afterSort[i]);
			}
		} else {
			if (afterSort[i] == beforeSort[i] && afterSort[i] > max) {
				result.push_back(afterSort[i]);
			}
			if (beforeSort[i - 1] > max) {
				max = beforeSort[i - 1];
			}
		}
	}

	cout << result.size() << endl;
	for (int i = 0; i < result.size(); i++) {
		cout << result[i];
		if (i != result.size() - 1) {
			cout << " ";
		}
	}
	printf("\n");
}
