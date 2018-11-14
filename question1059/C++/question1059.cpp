#include<iostream>
#include<vector>
#include<map>
#include<cmath> 

using namespace std;

struct factor{
	int num;
	int count;
	factor(int _num, int _count) : num(_num), count(_count) {};
}; 

bool isPrime(int num);

int main(){
	vector<factor> primes;
	int num;
	scanf("%d", &num);
	printf("%d=", num);
	if(isPrime(num) || num == 1){
		printf("%d", num);
		return 0;
	}
	for(int i = 2; i <= sqrt(num); i++){
		if(isPrime(i) && num % i == 0){
			primes.push_back(factor(i, 0));
		}
	}
	for(int i = 0; i < primes.size(); i++){
		while(num % primes[i].num == 0){
			primes[i].count++;
			num /= primes[i].num;
		}
	}
	if(num != 1){	//如果上述步骤后num仍然大于1，说明num有且仅有一个大于sqrt(num)的质因子(有可能是num本身) 
		primes.push_back(factor(num, 1));
	}
	for(int i = 0; i < primes.size(); i++){
		if(primes[i].count == 1){
			printf("%d", primes[i].num);
		}else{
			printf("%d^%d", primes[i].num, primes[i].count);
		}
		if(i != primes.size() - 1){
			printf("*");
		}
	}
	return 0;
}

bool isPrime(int num){
	if(num == 1){
		return false;
	}
	for(int i = 2; i <= sqrt(num); i++){
		if(num % i == 0){
			return false;
		}
	}
	return true;
} 
