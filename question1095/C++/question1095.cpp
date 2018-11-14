#include<iostream>
#include<map>
#include<algorithm>
#include<string.h>
 
using namespace std;

struct record {
	char plate_number[8];
	int time;	//����Ϊ��λ��ʱ��
	char description[4];
};

int N, K;
record allRecords[10000];
record validRecords[10000];
int num = 0;	//��Ч��¼������ 
map<string, int> parkTime;

bool cmpByIdAndTime(record r1, record r2);
bool cmpByTime(record r1, record r2);
int changeToSecond(int hh, int mm, int ss);

int main() {
	scanf("%d%d", &N, &K);
	int hh, mm, ss, time;
	for(int i = 0; i < N; i++) {
		scanf("%s %d:%d:%d %s", allRecords[i].plate_number, &hh, &mm, &ss, allRecords[i].description);
		time = changeToSecond(hh, mm, ss);
		allRecords[i].time = time;
	}
	sort(allRecords, allRecords + N, cmpByIdAndTime);
	int maxTime = 0;
	for(int i = 0; i < N - 1; i++) {
		if(strcmp(allRecords[i].plate_number, allRecords[i + 1].plate_number) == 0
		        && strcmp(allRecords[i].description, "in") == 0 && strcmp(allRecords[i + 1].description, "out") == 0) {
		    parkTime[allRecords[i].plate_number] += allRecords[i + 1].time - allRecords[i].time;
		    if(parkTime[allRecords[i].plate_number] > maxTime){
		    	maxTime = parkTime[allRecords[i].plate_number];
			}
			validRecords[num++] = allRecords[i];
			validRecords[num++] = allRecords[i + 1];
		}
	}
	sort(validRecords, validRecords + num, cmpByTime);
	int now = 0;
	int count = 0;
	for(int i = 0; i < K; i++) {
		scanf("%d:%d:%d", &hh, &mm, &ss);
		int nowTime = changeToSecond(hh, mm, ss);
		//���ڲ�ѯʱ���ǵ����ģ����ǲ�ѯ��һ��ʱ���ʱ�������ǰһ��ʱ���ѯ�ļ��������ϼ������� 
		while(now < num && validRecords[now].time <= nowTime){	
			if(strcmp(validRecords[now].description, "in") == 0){
				count++;
			}else{
				count--;
			}
			now++;
		}
		printf("%d\n", count);
	}
	map<string, int>::iterator it;
	for(it = parkTime.begin(); it != parkTime.end(); it++){
		if(it->second == maxTime){
			printf("%s ", it->first.c_str());
		}
	}
	printf("%02d:%02d:%02d\n", maxTime / 3600, maxTime % 3600 / 60, maxTime % 60);
	return 0;
}

bool cmpByIdAndTime(record r1, record r2) {
	if(strcmp(r1.plate_number, r2.plate_number) == 0) {
		return r1.time < r2.time;
	} else {
		return strcmp(r1.plate_number, r2.plate_number) < 0;
	}
}

bool cmpByTime(record r1, record r2){
	return r1.time < r2.time;
}

int changeToSecond(int hh, int mm, int ss) {
	return hh * 60 * 60 + mm * 60 + ss;
}

