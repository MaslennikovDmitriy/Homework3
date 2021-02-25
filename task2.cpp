#include <iostream>
#include <clocale>
#include <cmath>       

unsigned int hash(double d)
{
	auto h = 0U;
	h = fmod(d, 3) * pow(d, 2) * 2 + 256;
	return fmod(h, 64);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << hash(563.88) << std::endl;
	std::cout << hash(1.775) << std::endl;
	std::cout << hash(2435.256) << std::endl;
	std::cout << hash(-52.33) << std::endl;
	std::cout << hash(565.12) << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}