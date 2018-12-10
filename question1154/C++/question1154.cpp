#include<iostream>
#include<vector>
#include<set>

using namespace std;

struct edge {
	int v1, v2;
	edge(int _v1, int _v2) {
		v1 = _v1;
		v2 = _v2;
	}
};

int N, M;
vector<edge> edges;

int main() {
	scanf("%d %d", &N, &M);
	for(int i = 0; i < M; i++) {
		int v1, v2;
		scanf("%d %d", &v1, &v2);
		edges.push_back(edge(v1, v2));
	}
	int K;
	scanf("%d", &K);
	for(int i = 0 ; i <  K; i++) {
		int color[N];
		set<int> colorSet;
		for(int j = 0; j < N; j++) {
			scanf("%d", &color[j]);
			colorSet.insert(color[j]);
		}
		bool flag = true;
		for(int j = 0; j < edges.size(); j++) {
			if(color[edges[j].v1] == color[edges[j].v2]) {
				printf("No\n");
				flag = false;
				break;
			}
		}
		if(flag) {
			printf("%d-coloring\n", colorSet.size());
		}
	}
	return 0;
}
