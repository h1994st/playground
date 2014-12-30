/*
 ID: h1994st2
 PROG: milk2
 LANG: C++
 */
#include <cstdio>
#include <cstring>
#include <iostream>

#define MAX 5001

using namespace std;

int n;
int timeslot[MAX][2];

void swapTimeslot(const int &a, const int &b) {
    int t1 = timeslot[a][0];
    int t2 = timeslot[a][1];
    timeslot[a][0] = timeslot[b][0];
    timeslot[a][1] = timeslot[b][1];
    timeslot[b][0] = t1;
    timeslot[b][1] = t2;
}

int ones(const int &l, const int &r) {
    int pivot = timeslot[l][0];
    int i = l, j = r;
    bool flag = false;
    while (i < j) {
        if (flag) {
            // Left scan
            if (timeslot[i][0] > pivot) {
                swapTimeslot(i, j);
                flag = !flag;
            } else {
                i++;
            }
        } else {
            // Right scan
            if (timeslot[j][0] < pivot) {
                swapTimeslot(i, j);
                flag = !flag;
            } else {
                j--;
            }
        }
    }
    return i;
}

void quicksort(const int &l, const int &r) {
    if (l < r) {
        int mid = ones(l, r);
        quicksort(l, mid - 1);
        quicksort(mid + 1, r);
    }
}

int main() {
    ios::sync_with_stdio(false);
    freopen("milk2.in", "r", stdin);
    freopen("milk2.out", "w", stdout);
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &timeslot[i][0], &timeslot[i][1]);
    }
    
    // Sort timeslot
    quicksort(0, n - 1);
    
    // Solve
    int longestContinuousTime = 0, longestIdleTime = 0;
    int l = timeslot[0][0], r = timeslot[0][1];
    longestContinuousTime = max(longestContinuousTime, r - l);
    for (int i = 1; i < n; i++) {
        if (timeslot[i][0] > r) {
            // New time slot
            int idleTime = timeslot[i][0] - r;
            int continuousTime = r - l;
            l = timeslot[i][0];
            r = timeslot[i][1];
            longestContinuousTime = max(longestContinuousTime, continuousTime);
            longestIdleTime = max(longestIdleTime, idleTime);
            longestContinuousTime = max(longestContinuousTime, r - l);
        } else {
            if (timeslot[i][1] > r) {
                r = timeslot[i][1];
            }
        }
    }
    
    printf("%d %d\n", longestContinuousTime, longestIdleTime);
    
    return 0;
}
