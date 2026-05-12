#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <set>

using namespace std;

// Возведение в степень по модулю
int stepen(int osnova, int pokazatel, int modul) {
    int itog = 1;
    osnova %= modul;
    while (pokazatel > 0) {
        if (pokazatel % 2 == 1) itog = (itog * osnova) % modul;
        osnova = (osnova * osnova) % modul;
        pokazatel /= 2;
    }
    return itog;
}

// Наибольший общий делитель (алгоритм Евклида)
int naibolshiy_delitel(int pervoe, int vtoroe) {
    while (vtoroe != 0) {
        int vrem = vtoroe;
        vtoroe = pervoe % vtoroe;
        pervoe = vrem;
    }
    return pervoe;
}

// Решето Эратосфена — поиск простых чисел до границы
vector<int> poisk_prostykh(int granica) {
    size_t predel = static_cast<size_t>(granica);
    vector<bool> prostoe(predel + 1, true);
    prostoe[0] = prostoe[1] = false;
    
    for (size_t i = 2; i * i <= predel; ++i) {
        if (prostoe[i]) {
            for (size_t j = i * i; j <= predel; j += i)
                prostoe[j] = false;
        }
    }
    
    vector<int> spisok;
    for (size_t i = 2; i <= predel; ++i)
        if (prostoe[i]){
            spisok.push_back(static_cast<int>(i));
        }
    return spisok;
}

// Генерация числа F как произведения простых множителей
void sozdat_F(int razryad, const vector<int>& spisok, int& F, vector<pair<int, int>>& mnojiteli) {
    random_device ustroystvo;
    mt19937 generator(ustroystvo());
    uniform_int_distribution<size_t> index_gen(0, spisok.size() - 1);
    uniform_int_distribution<int> stepen_gen(1, 2);

    F = 1;
    mnojiteli.clear();

    int nuzhnyy_razryad = (razryad / 2) + 1;
    if (nuzhnyy_razryad < 2) nuzhnyy_razryad = 2;
    
    int tekushiy_razryad = 0;
    int maks_popytok = 100;
    
    for (int popytka = 0; popytka < maks_popytok && tekushiy_razryad < nuzhnyy_razryad; ++popytka) {
        int q = spisok[index_gen(generator)];
        int a = stepen_gen(generator);
        int proizvedenie = 1;
        for (int i = 0; i < a; i++) proizvedenie *= q;
        
        if (proizvedenie <= 0 || proizvedenie > 1000000) continue;
        if (F > 1000000 / proizvedenie) continue;
        
        F *= proizvedenie;
        mnojiteli.push_back({q, a});
        
        long long temp = F;
        tekushiy_razryad = 0;
        while (temp > 0) { tekushiy_razryad++; temp >>= 1; }
    }

    if (F < 2) F = 2;
}

// Генерация чётного R, меньшего F
int sozdat_R(int F) {
    if (F <= 2) return 2;
    random_device ustroystvo;
    mt19937 generator(ustroystvo());
    uniform_int_distribution<int> diapazon(2, F - 1);
    int R;
    do {
        R = diapazon(generator);
    } while (R % 2 != 0 || R >= F);
    return R;
}

// Тест Поклингтона: a^(n-1) ≡ 1 (mod n) и НОД(a^((n-1)/q) - 1, n) != 1
bool proverka_poklingtona(int chislo, const vector<pair<int, int>>& mnojiteli, int nadezhnost, int& otbrosheno) {
    if (chislo < 2) return false;
    if (chislo == 2 || chislo == 3) return true;
    if (chislo % 2 == 0) return false;

    random_device ustroystvo;
    mt19937 generator(ustroystvo());
    
    for (int shag = 0; shag < nadezhnost; ++shag) {
        uniform_int_distribution<int> diapazon(2, chislo - 1);
        int a = diapazon(generator);
        
        // Проверка 1: a^(n-1) ≡ 1 (mod n)
        if (stepen(a, chislo - 1, chislo) != 1) {
            otbrosheno++;
            return false;
        }
        
        // Проверка 2: НОД(a^((n-1)/q) - 1, n) != 1 → составное
        bool vse_usloviya = true;
        
        for (size_t nomer = 0; nomer < mnojiteli.size(); ++nomer) {
            int q = mnojiteli[nomer].first;
            int pokaz = (chislo - 1) / q;
            int znachenie = stepen(a, pokaz, chislo);  
            
            if (naibolshiy_delitel(znachenie - 1, chislo) != 1) {
                vse_usloviya = false;
                break;
            }
        }
        
        if (!vse_usloviya) {
            otbrosheno++;
            return false;
        }
    }
    
    return true;
}

// Полная проверка
bool polnaya_proverka(int chislo, const vector<pair<int, int>>& mnojiteli, int nadezhnost, int& otbrosheno) {
    int vremennyy_schet = 0;
    
    // Основной тест
    if (!proverka_poklingtona(chislo, mnojiteli, nadezhnost, vremennyy_schet)) {
        otbrosheno += vremennyy_schet;
        return false;
    }
    
    otbrosheno += vremennyy_schet;
    
    // Дополнительная проверка с t=2
    int dop_schet = 0;
    bool dop_proverka = proverka_poklingtona(chislo, mnojiteli, 2, dop_schet);
    otbrosheno += dop_schet;
    
    return dop_proverka;
}

// Генерация кандидата и проверка на простоту
bool poisk_kandidata(int razryad, const vector<int>& spisok, int& chislo, int& F, 
                        vector<pair<int, int>>& mnojiteli, int nadezhnost, int& otbrosheno, 
                        set<int>& ispolzovannye) {
    const int MAKS_POPYTOK = 500;
    
    for (int nomer = 0; nomer < MAKS_POPYTOK; ++nomer) {
       
        sozdat_F(razryad, spisok, F, mnojiteli);
        if (F < 2) continue;
        
        int R = sozdat_R(F);
        
        chislo = R * F + 1;
        if (chislo < 0) continue;
        
        // Проверка разрядности
        int dlinnoe_chislo = 0;
        long long temp = chislo;
        while (temp > 0) { dlinnoe_chislo++; temp >>= 1; }
        if (dlinnoe_chislo != razryad) continue;
        
        // Проверка условия F > sqrt(n)
        int koren = static_cast<int>(sqrt(chislo));
        if (F <= koren - 1) continue;
        
        // НОД(R, F) должно быть 1
        if (naibolshiy_delitel(R, F) != 1) continue;
        
        // Проверка на уникальность
        if (ispolzovannye.find(chislo) != ispolzovannye.end()) continue;
        
        int otbrosheno_vrem = 0;
        if (polnaya_proverka(chislo, mnojiteli, nadezhnost, otbrosheno_vrem)) {
            otbrosheno += otbrosheno_vrem;
            ispolzovannye.insert(chislo);
            return true;
        } else {
            otbrosheno += otbrosheno_vrem;
        }
    }
    return false;
}

int main() {
    int dlina;
    cout << "Введите требуемую разрядность чисел (bits): ";
    cin >> dlina;
    
    // Таблица простых чисел до 500
    vector<int> tablica = poisk_prostykh(500);
    
    int nadezhnost = 3;
    vector<int> naydennye;
    vector<bool> itogi;
    vector<int> schetchik_otbrosa;
    set<int> unikalnye;
    
    cout << "Генерация 10 простых чисел разрядностью " << dlina << " бит..." << endl << endl;
    
    // Генерация 10 простых чисел
    for (int nomer = 0; nomer < 10; ++nomer) {
        int chislo = 0, F = 0;
        vector<pair<int, int>> mnojiteli;
        int otbrosheno = 0;
        bool udacha = poisk_kandidata(dlina, tablica, chislo, F, mnojiteli, nadezhnost, otbrosheno, unikalnye);
        
        naydennye.push_back(chislo);
        itogi.push_back(udacha);
        schetchik_otbrosa.push_back(otbrosheno);
    }
    
    // Вывод результатов
    cout << "РЕЗУЛЬТАТЫ РАБОТЫ ПРОГРАММЫ" << endl;
    cout << "№" << "     " << "Простое число" << "     " << "Результат" << "     " << "Отвергнуто" << endl;
    cout << endl;
    
    for (size_t nomer = 0; nomer < 10; ++nomer) {
        cout << (nomer + 1);
        if (naydennye[nomer] != 0)
            cout << "          " << naydennye[nomer];
        else
            cout << "          ";
        cout << "          " << (itogi[nomer] ? "true" : "false");
        cout << "          " << schetchik_otbrosa[nomer] << endl;
    }
           
    return 0;
}
