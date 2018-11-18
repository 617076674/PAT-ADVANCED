#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

struct Record{
	char name[25];	//姓名 
	int month, dd, hh, mm;	//月份、日、时、分
	bool status;	//status==true表示该记录为on-line，否则为off-line 
};

const int maxn = 1010;
int toll[25];	//资费
Record rec[maxn], temp;

bool cmp(Record a, Record b);
void get_ans(int on, int off, int &time, int &money);

int main(){
	for(int i = 0; i < 24; i++){
		scanf("%d", &toll[i]);	//资费 
	}
	int n;
	scanf("%d", &n);	//记录数
	char line[10];	//临时存放on-line或off-line的输入
	for(int i = 0; i < n; i++){
		scanf("%s %d:%d:%d:%d %s", rec[i].name, &rec[i].month, &rec[i].dd, &rec[i].hh, &rec[i].mm, line);
		if(strcmp(line, "on-line") == 0){
			rec[i].status = true;	//如果是on-line，则令status为true 
		}else{
			rec[i].status = false;	//如果是off-line，则令status为false 
		}
	}
	sort(rec, rec + n, cmp);	//排序 
	int on = 0, off, next;	//on和off为配对的两条记录，next为下一个用户
	while(on < n){	//每次循环处理单个用户的所有记录 
		int needPrint = 0;	//needPrint表示该用户是否需要输出
		next = on;	//从当前位置开始寻找下一个用户
		while(next < n && strcmp(rec[next].name, rec[on].name) == 0){
			if(needPrint == 0 && rec[next].status){
				needPrint = 1;	//找到on，置needPrint为1 
			}else if(needPrint == 1 && !rec[next].status){
				needPrint = 2;	//在on之后如果找到off，置needPrint为2 
			}
			next++;	//next自增，直到找到不同名字，即下一个用户 
		} 
		if(needPrint < 2){	//没有找到配对的on-off 
			on = next;
			continue;
		}
		int AllMoney = 0;	//总共花费的钱
		printf("%s %02d\n", rec[on].name, rec[on].month);
		while(on < next){
			while(on < next - 1 && !(rec[on].status && !rec[on + 1].status)){
				on++;	//直到找到连续的on-line和off-line 
			}
			off = on + 1;	//off必须是on的下一个
			if(off == next){	//已经输出完毕所有配对的on-line和off-line 
				on = next;
				break;
			}
			printf("%02d:%02d:%02d ", rec[on].dd, rec[on].hh, rec[on].mm);
			printf("%02d:%02d:%02d ", rec[off].dd, rec[off].hh, rec[off].mm);
			int time = 0, money = 0;	//时间、单次记录花费的钱
			get_ans(on, off, time, money);	//计算on到off内的时间和金钱
			AllMoney += money;
			printf("%d $%.2f\n", time, money / 100.0);
			on = off + 1;	//完成一个配对，从off + 1开始找下一对 
		}
		printf("Total amount: $%.2f\n", AllMoney / 100.0); 
	}
	return 0; 
}
 
bool cmp(Record a, Record b){
	int s = strcmp(a.name, b.name);
	if(s != 0){
		return s < 0;	//优先按姓名字典序从小到大排序 
	}else if(a.month != b.month){
		return a.month < b.month;	//按月份从小到大排序 
	}else if(a.dd != b.dd){
		return a.dd < b.dd;	//按日期从小到大排序 
	}else if(a.hh != b.hh){
		return a.hh < b.hh;	//按小时从小到大排序 
	}else{
		return a.mm < b.mm;	//按分钟从小到大排序 
	}
}

void get_ans(int on, int off, int &time, int &money){
	temp = rec[on];
	while(temp.dd < rec[off].dd || temp.hh < rec[off].hh || temp.mm < rec[off].mm){
		time++;	//该次记录总时间加1min
		money += toll[temp.hh];	//花费增加toll[temp.hh]
		temp.mm++;	//当前时间加1min 
		if(temp.mm >= 60){	//当前分钟数到达60 
			temp.mm = 0; //进入下一个小时
			temp.hh++; 
		}
		if(temp.hh >= 24){	//当前小时数到达24 
			temp.hh = 0;	//进入下一天 
			temp.dd++;
		} 
	}
} 
