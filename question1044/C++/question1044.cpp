#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	int nums[N + 1];	//������N��ֵ����֮���������������
	nums[0] = 0;
	for(int i = 1; i <= N; i++) {
		scanf("%d", &nums[i]);
	}
	int sum[N + 1];	//sum[i]�洢nums[1] + ... + nums[i]��ֵ��i >= 1
	for(int i = 0; i <= N; i++) {
		if(i == 0) {
			sum[i] = nums[i];
		} else {
			sum[i] = nums[i] + sum[i - 1];
		}
	}
	vector<pair<int, int> > result;
	for(int i = 1; i <= N; i++) {
		int find = sum[i - 1] + M;
		int j = lower_bound(sum + i, sum + N + 1, find) - sum;
		if(sum[j] == find) {
			if(result.empty()) {	//���resultΪ�գ�ֱ�Ӵ��� 
				result.push_back(make_pair(i, j));
			} else {
				pair<int, int> p = result[result.size() - 1]; 
				if(sum[p.second] - sum[p.first - 1] - M != 0) {	//�ж�result�е����һ��Ԫ�ص�����i��j֮���ֵ�ĺ��Ƿ�պ�ΪM 
					result.clear();
					result.push_back(make_pair(i, j));
				} else {
					result.push_back(make_pair(i, j));
				}
			}
		} else if(sum[j] > find) {
			if(result.empty()) {
				result.push_back(make_pair(i, j));
			} else {
				pair<int, int> p = result[result.size() - 1];
				if(sum[p.second] - sum[p.first - 1] - M > sum[j] - sum[i - 1] - M) {
					result.clear();
					result.push_back(make_pair(i, j));
				} else if(sum[p.second] - sum[p.first - 1] - M == sum[j] - sum[i - 1] - M) {
					result.push_back(make_pair(i, j));
				}
			}
		}
	}
	for(int i = 0; i < result.size(); i++) {
		printf("%d-%d\n", result[i].first, result[i].second);
	}
}
