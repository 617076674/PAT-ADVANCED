#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int main(){
	int M, N, S;
	scanf("%d %d %d", &M, &N, &S);
	if(M < S){
		cout << "Keep going..." << endl;
		return 0;
	}
	vector<string> winners;
	int pre = M;
	string name;
	for(int i = 1; i <= M; i++){
		cin >> name;
		if(i == S){
			winners.push_back(name);
			pre = S;
			continue;
		}
		if(i - pre == N){
			while(i <= M && find(winners.begin(), winners.end(), name) != winners.end()){
				cin >> name;
				i++;
			}
			if(i <= M){
				winners.push_back(name);
				pre = i;
			}
		}
	}
	for(int i = 0; i < winners.size(); i++){
		cout << winners[i] << endl;
	}
	return 0;
} 
