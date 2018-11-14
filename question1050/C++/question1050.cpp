#include<iostream>
#include<string>

using namespace std;

int main(){
	bool flag[256];
	fill(flag, flag + 256, true);
	string input1;
	string input2;
	getline(cin, input1);
	getline(cin, input2);
	for(int i = 0; i < input2.length(); i++){
		flag[input2[i]] = false;
	}
	for(int i = 0; i < input1.length(); i++){
		if(flag[input1[i]]){
			printf("%c", input1[i]);
		}
	}
	return 0;
}
