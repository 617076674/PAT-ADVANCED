#include<iostream>
#include<time.h>

using namespace std;

int main() {
	long startTime;
	long endTime;

	cin >> startTime >> endTime;

	long time = (endTime - startTime) / 100;
	if ((endTime - startTime) % 100 >= 50) {
		time++;
	}

	if (time >= 60 * 60) {
		int hour = time / (60 * 60);
		if (hour <= 9) {
			cout << "0" << hour << ":";
		} else {
			cout << hour << ":";
		}
		int miniute = (time - hour * 60 * 60) / 60;
		if (miniute <= 9) {
			cout << "0" << miniute << ":";
		} else {
			cout << miniute << ":";
		}
		int second = time - hour * 60 * 60 - miniute * 60;
		if (second <= 9) {
			cout << "0" << second;
		} else {
			cout << second;
		}
	} else if (time >= 60) {
		cout << "00:";
		int miniute = time / 60;
		if (miniute <= 9) {
			cout << "0" << miniute << ":";
		} else {
			cout << miniute << ":";
		}
		int second = time - miniute * 60;
		if (second <= 9) {
			cout << "0" << second;
		} else {
			cout << second;
		}
	} else {
		cout << "00:00:";
		int second = time;
		if (second <= 9) {
			cout << "0" << second;
		} else {
			cout << second;
		}
	}

}