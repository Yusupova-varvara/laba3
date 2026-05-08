#include <iostream>
#include <cmath>
using namespace std;

// НОД
int gcd(int a, int b) {
    while (b) { int t = b; b = a % b; a = t; }
    return a;
}
int main() {
    int a, b;
    cout << "Введите a и b: ";
    cin >> a >> b;

    if (b == 1) {
        cout << "infinity" << endl;
        return 0;
    }

    double sum = 0.0;
    double term = 1.0;

    for (int n = 1; n <= 1000; n++) {
        term = pow(n, a) / pow(b, n);
        if (term < 1e-15) break;
        sum += term;
    }

    // Переводим в дробь
    int den = 1;
    while (fabs(sum * den - round(sum * den)) > 1e-10 && den < 100000) {
        den++;
    }

    int num = round(sum * den);
    int g = gcd(num, den);
    num /= g;
    den /= g;

    cout << num << "/" << den << endl;
    return 0;
}

