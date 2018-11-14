#include<iostream>

using namespace std;

struct node {
	char data;
	int next;
	node() {};
	node(char _data, int _next) : data(_data), next(_next) {};
};

node Node[100000];
bool flag[100000];

int main() {
	int first1, first2, N, now, next, cur1, cur2;
	char c;
	scanf("%d %d %d", &first1, &first2, &N);
	for(int i = 0; i < N; i++) {
		scanf("%d %c %d", &now, &c, &next);
		Node[now] = node(c, next);
	}
	fill(flag, flag + 100000, false);
	cur1 = first1;
	while(cur1 != -1) {
		flag[cur1] = true;
		cur1 = Node[cur1].next;
	}
	cur2 = first2;
	while(cur2 != -1) {
		if(flag[cur2]) {
			break;
		}
		cur2 = Node[cur2].next;
	}
	if(cur2 == -1) {
		printf("-1\n");
	} else {
		printf("%05d\n", cur2);
	}
	return 0;
}
