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
	scanf("%d", &K);
	for(int i = 0; i < K; i++){
		scanf("%d %lf", &N, &aN);
		coefficients[N] += aN;
	}
	scanf("%d", &K);
	for(int i = 0; i < K; i++){
		scanf("%d %lf", &N, &aN);
		coefficients[N] += aN;
	}
	vector<pair<int, double> > results;
	for(int i = 1000; i >= 0; i--){
		if(fabs(coefficients[i]) >= 0.00000001){
			results.push_back(make_pair(i, coefficients[i]));
		}
	}
	printf("%d", results.size());
	for(int i = 0; i < results.size(); i++){
		printf(" %d %.1f", results[i].first, results[i].second);
	}
	return 0; 
}
