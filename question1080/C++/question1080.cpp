#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct student {
	int id;
	int GE;
	int GI;
	int rank;
	vector<int> prefer;
};

struct school {
	int id;
	int quote;
	vector<student> admit;
	vector<int> result;
};

int admitted[40000];	//编号为i的学生被编号为admitted[i]的学校录取了 

bool cmp(student s1, student s2);

int main() {
	int N, M, K;
	scanf("%d%d%d", &N, &M, &K);
	school schools[M];
	for(int i = 0; i < M; i++) {
		schools[i].id = i;
		scanf("%d", &schools[i].quote);
	}
	student students[N];
	int num;
	for(int i = 0; i < N; i++) {
		admitted[i] = -1;	//为了防止和编号为0的学校发生冲突，数组的初值设置为-1 
		students[i].id = i;
		scanf("%d%d", &students[i].GE, &students[i].GI);
		for(int j = 0; j < K; j++) {
			scanf("%d", &num);
			students[i].prefer.push_back(num);
		}
	}
	sort(students, students + N, cmp);
	for(int i = 0; i < N; i++) {
		if(i > 0 && students[i].GE + students[i].GI == students[i - 1].GE + students[i - 1].GI && students[i].GE == students[i - 1].GE) {
			students[i].rank = students[i - 1].rank;
		} else {
			students[i].rank = i + 1;
		}
		for(int j = 0; j < students[i].prefer.size(); j++) {
			int schoolNumber = students[i].prefer[j];
			if(schools[schoolNumber].admit.size() < schools[schoolNumber].quote) {
				schools[schoolNumber].admit.push_back(students[i]);
				admitted[students[i].id] = schoolNumber; 
				break;
			} else {
				student lastStudent = schools[schoolNumber].admit[schools[schoolNumber].admit.size() - 1];
				if(lastStudent.rank == students[i].rank) {	//如果新的申请者的排名和其志愿学校录取额最后一个学生的排名相同，即使超额了也得录取之 
					schools[schoolNumber].admit.push_back(students[i]);
					admitted[students[i].id] = schoolNumber;
					break;
				}
			}
		}
	}
	for(int i = 0; i < N; i++){
		if(admitted[i] == -1){
			continue;
		}
		schools[admitted[i]].result.push_back(i);
	}
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < schools[i].result.size(); j++) {
			printf("%d", schools[i].result[j]);
			if(j != schools[i].result.size() - 1) {
				printf(" ");
			}
		}
		printf("\n");
	}
	return 0;
}

bool cmp(student s1, student s2) {
	if(s1.GE + s1.GI == s2.GE + s2.GI) {
		return s1.GE > s2.GE;
	} else {
		return s1.GE + s1.GI > s2.GE + s2.GI;
	}
}
