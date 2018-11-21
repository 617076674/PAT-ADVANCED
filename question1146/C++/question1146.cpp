#include<iostream>
#include<vector>

using namespace std;

vector<int> graph[1001];

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	int inDegree[N + 1];	//ÿ����������
	fill(inDegree + 1, inDegree + N + 1, 0);	//��ʼ��ÿ���������Ⱦ�Ϊ0 
	int from, to;
	for(int i = 0; i < M; i++) {
		scanf("%d %d", &from, &to);
		graph[from].push_back(to);
		inDegree[to]++;	//����to����ȼ�1 
	}
	vector<int> results;	//�洢��� 
	int K;
	scanf("%d", &K);
	for(int i = 0; i < K; i++) {
		int tempInDegree[N + 1];
		for(int j = 1; j < N + 1; j++) {
			tempInDegree[j] = inDegree[j];	//tempInDegree����һ��inDegree���� 
		}
		int num;
		bool flag = true;	//�����жϵ�ǰ�����Ƿ����������� 
		for(int j = 0; j < N; j++) {
			scanf("%d", &num);
			if(!flag){	//����Ѿ�ȷ���˵�ǰ���в���������������ֻ�����num����������������� 
				continue;
			}
			if(tempInDegree[num] != 0) {	//һ����Ȳ�Ϊ0��˵�������������� 
				results.push_back(i);	//ע�⣬���forѭ���漰���������ݣ�������break 
				flag = false;
			}
			for(int k = 0; k < graph[num].size(); k++) {	//����num��������һ���������ȼ�1 
				tempInDegree[graph[num][k]]--;
			}
		}
	}
	for(int i = 0; i < results.size(); i++) {	//������ 
		printf("%d", results[i]);
		if(i != results.size() - 1) {
			printf(" ");
		} else {
			printf("\n");
		}
	}
	return 0;
}
