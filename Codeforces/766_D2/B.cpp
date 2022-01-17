#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, m;
    int mid_r, mid_c;
    int distance;
    vector<int> distances;

    cin >> n >> m;
    mid_r = (n - 1) / 2;
    mid_c = (m - 1) / 2;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            distance = 0;

            if (i <= mid_r) {
                distance += abs(i - n + 1);
            } else {
                distance += i;
            }

            if (j <= mid_c) {
                distance += abs(j - m + 1);
            } else {
                distance += j;
            }

            distances.push_back(distance);
        }
    }

    sort(distances.begin(), distances.end());
    for (auto num : distances) {
        cout << num << ' ';
    }
    cout << endl;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
