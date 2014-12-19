/*
ID: h1994st2
PROG: gift1
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <iostream>

#define NP_MAX 10
#define NAME_LENGTH_MAX 15

using namespace std;

int n = 0; // NP
char name[NP_MAX][NAME_LENGTH_MAX];
int ans[NP_MAX];

int getIndex(char *str) {
	for (int i = 0; i < n; i++)
		if (strcmp(str, name[i]) == 0) return i;
	return -1;
}

int main() {
	ios::sync_with_stdio(false);
	freopen("gift1.in", "r", stdin);
	freopen("gift1.out", "w", stdout);

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%s", name[i]);
	
	for (int i = 0; i < n; i++) {
		char giverName[NAME_LENGTH_MAX];
		scanf("%s", giverName);
		int giverIndex = getIndex(giverName);

		int money = 0, numberOfReceiver = 0;
		scanf("%d %d", &money, &numberOfReceiver);
		ans[giverIndex] -= money;

		if (numberOfReceiver == 0) continue;
		int per = money / numberOfReceiver;
		ans[giverIndex] += (money % numberOfReceiver);
		for (int j = 0; j < numberOfReceiver; j++) {
			char receiverName[NAME_LENGTH_MAX];
			scanf("%s", receiverName);
			int receiverIndex = getIndex(receiverName);

			ans[receiverIndex] += per;
		}
	}

	for (int i = 0; i < n; i++)
		printf("%s %d\n", name[i], ans[i]);

	return 0;
}
