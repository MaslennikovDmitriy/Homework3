#include <iostream>
#include <clocale>
#include <cmath>
#include <chrono>
#include <vector>
#include <algorithm>

const int N = 100;

unsigned int hash(double d)
{
    static int f = 0;
    srand(time(0) * f++ * 150);
    int h;
    h = d + rand() % 1000 + (time(0) + rand() % 100 * 1000000000) / (time(0) - rand() % 10 * 1000000000) + rand() % 10;
    return abs(h);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    auto now = std::chrono::system_clock::now();
    std::cout << hash(563.88) << std::endl;
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - now);
    std::cout << "Âðåìÿ ðàáîòû ôóíêöèè: " << elapsed.count() << " (ìñ)" << std::endl;

    std::vector <int> hashes(N);
    std::vector <double> v(N);
    int f = 0;
    for (int i = 0; i < N; i++)
    {
        srand(time(0) * f++ * 150);
        v[i] = rand() % 10000; // для исследования числа коллизий в зависимости от количества чисел
        //v[i] = i; // для исследования равномерности
        hashes[i] = hash(v[i]);
        std::cout << hashes[i] << std::endl;
    }
    std::cout << std::endl;

    for (int k = 1; k < N; k++) // исследование количества коллизий
    {
        std::vector <size_t> Rep;
        int count = 0;

        for (size_t i = 0; i < k - 1; i++)
        {
            bool r = true;

            for (size_t j = 0; j < Rep.size(); j++)
            {
                if (Rep[j] == hashes[i])
                {
                    r = false;
                    break;
                }
            }

            if (r == true)
            {
                Rep.push_back(hashes[i]);

                for (size_t j = i + 1; j < k; j++)
                {
                    if (hashes[j] == hashes[i])
                    {
                        count++;
                    }
                }
            }
        }

        std::cout << "N = " << k + 1 << "; количество коллизий: " << count << std::endl;
    }
    std::cout << std::endl;
    std::sort(hashes.begin(), hashes.end()); // исследование равномерности
    int h = hashes[0];
    int max = (hashes[N - 1] - hashes[0]) / 10;
    int count = 0;
    size_t j = 0;
    for (int i = 0; i < 100; i++)
    {
        if ((hashes[i] - h) < max)
        {
            count++;
        }
        else
        {
            h = h + max;
            j++;
            std::cout << "На " << j << "-ом отрезке: " << count << " значений хэш-функции;" << std::endl;
            count = 0;
        }
    }
    return EXIT_SUCCESS;
}
