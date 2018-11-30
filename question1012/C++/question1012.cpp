#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct student {
	int id;	//存放6位整数的ID
	int grade[4];	//存放4个分数 
};

int N, M;
student stu[2010];
char course[4] = {'A', 'C', 'M', 'E'};	//按优先级顺序，方便输出
int Rank[1000000][4] = {0};	//Rank[id][0] ~ Rank[id][4]为4门课对应的排名
int now;	//cmp函数中使用，表示当前按now号分数排序stu数组 

bool cmp(student a, student b);	//stu数组按now号分数递减排序 

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
