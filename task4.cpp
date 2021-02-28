#include <iostream>
#include <vector>
#include <clocale>
#include <sstream>
#include <stdlib.h>
#include <fstream>

const int N = 300;

void check(std::vector <size_t> hash1, std::vector <size_t> counter)
{
    for (int k = 1; k < N; k++)
    {
        std::vector <size_t> Rep1;
        int count = 0;
        for (size_t i = 0; i < k - 1; i++)
        {
            bool r = true;
            for (size_t j = 0; j < Rep1.size(); j++)
            {
                if (Rep1[j] == hash1[i])
                {
                    r = false;
                    break;
                }
            }
            if (r == true)
            {
                Rep1.push_back(hash1[i]);

                for (size_t j = i + 1; j < k; j++)
                {
                    if (hash1[j] == hash1[i])
                    {
                        count++;
                    }
                }
            }
        }

        std::cout << "N = " << k + 1 << "; количество коллизий: " << count << std::endl;
        counter[k] = count;
    }
}

unsigned int RSHash(const char* str, unsigned int length)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = hash * a + (*str);
        a = a * b;
    }

    return hash;
}

unsigned int JSHash(const char* str, unsigned int length)
{
    unsigned int hash = 1315423911;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((hash << 5) + (*str) + (hash >> 2));
    }

    return hash;
}

unsigned int PJWHash(const char* str, unsigned int length)
{
    const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    const unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
    const unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
    const unsigned int HighBits =
        (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << OneEighth) + (*str);

        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }
    return hash;
}

unsigned int ELFHash(const char* str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int x = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << 4) + (*str);

        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }

        hash &= ~x;
    }

    return hash;
}

unsigned int BKDRHash(const char* str, unsigned int length)
{
    unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash * seed) + (*str);
    }

    return hash;
}

unsigned int SDBMHash(const char* str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (*str) + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

unsigned int DJBHash(const char* str, unsigned int length)
{
    unsigned int hash = 5381;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash;
}

unsigned int DEKHash(const char* str, unsigned int length)
{
    unsigned int hash = length;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
    }

    return hash;
}

unsigned int APHash(const char* str, unsigned int length)
{
    unsigned int hash = 0xAAAAAAAA;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((i & 1) == 0) ? ((hash << 7) ^ (*str) * (hash >> 3)) :
            (~((hash << 11) + ((*str) ^ (hash >> 5))));
    }

    return hash;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    char ar[26];
    for (size_t i = 0; i < 26; i++)
    {
        static int count = 97;
        ar[i] = (char)count;
        count++;
        //std::cout << ar[i] << std::endl;
    }
    std::vector <std::string> str_test(N);
    std::vector <size_t> counter(N);
    for (size_t j = 0; j < str_test.size(); j++)
    {
        for (size_t i = 0; i < 5; i++)
        {
            str_test[j] += ar[rand() % 25];
        }
    }
    /*for (size_t j = 0; j < str_test.size(); j++)
    {
        std::cout << str_test[j] << std::endl;
    }*/

    std::vector <size_t> hash1(N);
    /* for (size_t j = 0; j < str_test.size(); j++)
     {
         hash1[j] = RSHash(str_test[j].c_str(), N);
     }
     check(hash1);
     std::cout << std::endl;*/

     //for (size_t j = 0; j < str_test.size(); j++)
     //{
     //    hash1[j] = JSHash(str_test[j].c_str(), N);
     //}
     //check(hash1);
     //std::cout << std::endl;

     //for (size_t j = 0; j < str_test.size(); j++)
     //{
     //    hash1[j] = PJWHash(str_test[j].c_str(), N);
     //}
     //check(hash1);
     //std::cout << std::endl;

     /*for (size_t j = 0; j < str_test.size(); j++)
     {
         hash1[j] = ELFHash(str_test[j].c_str(), N);
     }
     check(hash1);
     std::cout << std::endl;*/

     /*for (size_t j = 0; j < str_test.size(); j++)
     {
         hash1[j] = BKDRHash(str_test[j].c_str(), N);
     }
     check(hash1);
     std::cout << std::endl;*/

     /*for (size_t j = 0; j < str_test.size(); j++)
     {
         hash1[j] = SDBMHash(str_test[j].c_str(), N);
     }
     check(hash1);
     std::cout << std::endl;*/

     /*for (size_t j = 0; j < str_test.size(); j++)
     {
         hash1[j] = DJBHash(str_test[j].c_str(), N);
     }
     check(hash1);
     std::cout << std::endl;*/

     /*for (size_t j = 0; j < str_test.size(); j++)
     {
         hash1[j] = DEKHash(str_test[j].c_str(), N);
     }
     check(hash1);
     std::cout << std::endl;*/

    for (size_t j = 0; j < str_test.size(); j++)
    {
        hash1[j] = APHash(str_test[j].c_str(), N);
        //std::cout << hash1[j] << std::endl;
    }
    check(hash1, counter);
    std::cout << std::endl;
    system("pause");
    return EXIT_SUCCESS;
}