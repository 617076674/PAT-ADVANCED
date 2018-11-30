#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

struct person{
	char name[9];
	int age;
	int worth;
};

int N, K;
vector<person> people;

bool cmp(person p1, person p2);

int main(){
	scanf("%d %d", &N, &K);
	char name[9];
	int age, worth;
	for(int i = 0; i < N; i++){
		scanf("%s %d %d", name, &age, &worth);
		person p;
		strcpy(p.name, name);
		p.age = age;
		p.worth = worth;
		people.push_back(p);
	}
	sort(people.begin(), people.end(), cmp);
	int M, Amin, Amax, count;
	for(int i = 1; i <= K; i++){
		scanf("%d %d %d", &M, &Amin, &Amax);
		printf("Case #%d:\n", i);
		count = 0;
		for(int j = 0; j < people.size(); j++){
			if(count == M){
				break;
			}
			if(people[j].age >= Amin && people[j].age <= Amax){
				printf("%s %d %d\n", people[j].name, people[j].age, people[j].worth);
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
			return strcmp(p1.name, p2.name) < 0;
		}else{
			return p1.age < p2.age;
		}
	}else{
		return p1.worth > p2.worth;
	}
}
