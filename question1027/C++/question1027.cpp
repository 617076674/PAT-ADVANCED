#include<iostream>
#include<utility>

using namespace std;

char Mars[13] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C'};

pair<char, char> change(int num);

int main(){
	int Red, Green, Blue;
	scanf("%d %d %d", &Red, &Green, &Blue);
	pair<char, char> RedPair = change(Red);
	pair<char, char> GreenPair = change(Green);
	pair<char, char> BluePair = change(Blue);
	printf("#%c%c%c%c%c%c\n", RedPair.first, RedPair.second, GreenPair.first, GreenPair.second, BluePair.first, BluePair.second);
	return 0;
}

pair<char, char> change(int num){
	pair<char, char> result;
	result.first = Mars[num / 13];
	result.second = Mars[num % 13];
	return result;
}
