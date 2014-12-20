/*
ID: h1994st2
PROG: friday
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int week[7], monthDay[12] = {31, 28, 31, 30, 31, 30 ,31, 31, 30, 31, 30, 31};

inline bool isLeapYear(int &year) {
	return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

int main() {
	ios::sync_with_stdio(false);
	freopen("friday.in", "r", stdin);
	freopen("friday.out", "w", stdout);

	int n = 0;
	scanf("%d", &n);

	int firstDay = 0;
	for (int i = 1900; i < 1900 + n; i++) {
		monthDay[1] = isLeapYear(i) ? 29: 28;
		for (int j = 0; j < 12; j++) {
			week[(13 + firstDay - 1) % 7]++;
			firstDay = (monthDay[j] % 7) + firstDay;
		}
	}

	for (int i = 0; i < 7; i++) {
		int j = (i + 5) % 7;
		printf("%d%c", week[j], (6 == i ? '\n' : ' '));
	}

	return 0;
}
