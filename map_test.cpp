#include <map>
#include "map.hpp"

template <typename Key, typename T>
void printCompare(std::map<Key, T> &stl_map, ft::map<T, T> &ft_map)
{
	std::cout << std::endl << "------------------------------" << std::endl;
	std::cout << "STL : " << std::endl;
	std::cout << "Empty		: " << stl_map.empty() << std::endl;
	std::cout << "Size		: " << stl_map.size() << std::endl;
	std::cout << "Max_size	: " << stl_map.max_size() << std::endl;
	std::cout << "Content	: " << "{ ";
	typename std::map<Key, T>::iterator it = stl_map.begin();
	typename std::map<Key, T>::iterator ite = stl_map.end();
	while (it != ite) {
		std::cout << it->first << " | " << it->second;
		if (++it != ite)
			std::cout << ", ";
	}
	std::cout << " }" << std::endl;

	std::cout << std::endl << "------------------------------" << std::endl;
	std::cout << "FT : " << std::endl;
	std::cout << "Empty		: " << ft_map.empty() << std::endl;
	std::cout << "Size		: " << ft_map.size() << std::endl;
	std::cout << "Max_size	: " << ft_map.max_size() << std::endl;
	std::cout << "Content	: " << "{ ";
	typename ft::map<Key, T>::iterator ft_it = ft_map.begin();
	typename ft::map<Key, T>::iterator ft_ite = ft_map.end();
	while (ft_it != ft_ite) {
		std::cout << ft_it->first << " | " << ft_it->second;
		if (++ft_it != ft_ite)
			std::cout << ", ";
	}
	std::cout << " }" << std::endl << std::endl;
}

void map_test()
{
	std::map<int, int> stl_map;
	ft::map<int, int> ft_map;
	printCompare(stl_map, ft_map);

	stl_map.insert(std::pair<int, int>(50, 51));
	stl_map.insert(std::pair<int, int>(40, 41));
	stl_map.insert(std::pair<int, int>(60, 60));
	stl_map.insert(std::pair<int, int>(55, 55));
	stl_map.insert(std::pair<int, int>(80, 80));
	stl_map.insert(std::pair<int, int>(70, 70));
	stl_map.insert(std::pair<int, int>(75, 75));
	stl_map.insert(stl_map.begin(), std::pair<int, int>(90, 90));
	stl_map[100] = 105;
	ft_map.insert(ft::pair<int, int>(50, 51));
	ft_map.insert(ft::pair<int, int>(40, 41));
	ft_map.insert(ft::pair<int, int>(60, 60));
	ft_map.insert(ft::pair<int, int>(55, 55));
	ft_map.insert(ft::pair<int, int>(80, 80));
	ft_map.insert(ft::pair<int, int>(70, 70));
	ft_map.insert(ft::pair<int, int>(75, 75));
	ft_map.insert(ft_map.begin(), ft::pair<int, int>(90, 90));
	ft_map[100] = 105;
	printCompare(stl_map, ft_map);

	std::cout << "Insert range :" << std::endl;
	std::map<int, int> stl_map2;
	ft::map<int, int> ft_map2;
	stl_map2.insert(stl_map.begin(), stl_map.end());
	ft_map2.insert(ft_map.begin(), ft_map.end());
	printCompare(stl_map2, ft_map2);

	std::cout << "Erase :" << std::endl;
	stl_map.erase(stl_map.begin());
	ft_map.erase(ft_map.begin());
	stl_map.erase(50);
	ft_map.erase(50);
	stl_map.erase(stl_map.find(55), stl_map.find(70));
	ft_map.erase(ft_map.find(55), ft_map.find(70));
	printCompare(stl_map, ft_map);

	std::cout << "Swap & clear:" << std::endl;
	stl_map.swap(stl_map2);
	ft_map.swap(ft_map2);
	printCompare(stl_map, ft_map);
	stl_map2.clear();
	ft_map2.clear();
	printCompare(stl_map2, ft_map2);

	std::cout << "Key compare: 40, 60" << std::endl << "STL: " << stl_map.key_comp()(40,60);
	std::cout << std::endl << "FT: " << ft_map.key_comp()(40, 60) << std::endl;
	std::cout << "Key compare: 60, 40" << std::endl << "STL: " << stl_map.key_comp()(60,40);
	std::cout << std::endl << "FT: " << ft_map.key_comp()(60, 40) << std::endl;

	std::cout << "Value compare: 41, 51" << std::endl << "STL: " << stl_map.key_comp()(41,51);
	std::cout << std::endl << "FT: " << ft_map.key_comp()(41, 51) << std::endl;
	std::cout << "Value compare: 51, 41" << std::endl << "STL: " << stl_map.key_comp()(51,41);
	std::cout << std::endl << "FT: " << ft_map.key_comp()(51, 41) << std::endl;

	std::cout << std::endl << "Lower bound: 45 & 50" << std::endl << "STL: " << stl_map.lower_bound(45)->first;
	std::cout << " & " << stl_map.lower_bound(50)->first << std::endl << "FT: " << ft_map.lower_bound(45)->first;
	std::cout << " & " << ft_map.lower_bound(50)->first << std::endl;

	std::cout << std::endl << "Upper bound: 45 & 50" << std::endl << "STL: " << stl_map.upper_bound(45)->first;
	std::cout << " & " << stl_map.upper_bound(50)->first << std::endl << "FT: " << ft_map.upper_bound(45)->first;
	std::cout << " & " << ft_map.upper_bound(50)->first << std::endl;

	std::cout << std::endl << "Equal_range: 65" << std::endl << "STL: first: " << stl_map.equal_range(65).first->first;
	std::cout << " second: " << stl_map.equal_range(65).second->first << std::endl << "FT: first: ";
	std::cout << ft_map.equal_range(65).first->first << " second: " << ft_map.equal_range(65).second->first << std::endl << std::endl;
}

