#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

struct Record{
	char name[25];	//���� 
	int month, dd, hh, mm;	//�·ݡ��ա�ʱ����
	bool status;	//status==true��ʾ�ü�¼Ϊon-line������Ϊoff-line 
};

const int maxn = 1010;
int toll[25];	//�ʷ�
Record rec[maxn], temp;

bool cmp(Record a, Record b);
void get_ans(int on, int off, int &time, int &money);

int main(){
	for(int i = 0; i < 24; i++){
		scanf("%d", &toll[i]);	//�ʷ� 
	}
	int n;
	scanf("%d", &n);	//��¼��
	char line[10];	//��ʱ���on-line��off-line������
	for(int i = 0; i < n; i++){
		scanf("%s %d:%d:%d:%d %s", rec[i].name, &rec[i].month, &rec[i].dd, &rec[i].hh, &rec[i].mm, line);
		if(strcmp(line, "on-line") == 0){
			rec[i].status = true;	//�����on-line������statusΪtrue 
		}else{
			rec[i].status = false;	//�����off-line������statusΪfalse 
		}
	}
	sort(rec, rec + n, cmp);	//���� 
	int on = 0, off, next;	//on��offΪ��Ե�������¼��nextΪ��һ���û�
	while(on < n){	//ÿ��ѭ���������û������м�¼ 
		int needPrint = 0;	//needPrint��ʾ���û��Ƿ���Ҫ���
		next = on;	//�ӵ�ǰλ�ÿ�ʼѰ����һ���û�
		while(next < n && strcmp(rec[next].name, rec[on].name) == 0){
			if(needPrint == 0 && rec[next].status){
				needPrint = 1;	//�ҵ�on����needPrintΪ1 
			}else if(needPrint == 1 && !rec[next].status){
				needPrint = 2;	//��on֮������ҵ�off����needPrintΪ2 
			}
			next++;	//next������ֱ���ҵ���ͬ���֣�����һ���û� 
		} 
		if(needPrint < 2){	//û���ҵ���Ե�on-off 
			on = next;
			continue;
		}
		int AllMoney = 0;	//�ܹ����ѵ�Ǯ
		printf("%s %02d\n", rec[on].name, rec[on].month);
		while(on < next){
			while(on < next - 1 && !(rec[on].status && !rec[on + 1].status)){
				on++;	//ֱ���ҵ�������on-line��off-line 
			}
			off = on + 1;	//off������on����һ��
			if(off == next){	//�Ѿ�������������Ե�on-line��off-line 
				on = next;
				break;
			}
			printf("%02d:%02d:%02d ", rec[on].dd, rec[on].hh, rec[on].mm);
			printf("%02d:%02d:%02d ", rec[off].dd, rec[off].hh, rec[off].mm);
			int time = 0, money = 0;	//ʱ�䡢���μ�¼���ѵ�Ǯ
			get_ans(on, off, time, money);	//����on��off�ڵ�ʱ��ͽ�Ǯ
			AllMoney += money;
			printf("%d $%.2f\n", time, money / 100.0);
			on = off + 1;	//���һ����ԣ���off + 1��ʼ����һ�� 
		}
		printf("Total amount: $%.2f\n", AllMoney / 100.0); 
	}
	return 0; 
}
 
bool cmp(Record a, Record b){
	int s = strcmp(a.name, b.name);
	if(s != 0){
		return s < 0;	//���Ȱ������ֵ����С�������� 
	}else if(a.month != b.month){
		return a.month < b.month;	//���·ݴ�С�������� 
	}else if(a.dd != b.dd){
		return a.dd < b.dd;	//�����ڴ�С�������� 
	}else if(a.hh != b.hh){
		return a.hh < b.hh;	//��Сʱ��С�������� 
	}else{
		return a.mm < b.mm;	//�����Ӵ�С�������� 
	}
}

void get_ans(int on, int off, int &time, int &money){
	temp = rec[on];
	while(temp.dd < rec[off].dd || temp.hh < rec[off].hh || temp.mm < rec[off].mm){
		time++;	//�ôμ�¼��ʱ���1min
		money += toll[temp.hh];	//��������toll[temp.hh]
		temp.mm++;	//��ǰʱ���1min 
		if(temp.mm >= 60){	//��ǰ����������60 
			temp.mm = 0; //������һ��Сʱ
			temp.hh++; 
		}
		if(temp.hh >= 24){	//��ǰСʱ������24 
			temp.hh = 0;	//������һ�� 
			temp.dd++;
		} 
	}
} 
