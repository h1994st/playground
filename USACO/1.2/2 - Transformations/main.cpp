/*
 ID: h1994st2
 PROG: transform
 LANG: C++
 */
#include <cstdio>
#include <cstring>
#include <iostream>

#define MAX 11

using namespace std;

int n;
char src[MAX][MAX], dest[MAX][MAX];

int main() {
    ios::sync_with_stdio(false);
    freopen("transform.in", "r", stdin);
    freopen("transform.out", "w", stdout);
    
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
		scanf("%s", src[i]);

	for (int i = 0; i < n; i++)
		scanf("%s", dest[i]);
    
    return 0;
}
