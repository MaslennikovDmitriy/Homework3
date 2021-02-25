#include <iostream>
#include <string>
#include <clocale>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

using namespace boost::multi_index;

struct Rec
{
	std::string name, phone, addr;
	struct ByName {};
	struct ByPhone {};
	struct ByAddr {};
};

typedef boost::multi_index_container<Rec, indexed_by< ordered_unique< tag<Rec::ByName>,
	member<Rec, std::string, &Rec::name>
>,
ordered_non_unique<
	tag<Rec::ByPhone>, member<Rec, std::string, &Rec::phone>
>,
ordered_non_unique<
	tag<Rec::ByAddr>, member<Rec, std::string, &Rec::addr>
>
>
> Store;

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");

	Store store;
	Rec r1 = { "Jonathan Joestar", "+442089786564", "������" };
	Rec r2 = { "Joseph Joestar", "18703067492", "���" };
	Rec r3 = { "Jotaro Kujo", "+819067554761", "������" };
	Rec r4 = { "Josuke Higashikata", "+818963478452", "�����" };
	Rec r5 = { "Giorno Giovanna", "+390669824589", "������" };
	Rec r6 = { "Jolyne Kujo", "+819067554762", "������" };
	store.insert(r1);
	store.insert(r2);
	store.insert(r3);
	store.insert(r4);
	store.insert(r5);
	store.insert(r6);
	std::string find_id = "Giorno Giovanna"; // ����� �� �����
	typedef Store::index<Rec::ByName>::type List;
	const List& ls = store.get<Rec::ByName>();
	List::const_iterator it = ls.find(find_id);
	if (it != ls.end())
	{
		std::cout << "�����: " << (*it).addr << std::endl;
		std::cout << "�����: " << (*it).phone << std::endl;
	}
	std::cout << std::endl;

	std::string find_phone = "18703067492"; // ����� �� ������
	Store::index<Rec::ByPhone>::type::iterator it0, it1;
	tie(it0, it1) = store.get<Rec::ByPhone>().equal_range(find_phone);
	while (it0 != it1)
	{
		std::cout << "���: " << (*it0).name << std::endl;
		++it0;
	}
	std::cout << std::endl;

	std::string find_address = "�����"; // ����� �� ������
	Store::index<Rec::ByAddr>::type::iterator it2, it3;
	tie(it2, it3) = store.get<Rec::ByAddr>().equal_range(find_address);
	while (it2 != it3)
	{
		std::cout << "���: " << (*it2).name << std::endl;
		++it2;
	}

	std::cout << std::endl;
	size_t count = 1;
	for (auto it = store.begin(); it != store.end(); ++it) // ����� ������������� �� ������ ����������
	{
		std::cout << count << "-�� �������:" << std::endl;
		std::cout << "���: " << (*it).name << ", �����: " << (*it).phone << ", �����: " << (*it).addr << ";" << std::endl;
		count++;
	}

	system("pause");
	return EXIT_SUCCESS;
}