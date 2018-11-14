#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>

using namespace std;

int N;
int father[1000];	//���鼯�������˵ı���Ǵ�0 ~ N - 1�� 
vector<int> hoppy[1001];	//������Ȥ���˽��з��� 
int countFather[1000] = {0};	//countFather[i]��ʾ��iΪ���ڵ������ 

int change(string s);
int findFather(int x);
void unionTwo(int a, int b); 

int main(){
	cin >> N;
	string count;
	int num; 
	for(int i = 0; i < N; i++){
		father[i] = i;	//��ʼʱ���Գ�һ���ڵ�
		cin >> count;
		int total = change(count);
		for(int j = 0; j < total; j++){
			cin >> num;
			hoppy[num].push_back(i);
		} 
	}
	for(int i = 1; i <= 1000; i++){
		int size = hoppy[i].size(); 
		for(int j = 0; j < size - 1; j++){	//ֱ��д��for(int j = 0; j < hoppy[i].size() - 1; j++)�ᱨ�δ��󣬲�֪Ϊ�� 
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
