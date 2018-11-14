#include<iostream>
#include<string>
#include<map>

using namespace std;

bool isPartOfWord(char c);

int main(){
	string input;
	getline(cin, input);
	for(int i = 0; i < input.length(); i++){
		if(input[i] >= 'A' && input[i] <= 'Z'){
			input[i] = input[i] - 'A' + 'a';
		}
	}
	map<string, int> wordMap;
	for(int i = 0; i < input.length(); i++){
		if(!isPartOfWord(input[i])){
			continue;
		}
		int j = i;
		while(isPartOfWord(input[j])){
			j++;
		}
		wordMap[input.substr(i, j - i)]++;
		i = j;
	}
	string result;
	int count = 0;
	for(map<string, int>::iterator it = wordMap.begin(); it != wordMap.end(); it++){
		if(it->second > count){
			result = it->first;
			count = it->second;
		}
	}
	cout << result << " " << count << endl;
	return 0;
}

bool isPartOfWord(char c){
	if((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
		return true;
	}
	return false;
}
