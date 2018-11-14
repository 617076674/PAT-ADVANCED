#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

bool cmp(string s1, string s2);

int main(){
	int N;
	scanf("%d", &N);
	string input[N];
	for(int i = 0; i < N; i++){
		cin >> input[i];
	}
	sort(input, input + N, cmp);
	string result;
	for(int i = 0; i < N; i++){
		result += input[i];
	}
	while(result.size() != 0 && result[0] == '0'){
		result.erase(result.begin());
	}
	if(result.size() == 0){
		printf("0\n");
	}else{
		cout << result << endl;
	}
	return 0;
}

bool cmp(string s1, string s2){
	return (s1 + s2).compare(s2 + s1) < 0;
} 
