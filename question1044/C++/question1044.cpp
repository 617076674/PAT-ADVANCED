#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	int nums[N + 1];	//必须在N的值输入之后再来定义该数组
	nums[0] = 0;
	for(int i = 1; i <= N; i++) {
		scanf("%d", &nums[i]);
	}
	int sum[N + 1];	//sum[i]存储nums[1] + ... + nums[i]的值，i >= 1
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
			if(result.empty()) {	//如果result为空，直接存入 
				result.push_back(make_pair(i, j));
			} else {
				pair<int, int> p = result[result.size() - 1]; 
				if(sum[p.second] - sum[p.first - 1] - M != 0) {	//判断result中的最后一个元素的索引i和j之间的值的和是否刚好为M 
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
