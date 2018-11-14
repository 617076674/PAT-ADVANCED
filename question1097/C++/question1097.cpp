#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

struct node {
	int address;
	int key;
	int next;
	node() {};
	node(int _address, int _key, int _next) : address(_address), key(_key), next(_next) {};
};

node Node[100000];
bool remainFlag[10001];	//标记链表中已经出现过的节点绝对值 

int main() {
	fill(remainFlag, remainFlag + 10001, false);
	int first, N, address, key, next, cur;
	scanf("%d %d", &first, &N);
	for(int i = 0; i < N; i++) {
		scanf("%d %d %d", &address, &key, &next);
		Node[address] = node(address, key, next);
	}
	vector<node> remained;
	vector<node> removed;
	cur = first;
	while(cur != -1){
		if(!remainFlag[abs(Node[cur].key)]){
			remained.push_back(Node[cur]);
			remainFlag[abs(Node[cur].key)] = true;
		}else{
			removed.push_back(Node[cur]);
		}
		cur = Node[cur].next;
	}
	for(int i = 0; i < remained.size(); i++){
		if(i != remained.size() - 1){
			printf("%05d %d %05d\n", remained[i].address, remained[i].key, remained[i + 1].address);
		}else{
			printf("%05d %d -1\n", remained[i].address, remained[i].key);
		}
	}
	for(int i = 0; i < removed.size(); i++){
		if(i != removed.size() - 1){
			printf("%05d %d %05d\n", removed[i].address, removed[i].key, removed[i + 1].address);
		}else{
			printf("%05d %d -1\n", removed[i].address, removed[i].key);
		}
	}
	return 0;
}
