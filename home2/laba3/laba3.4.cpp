#include <iostream>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;

    int arr[100];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int pos = 0;
    int scoreP = 0, scoreV = 0;
    int lastOpponent = -1;
    int turn = 0;

    while (pos < n) {
        int maxSum = -1000000;
        int bestTake = 1;
        int leftover = n - pos;

        for (int take = 1; take <= m && take <= leftover; take++) {
            if (take == lastOpponent) {
                continue;
            }

            int sum = 0;
            for (int i = pos; i < pos + take; i++) {
                sum += arr[i];
            }

            if (sum > maxSum) {
                maxSum = sum;
                bestTake = take;
            }
        }

        lastOpponent = bestTake;
        if (turn == 0) {
            scoreP += maxSum;
        }
        else {
            scoreV += maxSum;
        }

        pos += bestTake;
        turn = 1 - turn;
    }

    if (scoreP > scoreV) {
        cout << "1" << endl;
    }
    else {
        cout << "0" << endl;
    }
    return 0;
}

