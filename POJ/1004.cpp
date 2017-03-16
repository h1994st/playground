#include <iostream>

using namespace std;

int main() {
    double balance, result = 0.0f;
    for (int i = 0; i < 12; ++i) {
        cin >> balance;
        result += balance;
    }

    cout << '$' << result / 12 << endl;

    return 0;
}
