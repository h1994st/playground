/*
ID: h1994st2
PROG: beads
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <iostream>

#define N_MAX 351

using namespace std;

int n, r, l;
char rKey, lKey;
char necklace[N_MAX];

int main() {
	ios::sync_with_stdio(false);
	freopen("beads.in", "r", stdin);
	freopen("beads.out", "w", stdout);

	scanf("%d", &n);
	scanf("%s", necklace);

	int ans = 0;
	for (int i = 0; i < n; i++) {
		l = 0;
		r = 0;
		rKey = 'w';
		lKey = 'w';
		// Right
		for (int j = i; j < i + n; j++) {
            if (rKey == 'w' && necklace[j % n] != 'w')
                rKey = necklace[j % n];
            if (necklace[j % n] == 'w' || (rKey != 'w' && necklace[j % n] == rKey))
                r++;
            else
                break;
        }
        
        // Left
        for (int j = i + n - 1; j >= 0; j--) {
            if (lKey == 'w' && necklace[j % n] != 'w')
                lKey = necklace[j % n];
            if (necklace[j % n] == 'w' || (lKey != 'w' && necklace[j % n] == lKey))
                l++;
            else
                break;
        }

		ans = max(min(n, l + r), ans);
		if (ans == n) break;
	}
	printf("%d\n", ans);

	return 0;
}
