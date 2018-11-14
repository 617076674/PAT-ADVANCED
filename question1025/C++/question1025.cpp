#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

struct student {
	string number;
	int score;
	int final_rank;
	int location_number;
	int local_rank;
};

int N;
vector<student> students[101];
vector<student> allStudents;

bool cmp(student stu1, student stu2);

int main() {
	scanf("%d", &N);
	int K;
	string number;
	int score;
	student stu;
	for(int i = 1; i <= N; i++) {
		scanf("%d", &K);
		for(int j = 0; j < K; j++) {
			cin >> number >> score;
			stu.number = number;
			stu.score = score;
			stu.location_number = i;
			students[i].push_back(stu);
		}
	}
	for(int i = 1; i <= N; i++) {
		sort(students[i].begin(), students[i].end(), cmp);
	}
	for(int i = 1; i <= N; i++) {
		for(int j = 0; j < students[i].size(); j++) {
			if(j > 0 && students[i][j].score == students[i][j - 1].score) {
				students[i][j].local_rank = students[i][j - 1].local_rank;
			} else {
				students[i][j].local_rank = j + 1;
			}
			allStudents.push_back(students[i][j]);
		}
	}
	sort(allStudents.begin(), allStudents.end(), cmp);
	for(int i = 0; i < allStudents.size(); i++) {
		if(i > 0 && allStudents[i].score == allStudents[i - 1].score) {
			allStudents[i].final_rank = allStudents[i - 1].final_rank;
		} else {
			allStudents[i].final_rank = i + 1;
		}
	}
	cout << allStudents.size() << endl;
	for(int i = 0; i < allStudents.size(); i++){
		cout << allStudents[i].number << " " << allStudents[i].final_rank << " " << allStudents[i].location_number 
			<< " " << allStudents[i].local_rank << endl;
	}
}

bool cmp(student stu1, student stu2) {
	if(stu1.score == stu2.score) {
		return stu2.number.compare(stu1.number) > 0;
	} else {
		return stu1.score > stu2.score;
	}
}
