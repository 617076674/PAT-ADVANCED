#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct node {
	int address;
	int key;
	int next;
	node() {};
	node(int _address, int _key, int _next) : address(_address), key(_key), next(_next) {};
};

node Node[100000];
bool flag[100000];

bool cmp(node node1, node node2);

int main() {
	int N, first, now, key, next, cur;
	fill(flag, flag + 100000, false);
	scanf("%d %d", &N, &first);
	for(int i = 0; i < N; i++) {
		scanf("%d %d %d", &now, &key, &next);
		Node[now] = node(now, key, next);
		flag[now] = true;
	}
	vector<node> nodes;
	if(!flag[first]){
		printf("0 -1\n");
		return 0;
	}
	cur = first;
	while(cur != -1) {
		nodes.push_back(Node[cur]);
		cur = Node[cur].next;
	}
	sort(nodes.begin(), nodes.end(), cmp);
	printf("%d %05d\n", nodes.size(), nodes[0].address);
	for(int i = 0; i < nodes.size(); i++) {
		if(i != nodes.size() - 1) {
			printf("%05d %d %05d\n", nodes[i].address, nodes[i].key, nodes[i + 1].address);
		} else {
			printf("%05d %d -1\n", nodes[i].address, nodes[i].key);
		}
	}
	return 0;
}

bool cmp(node node1, node node2) {
	return node1.key < node2.key;
}
