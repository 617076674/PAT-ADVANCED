#include<iostream>
#include<algorithm>

using namespace std;

struct station {
	double price;
	double distance;
};

bool cmp(station s1, station s2);

int main() {
	double Cmax, D, Davg;
	int N;
	cin >> Cmax >> D >> Davg >> N;
	station stations[N + 1];
	for(int i = 1; i < N + 1; i++) {
		scanf("%lf %lf", &stations[i].price, &stations[i].distance);
	}
	sort(stations + 1, stations + N + 1, cmp);
	if(D == 0) {	//������ݾ���Ŀ�ĵصľ���D��0�����ǲ���Ҫ�κλ��Ѿ��Ѿ�������Ŀ�ĵ�
		printf("0.00");
		return 0;
	}
	if(stations[1].distance != 0) {	//�����1�ż���վ�ľ����뺼�ݴ���0������һ��ʼ����Ϊ�գ����ǲ����ܵ���Ŀ�ĵ�
		printf("The maximum travel distance = 0.00\n");
		return 0;
	}
	double cost = 0.0;	//�������ܶ�
	double maxLen = Cmax * Davg;	//����״̬�����н���������
	int now = 1;	//һ��ʼ���Ǵ���1�ż���վ��λ��
	int next;	//��һ������վ
	double nowOil = 0.0;	//��ǰ���ǵ������ж�����
	while(true) {
		//�����ǰ����վ�Ѿ������һ������վ��
		if(now == N) {
			if(stations[now].distance + maxLen < D) {
				//�����һ������վ������Ҳ���ﲻ��Ŀ�ĵ�D
				printf("The maximum travel distance = %.2lf\n", stations[now].distance + maxLen);
			} else {
				//�����һ������վ�����Ϳ��Ե���Ŀ�ĵ�D��������û��Ҫ������
				if(nowOil < (D - stations[now].distance) / Davg) {
					cost += stations[now].price * ((D - stations[now].distance) / Davg - nowOil);
				}
				printf("%.2lf\n", cost);
			}
			break;
		}
		int min = now + 1;
		int i = now + 1;
		//�����now�����͵��ﲻ����һ������վ
		if(stations[i].distance > stations[now].distance + maxLen) {
			//�����nowվ������Ҳ���ﲻ��Ŀ�ĵ�
			if(D > stations[now].distance + maxLen) {
				printf("The maximum travel distance = %.2lf\n", stations[now].distance + maxLen);
			} else {
				//�����nowվ�����͵��ﲻ����һ������վ���ǿ��Ե���Ŀ�ĵ�
				if(nowOil < (D - stations[now].distance) / Davg) {
					cost += stations[now].price * ((D - stations[now].distance) / Davg - nowOil);
				}
				printf("%.2lf\n", cost);
			}
			break;
		}
		for(; stations[i].distance - stations[now].distance <= maxLen && i < N + 1; i++) {	//ѭ��a 
			//��now�ܵ������һ������վ��Ѱ�Ҽ۸���͵��Ǹ�����վ���
			if(stations[i].price < stations[min].price) {
				min = i;
			}
			//��nowλ���ܵ������һ������վ��Ѱ�Ҽ۸��now����վ���ͻ�۸���ͬ�ļ���վ
			if(stations[i].price <= stations[now].price) {
				next = i;
				break;
			}
		}
		//������ܵ������һ������վ���޷��ҵ��۸�ȵ�ǰ����վ���ͻ���ͬ�ļ���վ����ô���ǵ���һ������վ��ѡȡ�ܵ���ļ���վ��۸���͵ļ���վ
		if(i == N + 1 || stations[i].distance - stations[now].distance > maxLen) {	//ȡ��ѭ��a��ѭ����ֹ���෴���� 
			//�����nowվ�����;��ܹ�����Ŀ�ĵ���
			if(stations[now].distance + maxLen >= D) {
				if(nowOil < (D - stations[now].distance) / Davg) {
					cost += stations[now].price * ((D - stations[now].distance) / Davg - nowOil);
				}
				printf("%.2lf\n", cost);
				break;
			}
			//������now�ܵ������һ������վ��Ѱ�Ҽ۸���͵��Ǹ�����վ
			next = min;
			//������
			cost += stations[now].price * (Cmax - nowOil);
			//����nextʱ����������Ͳ�Ϊ��
			nowOil = Cmax - (stations[next].distance - stations[now].distance) / Davg;
		} else {
			//�����now�ܵ������һ������վ�����ҵ���now����վ�۸���͵ļ���վ
			//�������D�ڼ���վnow��next֮�䣬��ôֻ����ܵ���Ŀ�ĵ�D���ͼ���
			if(stations[next].distance >= D) {
				if(nowOil < (D - stations[now].distance) / Davg) {
					cost += stations[now].price * ((D - stations[now].distance) / Davg - nowOil);
				}
				printf("%.2lf\n", cost);
				break;
			}
			//��now����վֻ����ܵ���next����վ���ͼ���
			if(nowOil < (stations[next].distance - stations[now].distance) / Davg) {
				cost += stations[now].price * ((stations[next].distance - stations[now].distance) / Davg - nowOil);
				//����nextʱ�����������Ϊ��
				nowOil = 0.0;
			} else {
				//����nextʱ�����������Ϊԭ�е��ͼ�ȥ·�ϻ��ѵ���
				nowOil -= (stations[next].distance - stations[now].distance) / Davg;
			}
		}
		now = next;
	}
	return 0;
}

bool cmp(station s1, station s2) {
	return s1.distance < s2.distance;
}
