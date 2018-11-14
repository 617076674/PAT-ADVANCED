#include<iostream>
#include<vector>

using namespace std;

struct point {
	int address;
	int data;
	int next;
};

int main() {

	int firstPointAddress;
	int n;
	int k;

	cin >> firstPointAddress >> n >> k;

	point points[100000];
	point tempPoint;
	int address;
	int data;
	int next;
	for (int i = 0; i < n; i++) {
		cin >> address >> data >> next;
		tempPoint.address = address;
		tempPoint.data = data;
		tempPoint.next = next;
		points[address] = tempPoint;
	}

	vector<point> beforeChangePoints;
	int tempAddress = firstPointAddress;

	while (true) {
		beforeChangePoints.push_back(points[tempAddress]);
		tempAddress = points[tempAddress].next;
		if (tempAddress == -1) {
			break;
		}
	}
	vector<point> afterChangePoints;
	int index = 0;
	while (index + k <= beforeChangePoints.size()) {
		for (int i = index + k - 1; i >= index; i--) {
			afterChangePoints.push_back(beforeChangePoints[i]);
		}
		index = index + k;
	}
	for (int i = index; i < beforeChangePoints.size(); i++) {
		afterChangePoints.push_back(beforeChangePoints[i]);
	}
	for (int i = 0; i < afterChangePoints.size() - 1; i++) {
		afterChangePoints[i].next = afterChangePoints[i + 1].address;
	}
	afterChangePoints[afterChangePoints.size() - 1].next = -1;

	for (int i = 0; i < afterChangePoints.size(); i++) {
		if (i != afterChangePoints.size() - 1) {
			printf("%05d %d %05d\n", afterChangePoints[i].address, afterChangePoints[i].data, afterChangePoints[i].next);
		} else {
			printf("%05d %d %d\n", afterChangePoints[i].address, afterChangePoints[i].data, afterChangePoints[i].next);
		}
	}
}