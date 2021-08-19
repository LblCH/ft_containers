#include "vector.hpp"
#include <vector>

template <class T>
void printCompare(std::vector<T> &stl_vector, ft::vector<T> &ft_vector)
{
	std::cout << std::endl << "------------------------------" << std::endl;
	std::cout << "STL : " << std::endl;
	std::cout << "Empty		: " << stl_vector.empty() << std::endl;
	std::cout << "Size		: " << stl_vector.size() << std::endl;
	std::cout << "Capacity	: " << stl_vector.capacity() << std::endl;
	std::cout << "Max_size	: " << stl_vector.max_size() << std::endl;
	std::cout << "Content	: " << "{ ";
	typename std::vector<T>::iterator it = stl_vector.begin();
	typename std::vector<T>::iterator ite = stl_vector.end();
	while (it != ite) {
		std::cout << *it;
		if (++it != ite)
			std::cout << ", ";
	}
	std::cout << " }" << std::endl;

	std::cout << std::endl << "------------------------------" << std::endl;
	std::cout << "FT : " << std::endl;
	std::cout << "Empty		: " << ft_vector.empty() << std::endl;
	std::cout << "Size		: " << ft_vector.size() << std::endl;
	std::cout << "Capacity	: " << ft_vector.capacity() << std::endl;
	std::cout << "Max_size	: " << ft_vector.max_size() << std::endl;
	std::cout << "Content	: " << "{ ";
	typename ft::vector<T>::iterator ft_it = ft_vector.begin();
	typename ft::vector<T>::iterator ft_ite = ft_vector.end();
	while (ft_it != ft_ite) {
		std::cout << *ft_it;
		if (++ft_it != ft_ite)
			std::cout << ", ";
	}
	std::cout << " }" << std::endl << std::endl;
}

void test_vector()
{
	std::cout << "\33[1;31m" << "Default int vectors " << "\33[0m" << std::endl;
	std::vector<int> stl_vector;
	ft::vector<int> ft_vector;
	printCompare<int>(stl_vector, ft_vector);

	std::cout << "\33[1;31m" << "Default string vectors " << "\33[0m" << std::endl;
	std::vector<std::string> stl_vector1;
	ft::vector<std::string> ft_vector1;
	printCompare<std::string>(stl_vector1, ft_vector1);

	std::cout << "\33[1;31m" << "Default string vectors " << "\33[0m" << std::endl;
	stl_vector1.push_back("string");
	ft_vector1.push_back("string");
	printCompare<std::string>(stl_vector1, ft_vector1);

	std::cout << "\33[1;31m" << "Empty int vectors " << "\33[0m" << std::endl;
	std::vector<int> stl_vector2(0);
	ft::vector<int> ft_vector2(0);
	printCompare<int>(stl_vector, ft_vector);

	std::cout << "\33[1;31m" << "Fill construct int vectors 5 elems of 13 " << "\33[0m" << std::endl;
	std::vector<int> stl_vector3(5, 13);
	ft::vector<int> ft_vector3(5, 13);
	printCompare<int>(stl_vector3, ft_vector3);

	std::cout << "\33[1;31m" << "Range construct int vectors from previous" << "\33[0m" << std::endl;
	std::vector<int> stl_vector4(stl_vector3.begin(), stl_vector3.end());
	ft::vector<int> ft_vector4(ft_vector3.begin(), ft_vector3.end());
	printCompare<int>(stl_vector4, ft_vector4);

	std::cout << "\33[1;31m" << "Copy construct int vectors from previous" << "\33[0m" << std::endl;
	std::vector<int> stl_vector5(stl_vector4.begin(), stl_vector4.end());
	ft::vector<int> ft_vector5(ft_vector4.begin(), ft_vector4.end());
	printCompare<int>(stl_vector5, ft_vector5);

	std::cout << "\33[1;31m" << "pop & push 5, push from front prev, resize 7 with 2" << "\33[0m" << std::endl;
	stl_vector5.pop_back();
	ft_vector5.pop_back();
	stl_vector5.push_back(5);
	stl_vector5.push_back(stl_vector4.front());
	ft_vector5.push_back(5);
	ft_vector5.push_back(ft_vector4.front());
	stl_vector5.resize(7,2);
	ft_vector5.resize(7,2);
	printCompare<int>(stl_vector5, ft_vector5);

	std::cout << "\33[1;31m" << "Assign with rbegin, rend + reserve 10" << "\33[0m" << std::endl;
	std::vector<int> stl_vector6;
	ft::vector<int> ft_vector6;
	stl_vector6.assign(stl_vector5.rbegin(), stl_vector5.rend());
	ft_vector6.assign(ft_vector5.rbegin(), ft_vector5.rend());
	stl_vector6.reserve(10);
	ft_vector6.reserve(10);
	printCompare<int>(stl_vector6, ft_vector6);

	std::cout << "\33[1;31m" << "Access [2], at[1] [12], front, back" << "\33[0m" << std::endl;
	std::cout << stl_vector6[2] << " " << stl_vector6.at(1) << " ";
	try {std::cout << stl_vector6.at(12);}
	catch(const std::exception& e) {
		std::cout << e.what() << ' ';
	}
	std::cout << stl_vector6.front() << " " << stl_vector6.back() << std::endl;
	std::cout << ft_vector6[2] << ' ' << ft_vector6.at(1) << " ";
	try {std::cout << ft_vector6.at(12);}
	catch(const std::exception& e) {
		std::cout << e.what() << ' ';
	}
	std::cout << ft_vector6.front() << " " << ft_vector6.back() << std::endl;

	std::cout << "\33[1;31m" << "Erase end " << "\33[0m" << std::endl;
//	std::cout << *stl_vector5.rbegin() <<
	for (ft::vector<int>::reverse_iterator it = ft_vector5.rbegin(); it != ft_vector5.rend(); ++it) {
		std::cout << *it << ", ";
	}
	std::cout << std::endl;

}


int main()
{
	test_vector();
	return 0;
}
