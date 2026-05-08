#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

// НОД
long long gcd(long long a, long long b) {
    while (b) { long long t = b; b = a % b; a = t; }
    return a;
}

// Быстрое возведение в степень по модулю
long long modPow(long long a, long long e, long long m) {
    long long r = 1;
    while (e) {
        if (e & 1) r = (r * a) % m;
        a = (a * a) % m;
        e >>= 1;
    }
    return r;
}

int main() {
    srand(time(0));

    // Решето Эратосфена — простые числа до 500
    bool isPrime[501];
    int primes[100], pc = 0;
    for (int i = 2; i <= 500; i++) isPrime[i] = true;
    for (int i = 2; i * i <= 500; i++)
        if (isPrime[i])
            for (int j = i * i; j <= 500; j += i)
                isPrime[j] = false;
    for (int i = 2; i <= 500; i++)
        if (isPrime[i]) primes[pc++] = i;

    int bits, t;
    cout << "bits и t: ";
    cin >> bits >> t;

    cout << "\n№\tЧисло\t\tОтвергнуто\n";

    // Генерируем 10 простых чисел
    for (int num = 0; num < 10; num++) {
        int rejected = 0;
        long long n, F;
        bool ok;

        do {
            ok = true;

            // Генерируем F
            F = 1;
            long long minF = 1LL << (bits / 2 + 1);
            long long maxF = (1LL << (bits / 2 + 2)) - 1;
            while (F < minF) {
                F *= primes[rand() % pc];
                if (F > maxF) F = 1;
            }

            // n = R * F + 1, R — чётное
            long long R = (rand() % (F - 2) + 2) | 1;
            if (R % 2) R--;
            n = R * F + 1;

            // Проверка разрядности
            int bc = 0;
            for (long long x = n; x; x >>= 1) bc++;
            if (bc != bits) { rejected++; ok = false; continue; }

            // Простые делители F
            long long q[50], tempF = F;
            int qc = 0;
            for (int i = 0; i < pc && tempF > 1; i++) {
                if (tempF % primes[i] == 0) {
                    q[qc++] = primes[i];
                    while (tempF % primes[i] == 0) tempF /= primes[i];
                }
            }

            // Тест Поклингтона (параметр t)
            for (int j = 0; j < t && ok; j++) {
                long long a = rand() % (n - 2) + 2;
                if (modPow(a, n - 1, n) != 1) { ok = false; break; }
                for (int i = 0; i < qc; i++) {
                    long long exp = (n - 1) / q[i];
                    if (gcd(modPow(a, exp, n) - 1, n) != 1) {
                        ok = false;
                        break;
                    }
                }
            }
            // Дополнительная проверка с t = 2
            if (ok && t > 2) {
                for (int j = 0; j < 2 && ok; j++) {
                    long long a = rand() % (n - 2) + 2;
                    if (modPow(a, n - 1, n) != 1) { ok = false; break; }
                    for (int i = 0; i < qc; i++) {
                        long long exp = (n - 1) / q[i];
                        if (gcd(modPow(a, exp, n) - 1, n) != 1) {
                            ok = false;
                            break;
                        }
                    }
                }
            }

            if (!ok) rejected++;
        } while (!ok);

        cout << num + 1 << "\t" << n << "\t\t" << rejected << endl;
    }

    return 0;
}

