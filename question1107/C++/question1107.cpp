#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>

using namespace std;

int N;
int father[1000];	//并查集，假设人的编号是从0 ~ N - 1的 
vector<int> hoppy[1001];	//根据兴趣将人进行分组 
int countFather[1000] = {0};	//countFather[i]表示以i为父节点的人数 

int change(string s);
int findFather(int x);
void unionTwo(int a, int b); 

int main(){
	cin >> N;
	string count;
	int num; 
	for(int i = 0; i < N; i++){
		father[i] = i;	//初始时各自成一个节点
		cin >> count;
		int total = change(count);
		for(int j = 0; j < total; j++){
			cin >> num;
			hoppy[num].push_back(i);
		} 
	}
	for(int i = 1; i <= 1000; i++){
		int size = hoppy[i].size(); 
		for(int j = 0; j < size - 1; j++){	//直接写成for(int j = 0; j < hoppy[i].size() - 1; j++)会报段错误，不知为何 
			unionTwo(hoppy[i][j], hoppy[i][j + 1]);
		}
	}
	for(int i = 0; i < N; i++){
		countFather[findFather(i)]++;
	}
	sort(countFather, countFather + N);
	int clusters;
	for(int i = N - 1; i >= 0; i--){
		if(countFather[i] == 0){
			clusters = N - 1 - i;
			break;
		}
	}
	cout << clusters << endl;
	for(int i = N - 1; i > N - 1 - clusters; i--){
		cout << countFather[i];
		if(i != N - clusters){
			cout << " ";
		}
	}
	cout << endl;
	return 0; 
}

int change(string s){
	s = s.substr(s.length() - 2, 1);
	stringstream ss;
	ss << s;
	int result;
	ss >> result;
	return result;
}

int findFather(int x){
	int a = x;
	while(x != father[x]){
		x = father[x];
	}
	while(a != father[a]){
		int z = a;
		a = father[a];
		father[z] = x;
	}
	return x;
}

void unionTwo(int a, int b){
	int aFather = findFather(a);
	int bFather = findFather(b);
	if(aFather != bFather){
		father[aFather] = bFather;
	}
}
