#include<iostream>
#include<vector>
#include<utility>
#include<queue>
#include<algorithm>
#include<set>

using namespace std;

bool flag[10000];	//flag[i] = true表示编号为i的人是男性
set<int> graph[10000];
int start, destination;
set<int> set1, set2;
vector<pair<int, int> > results;

int changeToInt(char* s);
void init();
bool cmp(pair<int, int> p1, pair<int, int> p2);

int main() {
	fill(flag, flag + 10000, true);
	int N, M;
	scanf("%d %d", &N, &M);
	char s1[6], s2[6];
	int id1, id2;
	for(int i = 0; i < M; i++) {
		scanf("%s %s", s1, s2);
		id1 = changeToInt(s1);
		id2 = changeToInt(s2);
		if(s1[0] == '-') {
			flag[id1] = false;
		}
		if(s2[0] == '-') {
			flag[id2] = false;
		}
		graph[id1].insert(id2);
		graph[id2].insert(id1);
	}
	int K;
	scanf("%d", &K);
	for(int i = 0; i < K; i++) {
		init();
		scanf("%s %s", s1, s2);
		start = changeToInt(s1);
		destination = changeToInt(s2);
		for(set<int>::iterator it = graph[start].begin(); it != graph[start].end(); it++) {
			if(flag[*it] == flag[start] && *it != destination) {
				set1.insert(*it);
			}
		}
		for(set<int>::iterator it = graph[destination].begin(); it != graph[destination].end(); it++) {
			if(flag[*it] == flag[destination] && *it != start) {
				set2.insert(*it);
			}
		}
		for(set<int>::iterator it1 = set1.begin(); it1 != set1.end(); it1++) {
			for(set<int>::iterator it2 = graph[*it1].begin(); it2 != graph[*it1].end(); it2++) {
				if(set2.find(*it2) != set2.end()) {
					results.push_back(make_pair(*it1, *it2));
				}
			}
		}
		sort(results.begin(), results.end(), cmp);
		printf("%d\n", results.size());
		for(int j = 0; j < results.size(); j++) {
			printf("%04d %04d\n", results[j].first, results[j].second);
		}
	}
	return 0;
}

int changeToInt(char* s) {
	int result = 0;
	if(s[0] == '-') {
		for(int i = 1; i <= 4; i++) {
			result = result * 10 + s[i] - '0';
		}
	} else {
		for(int i = 0; i <= 3; i++) {
			result = result * 10 + s[i] - '0';
		}
	}
	return result;
}

void init() {
	set1.clear();
	set2.clear();
	results.clear();
}

bool cmp(pair<int, int> p1, pair<int, int> p2) {
	if(p1.first == p2.first) {
		return p1.second < p2.second;
	} else {
		return p1.first < p2.first;
	}
}
