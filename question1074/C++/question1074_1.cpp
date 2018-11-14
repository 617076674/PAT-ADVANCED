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

	vector<point> points;
	point tempPoint;
	int address;
	int data;
	int next;
	for (int i = 0; i < n; i++) {
		cin >> address >> data >> next;
		tempPoint.address = address;
		tempPoint.data = data;
		tempPoint.next = next;
		points.push_back(tempPoint);
	}

	vector<point> beforeChangePoints;
	int tempAddress = firstPointAddress;
	vector<bool> flag;
	for (int i = 0; i < points.size(); i++) {
		flag.push_back(false);
	}
	while (true) {
		for (int i = 0; i < points.size(); i++) {
			if (flag[i]) {
				continue;
			}
			if (points[i].address == tempAddress) {
				beforeChangePoints.push_back(points[i]);
				flag[i] = true;
				tempAddress = points[i].next;
				break;
			}
		}
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

	vector<point> afterChangePoints;
	tempAddress = firstPointAddress;
	vector<bool> flag2;
	for (int i = 0; i < beforeChangePoints.size(); i++) {
		flag2.push_back(false);
	}
	while (true) {
		for (int i = 0; i < beforeChangePoints.size(); i++) {
			if (flag2[i]) {
				continue;
			}
			if (beforeChangePoints[i].address == tempAddress) {
				afterChangePoints.push_back(beforeChangePoints[i]);
				flag2[i] = true;
				tempAddress = beforeChangePoints[i].next;
				break;
			}
		}
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