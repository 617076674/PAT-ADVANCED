#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

struct student{
	int number;
	string name;
	int score;
	student(int _number, string _name, int _score) : number(_number), name(_name), score(_score) {};
};

int N, C;
vector<student> students;

bool cmp1(student s1, student s2);
bool cmp2(student s1, student s2);
bool cmp3(student s1, student s2);

int main(){
	cin >> N >> C;
	int number;
	string name;
	int score;
	for(int i = 0; i < N; i++){
		cin >> number >> name >> score;
		students.push_back(student(number, name, score));
	}
	if(C == 1){
		sort(students.begin(), students.end(), cmp1);
	}else if(C == 2){
		sort(students.begin(), students.end(), cmp2);
	}else{
		sort(students.begin(), students.end(), cmp3);
	}
	for(int i = 0; i < students.size(); i++){
		printf("%06d ", students[i].number);
		cout << students[i].name << " " << students[i].score << endl;
	}
	return 0;
} 

bool cmp1(student s1, student s2){
	return s1.number < s2.number;
}

bool cmp2(student s1, student s2){
	if(s1.name.compare(s2.name) == 0){
		return s1.number < s2.number;
	}else{
		return s1.name.compare(s2.name) < 0;
	}
}

bool cmp3(student s1, student s2){
	if(s1.score == s2.score){
		return s1.number < s2.number;
	}else{
		return s1.score < s2.score;
	}
}
