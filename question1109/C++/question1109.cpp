#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;

struct person{	//�洢��������� 
	char name[9];
	int height;
};

bool cmp(person p1, person p2);	//�����߽��������������ͬ���������������� 
void showPeople(vector<person> row);	//��ʾÿһ�е����� 

int main(){
	int N, K;
	scanf("%d %d", &N, &K);	//��ȡ�������������� 
	person people[N];
	for(int i = 0; i < N; i++){
		scanf("%s %d", people[i].name, &people[i].height);	//����ÿ���˵���������� 
	}
	sort(people, people + N, cmp);	//����ߴӸߵ�������
	int otherRow = N / K;	//�����һ�е�ÿ������ 
	int lastRow = N - otherRow * (K - 1);	//���һ�е�����
	vector<person> row;	  //�洢ÿ�е��� 
	for(int i = N - 1; i >= N - lastRow; i--){
		row.push_back(people[i]);	//���һ�� 
	}
	showPeople(row);	//��������һ�е����� 
	for(int i = 0; i < K - 1; i++){
		row.clear();	//��ʼ�µ�һ��ǰ�����row 
		for(int j = N - lastRow - 1 - otherRow * i; j >= N - lastRow - otherRow * (i + 1); j--){	//��ÿ��otherRow���˶�people�����е����ݽ��з��� 
			row.push_back(people[j]);	//������ 
		}
		showPeople(row);	//��������е����� 
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
	int mid = size / 2;	//ȷ������ߵ�λ�ã�������0��ʼ 
	people[mid] = row[0];
	int left = mid - 1;	//ȷ���������ߵ���һ��λ�� 
	int right = mid + 1;	//ȷ��������ұߵ���һ��λ�� 
	for(int i = 1; i < size; i++){
		if(i % 2 == 1){	//�ȷ���� 
			people[left--] = row[i];
		}else{	//�ٷ��ұ� 
			people[right++] = row[i];
		}
	}
	for(int i = 0; i < size; i++){	//���ÿ������ 
		printf("%s", people[i].name);
		if(i != size - 1){
			printf(" ");
		}else{
			printf("\n");
		}
	}
}
