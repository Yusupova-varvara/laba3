#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x, y;
    double Xn, Xk, dX
    cout << "Введите Xнач: ";
    cin >> Xn;
    cout << "Введите Xкон: ";
    cin >> Xk;
    cout << "Введите шаг dX: ";
    cin >> dX;
    cout << "\nx\ty" << endl;
    
    for (x = Xn; x <= Xk + 1e-10; x += dX) {
        if (x >= -5 && x <= -2)
            y = -(x + 3.5)*(x + 3.5) + 2.25;
        else if (x > -2 && x < 2)
            y = -sqrt(4 - x*x);
        else if (x >= 2 && x <= 8)
            y = log2(x) - 1;
        else if (x > 8 && x <= 9)
            y = -2*x + 18;
        else {
            cout << x << "\t—" << endl;
            continue;
        }
        cout << x << "\t" << y << endl;
    }
    return 0;
}

