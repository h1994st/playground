/*
ID: h1994st2
PROG: ride
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <iostream>

#define STR_LENGTH 6

using namespace std;

int main() {
	freopen("ride.in", "r", stdin);
	freopen("ride.out", "w", stdout);

	char str[STR_LENGTH + 1];

	scanf("%s", str);
	int comet = 1;
	for (int i = 0; i < strlen(str); i++) {
		comet *= (str[i] - 'A' + 1);
	}
	comet %= 47;

	scanf("%s", str);
	int group = 1;
	for (int i = 0; i < strlen(str); i++) {
		group *= (str[i] - 'A' + 1);
	}
	group %= 47;

	if (comet == group)
		printf("GO\n");
	else
		printf("STAY\n");

	return 0;
}
