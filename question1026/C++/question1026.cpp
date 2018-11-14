#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;

struct Player{
	int arriveTime, startTime, trainTime;	//����ʱ�䡢ѵ����ʼʱ�估ѵ��ʱ��
	bool isVIP;	//�Ƿ���VIP��Ա 
};

struct Table{
	int endTime, numServe;	//��ǰռ�ø���������Ա�Ľ���ʱ�估��ѵ��������
	bool isVIP;	//�Ƿ���VIP���� 
};

const int K = 111;	//������
const int INF = 1000000000;	//�������
Player newPlayer;	//��ʱ����¶������Ա
Table table[K];	//K������ 
vector<Player> player;	//��Ա���� 

int convertTime(int h, int m, int s);	//��ʱ��ת��Ϊ��sΪ��λ������ȽϺͼ���
bool cmpArriveTime(Player a, Player b);	//������ʱ������ 
bool cmpStartTime(Player a, Player b);	//����ʼʱ������
int nextVIPPlayer(int VIPi);	//���VIPi�ӵ�ǰVIP��Ա�Ƶ���һ��VIP��Ա 
void allotTable(int pID, int tID);	//�����ΪtID��������������ΪPID����Ա 

int main(){
	int n, k, m, VIPtable;
	scanf("%d", &n);	//��Ա��
	int stTime = convertTime(8, 0, 0);	//����ʱ��Ϊ8�� 
	int edTime = convertTime(21, 0, 0); //����ʱ��Ϊ21��
	for(int i = 0; i < n; i++){
		int h, m, s, trainTime, isVIP;	//ʱ���֡��롢ѵ��ʱ�����Ƿ���VIP��Ա
		scanf("%d:%d:%d %d %d", &h, &m, &s, &trainTime, &isVIP); 
		newPlayer.arriveTime = convertTime(h, m, s);	//����ʱ��
		newPlayer.startTime = edTime;	//��ʼʱ���ʼ��Ϊ21��
		if(newPlayer.arriveTime >= edTime){	//21�㼰�Ժ��ֱ���ų� 
			continue;	
		} 
		newPlayer.trainTime = trainTime <= 120 ? trainTime * 60 : 7200;	//ѵ��ʱ��
		newPlayer.isVIP = isVIP;	//�Ƿ���VIP 
		player.push_back(newPlayer); //��newPlayer���뵽��Ա������ 
	}
	scanf("%d%d", &k, &m);	//��������VIP������
	for(int i = 1; i <= k; i++){
		table[i].endTime = stTime;	//��ǰѵ������ʱ��Ϊ8��
		table[i].numServe = table[i].isVIP = 0;	//��ʼ��numServe��isVIP 
	}
	for(int i = 0; i < m; i++){
		scanf("%d", &VIPtable);	//VIP�������
		table[VIPtable].isVIP = 1;	//��ΪVIP���� 
	}
	sort(player.begin(), player.end(), cmpArriveTime);	//������ʱ������
	int i = 0, VIPi = -1;	//i����ɨ��������Ա��VIPi����ָ��ǰ��ǰ��VIP��Ա
	VIPi = nextVIPPlayer(VIPi);	//�ҵ���һ��VIP��Ա�ı��
	while(i < player.size()){	//��ǰ������ǰ�����ԱΪi 
		int idx = -1, minEndTime = INF;	//Ѱ�������ܿ��е�����
		for(int j = 1; j <= k; j++){
			if(table[j].endTime < minEndTime){
				minEndTime = table[j].endTime;
				idx = j;
			}
		}
		//idxΪ������е��������
		if(table[idx].endTime >= edTime){	//�Ѿ����ţ�ֱ��break 
			break;	
		}
		if(player[i].isVIP  && i < VIPi){
			i++;	//���i����VIP��Ա������VIPi > i��˵��i����Ա�Ѿ���ѵ�� 
			continue;
		}
		//���°������Ƿ���VIP����Ա�Ƿ���VIP������4���������
		if(table[idx].isVIP){
			if(player[i].isVIP){															//��һ�������������VIP����Ա��VIP 
				allotTable(i, idx);	//������idx�������Աi
				if(VIPi == i){
					VIPi = nextVIPPlayer(VIPi);	//�ҵ���һ��VIP��Ա 
				} 
				i++;
			}else{																			//�ڶ��������������VIP����Ա����VIP 
				//�����ǰ���׵�VIP��Ա�ȸ�VIP�����磬�Ͱ�����idx�������
				if(VIPi < player.size() && player[VIPi].arriveTime <= table[idx].endTime){
					allotTable(VIPi, idx);	//������idx�������ԱVIPi
					VIPi = nextVIPPlayer(VIPi);	//�ҵ���һ��VIP��Ա 
				}else{
					//����VIP��Ա�ȸ�VIP�����٣���Ȼ������idx�������Աi
					allotTable(i, idx);	//������idx�������Աi 
					i++;	//i����Ա��ʼѵ������˼������е���һ���� 
				} 
			}
		}else{
			if(!player[i].isVIP){															//�������������������VIP����Ա����VIP 
				allotTable(i, idx);	//������idx�������Աi
				i++;	//i����Ա��ʼѵ������˼������е���һ���� 
			}else{																			//�������������������VIP����Ա��VIP 
				//�ҵ�������е�VIP����
				int VIPidx = -1, minVIPEndTime = INF;
				for(int j = 1; j <= k; j++){
					if(table[j].isVIP && table[j].endTime < minVIPEndTime){
						minVIPEndTime = table[j].endTime;
						VIPidx = j;
					}
				}
				//������е�VIP���������VIPidx
				if(VIPidx != -1 && player[i].arriveTime >= table[VIPidx].endTime){
					//���VIP�������ڣ��ҿ���ʱ�����Ա����ʱ����
					//�Ͱ����������Աi
					allotTable(i, VIPidx);
					if(VIPi == i){
						VIPi = nextVIPPlayer(VIPi);	//�ҵ���һ��VIP��Ա 
					} 
					i++;
				}else{
					//�����Ա��ʱVIP������δ���У��Ͱ�����idx�������
					allotTable(i, idx);
					if(VIPi == i){
						VIPi = nextVIPPlayer(VIPi);	//�ҵ���һ��VIP��Ա 
					}
					i++; 
				}
			}
		}
	}
	sort(player.begin(), player.end(), cmpStartTime);	//����ʼʱ������
	for(int i = 0; i < player.size() && player[i].startTime < edTime; i++){
		int t1 = player[i].arriveTime;
		int t2 = player[i].startTime;
		printf("%02d:%02d:%02d ", t1 / 3600, t1 % 3600 / 60, t1 % 60);
		printf("%02d:%02d:%02d ", t2 / 3600, t2 % 3600 / 60, t2 % 60);
		printf("%.0f\n", round((t2 - t1) / 60.0));
	} 
	for(int i = 1; i <= k; i++){
		printf("%d", table[i].numServe);
		if(i < k){
			printf(" ");
		}
	}
	return 0;
} 

int convertTime(int h, int m, int s){
	return h * 3600 + m * 60 + s;	
}

bool cmpArriveTime(Player a, Player b){
	return a.arriveTime < b.arriveTime;
}

bool cmpStartTime(Player a, Player b){
	return a.startTime < b.startTime;
}

int nextVIPPlayer(int VIPi){
	VIPi++;	//�Ƚ�VIPi��1 
	while(VIPi < player.size() && !player[VIPi].isVIP){
		VIPi++;	//ֻҪ��ǰ��Ա����VIP������VIPi����һλ 
	}
	return VIPi;	//������һ��VIP��Ա��ID 
}

void allotTable(int pID, int tID){
	if(player[pID].arriveTime <= table[tID].endTime){	//������Ա�Ŀ�ʼʱ�� 
		player[pID].startTime = table[tID].endTime;
	}else{
		player[pID].startTime = player[pID].arriveTime;
	}
	//��������ѵ������ʱ�����Ϊ����Ա�Ľ���ʱ�䣬���÷���������1
	table[tID].endTime = player[pID].startTime + player[pID].trainTime;
	table[tID].numServe++; 
}
