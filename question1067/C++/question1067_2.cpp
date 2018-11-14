#include<iostream>
#include<algorithm>

using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	int array[N];
	int tempArray[N];
	for(int i = 0; i < N; i++){
		scanf("%d", &array[i]);
		tempArray[i] = i;
	}
	bool visited[N];
	fill(visited, visited + N, false);
	int blocks = 0;
	int result = 0;
	for(int i = 0; i < N; i++){
		if(array[i] == tempArray[i]){
			visited[i] = true;
		}else{
			result++;
		}
		if(!visited[i]){
			visited[i] = true;
			int temp = i;
			while(true){
				int j = array[temp];
				if(j == i){
					break;
				}
				visited[j] = true;
				temp = j;
			}
			blocks++;
		}
	}
	result += blocks - 2;
	if(array[0] == 0){
		result += 2;
	}
	printf("%d\n", result);
	return 0;
}
