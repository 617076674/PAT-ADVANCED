#include<iostream>
#include<string>

using namespace std;

string nextSequence(string s);

int main(){
	int d, N;
	cin >> d >> N;
	
	string firstNum = "";
	firstNum += d + '0';
	
	string result = firstNum;
	for(int i = 0; i < N - 1; i++){
		result = nextSequence(result);
	}
	
	cout << result << endl;
	
	return 0;
}

string nextSequence(string s){
	string result = "";
	int count;
	for(int i = 0; i < s.length(); i++){
		count = 1;
		while(s[i + 1] == s[i]){
			i++;
			count++;
		}
		result += s[i];
		result += count + '0';
	}
	return result;
}
