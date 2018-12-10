#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<unordered_map>

using namespace std;

struct student {
	char number[14];
	int score, site, date;
};
struct place {
	int siteNumber, people;
	place(int _siteNumber, int _people) {
		siteNumber = _siteNumber;
		people = _people;
	}
};

int N, M;
vector<student> filterBySiteNumber[1000], filterByLevel[3];	//将考生按考场编号进行分类;将考生按考试等级进行分类，0代表A级，1代表B级，2代表T级
unordered_map<int, vector<student> > filterByDate;	//将考生按日期进行分类

bool cmp1(student s1, student s2);
bool cmp2(place p1, place p2);

int main() {
	scanf("%d %d", &N, &M);
	student students[N];
	for(int i = 0; i < N; i++) {
		scanf("%s %d", students[i].number, &students[i].score);
		students[i].site = 0;
		for(int j = 1; j <= 3; j++) {
			students[i].site = students[i].site * 10 + students[i].number[j] - '0';
		}
		if(students[i].number[0] == 'A') {
			filterByLevel[0].push_back(students[i]);
		} else if(students[i].number[0] == 'B') {
			filterByLevel[1].push_back(students[i]);
		} else {
			filterByLevel[2].push_back(students[i]);
		}
		students[i].date = 0;
		for(int j = 4; j <= 9; j++) {
			students[i].date = students[i].date * 10 + students[i].number[j] - '0';
		}
		filterBySiteNumber[students[i].site].push_back(students[i]);
		filterByDate[students[i].date].push_back(students[i]);
	}
	for(int i = 0; i < 3; i++) {
		sort(filterByLevel[i].begin(), filterByLevel[i].end(), cmp1);
	}
	for(int i = 1; i <= M; i++) {
		int kind;
		scanf("%d", &kind);
		printf("Case %d: %d ", i, kind);
		if(kind == 1) {
			char type[2];
			scanf("%s", type);
			printf("%s\n", type);
			int choose;
			if(type[0] == 'A') {
				choose = 0;
			} else if(type[0] == 'B') {
				choose = 1;
			} else {
				choose = 2;
			}
			for(int j = 0; j < filterByLevel[choose].size(); j++) {
				printf("%s %d\n", filterByLevel[choose][j].number, filterByLevel[choose][j].score);
			}
			if(filterByLevel[choose].size() == 0) {
				printf("NA\n");
			}
		} else if(kind == 2) {
			int query;
			scanf("%d", &query);
			printf("%d\n", query);
			int sum = 0;
			for(int j = 0; j < filterBySiteNumber[query].size(); j++) {
				sum += filterBySiteNumber[query][j].score;
			}
			if(filterBySiteNumber[query].size() != 0) {
				printf("%d %d\n", filterBySiteNumber[query].size(), sum);
			} else {
				printf("NA\n");
			}
		} else {
			int queryDate;
			scanf("%d", &queryDate);
			printf("%06d\n", queryDate);
			vector<student> tempFilterBySiteNumber[1000];
			for(int j = 0; j < filterByDate[queryDate].size(); j++) {
				tempFilterBySiteNumber[filterByDate[queryDate][j].site].push_back(filterByDate[queryDate][j]);
			}
			vector<place> places;
			for(int j = 101; j < 1000; j++) {
				if(tempFilterBySiteNumber[j].size() > 0) {
					places.push_back(place(j, tempFilterBySiteNumber[j].size()));
				}
			}
			sort(places.begin(), places.end(), cmp2);
			for(int j = 0; j < places.size(); j++) {
				printf("%d %d\n", places[j].siteNumber, places[j].people);
			}
			if(places.size() == 0) {
				printf("NA\n");
			}
		}
	}
	return 0;
}

bool cmp1(student s1, student s2) {
	if(s1.score == s2.score) {
		return strcmp(s1.number, s2.number) < 0;
	} else {
		return s1.score > s2.score;
	}
}

bool cmp2(place p1, place p2) {
	if(p1.people == p2.people) {
		return p1.siteNumber < p2.siteNumber;
	}
	return p1.people > p2.people;
}
