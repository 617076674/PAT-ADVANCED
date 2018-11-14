#include<iostream>
#include<set>

using namespace std;

int father[10001];	//并查集

int findFather(int num);
void unionTwo(int a, int b); 

int main(){
	for(int i = 0; i < 10001; i++){
		father[i] = i;
	}
	int N, total = 0;
	scanf("%d", &N);
	for(int i = 0; i < N; i++){
		int count;
		scanf("%d", &count);
		int nums[count];
		for(int j = 0; j < count; j++){
			scanf("%d", &nums[j]);
			if(j > 0){
				unionTwo(nums[j], nums[j - 1]);
			}
			if(nums[j] > total){
				total = nums[j];
			}
		}
	}
	set<int> treeSet;
	for(int i = 1; i <= total; i++){
		treeSet.insert(findFather(i));
	}
	printf("%d %d\n", treeSet.size(), total);
	int Q, num1, num2;
	scanf("%d", &Q);
	for(int i = 0; i < Q; i++){
		scanf("%d %d", &num1, &num2);
		if(findFather(num1) == findFather(num2)){
			printf("Yes\n");
		}else{
			printf("No\n");
		}
	}
	return 0;
}

int findFather(int num){
	int a = num;
	while(num != father[num]){
		num = father[num];
	}
	while(a != father[a]){	//路径压缩 
		int z = a;
		a = father[a];
		father[z] = num;
	}
	return num;
}

void unionTwo(int a, int b){
	int aFather = findFather(a);
	int bFather = findFather(b);
	if(aFather != bFather){
		father[aFather] = bFather;
	}
}
