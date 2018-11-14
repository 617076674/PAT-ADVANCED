#include<iostream>
#include<string>

using namespace std;

int main(){
	string input;
	cin >> input;
	long countLeftP[input.length()];	//在索引i的左边有countLeftP[i]个P字符
	countLeftP[0] = 0;
	long total = 0;
	for(int i = 1; i < input.length(); i++){
		if(input[i - 1] == 'P'){
			countLeftP[i] = countLeftP[i - 1] + 1;
		}else{
			countLeftP[i] = countLeftP[i - 1];
		} 
	}
	long countRightT[input.length()];	//在索引i的右边有countRightT[i]个T字符
	countRightT[input.length() - 1] = 0;
	for(int i = input.length() - 2; i >= 0; i--){
		if(input[i + 1] == 'T'){
			countRightT[i] = countRightT[i + 1] + 1;
		}else{
			countRightT[i] = countRightT[i + 1];
		}
	}
	for(int i = 0; i < input.length(); i++){
		if(input[i] == 'A'){
			total += countLeftP[i] * countRightT[i];
		}
	}
	printf("%ld", total % 1000000007);
	return 0;
} 
