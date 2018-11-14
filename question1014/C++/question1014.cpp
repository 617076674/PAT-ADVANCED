#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

struct window{
	int endTime, popTime;	//窗口当前队伍的最后服务时间、队首客户的服务结束时间
	queue<int> q;	//队列 
};

int changeToMinute(int hour, int minute);

int main(){
	int N, M, K, Q;
	scanf("%d %d %d %d", &N, &M, &K, &Q);
	int needTime[K];
	window windows[N];
	for(int i = 0; i < K; i++){
		scanf("%d", &needTime[i]);	//读入服务需要时间 
	}
	for(int i = 0; i < N; i++){
		windows[i].popTime = windows[i].endTime = changeToMinute(8, 0);	//初始化每个窗口的popTime和endTime为08:00 
	}
	int inIndex = 0;	//当前第一个未入队的客户编号
	int result[K];	 
	for(int i = 0; i < min(N * M, K); i++){
		windows[inIndex % N].q.push(inIndex);	//循环入队
		windows[inIndex % N].endTime += needTime[inIndex];	//更新窗口的服务结束时间endTime
		if(inIndex < N){
			windows[inIndex].popTime = needTime[inIndex];	//对窗口的第一个客户，更新popTime 
		}
		result[inIndex] = windows[inIndex % N].endTime;	//当前入队的客户的服务结束时间直接保存作为答案
		inIndex++; 
	}
	for(; inIndex < K; inIndex++){	//处理剩余客户的入队 
		int idx = -1, minPopTime = 1000000000;	//寻找所有窗口的最小popTime 
		for(int i = 0; i < N; i++){
			if(windows[i].popTime < minPopTime){
				idx = i;
				minPopTime = windows[i].popTime;
			}
		}
		//找到最小popTime的窗口编号为idex，下面更新该窗口的队列情况 
		windows[idx].q.pop();	//队首客户离开 
		windows[idx].q.push(inIndex);	//客户inIndex入队 
		windows[idx].endTime += needTime[inIndex];	//更新该窗口队列的endTime
		windows[idx].popTime += needTime[windows[idx].q.front()];	//更新该窗口的popTime
		result[inIndex] = windows[idx].endTime; 	//客户inIndex的服务结束时间为该窗口的endTime 
	}
	int num;
	for(int i = 0; i < Q; i++){
		scanf("%d", &num);	//查询客户编号
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
