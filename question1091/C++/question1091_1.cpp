#include<iostream>

using namespace std;

int M, N, L, T;
int brain[1286][128][60];
bool visited[1286][128][60] = {false};
int directions[3][6] = {0, 0, 1, 0, 0, -1, 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1, 0};
int count = 0;
int totalCount = 0;

bool valid(int i, int j, int k);
void dfs(int i, int j, int k);

int main(){
	scanf("%d%d%d%d", &M, &N, &L, &T);
	for(int k = 0; k < L; k++){
		for(int i = 0; i < M; i++){
			for(int j = 0; j < N; j++){
				scanf("%d", &brain[i][j][k]);
			}
		}
	}
	for(int k = 0; k < L; k++){
		for(int i = 0; i < M; i++){
			for(int j = 0; j < N; j++){
				if(!visited[i][j][k] && brain[i][j][k] == 1){
					count = 0;
					dfs(i, j, k);
					if(count >= T){
						totalCount += count;
					}
				}
			}
		}
	}
	printf("%d\n", totalCount);
	return 0;
}

bool valid(int i, int j, int k){
	if(i >= 0 && i < M && j >= 0 && j < N && k >= 0 && k < L){
		return true;
	}else{
		return false;
	}
}

void dfs(int i, int j, int k){
	visited[i][j][k] = true;
	count++;
	for(int t = 0; t < 6; t++){
		int newI = directions[0][t] + i;
		int newJ = directions[1][t] + j;
		int newK = directions[2][t] + k;
		if(valid(newI, newJ, newK) && !visited[newI][newJ][newK] && brain[newI][newJ][newK] == 1){
			dfs(newI, newJ, newK);
		}
	}
}

