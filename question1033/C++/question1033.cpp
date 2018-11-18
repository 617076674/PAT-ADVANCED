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
	if(D == 0) {	//如果杭州距离目的地的距离D是0，我们不需要任何花费就已经到达了目的地
		printf("0.00");
		return 0;
	}
	if(stations[1].distance != 0) {	//如果第1号加油站的距离离杭州大于0，由于一开始油箱为空，我们不可能到达目的地
		printf("The maximum travel distance = 0.00\n");
		return 0;
	}
	double cost = 0.0;	//代表花费总额
	double maxLen = Cmax * Davg;	//满油状态下能行进的最大距离
	int now = 1;	//一开始我们处在1号加油站的位置
	int next;	//下一个加油站
	double nowOil = 0.0;	//当前我们的汽车有多少油
	while(true) {
		//如果当前加油站已经是最后一个加油站了
		if(now == N) {
			if(stations[now].distance + maxLen < D) {
				//在最后一个加油站加满油也到达不了目的地D
				printf("The maximum travel distance = %.2lf\n", stations[now].distance + maxLen);
			} else {
				//在最后一个加油站加满油可以到达目的地D，但我们没必要加满油
				if(nowOil < (D - stations[now].distance) / Davg) {
					cost += stations[now].price * ((D - stations[now].distance) / Davg - nowOil);
				}
				printf("%.2lf\n", cost);
			}
			break;
		}
		int min = now + 1;
		int i = now + 1;
		//如果在now加满油到达不了下一个加油站
		if(stations[i].distance > stations[now].distance + maxLen) {
			//如果在now站加满油也到达不了目的地
			if(D > stations[now].distance + maxLen) {
				printf("The maximum travel distance = %.2lf\n", stations[now].distance + maxLen);
			} else {
				//如果在now站加满油到达不了下一个加油站但是可以到达目的地
				if(nowOil < (D - stations[now].distance) / Davg) {
					cost += stations[now].price * ((D - stations[now].distance) / Davg - nowOil);
				}
				printf("%.2lf\n", cost);
			}
			break;
		}
		for(; stations[i].distance - stations[now].distance <= maxLen && i < N + 1; i++) {	//循环a 
			//在now能到达的下一个加油站里寻找价格最低的那个加油站编号
			if(stations[i].price < stations[min].price) {
				min = i;
			}
			//在now位置能到达的下一个加油站里寻找价格比now加油站更低或价格相同的加油站
			if(stations[i].price <= stations[now].price) {
				next = i;
				break;
			}
		}
		//如果在能到达的下一个加油站里无法找到价格比当前加油站更低或相同的加油站，那么我们的下一个加油站就选取能到达的加油站里价格最低的加油站
		if(i == N + 1 || stations[i].distance - stations[now].distance > maxLen) {	//取的循环a中循环终止的相反条件 
			//如果在now站加满油就能够到达目的地了
			if(stations[now].distance + maxLen >= D) {
				if(nowOil < (D - stations[now].distance) / Davg) {
					cost += stations[now].price * ((D - stations[now].distance) / Davg - nowOil);
				}
				printf("%.2lf\n", cost);
				break;
			}
			//我们在now能到达的下一个加油站里寻找价格最低的那个加油站
			next = min;
			//加满油
			cost += stations[now].price * (Cmax - nowOil);
			//到达next时，油箱里的油不为空
			nowOil = Cmax - (stations[next].distance - stations[now].distance) / Davg;
		} else {
			//如果在now能到达的下一个加油站里能找到比now加油站价格更低的加油站
			//如果距离D在加油站now和next之间，那么只需加能到达目的地D的油即可
			if(stations[next].distance >= D) {
				if(nowOil < (D - stations[now].distance) / Davg) {
					cost += stations[now].price * ((D - stations[now].distance) / Davg - nowOil);
				}
				printf("%.2lf\n", cost);
				break;
			}
			//在now加油站只需加能到达next加油站的油即可
			if(nowOil < (stations[next].distance - stations[now].distance) / Davg) {
				cost += stations[now].price * ((stations[next].distance - stations[now].distance) / Davg - nowOil);
				//到达next时，油箱里的油为空
				nowOil = 0.0;
			} else {
				//到达next时，油箱里的油为原有的油减去路上花费的油
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
