#include<iostream>
#include<cstring>

using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	char maxGirlName[11], maxGirlID[11], minBoyName[11], minBoyID[11];
	int maxGirlScore = -1;
	int minBoyScore = 101;
	char tempName[11], c, tempID[11];
	int score;
	for(int i = 0; i < N; i++){
		scanf("%s %c %s %d", tempName, &c, tempID, &score);
		if(c == 'F' && score > maxGirlScore){
			strcpy(maxGirlName, tempName);
			strcpy(maxGirlID, tempID);
			maxGirlScore = score;
		}else if(c == 'M' && score < minBoyScore){
			strcpy(minBoyName, tempName);
			strcpy(minBoyID, tempID);
			minBoyScore = score;
		}
	}
	if(maxGirlScore != -1 && minBoyScore != 101){
		printf("%s %s\n", maxGirlName, maxGirlID);
		printf("%s %s\n", minBoyName, minBoyID);
		printf("%d\n", maxGirlScore - minBoyScore);
	}else if(maxGirlScore == -1 && minBoyScore == 101){
		printf("Absent\n");
		printf("Absent\n");
		printf("NA\n");
	}else if(maxGirlScore != -1 && minBoyScore == 101){
		printf("%s %s\n", maxGirlName, maxGirlID);
		printf("Absent\n");
		printf("NA\n");
	}else{
		printf("Absent\n");
		printf("%s %s\n", minBoyName, minBoyID);
		printf("NA\n");
	}
	return 0;
}
