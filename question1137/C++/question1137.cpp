#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;

struct scores {
	int gP;
	int gMidTerm;
	int gFinal;
	int g;
};

bool compare(pair<string, scores> pair1, pair<string, scores> pair2);

int main() {
	int P, M, N;
	cin >> P >> M >> N;

	map<string, scores> messages;
	map<string, scores>::iterator it;

	scores tempScores;
	string tempName;
	int tempScore;
	for(int i = 0; i < P; i++) {
		cin >> tempName >> tempScore;
		if(tempScore >= 200) {
			tempScores.gP = tempScore;
			tempScores.gMidTerm = -1;
			tempScores.gFinal = -1;
			messages[tempName] = tempScores;
		}
	}

	for(int i = 0; i < M; i++) {
		cin >> tempName >> tempScore;
		it = messages.find(tempName);
		if(it != messages.end()) {
			it->second.gMidTerm = tempScore;
		}
	}

	for(int i = 0; i < N; i++) {
		cin >> tempName >> tempScore;
		it = messages.find(tempName);
		if(it != messages.end()) {
			it->second.gFinal = tempScore;
		}
	}

	vector<pair<string, scores> > results;
	for(it = messages.begin(); it != messages.end(); it++) {
		int gMidTerm = it->second.gMidTerm;
		int gFinal = it->second.gFinal;
		double g;
		if(gMidTerm > gFinal){
			g = gMidTerm * 0.4 + gFinal * 0.6;
		}else{
			g = gFinal;
		}
		int trueG = (int) g;
		if(g - trueG >= 0.5){
			trueG++;
		}
		it->second.g = trueG;
		if(trueG >= 60){
			results.push_back(make_pair(it->first, it->second));
		}
	}
	
	sort(results.begin(), results.end(), compare);
	
	for(int i = 0; i < results.size(); i++){
		cout << results[i].first << " " << results[i].second.gP << " " << results[i].second.gMidTerm 
			<< " " << results[i].second.gFinal << " " << results[i].second.g << endl;
	}
	
}

bool compare(pair<string, scores> pair1, pair<string, scores> pair2){
	if(pair1.second.g == pair2.second.g){
		if(pair1.first.compare(pair2.first) >= 0){
			return false;
		}else{
			return true;
		}
	}else{
		if(pair1.second.g <= pair2.second.g){
			return false;
		}else{
			return true;
		}
	}
}
