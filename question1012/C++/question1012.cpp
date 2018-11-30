#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct student {
	int id;	//���6λ������ID
	int grade[4];	//���4������ 
};

int N, M;
student stu[2010];
char course[4] = {'A', 'C', 'M', 'E'};	//�����ȼ�˳�򣬷������
int Rank[1000000][4] = {0};	//Rank[id][0] ~ Rank[id][4]Ϊ4�ſζ�Ӧ������
int now;	//cmp������ʹ�ã���ʾ��ǰ��now�ŷ�������stu���� 

bool cmp(student a, student b);	//stu���鰴now�ŷ����ݼ����� 

int main(){
	cin >> N >> M;
	for(int i = 0; i < N; i++){
		cin >> stu[i].id >> stu[i].grade[1] >> stu[i].grade[2] >> stu[i].grade[3];
		stu[i].grade[0] = (stu[i].grade[1] + stu[i].grade[2] + stu[i].grade[3]) / 3;
	}
	for(now = 0; now < 4; now++){
		sort(stu, stu + N, cmp);
		Rank[stu[0].id][now] = 1;
		for(int i = 1; i < N; i++){ 
			if(stu[i].grade[now] == stu[i - 1].grade[now]){
				Rank[stu[i].id][now] = Rank[stu[i - 1].id][now];
			}else{
				Rank[stu[i].id][now] = i + 1;
			}
		}
	}
	int query;
	for(int i = 0; i < M; i++){
		cin >> query;
		if(Rank[query][0] == 0){
			cout << "N/A" << endl;
		}else{
			int k = 0;
			for(int j = 1; j < 4; j++){
				if(Rank[query][j] < Rank[query][k]){
					k = j;
				}
			}
			cout << Rank[query][k] << " " << course[k] << endl;
		}
	}
	return 0;
}

bool cmp(student a, student b) {
	return a.grade[now] > b.grade[now]; 
} 
