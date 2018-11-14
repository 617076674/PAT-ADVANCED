#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

/*
	 scoreConsist用于存储一个人的得分情况 
*/
struct scoreConsist {
	int id;
	int rank;
	//score[0]存储总分，score[1] ~ score[K]存储各题分数，score[K + 1]存储全对题数 
	//初始化值全为-2，和编译失败结果-1，编译通过但得分为0相区别开 
	int score[7] = {-2, -2, -2, -2, -2, -2, -2};	
};

int N, K, M;
scoreConsist scores[10001];	 //scores[i]存储第i号人的得分情况 

bool cmp(scoreConsist s1, scoreConsist s2);

int main() {
	cin >> N >> K >> M;
	int problems[K + 1];	//存储各题满分值 
	for(int i = 1; i <= K; i++) {
		cin >> problems[i];
	}
	int user_id, problem_id, partial_score_obtained;
	for(int i = 0; i < M; i++) {
		cin >> user_id >> problem_id >> partial_score_obtained;
		scores[user_id].id = user_id;
		if(partial_score_obtained > scores[user_id].score[problem_id]) {
			scores[user_id].score[problem_id] = partial_score_obtained;
		}
	}
	for(int i = 1; i <= N; i++) {
		int sum = 0;
		int perfect = 0;
		for(int j = 1; j <= K; j++) {
			if(scores[i].score[j] == -1 || scores[i].score[j] == -2) {
				continue;
			}
			sum += scores[i].score[j];
			if(scores[i].score[j] == problems[j]) {
				perfect++;
			}
		}
		scores[i].score[0] = sum;	//计算总分 
		scores[i].score[K + 1] = perfect;	//计算全对题数 
	}
	vector<scoreConsist> scoreConsists;
	for(int i = 1; i <= N; i++) {
		bool flag = false;
		for(int j = 1; j <= K; j++) {
			if(scores[i].score[j] != -2 && scores[i].score[j] != -1) {
				flag = true;
				break;
			}
		}
		if(!flag) {
			continue;
		}
		scoreConsists.push_back(scores[i]);	//滤除去不需要显示的数据 
	}
	sort(scoreConsists.begin(), scoreConsists.end(), cmp);	//对需要显示的数据进行题目要求的排序 
	for(int i = 0; i < scoreConsists.size(); i++) {
		scoreConsists[i].rank = i + 1;
		if(i > 1 && scoreConsists[i].score[0] == scoreConsists[i - 1].score[0]) {
			scoreConsists[i].rank = scoreConsists[i - 1].rank;
		}
		printf("%d %05d %d ", scoreConsists[i].rank, scoreConsists[i].id, scoreConsists[i].score[0]);
		for(int j = 1; j <= K; j++) {
			if(scoreConsists[i].score[j] == -2) {	//如果是-2，说明根本没有提交，显示“-” 
				printf("-");
			} else if(scoreConsists[i].score[j] == -1) {	//如果是-1，说明提交了但是编译失败，根据样例应该显示“0” 
				printf("0");
			} else {
				printf("%d", scoreConsists[i].score[j]);
			}
			if(j != K) {
				printf(" ");
			} else {
				printf("\n");
			}
		}
	}
}

bool cmp(scoreConsist s1, scoreConsist s2) {
	if(s1.score[0] == s2.score[0]) {
		if(s1.score[K + 1] == s2.score[K + 1]) {
			return s1.id < s2.id;
		} else {
			return s1.score[K + 1] > s2.score[K + 1];
		}
	} else {
		return s1.score[0] > s2.score[0];
	}
}
