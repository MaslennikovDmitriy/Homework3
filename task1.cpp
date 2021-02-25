#include <iostream>
#include <clocale>
#include <vector>
#include <set>
#include <array>
#include <ctime>
#include <chrono>
#include <algorithm>

int main()
{
    setlocale(LC_ALL, "Russian");
    const size_t size = 100000U;
    std::vector <int> vec(size);
    std::array <int, size> arr;
    std::set <int> set;
    int q = 0;
    for (size_t i = 0; i < size; i++)
    {
        srand(time(0) * q++ * 7);
        int p = rand() % 1000;
        vec[i] = p;
        arr[i] = p;
    }

    auto now = std::chrono::system_clock::now();
    for (size_t i = 0; i < size; i++)
    {
        set.insert(vec[i]);
    }
    auto end = std::chrono::system_clock::now();
    int elapsed_set = std::chrono::duration_cast<std::chrono::milliseconds>(end - now).count();
    int elapsed = elapsed_set;
    std::string leader = "std::set";

    now = std::chrono::system_clock::now();
    sort(vec.begin(), vec.end());
    end = std::chrono::system_clock::now();
    int elapsed_vec = std::chrono::duration_cast<std::chrono::milliseconds>(end - now).count();
    if (elapsed > elapsed_vec)
    {
        elapsed = elapsed_vec;
        leader = "Vector";
    }

    now = std::chrono::system_clock::now();
    sort(arr.begin(), arr.end());
    end = std::chrono::system_clock::now();
    int elapsed_arr = std::chrono::duration_cast<std::chrono::milliseconds>(end - now).count();
    if (elapsed > elapsed_arr)
    {
        elapsed = elapsed_arr;
        leader = "Array";
    }

    std::cout << "Время сортировки std::set (в миллисекундах): " << elapsed_set << std::endl;
    std::cout << "Время сортировки std::vector (в миллисекундах): " << elapsed_vec << std::endl;
    std::cout << "Время сортировки std::array (в миллисекундах): " << elapsed_arr << std::endl;
    std::cout << std::endl;
    std::cout << "Лидер: " << leader << std::endl;
    // Пороговое значение N, при котором сменяется лидер, существует, однако его определение затруднено - в 4 тестах из 5 при N = 100000 быстрее оказывался std::vector. 
    // Сложность однозначного определения N может быть объяснена влиянием погрешности при измерении времени сортировки, вызванной внешними процессами компьютера.
    system("pause");
    return EXIT_SUCCESS;
}