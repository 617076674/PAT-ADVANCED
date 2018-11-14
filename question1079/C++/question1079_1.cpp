#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

struct node{
	int sales;
	vector<int> child;
};

int N;
double P;
double r;
node Node[100000];
double totalSales = 0.0;

void dfs(int nowVisit, int level);

int main(){
	cin >> N >> P >> r;
	int K, num;
	for(int i = 0; i < N; i++){
		cin >> K;
		if(K == 0){
			cin >> num;
			Node[i].sales = num; 
		}else{
			for(int j = 0; j < K; j++){
				cin >> num;
				Node[i].child.push_back(num);
			}
		}
	}
	dfs(0, 0);
	printf("%.1lf\n", totalSales);	//自动四舍五入 
	return 0;
}

void dfs(int nowVisit, int level){
	if(Node[nowVisit].child.size() == 0){
		totalSales += Node[nowVisit].sales * P * pow(1.0 + r / 100, level);
		return;
	}
	for(int i = 0; i < Node[nowVisit].child.size(); i++){
		dfs(Node[nowVisit].child[i], level + 1);
	}
}
