#include<iostream>
#include<map>
#include<vector>
#include<string>

using namespace std;

int n;	//电话数
int k;	//判断"Gang"的下限
int father[2001];	//并查集数组
int weight[2001] = {0};	//weight[i]表示编号为i的人的点权
int graph[2001][2001] = {0};	//无向图
int visited[2001] = {false};	//标记数组
map<string, int> result;	//存放结果，头头名字->该头头对应团队的成员数 
map<string, int> stringToInt;	//姓名->编号
map<int, string> intToString;	//编号->姓名
int totalPeople = 0;	//总人数
int gangEdgeWeight[2001];	//gangEdgeWeight[i]存放以i为头头的一个"Gang"的总点权
int gangSize[2001];	//gangSize[i]存放以i为头头的一个"Gang"的总人数

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
		father[i] = i;	//并查集初始化
		gangSize[i] = 1;	//每个人各自一伙
		gangEdgeWeight[i] = weight[i]; 
	}
	for(int i = 0; i < totalPeople; i++) {
		for(int j = 0; j < totalPeople; j++) {
			if(graph[i][j] != 0) {
				unionTwo(i, j);	//并查集的合并操作
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
	while(a != father[a]){	//路径压缩 
		int z = a;
		a = father[a];
		father[z] = x;
	}
	return x;
}

void unionTwo(int x, int y) {
	int xFather = findFather(x);	//这里得调用findFather()函数，而不是直接在father[]数组里取 
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
