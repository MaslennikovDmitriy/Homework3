#include <iostream>
#include <iomanip>
#include <functional>
#include <vector>
#include <boost/functional/hash.hpp>
#include <ctime>
#include <clocale>

using namespace std;

int N = 200;

struct Animal
{
    unsigned int age;
    char name;
    friend size_t hash_value(const Animal& animal);
};

size_t hash_value(const Animal& animal)
{
    size_t seed = 0;
    boost::hash_combine(seed, animal.age);
    boost::hash_combine(seed, animal.name);
    return seed;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    vector <Animal> Animals(N);
    vector <size_t> hashes(N);
    unsigned int j = 1;
    int k = 65;
    int f = 0;
    for (int i = 0; i < N; i++)
    {
        srand(time(0) * f++ * 10);
        Animals[i] = { (j + rand() % 150), char(k + rand() % 36) };
        hashes[i] = hash_value(Animals[i]);
    }

    for (int k = 1; k < N; k++)
    {
        vector <size_t> Rep;
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

        cout << "N = " << k + 1 << "; количество коллизий: " << count << endl;
    }
    system("pause");
    return EXIT_SUCCESS;
}
