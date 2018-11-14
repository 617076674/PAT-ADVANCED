#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

using namespace std;

struct student{
	string name;
	string ID;
	int grade;
	student(string _name, string _ID, int _grade) : name(_name), ID(_ID), grade(_grade){};
};

int N;
vector<student> students;
vector<student> result;
int grade1, grade2;

bool cmp(student s1, student s2);

int main(){
	cin >> N;
	string name, ID;
	int grade;
	for(int i = 0; i < N; i++){
		cin >> name >> ID >> grade;
		students.push_back(student(name, ID, grade));
	}
	cin >> grade1 >> grade2;
	for(int i = 0; i < students.size(); i++){
		if(students[i].grade >= grade1 && students[i].grade <= grade2){
			result.push_back(students[i]);
		}
	}
		sort(result.begin(), result.end(), cmp);
	if(result.size() == 0){
		printf("NONE\n");
	}else{
		for(int i = 0; i < result.size(); i++){
			cout << result[i].name << " " << result[i].ID << endl;
		}
	}
	return 0;
} 

bool cmp(student s1, student s2){
	return s1.grade > s2.grade;
}
