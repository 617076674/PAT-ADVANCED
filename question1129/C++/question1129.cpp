#include<iostream>
#include<set>

using namespace std;

struct node {
	int num;
	int count;
	node(int _num, int _count) : num(_num), count(_count) {};
	friend bool operator < (node n1, node n2) {	//重载小于号才能放进set集合里 
		if(n1.count == n2.count) {
			return n1.num < n2.num;
		} else {
			return n1.count > n2.count;
		}
	}
};

int main() {
	int N, K;
	scanf("%d %d", &N, &K);
	int input[N];
	for(int i = 0; i < N; i++) {
		scanf("%d", &input[i]);
	}
	set<node> results;
	results.insert(node(input[0], 1));	 
	int count[N + 1];	//count[i]统计i出现的次数
	fill(count + 1, count + N + 1, 0);	//初始化为0次
	count[input[0]]++;
	for(int i = 1; i < N; i++) {
		printf("%d:", input[i]);
		int index = 0;
		set<node>::iterator it;
		for(it = results.begin(); it != results.end(); it++){	 
			printf(" %d", (*it).num);	//输出set集合results中的前K项的数字 
			index++;
			if(index >= K){
				break;
			}
		}
		it = results.find(node(input[i], count[input[i]]));	//在set集合results中寻找数字input[i]，其出现次数是count[input[i]] 
		if(it == results.end()){	//如果没找到 
			results.insert(node(input[i], 1));	//说明input[i]是一个新的数字，其出现次数为1 
		}else{
			results.erase(it);	//如果找到了，先删除set集合中原先的值 
			results.insert(node(input[i], count[input[i]] + 1));	//往set集合中插入一个新值，其数字是input[i]，出现次数是count[input[i]] + 1 
		}	
		count[input[i]]++;	//增加input[i]出现的次数 
		printf("\n");
	}
	return 0;
}
