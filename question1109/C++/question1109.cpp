#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;

struct person{	//存储人名和身高 
	char name[9];
	int height;
};

bool cmp(person p1, person p2);	//按升高降序排序，若身高相同，则按人名升序排序 
void showPeople(vector<person> row);	//显示每一行的人名 

int main(){
	int N, K;
	scanf("%d %d", &N, &K);	//读取总人数和总行数 
	person people[N];
	for(int i = 0; i < N; i++){
		scanf("%s %d", people[i].name, &people[i].height);	//读入每个人的人名和身高 
	}
	sort(people, people + N, cmp);	//按身高从高到低排序
	int otherRow = N / K;	//除最后一行的每行人数 
	int lastRow = N - otherRow * (K - 1);	//最后一行的人数
	vector<person> row;	  //存储每行的人 
	for(int i = N - 1; i >= N - lastRow; i--){
		row.push_back(people[i]);	//最后一行 
	}
	showPeople(row);	//先输出最后一行的人名 
	for(int i = 0; i < K - 1; i++){
		row.clear();	//开始新的一行前先清空row 
		for(int j = N - lastRow - 1 - otherRow * i; j >= N - lastRow - otherRow * (i + 1); j--){	//按每行otherRow个人对people数组中的数据进行分行 
			row.push_back(people[j]);	//其他行 
		}
		showPeople(row);	//输出其他行的人名 
	} 
	return 0;
}

bool cmp(person p1, person p2){
	if(p1.height == p2.height){
		return strcmp(p1.name, p2.name) > 0;
	}else{
		return p1.height < p2.height;
	}
}

void showPeople(vector<person> row){
	int size = row.size();
	person people[size];
	int mid = size / 2;	//确定最高者的位置，索引从0开始 
	people[mid] = row[0];
	int left = mid - 1;	//确定最高者左边的下一个位置 
	int right = mid + 1;	//确定最高者右边的下一个位置 
	for(int i = 1; i < size; i++){
		if(i % 2 == 1){	//先放左边 
			people[left--] = row[i];
		}else{	//再放右边 
			people[right++] = row[i];
		}
	}
	for(int i = 0; i < size; i++){	//输出每行人名 
		printf("%s", people[i].name);
		if(i != size - 1){
			printf(" ");
		}else{
			printf("\n");
		}
	}
}
