#include<iostream>
#include<algorithm>

using namespace std;

int main(){
	int N;
	scanf("%d", &N);
	int array[N];	//��Ÿ����ֵ�ǰ������λ�ñ�� 
	int unOrdered = 0;	//unOrdered��¼��0���ⲻ�ڱ�λ�ϵ����ĸ��� 
	int num; 
	for(int i = 0; i < N; i++){
		scanf("%d", &num);
		array[num] = i;
		if(array[i] != i && i != 0){
			unOrdered++;
		}
	}
	int k = 1;	//k��ų�0��Ϊ��ǰ���ڱ�λ�ϵ���С��
	int result = 0;
	while(unOrdered > 0){
		//���0�ڱ�λ�ϣ���Ѱ��һ����ǰ���ڱ�λ�ϵ�����0���� 
		if(array[0] == 0){
			while(k < N){
				if(array[k] != k){
					swap(array[k], array[0]);
					result++;
					break;
				}
				k++;
			}
		}
		//ֻҪ0���ڱ�λ���ͽ�0����λ�õ����ĵ�ǰ����λ����0��λ�ý��� 
		while(array[0] != 0){
			swap(array[0], array[array[0]]);	//��0��array[0]���� 
			result++;	//����������1 
			unOrdered--;	//���ڱ�λ�ϵ����ĸ�����1 
		}
	} 
	printf("%d\n", result);
	return 0;
}
