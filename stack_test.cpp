#include "stack.hpp"
#include <stack>

template<class T>
void printCompare(std::stack<T> &stl_stack, ft::stack<T> &ft_stack)
{
	std::cout << std::endl << "------------------------------" << std::endl;
	std::cout << "STL : " << std::endl;
	std::cout << "Empty		: " << stl_stack.empty() << std::endl;
	std::cout << "Size		: " << stl_stack.size() << std::endl;
	if(stl_stack.top())
		std::cout << "Top		: " << stl_stack.top() << std::endl;

	std::cout << std::endl << "------------------------------" << std::endl;
	std::cout << "FT : " << std::endl;
	std::cout << "Empty		: " << ft_stack.empty() << std::endl;
	std::cout << "Size		: " << ft_stack.size() << std::endl;
	if (ft_stack.top())
		std::cout << "Top		: " << ft_stack.top() << std::endl;
}

void stack_test()
{
	std::stack<int> stl_stack;
	ft::stack<int> ft_stack;

	std::cout << "Push 13 & 20" << std::endl;
	stl_stack.push(13);
	ft_stack.push(13);
	stl_stack.push(20);
	ft_stack.push(20);
	printCompare(stl_stack, ft_stack);
	stl_stack.pop();
	ft_stack.pop();
	std::cout << std::endl << "Pop & Top: " << std::endl << "STL: " << stl_stack.top() << std::endl;
	std::cout << "FT: " << ft_stack.top() << std::endl;
}


