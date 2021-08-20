#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "vector.hpp"

namespace ft {
	template <class T, class Container = vector<T> >
	class stack {
	private:
		Container			c;
	public:
		typedef T			value_type;
		typedef size_t		size_type;
		typedef Container 	container_type;

		explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}
		~stack() {}

		bool empty() const {return c.empty();}
		size_type size() const {return c.size();}
		value_type& top() {return c.back();}
		const value_type& top() const {return c.back();}
		void push (const value_type& val) {c.push_back(val);}
		void pop() {c.pop_back();}

		template <class friendT, class friendContainer>
		friend bool operator== (const stack<friendT,friendContainer>& lhs, const stack<friendT,friendContainer>& rhs);
		template <class friendT, class friendContainer>
		friend bool operator!= (const stack<friendT,friendContainer>& lhs, const stack<friendT,friendContainer>& rhs);
		template <class friendT, class friendContainer>
		friend bool operator<  (const stack<friendT,friendContainer>& lhs, const stack<friendT,friendContainer>& rhs);
		template <class friendT, class friendContainer>
		friend bool operator<= (const stack<friendT,friendContainer>& lhs, const stack<friendT,friendContainer>& rhs);
		template <class friendT, class friendContainer>
		friend bool operator>  (const stack<friendT,friendContainer>& lhs, const stack<friendT,friendContainer>& rhs);
		template <class friendT, class friendContainer>
		friend bool operator>= (const stack<friendT,friendContainer>& lhs, const stack<friendT,friendContainer>& rhs);
	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c == rhs.c;
	}
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c != rhs.c;
	}
	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c < rhs.c;
	}
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c <= rhs.c;
	}
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c > rhs.c;
	}
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.c >= rhs.c;
	}
}

#endif //FT_CONTAINERS_STACK_HPP
