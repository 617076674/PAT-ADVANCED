#include<iostream>
#include<vector>

using namespace std;

vector<int> graph[1001];

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	int inDegree[N + 1];	//每个顶点的入度
	fill(inDegree + 1, inDegree + N + 1, 0);	//初始化每个顶点的入度均为0 
	int from, to;
	for(int i = 0; i < M; i++) {
		scanf("%d %d", &from, &to);
		graph[from].push_back(to);
		inDegree[to]++;	//顶点to的入度加1 
	}
	vector<int> results;	//存储结果 
	int K;
	scanf("%d", &K);
	for(int i = 0; i < K; i++) {
		int tempInDegree[N + 1];
		for(int j = 1; j < N + 1; j++) {
			tempInDegree[j] = inDegree[j];	//tempInDegree复制一份inDegree数组 
		}
		int num;
		bool flag = true;	//用来判断当前序列是否是拓扑排序 
		for(int j = 0; j < N; j++) {
			scanf("%d", &num);
			if(!flag){	//如果已经确定了当前序列不是拓扑排序，我们只需读入num，无需进入下述操作 
				continue;
			}
			if(tempInDegree[num] != 0) {	//一旦入度不为0，说明不是拓扑排序 
				results.push_back(i);	//注意，这个for循环涉及到读入数据，不可以break 
				flag = false;
			}
			for(int k = 0; k < graph[num].size(); k++) {	//将与num相连的另一个顶点的入度减1 
				tempInDegree[graph[num][k]]--;
			}
		}
	}
	for(int i = 0; i < results.size(); i++) {	//输出结果 
		printf("%d", results[i]);
		if(i != results.size() - 1) {
			printf(" ");
		} else {
			printf("\n");
		}
	}
	return 0;
}
