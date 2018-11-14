#include<iostream>
#include<vector>

using namespace std;

long long changeToKnut(long long Galleon, long long Sickle, long long Knut);

int main(){
	long long Galleon1, Sickle1, Knut1, Galleon2, Sickle2, Knut2;
	scanf("%lld.%lld.%lld", &Galleon1, &Sickle1, &Knut1);
	long long AKnuts = changeToKnut(Galleon1, Sickle1, Knut1);
	scanf("%lld.%lld.%lld", &Galleon2, &Sickle2, &Knut2);
	long long BKnuts = changeToKnut(Galleon2, Sickle2, Knut2);
	long long totalKnuts = AKnuts + BKnuts;
	vector<long long> result;
	result.push_back(totalKnuts % 29);
	totalKnuts /= 29;
	result.push_back(totalKnuts % 17);
	result.push_back(totalKnuts / 17);
	printf("%lld.%lld.%lld\n", result[2], result[1], result[0]);
	return 0;
}

long long changeToKnut(long long Galleon, long long Sickle, long long Knut){
	return Galleon * 17 * 29 + Sickle * 29 + Knut;
}
