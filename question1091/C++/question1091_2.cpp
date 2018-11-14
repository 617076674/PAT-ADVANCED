#include<iostream>
#include<queue>

using namespace std;

struct node {
	int i;
	int j;
	int k;
	node(int _i, int _j, int _k) : i(_i), j(_j), k(_k) {};
};

int M, N, L, T;
int brain[1286][128][60];
bool inq[1286][128][60] = {false};
int directions[3][6] = {0, 0, 1, 0, 0, -1, 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1, 0};
int count = 0;
int totalCount = 0;

bool valid(int i, int j, int k);
void bfs(int i, int j, int k);

int main() {
	scanf("%d%d%d%d", &M, &N, &L, &T);
	for(int k = 0; k < L; k++) {
		for(int i = 0; i < M; i++) {
			for(int j = 0; j < N; j++) {
				scanf("%d", &brain[i][j][k]);
			}
		}
	}
	for(int k = 0; k < L; k++) {
		for(int i = 0; i < M; i++) {
			for(int j = 0; j < N; j++) {
				if(!inq[i][j][k] && brain[i][j][k] == 1) {
					count = 0;
					bfs(i, j, k);
					if(count >= T) {
						totalCount += count;
					}
				}
			}
		}
	}
	printf("%d\n", totalCount);
	return 0;
}

bool valid(int i, int j, int k) {
	if(i >= 0 && i < M && j >= 0 && j < N && k >= 0 && k < L) {
		return true;
	} else {
		return false;
	}
}

void bfs(int i, int j, int k) {
	queue<node> q;
	q.push(node(i, j, k));
	inq[i][j][k] = true;
	while(!q.empty()) {
		node now = q.front();
		q.pop();
		count++;
		for(int t = 0; t < 6; t++) {
			int newI = directions[0][t] + now.i;
			int newJ = directions[1][t] + now.j;
			int newK = directions[2][t] + now.k;
			if(valid(newI, newJ, newK) && !inq[newI][newJ][newK] && brain[newI][newJ][newK] == 1) {
				q.push(node(newI, newJ, newK));
				inq[newI][newJ][newK] = true;
			}
		}
	}
}
