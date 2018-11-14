#include<iostream>
#include<vector>
#include<utility>
#include<cmath>

using namespace std;

double coefficients1[1001];
double coefficients2[1001];
double coefficients[2001];
vector<pair<int, double> > results;

int main(){

	fill(coefficients1, coefficients1 + 1001, 0.0);
	fill(coefficients2, coefficients2 + 1001, 0.0);
	fill(coefficients, coefficients + 2001, 0.0);
	int K, N;
	double aN;
	scanf("%d", &K);
	for(int i = 0; i < K; i++){
		scanf("%d %lf", &N, &aN);
		coefficients1[N] += aN;
	}
	scanf("%d", &K);
	for(int i = 0; i < K; i++){
		scanf("%d %lf", &N, &aN);
		coefficients2[N] += aN;
	}
	for(int i = 0; i < 1001; i++){
		if(fabs(coefficients1[i]) >= 0.00000001){
			for(int j = 0; j < 1001; j++){
				if(fabs(coefficients2[j]) >= 0.00000001){
					coefficients[i + j] += coefficients1[i] * coefficients2[j]; 
				}
			}
		}
	}
	for(int i = 2000; i >= 0; i--){
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
