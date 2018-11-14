#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

struct window{
	int endTime, popTime;	//���ڵ�ǰ�����������ʱ�䡢���׿ͻ��ķ������ʱ��
	queue<int> q;	//���� 
};

int changeToMinute(int hour, int minute);

int main(){
	int N, M, K, Q;
	scanf("%d %d %d %d", &N, &M, &K, &Q);
	int needTime[K];
	window windows[N];
	for(int i = 0; i < K; i++){
		scanf("%d", &needTime[i]);	//���������Ҫʱ�� 
	}
	for(int i = 0; i < N; i++){
		windows[i].popTime = windows[i].endTime = changeToMinute(8, 0);	//��ʼ��ÿ�����ڵ�popTime��endTimeΪ08:00 
	}
	int inIndex = 0;	//��ǰ��һ��δ��ӵĿͻ����
	int result[K];	 
	for(int i = 0; i < min(N * M, K); i++){
		windows[inIndex % N].q.push(inIndex);	//ѭ�����
		windows[inIndex % N].endTime += needTime[inIndex];	//���´��ڵķ������ʱ��endTime
		if(inIndex < N){
			windows[inIndex].popTime = needTime[inIndex];	//�Դ��ڵĵ�һ���ͻ�������popTime 
		}
		result[inIndex] = windows[inIndex % N].endTime;	//��ǰ��ӵĿͻ��ķ������ʱ��ֱ�ӱ�����Ϊ��
		inIndex++; 
	}
	for(; inIndex < K; inIndex++){	//����ʣ��ͻ������ 
		int idx = -1, minPopTime = 1000000000;	//Ѱ�����д��ڵ���СpopTime 
		for(int i = 0; i < N; i++){
			if(windows[i].popTime < minPopTime){
				idx = i;
				minPopTime = windows[i].popTime;
			}
		}
		//�ҵ���СpopTime�Ĵ��ڱ��Ϊidex��������¸ô��ڵĶ������ 
		windows[idx].q.pop();	//���׿ͻ��뿪 
		windows[idx].q.push(inIndex);	//�ͻ�inIndex��� 
		windows[idx].endTime += needTime[inIndex];	//���¸ô��ڶ��е�endTime
		windows[idx].popTime += needTime[windows[idx].q.front()];	//���¸ô��ڵ�popTime
		result[inIndex] = windows[idx].endTime; 	//�ͻ�inIndex�ķ������ʱ��Ϊ�ô��ڵ�endTime 
	}
	int num;
	for(int i = 0; i < Q; i++){
		scanf("%d", &num);	//��ѯ�ͻ����
		if(result[num - 1] - needTime[num - 1] >= changeToMinute(17, 0)){
			printf("Sorry\n");
		}else{
			printf("%02d:%02d\n", result[num - 1] / 60, result[num - 1] % 60);
		} 
	}
	return 0;
}

int changeToMinute(int hour, int minute){
	return hour * 60 + minute;
}
