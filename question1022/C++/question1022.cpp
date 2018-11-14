#include<iostream>
#include<map>
#include<cstring>
#include<vector>

using namespace std;

struct book {
	int id;
	char title[81];
	char author[81];
	char key[51];
	char publisher[81];
	int year;
};

int main() {
	int N, M;
	scanf("%d", &N);
	map<int, book> bookMap;	//由id和book构成的映射表
	for(int i = 0; i < N; i++) {
		book tempBook;
		scanf("%d", &tempBook.id);
		getchar();
		scanf("%[^\n]", tempBook.title);
		getchar();
		scanf("%[^\n]", tempBook.author);
		getchar();
		scanf("%[^\n]", tempBook.key);
		getchar();
		scanf("%[^\n]", tempBook.publisher);
		getchar();
		scanf("%d", &tempBook.year);
		bookMap[tempBook.id] = tempBook;
	}
	scanf("%d", &M);
	getchar();
	char query[100];
	int queryYear;
	vector<int> results;
	for(int i = 0; i < M; i++) {
		results.clear();
		char c = getchar();
		getchar();
		getchar();
		if(c != '5') {
			scanf("%[^\n]", query);
			printf("%c: %s\n", c, query);
		} else {
			scanf("%d", &queryYear);
			printf("%c: %04d\n", c, queryYear);
		}
		getchar();
		for(map<int, book>::iterator it = bookMap.begin(); it != bookMap.end(); it++) {
			if(c == '1') {
				if(strcmp(it->second.title, query) == 0) {
					results.push_back(it->first);
				}
			} else if(c == '2') {
				if(strcmp(it->second.author, query) == 0) {
					results.push_back(it->first);
				}
			} else if(c == '3') {
				if(strstr(it->second.key, query)) {
					results.push_back(it->first);
				}
			} else if(c == '4') {
				if(strcmp(it->second.publisher, query) == 0) {
					results.push_back(it->first);
				}
			} else if(c == '5') {
				if(it->second.year == queryYear) {
					results.push_back(it->first);
				}
			}
		}
		if(results.size() == 0) {
			printf("Not Found\n");
		} else {
			for(int j = 0; j < results.size(); j++) {
				printf("%07d\n", results[j]);
			}
		}
	}
}

