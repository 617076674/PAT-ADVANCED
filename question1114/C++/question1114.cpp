#include<iostream>
#include<set>
#include<algorithm>

using namespace std;

struct person {
	int id;
	int Mestate;
	int Area;
	person() {
		Mestate = 0;
		Area = 0;
	}
	person(int _id, int _Mestate, int _Area) : id(_id), Mestate(_Mestate), Area(_Area) {};
};

struct family{
	int ID;
	int M;
	int Totalsets;
	int Totalarea;
	family() {};
	family(int _ID, int _M, int _Totalsets, int _Totalarea) : ID(_ID), M(_M), Totalsets(_Totalsets), Totalarea(_Totalarea) {};
};

bool flag[10000];
int parent[10000];
person people[10000];

int findFather(int x);
void unionTwo(int a, int b);
bool cmp(family f1, family f2);

int main() {
	fill(flag, flag + 10000, false);
	for(int i = 0; i < 10000; i++) {	//并查集初始化
		parent[i] = i;
	}
	int N;
	scanf("%d", &N);
	int ID, Father, Mother, k, child, Mestate, Area;
	for(int i = 0; i < N; i++) {
		scanf("%d %d %d %d", &ID, &Father, &Mother, &k);
		flag[ID] = true;
		if(Father != -1) {
			unionTwo(ID, Father);
			flag[Father] = true;
		}
		if(Mother != -1) {
			unionTwo(ID, Mother);
			flag[Mother] = true;
		}
		for(int j = 0; j < k; j++){
			scanf("%d", &child);
			unionTwo(ID, child);
			flag[child] = true;
		}
		scanf("%d %d", &Mestate, &Area);
		people[ID] = person(ID, Mestate, Area);
	}
	set<int> fatherSet;
	for(int i = 0; i < 10000; i++){
		if(!flag[i]){
			continue;
		}
		fatherSet.insert(findFather(i));
	}
	printf("%d\n", fatherSet.size());
	family families[fatherSet.size()];
	int index = 0;
	for(set<int>::iterator it = fatherSet.begin(); it != fatherSet.end(); it++){
		int ID = -1, M = 0, Totalsets = 0, Totalarea = 0;
		for(int i = 0; i < 10000; i++){
			if(!flag[i] || findFather(i) != *it){
				continue;
			}
			if(ID == -1){
				ID = i;
			}
			M++;
			Totalsets += people[i].Mestate;
			Totalarea += people[i].Area;
		}
		families[index++] = family(ID, M, Totalsets, Totalarea);
	}
	sort(families, families + fatherSet.size(), cmp);
	for(int i = 0; i < fatherSet.size(); i++){
		printf("%04d %d %.3f %.3f\n", families[i].ID, families[i].M, families[i].Totalsets * 1.0 / families[i].M, 
			families[i].Totalarea * 1.0 / families[i].M);
	}
	return 0;
}

int findFather(int x) {
	int a = x;
	while(x != parent[x]) {
		x = parent[x];
	}
	while(a != parent[a]) {	//路径压缩 
		int z = a;
		a = parent[a];
		parent[z] = x;
	}
	return x;
}

void unionTwo(int a, int b) {
	int aFather = findFather(a);
	int bFather = findFather(b);
	if(aFather != bFather) {
		parent[aFather] = bFather;
	}
}

bool cmp(family f1, family f2){
	if(f1.Totalarea * 1.0 / f1.M == f2.Totalarea * 1.0 / f2.M){
		return f1.ID < f2.ID;
	}else{
		return f1.Totalarea * 1.0 / f1.M > f2.Totalarea * 1.0 / f2.M;
	}
}
