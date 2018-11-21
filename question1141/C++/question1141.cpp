#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

struct school{
	int rank;
	string name;
	int score[3];	//score[0]代表scoreB, score[1]代表score[A], score[2]代表score[T]
	int TWS;
	int Ns; 
};

map<string, school> schoolMap;

bool cmp(school s1, school s2);

int main(){
	int N;
	scanf("%d", &N);
	string ID, schoolName;
	int score;
	for(int i = 0; i < N; i++){
		cin >> ID >> score >> schoolName;
		for(int i = 0; i < schoolName.length(); i++){
			if(schoolName[i] >= 'A' && schoolName[i] <= 'Z'){
				schoolName[i] = schoolName[i] - 'A' + 'a';
			}
		}
		if(schoolMap.find(schoolName) == schoolMap.end()){
			school tempSchool;
			tempSchool.name = schoolName;
			if(ID[0] == 'B'){
				tempSchool.score[0] = score;
				tempSchool.score[1] = 0;
				tempSchool.score[2] = 0;
			}else if(ID[0] == 'A'){
				tempSchool.score[1] = score;
				tempSchool.score[0] = 0;
				tempSchool.score[2] = 0;
			}else{
				tempSchool.score[2] = score;
				tempSchool.score[0] = 0;
				tempSchool.score[1] = 0;
			}
			tempSchool.Ns = 1;
			schoolMap[schoolName] = tempSchool;
		}else{
			if(ID[0] == 'B'){
				schoolMap[schoolName].score[0] += score;
			}else if(ID[0] == 'A'){
				schoolMap[schoolName].score[1] += score;
			}else{
				schoolMap[schoolName].score[2] += score;
			}
			schoolMap[schoolName].Ns++;
		}
	}
	vector<school> schools;
	for(map<string, school>::iterator it = schoolMap.begin(); it != schoolMap.end(); it++){
		it->second.TWS = it->second.score[0] * 1.0 / 1.5 + it->second.score[1] + it->second.score[2] * 1.5;
		schools.push_back(it->second);
	}
	sort(schools.begin(), schools.end(), cmp);
	schools[0].rank = 1;
	for(int i = 1; i < schools.size(); i++){
		if(schools[i].TWS == schools[i - 1].TWS){
			schools[i].rank = schools[i - 1].rank;
		}else{
			schools[i].rank = i + 1;
		}
	}
	cout << schools.size() << endl;
	for(int i = 0; i < schools.size(); i++){
		cout << schools[i].rank << " " << schools[i].name << " " << schools[i].TWS << " " << schools[i].Ns << endl;
	}
}

bool cmp(school s1, school s2){
	if(s1.TWS == s2.TWS){
		if(s1.Ns == s2.Ns){
			return s1.name < s2.name;
		}else{
			return s1.Ns < s2.Ns;
		}
	}else{
		return s1.TWS > s2.TWS;
	}
}
