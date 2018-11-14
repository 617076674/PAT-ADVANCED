#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int couple[100000];
bool flag[100000];

int main(){
	fill(couple, couple + 100000, -1);
	fill(flag, flag + 100000, false);
	int N;
	scanf("%d", &N);
	int num1, num2;
	for(int i = 0; i < N; i++){
		scanf("%d %d", &num1, &num2);
		couple[num1] = num2;
		couple[num2] = num1;
	}
	int M, num;
	scanf("%d", &M);
	for(int i = 0; i < M; i++){
		scanf("%d", &num);
		flag[num] = true;
	}
	vector<int> single;
	for(int i = 0; i < 100000; i++){
		if(!flag[i]){
			continue;
		}
		if(couple[i] == -1 || (couple[i] != -1 && !flag[couple[i]])){
			single.push_back(i);
		}
	}
	sort(single.begin(), single.end());
	printf("%d\n", single.size());
	for(int i = 0; i < single.size(); i++){
		printf("%05d", single[i]);
		if(i != single.size() - 1){
			printf(" "); 
		}else{
			printf("\n");
		}
	}
	return 0;
}
