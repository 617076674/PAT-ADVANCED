#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

struct programmer {
	int id;
	int data;
	int rank;
	friend bool operator < (programmer pg1, programmer pg2) {
		return pg1.data < pg2.data;
	}
};

bool cmp(programmer pg1, programmer pg2);

int main() {
	int NP, NG, num;
	scanf("%d %d", &NP, &NG);
	programmer pgs[NP];
	queue<programmer> programmers;
	queue<programmer> tempProgrammers;
	priority_queue<programmer> pqProgrammers;
	for(int i = 0; i < NP; i++) {
		pgs[i].id = i;
		scanf("%d", &pgs[i].data);
	}
	for(int i = 0; i < NP; i++){
		scanf("%d", &num);
		programmers.push(pgs[num]);
	}
	vector<programmer> results;
	int index = 0;
	while(programmers.size() != 1){
		int size = programmers.size();	//队列programmers中的元素个数一直在变，提前记录其个数 
		for(int i = 0; i < size; i += NG){
			for(int j = i; j < i + NG && j < size; j++){
				pqProgrammers.push(programmers.front());
				programmers.pop();
			}
			tempProgrammers.push(pqProgrammers.top());
			pqProgrammers.pop();
			while(!pqProgrammers.empty()){
				results.push_back(pqProgrammers.top());
				pqProgrammers.pop();
			}
		}
		while(!programmers.empty()){
			programmers.pop();
		}
		while(!tempProgrammers.empty()){
			programmers.push(tempProgrammers.front());
			tempProgrammers.pop();
		}
		for(int i = index; i < results.size(); i++){
			results[i].rank = programmers.size() + 1;
		}
		index = results.size();
	}
	programmers.front().rank = 1;
	results.push_back(programmers.front());
	sort(results.begin(), results.end(), cmp);
	for(int i = 0; i < results.size(); i++){
		printf("%d", results[i].rank);
		if(i != results.size() - 1){
			printf(" ");
		}
	}
}

bool cmp(programmer pg1, programmer pg2){
	return pg1.id < pg2.id;
}
