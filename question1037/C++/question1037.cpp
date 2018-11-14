#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int Nc, Np;
vector<int> positiveCoupons;
vector<int> negativeCoupons;
vector<int> positiveValues;
vector<int> negativeValues;
long result;

bool cmp(int a, int b);

int main(){
	scanf("%d", &Nc);
	int num;
	for(int i = 0; i < Nc; i++){
		scanf("%d", &num);
		if(num < 0){
			negativeCoupons.push_back(num);
		}else if(num > 0){
			positiveCoupons.push_back(num);
		}
	}
	scanf("%d", &Np);
	for(int i = 0; i < Np; i++){
		scanf("%d", &num);
		if(num < 0){
			negativeValues.push_back(num);
		}else if(num > 0){
			positiveValues.push_back(num);
		}
	}
	sort(positiveCoupons.begin(), positiveCoupons.end(), cmp);
	sort(positiveValues.begin(), positiveValues.end(), cmp);
	for(int i = 0; i < positiveCoupons.size() && i < positiveValues.size(); i++){
		result += positiveCoupons[i] * positiveValues[i];
	}
	sort(negativeCoupons.begin(), negativeCoupons.end());
	sort(negativeValues.begin(), negativeValues.end());
	for(int i = 0; i < negativeCoupons.size() && i < negativeValues.size(); i++){
		result += negativeCoupons[i] * negativeValues[i];
	}
	printf("%ld\n", result);
	return 0;
}

bool cmp(int a, int b){
	return a > b;
}
