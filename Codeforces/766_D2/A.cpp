#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    int n, m, r, c;
    char cell;
    int ret;

    cin >> t;
    while (t--) {
        cin >> n >> m >> r >> c;
        ret = 3;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> cell;
                if (cell == 'W') continue;

                // a black cell
                if ((i == (r - 1) && j == (c - 1)) && ret > 0) {
                    ret = 0;
                } else if ((i == (r - 1) || j == (c - 1)) && ret > 1) {
                    ret = 1;
                } else if (ret > 2) {
                    ret = 2;
                }
            }
        }

        if (ret == 3) ret = -1;
        cout << ret << endl;
    }

    return 0;
}
