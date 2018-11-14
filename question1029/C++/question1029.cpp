#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int INF = 0x7fffffff;

int main() {
	int N1, N2;
	scanf("%d", &N1);
	queue<int> nums1, nums2;
	int num;
	for(int i = 0; i < N1; i++) {
		scanf("%d", &num);
		nums1.push(num);
	}
	nums1.push(INF);
	scanf("%d", &N2);
	int count = 0;
	for(int i = 0; i < N2; i++) {
		scanf("%d", &num);
		nums2.push(num);
		if(count == (N1 + N2 - 1) / 2){
			printf("%d\n", min(nums1.front(), nums2.front()));
			return 0;
		}
		if(nums1.front() <= nums2.front()){
			nums1.pop();
		}else{
			nums2.pop();
		}
		count++;
	}
	nums2.push(INF);
    for(; count < (N1 + N2 - 1) / 2; count++) {
        if(nums1.front() < nums2.front())    
            nums1.pop();
        else                         
            nums2.pop();
    }
    printf("%d", min(nums1.front(), nums2.front()));
	return 0;
}
