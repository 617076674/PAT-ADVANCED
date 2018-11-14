#include<iostream>
#include<string>
#include<map>

using namespace std;

map<int, string> intToString;	//编号->姓名 
map<string, int> stringToInt;	//姓名->编号 
map<string, int> gang;		//Gang的头目姓名->Gang的人数 

int graph[2001][2001] = {0};	//邻接矩阵graph 
int weight[2001] = {0};		//点权weight，判断Gang中的头目是谁，需要用到点权 
bool visited[2001] = {false};	//标记是否被访问 

int n;	//边数n 
int k;	//判断一个团队是否是Gang的标准k 
int numPerson = 0;	//总人数numPerson 

/*
	dfs函数访问单个连通块
	
	nowVisit：当前访问的编号
	head：头目
	numMember：成员编号
	totalValue：连通块的总边权，判断一个团队是否是Gang，需要用到连通块的总边权 
*/ 
void dfs(int nowVisit, int& head, int& numMember, int& totalValue);

/*
	dfsTravel函数遍历整个图，获取每个连通块的信息 
*/
void dfsTravel(); 

/*
	change函数返回姓名str对应的编号 
*/
int change(string str);


int main() {
	cin >> n >> k;
	string name1;
	string name2;
	int time;
	for(int i = 0; i < n; i++) {
		cin >> name1 >> name2 >> time;	//输入边的两个端点和点权 
		int id1 = change(name1);
		int id2 = change(name2);
		weight[id1] += time;
		weight[id2] += time;
		graph[id1][id2] += time;
		graph[id2][id1] += time;	
	}
	dfsTravel();	//遍历整个图的所有连通块，获取Gang的信息
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
		head = nowVisit;	//当前访问节点的点权大于头目的点权，则更新头目 
	}
	for(int i = 0; i < numPerson; i++){
		if(graph[nowVisit][i] > 0){
			totalValue += graph[nowVisit][i];
			graph[nowVisit][i] = graph[i][nowVisit] = 0;	//删除这条边，防止回头
			if(!visited[i]){
				dfs(i, head, numMember, totalValue);	//如果i未被访问，则递归访问i 
			} 
		}
	}
}

void dfsTravel(){
	for(int i = 0; i < numPerson; i++){
		if(!visited[i]){
			int head = i;	//头目 
			int numMember = 0;	//成员数 
			int totalValue = 0;	//总边权
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
