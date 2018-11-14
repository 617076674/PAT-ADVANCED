#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

/*
	ͨ����¼ 
*/
struct call {
	string time;
	string description;
	call(string _time, string _description) : time(_time), description(_description) {};
};

/*
	�˵� 
*/
struct bill {
	string beginTime;
	string endTime;
	int totalMinutes;
	double price;
	bill(string _beginTime, string _endTime, int _totalMinutes, double _price) : beginTime(_beginTime), endTime(_endTime),
		totalMinutes(_totalMinutes), price(_price) {};
};

int price[24];	//ÿСʱ�۸� 
int N;	//ͨ����¼�� 
map<string, vector<call> > callMap;	//��ͨ����¼���������з��� 
map<string, vector<bill> > billMap;	//���˵����������з��� 
set<string> names;	//��¼���� 

bool cmp(call a, call b);	//��ͨ����¼����ʱ������ 
int getMonth(string s);	//��ȡ�·� 
int getDay(string s);	//��ȡ���� 
int getHour(string s);	//��ȡСʱ 
int getMinute(string s); 	//��ȡ���� 
int changeToMinutes(string s);	//��ʱ��ת��Ϊ���� 
int calculateTotalMinutes(string a, string b);	//��ȡͨ��ʱ�� 
double calculatePriceSameDay(string a, string b);	//��ȡͬһ���ڵļ۸� 
double calculatePrice(string a, string b);	//��ȡ��ͬ��ļ۸� 

int main() {
	for(int i = 0; i < 24; i++) {
		scanf("%d", &price[i]);
	}
	scanf("%d", &N);
	string name, time, description;
	for(int i = 0; i < N; i++) {
		cin >> name >> time >> description;
		callMap[name].push_back(call(time, description));
		names.insert(name);
	}
	map<string, vector<call> >::iterator it;
	for(it = callMap.begin(); it != callMap.end(); it++) {
		//��ͨ����¼�������� 
		sort(it->second.begin(), it->second.end(), cmp);
		for(int i = 0; i < it->second.size(); i++) {
			if(it->second[i].description.compare("on-line") == 0 && i + 1 < it->second.size()
			        && it->second[i + 1].description.compare("off-line") == 0) {
			    //����ͨ����¼����ÿ���˵��˵� 
				string beginTime = it->second[i].time.substr(3, it->second[i].time.length() - 3);
				string endTime = it->second[i + 1].time.substr(3, it->second[i + 1].time.length() - 3);
				int totalMinutes = calculateTotalMinutes(it->second[i].time, it->second[i + 1].time);
				double price = calculatePrice(it->second[i].time, it->second[i + 1].time);
				billMap[it->first].push_back(bill(beginTime, endTime, totalMinutes, price));
			}
		}
	}
	set<string>::iterator it2;
	for(it2 = names.begin(); it2 != names.end(); it2++) {
		if(billMap[*it2].size() == 0){	//���û��ͨ����¼����Ҫ��� 
			continue;
		}
		cout << *it2 << " " ;
		printf("%02d\n", getMonth(callMap[*it2][0].time));
		double amount = 0;
		for(int i = 0; i < billMap[*it2].size(); i++) {
			amount += billMap[*it2][i].price;
			cout << billMap[*it2][i].beginTime << " " << billMap[*it2][i].endTime << " " << billMap[*it2][i].totalMinutes
			     << " $";
			printf("%.2lf\n", billMap[*it2][i].price);
		}
		printf("Total amount: $%.2lf\n", amount);
	}
	return 0;
}

bool cmp(call a, call b) {
	return a.time < b.time;
}

int getMonth(string s){
	int month1 = s[0] - '0';
	int month2 = s[1] - '0';
	return month1 * 10 + month2;
}

int getDay(string s) {
	int day1 = s[3] - '0';
	int day2 = s[4] - '0';
	return day1 * 10 + day2;
}

int getHour(string s){
	int hour1 = s[6] - '0';
	int hour2 = s[7] - '0';
	return hour1 * 10 + hour2;
}

int getMinute(string s){
	int minute1 = s[9] - '0';
	int minute2 = s[10] - '0';
	return minute1 * 10 + minute2;
}

int changeToMinutes(string s) {
	int day = getDay(s);
	int hour = getHour(s);
	int minute = getMinute(s);
	return day * 24 * 60 + hour * 60 + minute;
}

int calculateTotalMinutes(string a, string b) {
	int aMinute = changeToMinutes(a);
	int bMinute = changeToMinutes(b);
	return bMinute - aMinute;
}

double calculatePriceSameDay(string a, string b) {
	int ahour = getHour(a);
	int aminute = getMinute(a);
	int bhour = getHour(b);
	int bminute = getMinute(b);
	double result = 0.0;
	if(ahour == bhour) {
		result = price[ahour] * (bminute - aminute) * 1.0 / 100;
	} else {
		result += price[ahour] * (60 - aminute);
		for(int i = ahour + 1; i < bhour; i++) {
			result += price[i] * 60;
		}
		if(bhour != 24) {
			result += price[bhour] * bminute;
		}
		result /= 100;
	}
	return result;
}

double calculatePrice(string a, string b) {
	int aday = getDay(a);
	int bday = getDay(b);
	if(aday == bday) {
		return calculatePriceSameDay(a, b);
	}
	double result = 0.0;
	result += calculatePriceSameDay(a, "01:01:24:00");
	result += calculatePriceSameDay("01:01:00:00", b);
	int sum = 0;
	for(int i = 0; i < 24; i++) {
		sum += price[i];
	}
	result += (bday - aday - 1) * sum * 60 * 1.0 / 100;
	return result;
}
