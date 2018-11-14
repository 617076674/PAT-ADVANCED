#include<iostream>
#include<string>
#include<map>

using namespace std;

map<int, string> intToString;	//���->���� 
map<string, int> stringToInt;	//����->��� 
map<string, int> gang;		//Gang��ͷĿ����->Gang������ 

int graph[2001][2001] = {0};	//�ڽӾ���graph 
int weight[2001] = {0};		//��Ȩweight���ж�Gang�е�ͷĿ��˭����Ҫ�õ���Ȩ 
bool visited[2001] = {false};	//����Ƿ񱻷��� 

int n;	//����n 
int k;	//�ж�һ���Ŷ��Ƿ���Gang�ı�׼k 
int numPerson = 0;	//������numPerson 

/*
	dfs�������ʵ�����ͨ��
	
	nowVisit����ǰ���ʵı��
	head��ͷĿ
	numMember����Ա���
	totalValue����ͨ����ܱ�Ȩ���ж�һ���Ŷ��Ƿ���Gang����Ҫ�õ���ͨ����ܱ�Ȩ 
*/ 
void dfs(int nowVisit, int& head, int& numMember, int& totalValue);

/*
	dfsTravel������������ͼ����ȡÿ����ͨ�����Ϣ 
*/
void dfsTravel(); 

/*
	change������������str��Ӧ�ı�� 
*/
int change(string str);


int main() {
	cin >> n >> k;
	string name1;
	string name2;
	int time;
	for(int i = 0; i < n; i++) {
		cin >> name1 >> name2 >> time;	//����ߵ������˵�͵�Ȩ 
		int id1 = change(name1);
		int id2 = change(name2);
		weight[id1] += time;
		weight[id2] += time;
		graph[id1][id2] += time;
		graph[id2][id1] += time;	
	}
	dfsTravel();	//��������ͼ��������ͨ�飬��ȡGang����Ϣ
	cout << gang.size() << endl;
	map<string, int>::iterator it;
	for(it = gang.begin(); it != gang.end(); it++){
		cout << it->first << " " << it->second << endl; 
	} 
	
	return 0;
}

void dfs(int nowVisit, int& head, int& numMember, int& totalValue){
	numMember++;
	visited[nowVisit] = true;
	if(weight[nowVisit] > weight[head]){
		head = nowVisit;	//��ǰ���ʽڵ�ĵ�Ȩ����ͷĿ�ĵ�Ȩ�������ͷĿ 
	}
	for(int i = 0; i < numPerson; i++){
		if(graph[nowVisit][i] > 0){
			totalValue += graph[nowVisit][i];
			graph[nowVisit][i] = graph[i][nowVisit] = 0;	//ɾ�������ߣ���ֹ��ͷ
			if(!visited[i]){
				dfs(i, head, numMember, totalValue);	//���iδ�����ʣ���ݹ����i 
			} 
		}
	}
}

void dfsTravel(){
	for(int i = 0; i < numPerson; i++){
		if(!visited[i]){
			int head = i;	//ͷĿ 
			int numMember = 0;	//��Ա�� 
			int totalValue = 0;	//�ܱ�Ȩ
			dfs(i, head, numMember, totalValue);
			if(numMember > 2 && totalValue > k){
				gang[intToString[head]] = numMember;
			} 
		}
	}
}

int change(string str){
	if(stringToInt.find(str) != stringToInt.end()){
		return stringToInt[str];
	}
	stringToInt[str] = numPerson;
	intToString[numPerson] = str;
	return numPerson++;
}
