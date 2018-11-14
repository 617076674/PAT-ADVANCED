#include<iostream>
#include<map>
#include<vector>
#include<string>

using namespace std;

int n;	//�绰��
int k;	//�ж�"Gang"������
int father[2001];	//���鼯����
int weight[2001] = {0};	//weight[i]��ʾ���Ϊi���˵ĵ�Ȩ
int graph[2001][2001] = {0};	//����ͼ
int visited[2001] = {false};	//�������
map<string, int> result;	//��Ž����ͷͷ����->��ͷͷ��Ӧ�Ŷӵĳ�Ա�� 
map<string, int> stringToInt;	//����->���
map<int, string> intToString;	//���->����
int totalPeople = 0;	//������
int gangEdgeWeight[2001];	//gangEdgeWeight[i]�����iΪͷͷ��һ��"Gang"���ܵ�Ȩ
int gangSize[2001];	//gangSize[i]�����iΪͷͷ��һ��"Gang"��������

int change(string str);
int findFather(int x);
void unionTwo(int x, int y);

int main() {
	cin >> n >> k;
	string name1, name2;
	int time;
	for(int i = 0; i < n; i++) {
		cin >> name1 >> name2 >> time;
		int id1 = change(name1);
		int id2 = change(name2);
		graph[id1][id2] += time;
		graph[id2][id1] += time;
		weight[id1] += time;
		weight[id2] += time;
	}
	for(int i = 0; i < totalPeople; i++) {
		father[i] = i;	//���鼯��ʼ��
		gangSize[i] = 1;	//ÿ���˸���һ��
		gangEdgeWeight[i] = weight[i]; 
	}
	for(int i = 0; i < totalPeople; i++) {
		for(int j = 0; j < totalPeople; j++) {
			if(graph[i][j] != 0) {
				unionTwo(i, j);	//���鼯�ĺϲ�����
			}
		}
	}
	for(int i = 0; i < totalPeople; i++) {
		if(gangSize[findFather(i)] > 2 && gangEdgeWeight[findFather(i)] > 2 * k) {
			result[intToString[findFather(i)]] = gangSize[findFather(i)]; 
		}
	}
	map<string, int>::iterator it;
	cout << result.size() << endl;
	for(it = result.begin(); it != result.end(); it++) {
		cout << it->first << " " << it->second << endl;
	}
	return 0;
}

int findFather(int x) {
	int a = x;
	while(x != father[x]) {
		x = father[father[x]];	 
	}
	while(a != father[a]){	//·��ѹ�� 
		int z = a;
		a = father[a];
		father[z] = x;
	}
	return x;
}

void unionTwo(int x, int y) {
	int xFather = findFather(x);	//����õ���findFather()������������ֱ����father[]������ȡ 
	int yFather = findFather(y);
	if(xFather == yFather){
		return;
	}
	if(weight[xFather] > weight[yFather]) {
		father[yFather] = xFather;
		gangSize[xFather] += gangSize[yFather];
		gangEdgeWeight[xFather] += gangEdgeWeight[yFather];
	} else {
		father[xFather] = yFather;
		gangSize[yFather] += gangSize[xFather];
		gangEdgeWeight[yFather] += gangEdgeWeight[xFather];
	}
}

int change(string str) {
	if(stringToInt.find(str) != stringToInt.end()) {
		return stringToInt[str];
	}
	stringToInt[str] = totalPeople;
	intToString[totalPeople] = str;
	return totalPeople++;
}
