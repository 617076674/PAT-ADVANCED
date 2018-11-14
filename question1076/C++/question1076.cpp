#include<iostream>
#include<queue>

using namespace std;

//用一个节点来将层级信息和节点编号信息封装在一起 
struct node{
	int number;
	int level;
	node(int _number, int _level) : number(_number), level(_level) {}	//构造函数 
};

int n;	//用户总数
int l;	//需要考虑的转发层数
int graph[2001][2001] = {0};	//有向图，0代表两者之间被有关注与被关注的关系，graph[i][j] = 1表示用户j关注了用户i 

void bfs(int nowVisit, int& count);

int main(){
	cin >> n >> l;
	int m, f;	//一个人的关注数m，被关注的人f 
	for(int i = 0; i < n; i++){
		cin >> m;
		for(int j = 0; j < m; j++){
			cin >> f;
			graph[f - 1][i] = 1;
		}
	}
	int k;
	cin >> k;
	int query;
	for(int i = 0; i < k; i++){
		cin >> query;
		int count = 0;
		bfs(query - 1, count);
		cout << count << endl;
	}
	
	return 0;
}

void bfs(int nowVisit, int& count){
	bool visited[2001] = {false};	//标记数组，标记某节点是否已被访问
	queue<node> q;
	q.push(node(nowVisit, 0));
	visited[nowVisit] = true;
	while(!q.empty()){
		node u = q.front();
		q.pop();
		for(int i = 0; i < 2001; i++){
			if(!visited[i] && graph[u.number][i] != 0){
				q.push(node(i, u.level + 1));
				if(u.level + 1 <= l){
					count++;
				}
				visited[i] = true;
			}
		}
	}
}
