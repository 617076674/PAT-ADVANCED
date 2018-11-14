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

	int index = 0;
	firstPointAddress = beforeChangePoints[k - 1].address;
	vector<point> tempFirstPointAddresses;
	for (int i = 2 * k; i <= beforeChangePoints.size(); i += k) {
		tempFirstPointAddresses.push_back(beforeChangePoints[i - 1]);
	}
	int count = 0;
	while (index + k <= beforeChangePoints.size()) {
		if (index + 2 * k <= beforeChangePoints.size()) {
			beforeChangePoints[index].next = tempFirstPointAddresses[count].address;
		} else {
			if (index + k == beforeChangePoints.size()) {
				beforeChangePoints[index].next = -1;
			} else {
				beforeChangePoints[index].next = beforeChangePoints[index + k].address;
			}
		}
		for (int i = index + 1; i < index + k; i++) {
			beforeChangePoints[i].next = beforeChangePoints[i - 1].address;
		}
		count++;
		index = index + k;
	}

	point points2[100000];
	
	for (int i = 0; i < beforeChangePoints.size(); i++) {
		points2[beforeChangePoints[i].address] = beforeChangePoints[i];
	}

	vector<point> afterChangePoints;
	tempAddress = firstPointAddress;

	while (true) {
		afterChangePoints.push_back(points2[tempAddress]);
		tempAddress = points2[tempAddress].next;
		if (tempAddress == -1) {
			break;
		}
	}

	for (int i = 0; i < afterChangePoints.size(); i++) {
		if (i != afterChangePoints.size() - 1) {
			printf("%05d %d %05d\n", afterChangePoints[i].address, afterChangePoints[i].data, afterChangePoints[i].next);
		} else {
			printf("%05d %d %d\n", afterChangePoints[i].address, afterChangePoints[i].data, afterChangePoints[i].next);
		}
	}
}