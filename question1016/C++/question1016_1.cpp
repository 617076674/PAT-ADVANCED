#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

struct call {	//通话记录 
	int month, day, hour, minute;
	string description;
	call(int _month, int _day, int _hour, int _minute, string _description) : 
		month(_month), day(_day), hour(_hour), minute(_minute), description(_description) {};
};

struct bill {	//账单
	int month1, day1, hour1, minute1;
	int month2, day2, hour2, minute2;
	int totalMinutes;
	double price;
	bill(int _month1, int _day1, int _hour1, int _minute1, int _month2, int _day2, int _hour2, int _minute2, int _totalMinutes, double _price) :
		month1(_month1), day1(_day1), hour1(_hour1), minute1(_minute1), month2(_month2), day2(_day2), hour2(_hour2), minute2(_minute2),
		totalMinutes(_totalMinutes), price(_price) {};
};

int price[24];	//每小时价格 
int N;	//通话记录数 
map<string, vector<call> > callMap;	//对通话记录按人名进行分类 
map<string, vector<bill> > billMap;	//对账单按人名进行分类 
set<string> names;	//记录人名 

bool cmp(call a, call b);	//对通话记录进行时间排序  
int changeToMinutes(int day, int hour, int minute);	//将时间转换为分钟 
double calculatePriceSameDay(int hour1, int minute1, int hour2, int minute2);	//获取同一天内的价格 
double calculatePrice(int day1, int hour1, int minute1, int day2, int hour2, int minute2);	//获取不同天的价格 

int main() {
	for(int i = 0; i < 24; i++) {
		scanf("%d", &price[i]);
	}
	scanf("%d", &N);
	string name, description;
	int month, day, hour, minute;
	for(int i = 0; i < N; i++) {
		cin >> name;
		scanf("%d:%d:%d:%d", &month, &day, &hour, &minute); 
		cin >> description;
		callMap[name].push_back(call(month, day, hour, minute, description));
		names.insert(name);
	}
	for(map<string, vector<call> >::iterator it = callMap.begin(); it != callMap.end(); it++) {
		//对通话记录进行排序 
		sort(it->second.begin(), it->second.end(), cmp);
		for(int i = 0; i < it->second.size(); i++) {
			if(it->second[i].description.compare("on-line") == 0 && i + 1 < it->second.size()
			        && it->second[i + 1].description.compare("off-line") == 0) {
			    //根据通话记录构建每个人的账单
				call c1 = it->second[i], c2 = it->second[i + 1];
				int beginTime = changeToMinutes(c1.day, c1.hour, c1.minute);
				int endTime = changeToMinutes(c2.day, c2.hour, c2.minute);
				int totalMinutes = endTime - beginTime;
				double price = calculatePrice(c1.day, c1.hour, c1.minute, c2.day, c2.hour, c2.minute);
				billMap[it->first].push_back(bill(c1.month, c1.day, c1.hour, c1.minute, c2.month, c2.day, c2.hour, c2.minute,
					totalMinutes, price));
			}
		}
	}
	for(set<string>::iterator it = names.begin(); it != names.end(); it++) {
		if(billMap[*it].size() == 0){	//如果没有通话记录，不要输出 
			continue;
		}
		cout << *it << " " ;
		printf("%02d\n", callMap[*it][0].month);
		double amount = 0;
		for(int i = 0; i < billMap[*it].size(); i++) {
			bill b = billMap[*it][i];
			amount += b.price;
			printf("%02d:%02d:%02d %02d:%02d:%02d %d $%.2f\n", b.day1, b.hour1, b.minute1, b.day2, b.hour2, b.minute2, b.totalMinutes, b.price);
		}
		printf("Total amount: $%.2f\n", amount);
	}
	return 0;
}

bool cmp(call a, call b) {
	return changeToMinutes(a.day, a.hour, a.minute) < changeToMinutes(b.day, b.hour, b.minute);
}

int changeToMinutes(int day, int hour, int minute) {
	return day * 24 * 60 + hour * 60 + minute;
}

double calculatePriceSameDay(int hour1, int minute1, int hour2, int minute2) {
	double result = 0.0;
	if(hour1 == hour2) {
		result = price[hour1] * (minute2 - minute1) * 1.0 / 100;
	} else {
		result += price[hour1] * (60 - minute1);
		for(int i = hour1 + 1; i < hour2; i++) {
			result += price[i] * 60;
		}
		if(hour2 != 24) {
			result += price[hour2] * minute2;
		}
		result /= 100;
	}
	return result;
}

double calculatePrice(int day1, int hour1, int minute1, int day2, int hour2, int minute2) {
	if(day1 == day2) {
		return calculatePriceSameDay(hour1, minute1, hour2, minute2);
	}
	double result = 0.0;
	result += calculatePriceSameDay(hour1, minute1, 24, 0);
	result += calculatePriceSameDay(0, 0, hour2, minute2);
	int sum = 0;
	for(int i = 0; i < 24; i++) {
		sum += price[i];
	}
	result += (day2 - day1 - 1) * sum * 60 * 1.0 / 100;
	return result;
}
