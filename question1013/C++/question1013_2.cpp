#include<iostream>
#include<vector>
#include<set>

using namespace std;

struct edge{
	int u, v;
	edge(int _u, int _v){
		u = _u;
		v = _v;
	}
};

int N, M, K;
vector<edge> edges;
int lost_city, count;
int father[1001];
set<int> fathers;

int findFather(int x);
void unionTwo(int a, int b);

int main(){
	scanf("%d %d %d", &N, &M, &K);
	int city1, city2;
	for(int i = 0; i < M; i++){
		scanf("%d %d", &city1, &city2);
		edges.push_back(edge(city1, city2));
	}
	for(int i = 0; i < K; i++){
		for(int j = 1; j < N + 1; j++){
			father[j] = j;
		}
		count = 0;
		fathers.clear();
		scanf("%d", &lost_city);
		for(int j = 0; j < edges.size(); j++){
			if(edges[j].u == lost_city || edges[j].v == lost_city){
				continue;
			}
			unionTwo(edges[j].u, edges[j].v);
		}
		for(int j = 1; j < N + 1; j++){
			if(j == lost_city){
				continue;
			}
			fathers.insert(findFather(j));
		}
		printf("%d\n", fathers.size() - 1);
	}
	return 0;
} 

int findFather(int x){
	int a = x;
	while(x != father[x]){
		x = father[x];
	}
	while(a != father[a]){
		int z = a;
		a = father[a];
		father[z] = x;
	}
	return x;
}

void unionTwo(int a, int b){
	int a_father = findFather(a);
	int b_father = findFather(b);
	if(a_father != b_father){
		father[a_father] = b_father;
	}
}
