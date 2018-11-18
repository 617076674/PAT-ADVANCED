#include<iostream>
#include<vector>
#include<set>

using namespace std;

struct edge{
	int v1, v2;
};

int main(){
	int N, M;
	scanf("%d %d", &N, &M);
	edge edges[M];
	for(int i = 0; i < M; i++){
		scanf("%d %d", &edges[i].v1, &edges[i].v2);
	}
	int K;
	scanf("%d", &K);
	for(int i = 0; i < K; i++){
		int Nv;
		scanf("%d", &Nv);
		int num;
		set<int> nums;
		for(int j = 0; j < Nv; j++){
			scanf("%d", &num);
			nums.insert(num);
		}
		bool flag = true;
		for(int j = 0; j < M; j++){	//��ÿһ���߶���Ҫ��ѯ�������˵��Ƿ�������һ����set������ 
			if(nums.find(edges[j].v1) == nums.end() && nums.find(edges[j].v2) == nums.end()){	//������������� 
				flag = false;
				break; 
			}
		}
		if(flag){
			printf("Yes\n");
		}else{
			printf("No\n");
		}
	}
	return 0;
}
