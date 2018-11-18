#include<iostream>
#include<vector>
#include<utility>
#include<cmath>

using namespace std;

int main(){
	double coefficients[1001];	//coefficients[i]代表该项系数为coefficients[i]，指数为i
	fill(coefficients, coefficients + 1001, 0.0);
	int K, N;		 
	double aN;
	scanf("%d", &K);	//读取第一个多项式的项数 
	for(int i = 0; i < K; i++){
		scanf("%d %lf", &N, &aN);	//读取第一个多项式中各项的系数和指数 
		coefficients[N] += aN;
	}
	scanf("%d", &K);	//读取第二个多项式的项数 
	for(int i = 0; i < K; i++){
		scanf("%d %lf", &N, &aN);	//读取第二个多项式中各项的系数和指数 
		coefficients[N] += aN;
	}
	vector<pair<int, double> > results;	//存储各项的指数和系数 
	for(int i = 1000; i >= 0; i--){
		if(fabs(coefficients[i]) >= 0.00000001){	//double类型的比较 
			results.push_back(make_pair(i, coefficients[i]));	//只要该项系数不为0，则添加进结果 
		}
	}
	printf("%d", results.size());	//输出总项数 
	for(int i = 0; i < results.size(); i++){
		printf(" %d %.1f", results[i].first, results[i].second);	//格式化输出结果 
	}
	printf("\n");
	return 0; 
}
