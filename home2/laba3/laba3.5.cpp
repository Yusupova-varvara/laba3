#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double Tk, Tsr, r, dt, T, t;
    int steps;

    cout << "Температура кофе (начальная): ";
    cin >> Tk;
    cout << "Температура среды: ";
    cin >> Tsr;
    cout << "Коэффициент остывания r: ";
    cin >> r;
    cout << "Шаг по времени dt (мин): ";
    cin >> dt;
    cout << "Количество шагов: ";
    cin >> steps;

    T = Tk;
    cout << "\nВремя (мин)\tТемпература\n";
    for (int i = 0; i <= steps; i++) {
        t = i * dt;
        cout << fixed << setprecision(1) << t << "\t\t";
        cout << fixed << setprecision(2) << T << endl;
        T = T - r * (T - Tsr) * dt;
    }

    return 0;
}

