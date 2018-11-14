#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

struct person{
	string name;
	int age;
	int worth;
	person(string _name, int _age, int _worth) : name(_name), age(_age), worth(_worth) {};
};

int N, K;
vector<person> people;

bool cmp(person p1, person p2);

int main(){
	cin >> N >> K;
	string name;
	int age, worth;
	for(int i = 0; i < N; i++){
		cin >> name >> age >> worth;
		people.push_back(person(name, age, worth));
	}
	sort(people.begin(), people.end(), cmp);
	int M, Amin, Amax, count;
	for(int i = 1; i <= K; i++){
		cin >> M >> Amin >> Amax;
		printf("Case #%d:\n", i);
		count = 0;
		for(int j = 0; j < people.size(); j++){
			if(count == M){
				break;
			}
			if(people[j].age >= Amin && people[j].age <= Amax){
				cout << people[j].name << " " << people[j].age << " " << people[j].worth << endl;
				count++;
			}
		}
		if(count == 0){
			printf("None\n");
		}
	} 
}

bool cmp(person p1, person p2){
	if(p1.worth == p2.worth){
		if(p1.age == p2.age){
			return p1.name.compare(p2.name) < 0;
		}else{
			return p1.age < p2.age;
		}
	}else{
		return p1.worth > p2.worth;
	}
}
