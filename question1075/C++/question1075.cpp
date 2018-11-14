#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

/*
	 scoreConsist���ڴ洢һ���˵ĵ÷���� 
*/
struct scoreConsist {
	int id;
	int rank;
	//score[0]�洢�ܷ֣�score[1] ~ score[K]�洢���������score[K + 1]�洢ȫ������ 
	//��ʼ��ֵȫΪ-2���ͱ���ʧ�ܽ��-1������ͨ�����÷�Ϊ0������ 
	int score[7] = {-2, -2, -2, -2, -2, -2, -2};	
};

int N, K, M;
scoreConsist scores[10001];	 //scores[i]�洢��i���˵ĵ÷���� 

bool cmp(scoreConsist s1, scoreConsist s2);

int main() {
	cin >> N >> K >> M;
	int problems[K + 1];	//�洢��������ֵ 
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
		scores[i].score[0] = sum;	//�����ܷ� 
		scores[i].score[K + 1] = perfect;	//����ȫ������ 
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
		scoreConsists.push_back(scores[i]);	//�˳�ȥ����Ҫ��ʾ������ 
	}
	sort(scoreConsists.begin(), scoreConsists.end(), cmp);	//����Ҫ��ʾ�����ݽ�����ĿҪ������� 
	for(int i = 0; i < scoreConsists.size(); i++) {
		scoreConsists[i].rank = i + 1;
		if(i > 1 && scoreConsists[i].score[0] == scoreConsists[i - 1].score[0]) {
			scoreConsists[i].rank = scoreConsists[i - 1].rank;
		}
		printf("%d %05d %d ", scoreConsists[i].rank, scoreConsists[i].id, scoreConsists[i].score[0]);
		for(int j = 1; j <= K; j++) {
			if(scoreConsists[i].score[j] == -2) {	//�����-2��˵������û���ύ����ʾ��-�� 
				printf("-");
			} else if(scoreConsists[i].score[j] == -1) {	//�����-1��˵���ύ�˵��Ǳ���ʧ�ܣ���������Ӧ����ʾ��0�� 
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
