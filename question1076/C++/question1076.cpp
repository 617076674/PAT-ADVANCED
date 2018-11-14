#include<iostream>
#include<queue>

using namespace std;

//��һ���ڵ������㼶��Ϣ�ͽڵ�����Ϣ��װ��һ�� 
struct node{
	int number;
	int level;
	node(int _number, int _level) : number(_number), level(_level) {}	//���캯�� 
};

int n;	//�û�����
int l;	//��Ҫ���ǵ�ת������
int graph[2001][2001] = {0};	//����ͼ��0��������֮�䱻�й�ע�뱻��ע�Ĺ�ϵ��graph[i][j] = 1��ʾ�û�j��ע���û�i 

void bfs(int nowVisit, int& count);

int main(){
	cin >> n >> l;
	int m, f;	//һ���˵Ĺ�ע��m������ע����f 
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
	bool visited[2001] = {false};	//������飬���ĳ�ڵ��Ƿ��ѱ�����
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
