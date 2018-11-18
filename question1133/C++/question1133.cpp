#include<iostream>
#include<vector>

using namespace std;

struct node{
	int address;
	int data;
	int next;
};

node Node[100000];

int main(){
	int first, N, K;
	scanf("%d %d %d", &first, &N, &K);
	int address, data, next;
	for(int i = 0; i < N; i++){
		scanf("%d %d %d", &address, &data, &next);
		Node[address].address = address;
		Node[address].data = data;
		Node[address].next = next;
	}
	int temp = first;
	vector<node> part1;
	vector<node> part2;
	vector<node> part3;
	while(temp != -1){
		if(Node[temp].data < 0){
			part1.push_back(Node[temp]);
		}else if(Node[temp].data > K){
			part3.push_back(Node[temp]);
		}else{
			part2.push_back(Node[temp]);
		}
		temp = Node[temp].next;
	}
	vector<node> part;
	for(int i = 0; i < part1.size(); i++){
		part.push_back(part1[i]);
	}
	for(int i = 0; i < part2.size(); i++){
		part.push_back(part2[i]);
	}
	for(int i = 0; i < part3.size(); i++){
		part.push_back(part3[i]);
	}
	for(int i = 0; i < part.size(); i++){
		if(i != part.size() - 1){
			printf("%05d %d %05d\n", part[i].address, part[i].data, part[i + 1].address);
		}else{
			printf("%05d %d -1\n", part[i].address, part[i].data);
		}
	}
	return 0;
}
