#include<iostream>
#include<cmath>
#include<vector>
#include<string> 

using namespace std;

string changeToString(int num, int D);	//把10进制的num转换成D进制，以string形式输出 
string reverse(string s);	//反转字符串 
int changeToInt(string s, int D);	//把D进制的字符串s转换成10进制数字 
bool isPrime(int num);

int main(){
	int N, D;
	while(true){
		scanf("%d", &N);
		if(N < 0){
			return 0;
		}
		scanf("%d", &D);
		if(isPrime(changeToInt(changeToString(N, D), D)) && isPrime(changeToInt(reverse(changeToString(N, D)), D))){
			printf("Yes\n");
		}else{
			printf("No\n");
		}
	}
}

string changeToString(int num, int D){
	vector<int> nums;
	while(num > 0){
		nums.push_back(num % D);
		num /= D;
	}
	string result = "";
	for(int i = nums.size() - 1; i >= 0; i--){
		result += nums[i] + '0';
	}
	return result;
}

string reverse(string s){
	string result = "";
	for(int i = s.length() - 1; i >= 0; i--){
		result += s[i];
	}
	return result;
}

int changeToInt(string s, int D){
	int result = 0;
	for(int i = s.length() - 1; i >= 0; i--){
		result = result * D + s[i] - '0';
	}
	return result; 
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
