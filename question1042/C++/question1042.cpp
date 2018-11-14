#include<iostream>
#include<string>

using namespace std;

int main(){
	string letter[5] = {"S", "H", "C", "D", "J"};
	string digit[13] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13"};
	string card[54];
	string newCard[54];
	for(int i = 0; i < 54; i++){
		if(i < 13){
			card[i] = letter[0] + digit[i];
		}else if(i >= 13 && i < 26){
			card[i] = letter[1] + digit[i - 13];
		}else if(i >= 26 && i < 39){
			card[i] = letter[2] + digit[i - 26];
		}else if(i >= 39 && i < 52){
			card[i] = letter[3] + digit[i - 39];
		}else{
			card[i] = letter[4] + digit[i - 52];
		}
	}
	int K;
	scanf("%d", &K);
	int nums[54];
	for(int i = 0; i < 54; i++){
		scanf("%d", &nums[i]);
	}
	for(int i = 0; i < K; i++){
		for(int j = 0; j < 54; j++){
			newCard[nums[j] - 1] = card[j];
		}
		for(int j = 0; j < 54; j++){
			card[j] = newCard[j];
		}
	}
	for(int i = 0; i < 54; i++){
		cout << card[i];
		if(i != 53){
			cout << " ";
		}else{
			cout << endl;
		}
	}
	return 0;
} 
