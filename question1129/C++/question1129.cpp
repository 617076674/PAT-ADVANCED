#include<iostream>
#include<set>

using namespace std;

struct node {
	int num;
	int count;
	node(int _num, int _count) : num(_num), count(_count) {};
	friend bool operator < (node n1, node n2) {	//����С�ںŲ��ܷŽ�set������ 
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
	int count[N + 1];	//count[i]ͳ��i���ֵĴ���
	fill(count + 1, count + N + 1, 0);	//��ʼ��Ϊ0��
	count[input[0]]++;
	for(int i = 1; i < N; i++) {
		printf("%d:", input[i]);
		int index = 0;
		set<node>::iterator it;
		for(it = results.begin(); it != results.end(); it++){	 
			printf(" %d", (*it).num);	//���set����results�е�ǰK������� 
			index++;
			if(index >= K){
				break;
			}
		}
		it = results.find(node(input[i], count[input[i]]));	//��set����results��Ѱ������input[i]������ִ�����count[input[i]] 
		if(it == results.end()){	//���û�ҵ� 
			results.insert(node(input[i], 1));	//˵��input[i]��һ���µ����֣�����ִ���Ϊ1 
		}else{
			results.erase(it);	//����ҵ��ˣ���ɾ��set������ԭ�ȵ�ֵ 
			results.insert(node(input[i], count[input[i]] + 1));	//��set�����в���һ����ֵ����������input[i]�����ִ�����count[input[i]] + 1 
		}	
		count[input[i]]++;	//����input[i]���ֵĴ��� 
		printf("\n");
	}
	return 0;
}
