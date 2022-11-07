#include <iostream>
#include <vector>
#include <map>

std::map<int, int> factorization(int x) {
    std::map<int, int> result;

    int i = 2;
    while (x != 1) {
        if (x % i == 0) {
            result[i] += 1;
            x /= i;
        } else {
            ++i;
        }
    }
    return result;
}

int fast_power(int x, int y, int radix) {
    int a = 1, b = x;

    while (y > 0) {
        if ((y & 1) == 1) {
            a *= b;
            a %= radix;
        }
        b *= b;
        b %= radix;
        y >>= 1;
//        std::cout << a << " " << b << '\n';
    }
    return a;
}

int fast_power(int x, int y) {
    int a = 1, b = x;

    while (y > 0) {
        if ((y & 1) == 1) {
            a *= b;
        }
        b *= b;
        y >>= 1;
    }
    return a;
}

std::map<std::pair<int, int>, int> get_r(std::map<int, int>& dividers, int a, int radix) {
    std::map<std::pair<int, int>, int> result;
    for (auto item : dividers) {
        for (int i = 0; i < item.first; ++i) {
            result[std::make_pair(item.first, i)] = fast_power(a, ((radix - 1) * i) / item.first, radix);
        }
    }
    return result;
}

int find_inverse_element(int x, int radix) {
    if (x == 0) {
        return 1;
    }

    for (int i = 1; i < radix; ++i) {
        if ((i * x) % radix == 1) {
            return i;
        }
    }
}

int solve_ctr(std::map<int, int>& sc) {
    int M = 1;

    for (auto item : sc) {
        M *= item.first;
    }

    std::vector<int> m;
    std::vector<int> n;
    for (auto item : sc) {
        m.push_back(M / item.first);
        n.push_back(find_inverse_element(M / item.first, item.first));
    }

    int ans = 0;
    int i = 0;
    for (auto item : sc) {
        ans += m[i] * n[i] * item.second;
        ++i;
    }

    return ans % M;
}

// при желании протестировать ключевые функции программы можно раскомментить соответсвующие части кода
int main() {
    // подготовительный этап
    int b, y, radix; // b, y - значение как в презентации докладчика, radix - порядок поля А
    std::cin >> b >> y >> radix;
    std::map<int, int> dividers = factorization(radix - 1); // получаем множители порядка поля

//    for (auto item : dividers) {
//        std::cout << item.first << " " << item.second << '\n';
//    }

    std::map<std::pair<int, int>, int> r = get_r(dividers, b, radix);  // r - таблица, как в презентации докладчика

//    for (auto item : r) {
//        std::cout << item.first.first << " " << item.first.second << " " << item.second << "\n";
//    }
//    std::cout << '\n';


    //     КТО
    std::map<int, int> sc; // система сравнений x с числами по разным модулям
    for (auto p : dividers) {
        int mod = fast_power(p.first, p.second);
        for (int i = 0; i < p.second; ++i) {
            // находим y_i, далее по нему восстанавливавем x_i
            int y_i = fast_power(y * find_inverse_element(fast_power(b, sc[mod]), radix), (radix - 1) / fast_power(p.first, i + 1), radix);
//            std::cout << p.first << " " << i << " " << y_i << " " << inverse_element << " " << sc[mod] << '\n';
            for (auto r_i : r) {
                if (r_i.first.first == p.first && r_i.second == y_i) {
                    sc[mod] += (r_i.first.second * fast_power(p.first, i));
                    break;
                }
            }
        }
    }

//    for (auto item : sc) {
//        std::cout << item.first << " " << item.second << '\n';
//    }
//    std::cout << '\n';

    // решение КТО и вывод ответа
    std::cout << solve_ctr(sc);
    return 0;
}
