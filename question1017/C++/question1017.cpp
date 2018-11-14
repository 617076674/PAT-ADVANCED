#include<iostream>
#include<algorithm>

using namespace std;

struct person {
	int arrive;
	int process;
	person() {}
	person(int _arrive, int _process) : arrive(_arrive), process(_process) {};
};

int earliest = 8 * 60 * 60;
int latest = 15 * 60 * 60;

int changeToSecond(int hour, int minute, int second);
bool cmp(person p1, person p2);

int main() {
	int N, K;
	scanf("%d %d", &N, &K);
	person people[N];
	int window[K];	//每个窗口能接受下一次服务的最早时间
	fill(window, window + K, earliest);
	int hour, minute, second, process;
	for(int i = 0; i < N; i++) {
		scanf("%d:%d:%d %d", &hour, &minute, &second, &process);
		people[i] = person(changeToSecond(hour, minute, second), process * 60);
	}
	sort(people, people + N, cmp);
	int wait = 0;
	int count = 0;
	for(int i = 0; i < N; i++) {
		if(people[i].arrive > latest) {
			continue;
		}
		count++;
		int earlistWindow = 0;
		for(int j = 1; j < K; j++) {
			if(window[j] < window[earlistWindow]) {
				earlistWindow = j;
			}
		}
		if(window[earlistWindow] > people[i].arrive) {	//如果客户来的时候需要等待 
			wait += window[earlistWindow] - people[i].arrive;
			window[earlistWindow] += people[i].process;
		}else{	//如果客户来的时候不需要等待 
			window[earlistWindow] = people[i].arrive + people[i].process;
		}
	}
	printf("%.1f\n", wait * 1.0 / (60 * count));
	return 0;
}

int changeToSecond(int hour, int minute, int second) {
	return hour * 60 * 60 + minute * 60 + second;
}

bool cmp(person p1, person p2) {
	return p1.arrive < p2.arrive;
}
