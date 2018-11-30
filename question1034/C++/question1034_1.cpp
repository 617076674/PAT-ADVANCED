#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<algorithm>

using namespace std;

struct node{
	int v;
	int time;
	node(int _v, int _time){
		v = _v;
		time = _time;
	}
};

struct gang{
	string head;
	int size;
	gang(string _head, int _size){
		head = _head;
		size = _size;
	}
};

int N, K;
map<string, int> stringToInt;
map<int, string> intToString;
int total = 0;
vector<node> graph[2000];
bool visited[2000];
int head, headTime, gangSize, pointWeight;

int changeToInt(string str);
void dfs(int nowVisit);
bool cmp(gang g1, gang g2);

int main(){
	fill(visited, visited + 2000, false);
	scanf("%d %d", &N, &K);
	string name1, name2;
	int person1, person2, time;
	for(int i = 0; i < N; i++){
		cin >> name1 >> name2 >> time;
		person1 = changeToInt(name1);
		person2 = changeToInt(name2);
		graph[person1].push_back(node(person2, time));
		graph[person2].push_back(node(person1, time));
	}
	vector<gang> gangs;
	for(int i = 0; i <= total; i++){
		if(visited[i]){
			continue;
		}
		head = i;
		headTime = 0;
		gangSize = 0;
		pointWeight = 0;
		dfs(i);
		if(gangSize > 2 && pointWeight > K * 2){
			gangs.push_back(gang(intToString[head], gangSize));
		}
	}
	sort(gangs.begin(), gangs.end(), cmp);
	cout << gangs.size() << endl;
	for(int i = 0; i < gangs.size(); i++){
		cout << gangs[i].head << " " << gangs[i].size << endl;
	}
	return 0;
} 

int changeToInt(string str){
	if(stringToInt.find(str) != stringToInt.end()){
		return stringToInt[str];
	}
	stringToInt[str] = total;
	intToString[total] = str;
	return total++;
}

void dfs(int nowVisit){
	visited[nowVisit] = true;
	gangSize++;
	int callTime = 0;
	for(int i = 0; i < graph[nowVisit].size(); i++){
		callTime += graph[nowVisit][i].time;
	}
	pointWeight += callTime;
	if(callTime > headTime){
		head = nowVisit;
		headTime = callTime;
	}
	for(int i = 0; i < graph[nowVisit].size(); i++){
		int v = graph[nowVisit][i].v;
		if(!visited[v]){
			dfs(v);
		}
	}
}

bool cmp(gang g1, gang g2){
	return g1.head < g2.head;
}
