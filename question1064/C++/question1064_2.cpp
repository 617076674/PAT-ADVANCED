#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

int N;
vector<int> inOrder;
int index = 0;
int levelOrder[1001];

void inOrderTraversal(int root);
void print();

int main(){
	cin >> N;
	int num;
	for(int i = 0; i < N; i++) {
		cin >> num;
		inOrder.push_back(num);
	}
	sort(inOrder.begin(), inOrder.end());
	inOrderTraversal(1);
	print();
	return 0;
}

void inOrderTraversal(int root){
	if(root > N){
		return;
	}
	inOrderTraversal(root * 2);
	levelOrder[root] = inOrder[index++];
	inOrderTraversal(root * 2 + 1);
}

void print() {
	for(int i = 1; i <= N; i++) {
		cout << levelOrder[i];
		if(i != N) {
			cout << " ";
		}
	}
	cout << endl;
}
