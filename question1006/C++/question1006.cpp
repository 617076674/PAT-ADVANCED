#include<iostream>
#include<cstring>

using namespace std;

int change(int hour, int minute, int second);

int main(){
	int M;
	scanf("%d", &M);
	char earliest[16], latest[16], temp[16];
	int first = 86400;
	int last = 0;
	int hour, minute, second;
	for(int i = 0; i < M; i++){
		scanf("%s", temp);
		scanf("%d:%d:%d", &hour, &minute, &second);
		if(change(hour, minute, second) < first){
			first = change(hour, minute, second);
			strcpy(earliest, temp);
		}
		scanf("%d:%d:%d", &hour, &minute, &second);
		if(change(hour, minute, second) > last){
			last = change(hour, minute, second);
			strcpy(latest, temp);
		}
	}
	printf("%s %s\n", earliest, latest);
	return 0;
}

int change(int hour, int minute, int second){
	return hour * 60 * 60 + minute * 60 + second;
}
