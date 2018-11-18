#include<iostream>
#include<vector>
#include<utility>
#include<cmath>

using namespace std;

int main(){
	double coefficients[1001];	//coefficients[i]�������ϵ��Ϊcoefficients[i]��ָ��Ϊi
	fill(coefficients, coefficients + 1001, 0.0);
	int K, N;		 
	double aN;
	scanf("%d", &K);	//��ȡ��һ������ʽ������ 
	for(int i = 0; i < K; i++){
		scanf("%d %lf", &N, &aN);	//��ȡ��һ������ʽ�и����ϵ����ָ�� 
		coefficients[N] += aN;
	}
	scanf("%d", &K);	//��ȡ�ڶ�������ʽ������ 
	for(int i = 0; i < K; i++){
		scanf("%d %lf", &N, &aN);	//��ȡ�ڶ�������ʽ�и����ϵ����ָ�� 
		coefficients[N] += aN;
	}
	vector<pair<int, double> > results;	//�洢�����ָ����ϵ�� 
	for(int i = 1000; i >= 0; i--){
		if(fabs(coefficients[i]) >= 0.00000001){	//double���͵ıȽ� 
			results.push_back(make_pair(i, coefficients[i]));	//ֻҪ����ϵ����Ϊ0������ӽ���� 
		}
	}
	printf("%d", results.size());	//��������� 
	for(int i = 0; i < results.size(); i++){
		printf(" %d %.1f", results[i].first, results[i].second);	//��ʽ�������� 
	}
	printf("\n");
	return 0; 
}
