#pragma once
#include<iostream>
#include<initializer_list>
#include<type_traits>
#include<algorithm>
#include<new>
#include<cstdlib>
#include<utility>
#include<memory>
#include"Macros.h"
#include<functional>
_PANAGIOTIS_BEGIN
template<typename _Ty>
class double_linked_list final {
private:
	//list_node,has three constructors
	//one default,one for copies of data and one for moving data with clear
	//specifiations the private constructor is used in order to craft data in place
	//calling its constructor  and a craft func to use only with this private constructor
	class list_node final {
	private:
		class secretClass {};
		template<class ..._Valty>
		list_node(secretClass, _Valty&& ..._Val)
			noexcept(std::is_nothrow_constructible_v<_Ty, _Valty...>)
			:data{ std::forward<_Valty>(_Val)... }, prev{}, next{}
		{
			//constructs the object in place
			static_assert(std::is_constructible_v<_Ty, _Valty...>,
				"the type must be constructible in place with these args");
		}
	public:
		//data members of every list_node 
		_Ty data;
		list_node* next;
		list_node* prev;
		list_node()noexcept(std::is_nothrow_default_constructible_v<_Ty>)
			:data{}, next{}, prev{}
		{
			static_assert(std::is_default_constructible_v<_Ty>, "the type must be"
				"default constructible in order to use this function");
		}
		list_node(const _Ty& item)noexcept(std::is_nothrow_copy_constructible_v<_Ty>)
			:data{ item }, next{}, prev{}
		{
			static_assert(std::is_copy_constructible_v<_Ty>, "the type must be "
				"copy constructible in order to use this function");
		}
		list_node(_Ty&& item)noexcept(std::is_nothrow_move_constructible_v<_Ty>)
			:data{ std::move(item) }, next{}, prev{}
		{
			static_assert(std::is_move_constructible_v<_Ty>, "the type must be "
				"move constructible in order to use this function");
		}
		//static func no need to make it non static
		template<class ..._Valty>
		static list_node* craft(_Valty&& ..._Val) {
			list_node* ptr = new list_node{ secretClass{},std::forward<_Valty>(_Val)... };
			return ptr;

		}
	};
	//thats my own iterator class
	//pretty much it is just a wrapper arroung my pointer 
	//it also has operator ++ in order to advance the pointer 
	//it also has += in order to progress it even further
	//it also has != and == for comparisons and operator *
	//with references qualifiers ,pretty much all that matters is where the pointer
	//shows 
	//and it also supports operator --,-,-=
	//pretty much the iterator is like if the pointer is null pointer dont move
	//else move 
	class list_node_iterator final {
	private:
		list_node* ptr;
		friend double_linked_list<_Ty>;
	public:
		//
		list_node_iterator()noexcept :ptr{}
		{
		}
		//
		list_node_iterator(list_node* ptr1)noexcept :ptr{ ptr1 }
		{
		}
		//
		list_node_iterator(const list_node_iterator& other)noexcept = default;
		//
		list_node_iterator(list_node_iterator&& other)noexcept = default;
		//
		list_node_iterator operator++()noexcept {
			if (ptr != nullptr) {
				ptr = ptr->next;
			}
			return list_node_iterator{ ptr };
		}
		//
		list_node_iterator operator++(int)noexcept {
			list_node_iterator tmp{ ptr };
			if (ptr != nullptr) {
				ptr = ptr->next;
			}
			return tmp;
		}
		//
		bool operator!=(const list_node_iterator& other)const noexcept {
			return ptr != other.ptr;
		}
		//
		bool operator ==(const list_node_iterator& other)const noexcept {
			return ptr == other.ptr;
		}
		//
		const _Ty& operator *()const& {
			if (ptr != nullptr) {
				return ptr->data;
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		_Ty& operator *()& {
			if (ptr != nullptr) {
				return ptr->data;
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		const _Ty&& operator *()const&& {
			if (ptr != nullptr) {
				return std::move(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		_Ty&& operator *()&& {
			if (ptr != nullptr) {
				return std::move(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		list_node_iterator operator +=(std::size_t counter)noexcept {
			for (std::size_t i = 0; i < counter; i++) {
				if (ptr != nullptr)ptr = ptr->next;
				else break;
			}
			return list_node_iterator{ ptr };
		}
		//
		const _Ty* operator ->()const& {
			if (ptr != nullptr) {
				return std::addressof(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		_Ty* operator ->()& {
			if (ptr != nullptr) {
				return std::addressof(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		const _Ty* operator ->()const&& {
			if (ptr != nullptr) {
				return std::addressof(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		_Ty* operator ->()&& {
			if (ptr != nullptr) {
				return std::addressof(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		list_node_iterator operator +(std::size_t counter)const noexcept {
			list_node* curr{ ptr };
			for (std::size_t i = 0; i < counter; i++) {
				if (curr != nullptr)curr = curr->next;
				else break;
			}
			return list_node_iterator{ curr };
		}
		friend list_node_iterator operator +(std::size_t counter, const
			list_node_iterator& it) noexcept {
			return it + counter;
		}
		//
		list_node_iterator operator --()noexcept {
			if (ptr != nullptr) {
				ptr = ptr->prev;
			}
			return list_node_iterator{ ptr };
		}
		//
		list_node_iterator operator--(int)noexcept {
			list_node_iterator tmp{ ptr };
			if (ptr != nullptr) {
				ptr = ptr->prev;
			}
			return tmp;
		}
		//
		list_node_iterator operator-(std::size_t counter)const noexcept {
			list_node* curr{ ptr };
			for (std::size_t i = 0; i < counter; i++) {
				if (curr != nullptr)curr = curr->prev;
				else break;
			}
			return list_node_iterator{ curr };
		}
		//
		list_node_iterator operator -=(std::size_t counter)noexcept {
			for (std::size_t i = 0; i < counter; i++) {
				if (ptr != nullptr)ptr = ptr->prev;
				else break;
			}
			return list_node_iterator{ ptr };
		}
		//
		list_node_iterator operator =(const list_node_iterator& other)noexcept {
			ptr = other.ptr;
			return *this;
		}
		//
		list_node_iterator operator =(list_node_iterator&& other)noexcept {
			ptr = other.ptr;
			return *this;
		}
		//
		~list_node_iterator()noexcept {
			ptr = nullptr;
		}
	};
	//thats my own const_iterator class
	//pretty much it is just a wrapper arroung my pointer 
	//it also has operator ++ in order to advance the pointer 
	//it also has += in order to progress it even further
	//it also has != and == for comparisons and operator *
	//with references qualifiers only for const 
	// ,pretty much all that matters is where the pointer
	//shows and remember this iterator is only to get the element not change it
	//it also supports operators: --,-,-=
	//it pretty much behaves like a real iterator 
	class list_node_const_iterator final {
	private:
		list_node* ptr;
		friend double_linked_list<_Ty>;
	public:
		//
		list_node_const_iterator()noexcept :ptr{}
		{
		}
		//
		list_node_const_iterator(list_node* ptr1)noexcept :ptr{ ptr1 }
		{
		}
		//
		list_node_const_iterator(const list_node_const_iterator& other)noexcept = default;
		//
		list_node_const_iterator(list_node_const_iterator&& other)noexcept = default;
		//
		list_node_const_iterator operator++()noexcept {
			if (ptr != nullptr) {
				ptr = ptr->next;
			}
			return list_node_const_iterator{ ptr };
		}
		//
		list_node_const_iterator operator++(int)noexcept {
			list_node_const_iterator tmp{ ptr };
			if (ptr != nullptr) {
				ptr = ptr->next;
			}
			return tmp;
		}
		//
		bool operator!=(const list_node_const_iterator& other)const noexcept {
			return ptr != other.ptr;
		}
		//
		bool operator ==(const list_node_const_iterator& other)const noexcept {
			return ptr == other.ptr;
		}
		//
		const _Ty& operator *()const& {
			if (ptr != nullptr) {
				return ptr->data;
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		const _Ty&& operator *()const&& {
			if (ptr != nullptr) {
				return std::move(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		list_node_const_iterator operator +=(std::size_t counter)noexcept {
			for (std::size_t i = 0; i < counter; i++) {
				if (ptr != nullptr)ptr = ptr->next;
				else break;
			}
			return list_node_const_iterator{ ptr };
		}
		//
		const _Ty* operator ->()const& {
			if (ptr != nullptr) {
				return std::addressof(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		const _Ty* operator ->()const&& {
			if (ptr != nullptr) {
				return std::addressof(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		//
		list_node_const_iterator operator +(std::size_t counter)const noexcept {
			list_node* curr{ ptr };
			for (std::size_t i = 0; i < counter; i++) {
				if (curr != nullptr)curr = curr->next;
				else break;
			}
			return list_node_const_iterator{ curr };
		}
		friend list_node_const_iterator operator +(std::size_t counter, const
			list_node_const_iterator& it) noexcept {
			return it + counter;
		}
		//
		list_node_const_iterator operator --()noexcept {
			if (ptr != nullptr) {
				ptr = ptr->prev;
			}
			return list_node_const_iterator{ ptr };
		}
		//
		list_node_const_iterator operator--(int)noexcept {
			list_node_const_iterator tmp{ ptr };
			if (ptr != nullptr) {
				ptr = ptr->prev;
			}
			return tmp;
		}
		//
		list_node_const_iterator operator-(std::size_t counter)const noexcept {
			list_node* curr{ ptr };
			for (std::size_t i = 0; i < counter; i++) {
				if (curr != nullptr)curr = curr->prev;
				else break;
			}
			return list_node_const_iterator{ curr };
		}
		//
		list_node_const_iterator operator -=(std::size_t counter)noexcept {
			for (std::size_t i = 0; i < counter; i++) {
				if (ptr != nullptr)ptr = ptr->prev;
				else break;
			}
			return list_node_const_iterator{ ptr };
		}
		//
		list_node_const_iterator operator =(const list_node_const_iterator& other)noexcept {
			ptr = other.ptr;
			return *this;
		}
		//
		list_node_const_iterator operator =(list_node_const_iterator&& other)noexcept {
			ptr = other.ptr;
			return *this;
		}
		//
		~list_node_const_iterator()noexcept {
			ptr = nullptr;
		}
	};
	//list_noder_reverse_iterator it has the same 
	//methods as the other iterators with some differences
	//first the operator ++ makes the iterator go backwards not forward
	//it supports the operator != and == and the operators * and ->
	//second it supports the operator += which again makes the iterator go backwards
	//because its a reverse iterator 
	//operator + return a temporary iterator .operator -- in that case make the iterator
	//go forward now (its reverse iterator),operator - same case 
	//also remember this iterator class pretty much is a wrapper around a list node
	//pointer so every operation modifies the pointer or uses it for something 
	class list_node_reverse_iterator final {
	private:
		list_node* ptr;
		friend double_linked_list<_Ty>;
	public:
		//
		list_node_reverse_iterator()noexcept :ptr{} {}
		//
		list_node_reverse_iterator(list_node* ptr1)noexcept :ptr{ ptr1 } {}
		//
		list_node_reverse_iterator(const list_node_reverse_iterator& other)noexcept = default;
		//
		list_node_reverse_iterator(list_node_reverse_iterator&& other)noexcept = default;
		//
		list_node_reverse_iterator operator++()noexcept {
			if (ptr != nullptr) {
				ptr = ptr->prev;
			}
			return list_node_reverse_iterator{ ptr };
		}
		//
		list_node_reverse_iterator operator++(int)noexcept {
			list_node_reverse_iterator tmp{ ptr };
			if (ptr != nullptr) {
				ptr = ptr->prev;
			}
			return tmp;
		}
		//
		bool operator !=(const list_node_reverse_iterator& other)const noexcept {
			return ptr != other.ptr;
		}
		//
		bool operator ==(const list_node_reverse_iterator& other)const noexcept {
			return ptr == other.ptr;
		}
		//
		const _Ty& operator *()const& {
			if (ptr != nullptr) {
				return ptr->data;
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		_Ty& operator *()& {
			if (ptr != nullptr) {
				return ptr->data;
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		const _Ty&& operator *()const&& {
			if (ptr != nullptr) {
				return std::move(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		_Ty&& operator *()&& {
			if (ptr != nullptr) {
				return std::move(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		list_node_reverse_iterator operator+=(std::size_t counter)noexcept {
			for (std::size_t i = 0; i < counter; i++) {
				if (ptr != nullptr)ptr = ptr->prev;
				else break;
			}
			return list_node_reverse_iterator{ ptr };
		}
		//
		const _Ty* operator ->()const& {
			if (ptr != nullptr) {
				return std::addressof(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		_Ty* operator ->()& {
			if (ptr != nullptr) {
				return std::addressof(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		const _Ty* operator ->()const&& {
			if (ptr != nullptr) {
				return std::addressof(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		_Ty* operator ->()&& {
			if (ptr != nullptr) {
				return std::addressof(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		list_node_reverse_iterator operator +(std::size_t counter)const noexcept {
			list_node* curr{ ptr };
			for (std::size_t i = 0; i < counter; i++) {
				if (curr != nullptr)curr = curr->prev;
				else break;
			}
			return list_node_reverse_iterator{ curr };
		}
		//
		friend list_node_reverse_iterator operator+(std::size_t counter, const
			list_node_reverse_iterator& it)noexcept {
			return it + counter;
		}
		//
		list_node_reverse_iterator operator --()noexcept {
			if (ptr != nullptr) {
				ptr = ptr->next;
			}
			return list_node_reverse_iterator{ ptr };
		}
		//
		list_node_reverse_iterator operator--(int)noexcept {
			list_node_reverse_iterator tmp{ ptr };
			if (ptr != nullptr) {
				ptr = ptr->next;
			}
			return tmp;
		}
		//
		list_node_reverse_iterator operator-(std::size_t counter)const noexcept {
			list_node* curr{ ptr };
			for (std::size_t i = 0; i < counter; i++) {
				if (curr != nullptr)curr = curr->next;
				else break;
			}
			return list_node_reverse_iterator{ curr };
		}
		//
		list_node_reverse_iterator operator -=(std::size_t counter)noexcept {
			for (std::size_t i = 0; i < counter; i++) {
				if (ptr != nullptr)ptr = ptr->next;
				else break;
			}
			return list_node_reverse_iterator{ ptr };
		}
		//
		list_node_reverse_iterator operator =(const list_node_reverse_iterator& other)noexcept {
			ptr = other.ptr;
			return *this;
		}
		//
		list_node_reverse_iterator operator =(list_node_reverse_iterator&& other)noexcept {
			ptr = other.ptr;
			return *this;
		}
		//
		~list_node_reverse_iterator()noexcept {
			ptr = nullptr;
		}
	};
	//list_noder_const_reverse_iterator it has the same 
	//methods as the other iterators with some differences
	//first the operator ++ makes the iterator go backwards not forward
	//it supports the operator != and == and the operators * and ->
	//second it supports the operator += which again makes the iterator go backwards
	//because its a reverse iterator 
	//operator + return a temporary iterator .operator -- in that case make the iterator
	//go forward now (its reverse iterator),operator - same case 
	//also remember this iterator class pretty much is a wrapper around a list node
	//pointer so every operation modifies the pointer or uses it for something 
	//also note that this iterator only gives the item for reading not for changing it
	class list_node_const_reverse_iterator final {
	private:
		list_node* ptr;
		friend double_linked_list<_Ty>;
	public:
		//
		list_node_const_reverse_iterator()noexcept :ptr{} {}
		//
		list_node_const_reverse_iterator(list_node* ptr1)noexcept :ptr{ ptr1 } {}
		//
		list_node_const_reverse_iterator(const list_node_const_reverse_iterator& other)noexcept = default;
		//
		list_node_const_reverse_iterator(list_node_const_reverse_iterator&& other)noexcept = default;
		//
		list_node_const_reverse_iterator operator++()noexcept {
			if (ptr != nullptr) {
				ptr = ptr->prev;
			}
			return list_node_const_reverse_iterator{ ptr };
		}
		//
		list_node_const_reverse_iterator operator++(int)noexcept {
			list_node_const_reverse_iterator tmp{ ptr };
			if (ptr != nullptr) {
				ptr = ptr->prev;
			}
			return tmp;
		}
		//
		bool operator !=(const list_node_const_reverse_iterator& other)const noexcept {
			return ptr != other.ptr;
		}
		//
		bool operator ==(const list_node_const_reverse_iterator& other)const noexcept {
			return ptr == other.ptr;
		}
		//
		const _Ty& operator *()const& {
			if (ptr != nullptr) {
				return ptr->data;
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		const _Ty&& operator *()const&& {
			if (ptr != nullptr) {
				return std::move(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		list_node_const_reverse_iterator operator+=(std::size_t counter)noexcept {
			for (std::size_t i = 0; i < counter; i++) {
				if (ptr != nullptr)ptr = ptr->prev;
				else break;
			}
			return list_node_const_reverse_iterator{ ptr };
		}
		//
		const _Ty* operator ->()const& {
			if (ptr != nullptr) {
				return std::addressof(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		const _Ty* operator ->()const&& {
			if (ptr != nullptr) {
				return std::addressof(ptr->data);
			}
			throw tried_to_access_an_empty_iterator_{ "tried to access an empty iterator" };
		}
		//
		list_node_const_reverse_iterator operator +(std::size_t counter)const noexcept {
			list_node* curr{ ptr };
			for (std::size_t i = 0; i < counter; i++) {
				if (curr != nullptr)curr = curr->prev;
				else break;
			}
			return list_node_const_reverse_iterator{ curr };
		}
		//
		friend list_node_const_reverse_iterator operator+(std::size_t counter,
			const list_node_const_reverse_iterator& it)noexcept {
			return it + counter;
		}
		//
		list_node_const_reverse_iterator operator --()noexcept {
			if (ptr != nullptr) {
				ptr = ptr->next;
			}
			return list_node_const_reverse_iterator{ ptr };
		}
		//
		list_node_const_reverse_iterator operator--(int)noexcept {
			list_node_const_reverse_iterator tmp{ ptr };
			if (ptr != nullptr) {
				ptr = ptr->next;
			}
			return tmp;
		}
		//
		list_node_const_reverse_iterator operator-(std::size_t counter)const noexcept {
			list_node* curr{ ptr };
			for (std::size_t i = 0; i < counter; i++) {
				if (curr != nullptr)curr = curr->next;
				else break;
			}
			return list_node_const_reverse_iterator{ curr };
		}
		//
		list_node_const_reverse_iterator operator -=(std::size_t counter)noexcept {
			for (std::size_t i = 0; i < counter; i++) {
				if (ptr != nullptr)ptr = ptr->next;
				else break;
			}
			return list_node_const_reverse_iterator{ ptr };
		}
		//
		list_node_const_reverse_iterator operator =(const list_node_const_reverse_iterator& other)noexcept {
			ptr = other.ptr;
			return *this;
		}
		//
		list_node_const_reverse_iterator operator =(list_node_const_reverse_iterator&& other)noexcept {
			ptr = other.ptr;
			return *this;
		}
		//
		~list_node_const_reverse_iterator()noexcept {
			ptr = nullptr;
		}
	};
	//start func done//
	list_node_iterator start()const noexcept {
		//start of the list 
		return head;
	}
	//start func done//
	list_node_iterator start()noexcept {
		//start of the list 
		return head;
	}
	//finish func done// 
	list_node_iterator finish()noexcept {
		//end of the list
		return nullptr;
	}
	//finish func done// 
	list_node_iterator finish()const noexcept {
		//end of the list 
		return nullptr;
	}
	//cstart func done// 
	list_node_const_iterator cstart()const noexcept {
		//start of the list 
		return head;
	}
	//cstart func done// 
	list_node_const_iterator cstart()noexcept {
		//start of the list 
		return head;
	}
	//cfinish func done// 
	list_node_const_iterator cfinish()noexcept {
		//end of the list
		return nullptr;
	}
	//cfinish func done// 
	list_node_const_iterator cfinish()const noexcept {
		//end of the list 
		return nullptr;
	}
	//rstart func done// 
	list_node_reverse_iterator rstart()const noexcept {
		//end of the list 
		return tail;
	}
	//rstart func done// 
	list_node_reverse_iterator rstart()noexcept {
		//end of the list 
		return tail;
	}
	//rfinish func done//
	list_node_reverse_iterator rfinish()noexcept {
		//end of the list from backwards prespective
		return nullptr;
	}
	//rfinish func done// 
	list_node_reverse_iterator rfinish()const noexcept {
		//end of the list from backwards prespective 
		return nullptr;
	}
	//crstart func done// 
	list_node_const_reverse_iterator crstart()const noexcept {
		//end of the list 
		return tail;
	}
	//crstart func done// 
	list_node_const_reverse_iterator crstart()noexcept {
		//end of the list 
		return tail;
	}
	//crfinish func done// 
	list_node_const_reverse_iterator crfinish()noexcept {
		//end of the list from backwards prespective
		return nullptr;
	}
	//crfinish func done// 
	list_node_const_reverse_iterator crfinish()const noexcept {
		//end of the list from backwards prespective 
		return nullptr;
	}
	//private members:
	list_node* head;
	list_node* tail;
	std::size_t count;
	//
	//push_back_node func done// 
	template<class _Valty>
	bool push_back_node(_Valty&& _Val) {
		//this function simply pushes a new node at the end of the list
		//if the list is empty ptr is the only node show ptr->prev=nullptr
		//because tail =nullptr head=tail=ptr;count++;
		//if the list is not empty tail->next=new node ptr->prev=tail tail=ptr count++
		list_node* ptr{ new (std::nothrow)list_node{std::forward<_Valty>(_Val)} };
		if (ptr != nullptr) {
			ptr->prev = tail;
			if (head == nullptr) {
				head = ptr;
			}
			else {
				tail->next = ptr;
			}
			tail = ptr;
			count++;
			return true;
		}
		return false;
	}
	//push_front_func done//
	template<typename _Valty>
	bool push_front_node(_Valty&& _Val) {
		//this functions simply pushes a new node at the start of the list
		//if the list is empty ptr->next=nullptr which is head, head=tail=ptr count++;
		//if the list is not empty ptr->next=head head->prev=ptr head=ptr count++;
		list_node* ptr{ new(std::nothrow)list_node{std::forward<_Valty>(_Val)} };
		if (ptr != nullptr) {
			ptr->next = head;
			if (head == nullptr) {
				tail = ptr;
			}
			else {
				head->prev = ptr;

			}
			head = ptr;
			count++;
			return true;
		}
		return false;
	}
	//pop_front func done//
	void pop_front_node() {
		//this func is very simple all it does is delete the first node in the list
		//if the list is empty it throws, if it has one node
		//then head=head->next delete ptr head=nullptr tail =nullptr and count --;
		//if it has more than one head=head->next delete ptr head->prev=nullptr count--;
		static_assert(std::is_nothrow_destructible_v<_Ty>, "the type _Ty must be"
			"destructible without throwing");
		if (count != 0) {
			list_node* ptr{ head };
			head = head->next;
			delete ptr;
			if (head == nullptr) {
				tail = nullptr;
			}
			else {
				head->prev = nullptr;
			}
			count--;
			return;
		}
		throw pop_from_an_empty_list{ "tried to pop from an empty list" };

	}
	//pop_back_node func done// 
	void pop_back_node() {
		//if the list is empty throws
		//if the list has one node tail=tail->prev which is nullptr and head=nullptr 
		//and delete ptr and count--;
		//if the list has two or more nodes tail=tail->prev; tail->next=nullpt delete ptr;
		//count--;
		static_assert(std::is_nothrow_destructible_v<_Ty>, "the type _Ty must be"
			"destructible without throwing");
		if (count != 0) {
			list_node* ptr{ tail };
			tail = tail->prev;
			if (tail == nullptr) {
				head = nullptr;

			}
			else {
				tail->next = nullptr;
			}
			delete ptr;
			count--;
			return;
		}
		throw pop_from_an_empty_list{ "tried to pop from an empty list" };
	}
	//clear func done//
	void clear()noexcept {
		//this is the destructor pretty much 
		//every time we keep the node with ptr move the head and then delete it 
		static_assert(std::is_nothrow_destructible_v<_Ty>, "the type must be"
			"destructible without throwing");
		list_node* ptr{};
		while (head != nullptr) {
			ptr = head;
			head = head->next;
			delete ptr;
		}
		count = 0;
		tail = nullptr;
	}
	//reverse_double_linked_list func done//
	void reverse_double_linked_list()noexcept {
		//this func pretty much reverses the list 
		//we pretty much everytime take a node and move it to the start 
		//and make head point to it and then take the next 
		//like this:
		//12345->21345->32145->43215->54321
		if (count < 2)return;
		tail = head;
		list_node* ptr1{ head };
		list_node* ptr2{ head->next };
		while (ptr2 != nullptr) {
			ptr1->next = ptr2->next;
			if (ptr2->next != nullptr) {
				ptr2->next->prev = ptr1;
			}
			ptr2->next = head;
			head->prev = ptr2;
			ptr2->prev = nullptr;
			head = ptr2;

			ptr2 = ptr1->next;


		}
		return;
	}
	//emplace_back_node func done// 
	template<class ..._Valty>
	bool emplace_back_node(_Valty&&..._Val) {
		//emplace_back_node pretty much is the same with push
		//the only difference is that we construct the data hold by list_node in place
		list_node* ptr = list_node::craft(std::forward<_Valty>(_Val)...);
		if (ptr != nullptr) {
			ptr->prev = tail;
			if (head == nullptr) {
				head = ptr;
			}
			else {
				tail->next = ptr;
			}
			tail = ptr;
			count++;
			return true;
		}
		return false;
	}
	//emplace_front_node func done// 
	template<class ..._Valty>
	bool emplace_front_node(_Valty&&..._Val) {
		//emplace_front_node pretty much is the same with push
		//the only difference is that we construct the data hold by list_node in place
		list_node* ptr = list_node::craft(std::forward<_Valty>(_Val)...);
		if (ptr != nullptr) {
			ptr->next = head;
			if (head == nullptr) {
				tail = ptr;
			}
			else {
				head->prev = ptr;

			}
			head = ptr;
			count++;
			return true;
		}
		return false;
	}
	//insert func done// 
	bool insert(list_node_const_iterator pos, const _Ty& data) {
		//this is an insert function
		//there are three scenarios
		//pos==cend() or point to an empty list
		//so don't do anything
		// 1)pos points to a node of other list or a deallocated node so the func throws
		//2)pos points to our list in that case we insert the element successfuly
		if (pos == cend()) {//no valid pos no insertion
			return false;
		}
		list_node* curr{ head };
		bool is_valid = false;
		while (curr != nullptr) {
			if (curr == pos.ptr)is_valid = true;//we see if the pos.ptr address is the same
			//with the nodes of our list if it is not then it is not a valid pos 
			curr = curr->next;
		}
		if (!is_valid) {
			throw not_a_valid_position{ "tried to insert element at an invalid"
								"position" };
		}
		list_node* ptr{ new (std::nothrow)list_node{data} };
		if (ptr == nullptr)return false;
		//we insert the node after the position simple
		//doesn't matter where the pos is we insert it either somewhere in the middle
		//or at the end no difference this code handles both scenarios
		//if we are in middle we make the first if no need to change tail
		//if we are at the end we change tail simply 
		count++;
		ptr->next = pos.ptr->next;
		if (pos.ptr->next != nullptr) {
			pos.ptr->next->prev = ptr;
		}
		else {
			tail = ptr;
		}
		pos.ptr->next = ptr;
		ptr->prev = pos.ptr;
		return true;
	}
	//add_unique func done//
	template<typename _Pred1>
	bool add_unique(list_node_const_iterator pos, const _Ty& data, _Pred1 _Pred) {
		//this function pretty much uses the same tactic as the insert function above
		//the only difference is that we check if the element is in the list 
		//if it is not then we insert it
		//this function takes a _Pred arg with default value std::equal_to<>{}
		// that is used in order to compare
		//this _Pred must be a func that can be called with two const _Ty& args 
		//and the return type must be bool else the behavior is undefined
		if (pos == cend()) {//no valid pos no insertion
			return false;
		}
		list_node* curr{ head };
		bool  is_valid = false;
		while (curr != nullptr) {
			if (curr == pos.ptr)is_valid = true;//we see if the pos.ptr address is the same
			//with the nodes of our list if it is not then it is not a valid pos 
			curr = curr->next;
		}
		if (!is_valid) {
			throw not_a_valid_position{ "tried to insert element at an invalid"
								"position" };
		}
		curr = head;
		while (curr != nullptr) {
			if (_Pred(std::as_const(curr->data), std::as_const(data)))return false;
			curr = curr->next;
		}
		list_node* ptr{ new (std::nothrow)list_node{data} };
		if (ptr == nullptr)return false;
		//we insert the node after the position simple
		//doesn't matter where the pos is we insert it either somewhere in the middle
		//or at the end no difference this code handles both scenarios
		//if we are in middle we make the first if no need to change tail
		//if we are at the end we change tail simply 
		count++;
		ptr->next = pos.ptr->next;
		if (pos.ptr->next != nullptr) {
			pos.ptr->next->prev = ptr;
		}
		else {
			tail = ptr;
		}
		pos.ptr->next = ptr;
		ptr->prev = pos.ptr;
		return true;
	}
	//erase_node_if func done// 
	template<typename _Pred1>
	void erase_node_if(_Pred1 _Pred) {
		//this func in simple terms deletes an element from a list
		//if a certain condition is met  that you gave as an argument
		//the remove_if which uses the pred
		//generally both methods remove and remove_if call the erase_node_if
		//with a pred the remove passes a simple lambda that checks if the ->data
		//is equal to the value you gave 
		static_assert(std::is_nothrow_destructible_v<_Ty>, "the type must be"
			"destructible without throwing");
		//the pred func should be able to be called with one const _Ty& arg
		//and the return type of this func should be bool or else the behavior
		//is undefined
		//if you keep finding the element at the start delete it 
		while (head != nullptr && _Pred(std::as_const(head->data))) {
			pop_front();
		}//empty or still have elements
		if (head != nullptr) {//still have elements if head==nullptr then zero elements
			list_node* prev{ head };//we know that head doesn't satisfy the pred
			list_node* curr{ head->next };//with curr and the rest of list we check
			//if the pred is satisfied
			while (curr != nullptr) {
				if (_Pred(std::as_const(curr->data))) {
					//the pred is satisfied we must erase the element
					//don't forget to connect the nodes not to 
					// lose the rest of the list
					prev->next = curr->next;
					if (curr->next != nullptr) {//if it is nullptr we have tail node
						//so we dont do this line if we have a tail node simple
						curr->next->prev = prev;
					}
					delete curr;
					curr = prev->next;
					count--;
				}
				else {
					prev = curr;
					curr = curr->next;
				}
			}//prev will always show at the tail when curr==nullptr
			tail = prev;
		}
	}
	//delete_duplicates func done//
	template<typename _Pred1>
	void delete_duplicates(_Pred1 _Pred) {
		//this func simply does two things
		//it is called by two funcs one that uses the std::equal_to<>() in order
		//to compare elements with the operator ==
		//and the other uses a pred to compare the elements if they are equal 
		//the _Pred func should be able to be called with two const _Ty& args
		//and the return type of this func should be bool or else the behavior is
		//undefined
		static_assert(std::is_nothrow_destructible_v<_Ty>, "the type must be"
			"destructible without throwing");
		//we pretty much have to pointers prev,curr
		//prev show at head and curr to head ->next
		//and we compare those pointers until curr ==nullptr 
		//whenever we encouter two equals based on pred we delete them and progress only 
		//curr else we progress curr and prev this func only works good if the results 
		//are sorted in ascending order otherwise we might want to use a hashset in order
		//to keep track of the elements 
		if (count < 2)return;
		list_node* prev{ head };
		list_node* curr{ head->next };
		while (curr != nullptr) {
			if (_Pred(std::as_const(prev->data), std::as_const(curr->data))) {//duplicate put out
				prev->next = curr->next;
				if (curr->next != nullptr) {//if it is nullptr we have tail node
					//so we dont do this line if we have a tail node simple
					curr->next->prev = prev;
				}
				delete curr;
				curr = prev->next;
				count--;
			}
			else {
				prev = curr;
				curr = curr->next;
			}
		}
		tail = prev;//dont forget to update tail, prev will always show to the tail after this 
		//because curr will be nullptr 
		return;
	}
	//is_ascending_ func done//
	template<typename Compare>
	bool is_ascending_(Compare comp)const {
		//this is a func that takes a comparator in order to compare the elements
		//and determine if they are sorted in ascending order
		//we use the method curr,prev in order to compare its element
		//the default value of the comparator is std::less_equal<>{}
		//the comp func should be a func that can be called by two args const _Ty&
		//and const _Ty& and the return type should be bool else the behavior is undefined
		if (count < 2)return true;
		list_node* prev{ head };
		list_node* curr{ head->next };
		while (curr != nullptr && comp(std::as_const(prev->data), std::as_const(curr->data))) {
			prev = curr;
			curr = curr->next;
		}
		if (curr != nullptr)return false;//we are not at the end so not in ascending order
		return true;
	}
	//is_descending_ func done// 
	template<typename Compare>
	bool is_descending_(Compare comp)const {
		//this is a func that takes a comparator in order to compare the elements
		//and determine if they are sorted in descending order
		//we use the method curr,prev in order to compare its element
		//the default value of the comparator is std::greater_equal<>{}
		//the comp func should be a func that can be called by two args const _Ty&
		//and const _Ty& and the return type should be bool else the behavior is undefined
		if (count < 2)return true;
		list_node* prev{ head };
		list_node* curr{ head->next };
		while (curr != nullptr && comp(std::as_const(prev->data), std::as_const(curr->data))) {
			prev = curr;
			curr = curr->next;
		}
		if (curr != nullptr)return false;
		return true;
	}
	//is_sorted_ func done 
	template<typename Compare1, typename Compare2>
	bool is_sorted_(Compare1 comp1, Compare2 comp2)const {
		//this is a func that takes two comparators in order to compare the elements
		//and determine if they are sorted in descending  and ascending order
		//we use the method curr,prev in order to compare its element
		//the default values of the comparators is std::less_equal<>{} and 
		// std::greater_equal<>{}
		//the comp funcs should be funcs that can be called by two args const _Ty&
		//and const _Ty& and the return type should be bool else the behavior is undefined
		if (count < 2)return true;
		list_node* prev{ head };
		list_node* curr{ head->next };
		bool asc = true;
		bool desc = true;
		//this checks in one pass if they are sorted
		while (curr != nullptr) {
			asc = asc && comp1(std::as_const(prev->data), std::as_const(curr->data));//<=
			desc = desc && comp2(std::as_const(prev->data), std::as_const(curr->data));//>=
			prev = curr;
			curr = curr->next;
		}
		return asc || desc;
	}
	//merge_lists func done//
	template<typename Compare>
	void merge_lists(double_linked_list<_Ty>& other, Compare comp) {
		static_assert(std::is_nothrow_destructible_v<_Ty>, "the type must be destructible without throwing");
		//this func simply merges two sorted lists in ascending order
		//the rules are simple we can't merge to ourselves
		//the other must not by empty whats the point
		//both must be in ascending order
		//this func uses a comparator in order to compare elements 
		//the default comparator is std::less_equal<>{} 
		//we create a new dummy list and we grow it with our elements
		//when the progress ends the other list points to nothing while this
		//point to the new list the node call Head is to make the code a little bit 
		//easier ,we take its elements from the lists and we compare ,the minimum goes first
		//then we advnace and then the next minimum beetween the two lists and then the next
		//the comp func should be a func that can be called by two args const _Ty&
		//and const _Ty& and the return type should be bool else the behavior is undefined
		if (this == &other)return;
		if (other.empty())return;
		if (!is_ascending_(comp) || !other.is_ascending_(comp))return;
		count += other.count;
		list_node* Head{ new (std::nothrow)list_node{} };
		if (Head == nullptr)return;
		list_node* ptr{ Head };
		list_node* curr1{ head };
		list_node* curr2{ other.head };
		while (curr1 != nullptr && curr2 != nullptr) {
			if (comp(std::as_const(curr1->data), std::as_const(curr2->data))) {
				ptr->next = curr1;
				curr1->prev = ptr;
				ptr = ptr->next;
				curr1 = curr1->next;
			}
			else {
				ptr->next = curr2;
				curr2->prev = ptr;
				ptr = ptr->next;
				curr2 = curr2->next;
			}
		}
		//whatever left we just give it because we now have only onel list
		if (curr1 == nullptr && curr2 != nullptr) {
			ptr->next = curr2;
			curr2->prev = ptr;
			tail = other.tail; //dont forget the tail
		}
		if (curr2 == nullptr && curr1 != nullptr) {
			ptr->next = curr1;
			curr1->prev = ptr;
			//the tail already points where we want it to be
		}
		head = Head->next;
		delete Head;//don't forget to delete the extra node
		other.head = other.tail = nullptr;
		other.count = 0;

	}
public:
	using iterator = list_node_iterator;
	using const_iterator = list_node_const_iterator;
	using reverse_iterator = list_node_reverse_iterator;
	using const_reverse_iterator = list_node_const_reverse_iterator;
	static_assert(std::is_object_v<_Ty>, "The C++ Standard forbids container adaptors of non-object types "
		"because of [container.requirements].");
	static_assert(!std::is_reference_v<_Ty>, "no references allowed");
	static_assert(!std::is_const_v<_Ty>, "no const types are allowed");
	static_assert(!std::is_volatile_v<_Ty>, "no volatile types are allowed");
	//
	double_linked_list()noexcept;
	//
	double_linked_list(const std::initializer_list<_Ty>& other);
	//
	double_linked_list(const double_linked_list<_Ty>& other);
	//
	double_linked_list(double_linked_list<_Ty>&& other)noexcept;
	//
	double_linked_list<_Ty>& operator =(double_linked_list<_Ty>&& other) & noexcept;
	//
	double_linked_list<_Ty>& operator =(const std::initializer_list<_Ty>& other)&;
	//
	double_linked_list<_Ty>& operator =(const double_linked_list<_Ty>& other)&;
	//
	bool push_back(const _Ty& data);
	//
	bool push_back(_Ty&& data);
	//
	bool insert_after(const_iterator pos, const _Ty& data);
	//
	bool add_unique_after(const_iterator pos, const _Ty& data);
	//
	template<typename _Pred1>
	bool add_unique_after(const_iterator pos, const _Ty& data, _Pred1 _Pred);
	//
	bool push_front(const _Ty& data);
	//
	template<class..._Valty>
	bool emplace_back(_Valty&&..._Val);
	//
	template<class..._Valty>
	bool emplace_front(_Valty&&..._Val);
	//
	bool push_front(_Ty&& data);
	//
	void pop_front();
	//
	void pop_back();
	//
	void show()const;
	//
	void reverse()noexcept;
	//
	void remove(const _Ty& data);
	//
	template<typename _Pred1>
	void remove_if(_Pred1 _Pred);
	//
	void unique();
	//
	template<typename _Pred1>
	void unique(_Pred1 _Pred);
	//
	void swap(double_linked_list<_Ty>& other)noexcept;
	//
	bool is_ascending()const;
	//
	template<typename Compare>
	bool is_ascending(Compare comp)const;
	//
	bool is_descending()const;
	//
	void merge(double_linked_list<_Ty>& other);
	//
	void merge(double_linked_list<_Ty>&& other);
	//
	template<typename Compare>
	void merge(double_linked_list<_Ty>& other, Compare comp);
	//
	template<typename Compare>
	void merge(double_linked_list<_Ty>&& other, Compare comp);
	//
	template<typename Compare>
	bool is_descending(Compare comp)const;
	//
	bool is_sorted()const;
	//
	template<typename Compare1, typename Compare2 >
	bool is_sorted(Compare1 comp1, Compare2 comp2)const;
	//
	~double_linked_list()noexcept;
	bool empty()const noexcept {
		//checs if the list is empty 
		return count == 0;
	}
	//
	std::size_t size()const noexcept {
		//it just shows the number of nodes the list currently has 
		return count;
	}
	//
	_NODISCARD _Ty&& back()&& {
		if (count == 0) {
			throw tried_to_access_an_empty_list_{ "tried to access  an empty list" };
		}
		return std::move(tail->data);

	}
	//
	_NODISCARD const _Ty&& back()const&& {
		if (count == 0) {
			throw tried_to_access_an_empty_list_{ "tried to access  an empty list" };
		}
		return std::move(tail->data);

	}
	//
	_NODISCARD const _Ty& back()const& {
		if (count == 0) {
			throw tried_to_access_an_empty_list_{ "tried to access  an empty list" };
		}
		return tail->data;

	}
	//
	_NODISCARD _Ty& back()& {
		if (count == 0) {
			throw tried_to_access_an_empty_list_{ "tried to access  an empty list" };
		}
		return tail->data;

	}
	//
	_NODISCARD const _Ty& front()const& {
		if (count == 0) {
			throw tried_to_access_an_empty_list_{ "tried to access  an empty list" };
		}
		return head->data;

	}
	//
	_NODISCARD _Ty& front()& {
		if (count == 0) {
			throw tried_to_access_an_empty_list_{ "tried to access  an empty list" };
		}
		return head->data;

	}
	//
	_NODISCARD _Ty&& front()&& {
		if (count == 0) {
			throw tried_to_access_an_empty_list_{ "tried to access  an empty list" };
		}
		return std::move(head->data);

	}
	//
	_NODISCARD const _Ty&& front()const&& {
		if (count == 0) {
			throw tried_to_access_an_empty_list_{ "tried to access  an empty list" };
		}
		return std::move(head->data);

	}
	//begin func done// 
	iterator begin()const noexcept {
		return start();
	}
	//begin func done// 
	iterator begin()noexcept {
		return start();
	}
	//end func done// 
	iterator end()const noexcept {
		return finish();
	}
	//end func done// 
	iterator end() noexcept {
		return finish();
	}
	//begin func done //
	const_iterator cbegin()const noexcept {
		return cstart();
	}
	//begin func done// 
	const_iterator cbegin()noexcept {
		return cstart();
	}
	//end func done// 
	const_iterator cend()const noexcept {
		return cfinish();
	}
	//end func done// 
	const_iterator cend() noexcept {
		return cfinish();
	}
	//rbegin func done// 
	reverse_iterator rbegin()noexcept {
		return rstart();
	}
	//rbegin func done// 
	reverse_iterator rbegin()const noexcept {
		return rstart();
	}
	//rend func done// 
	reverse_iterator rend()const noexcept {
		return rfinish();
	}
	//rend func done// 
	reverse_iterator rend() noexcept {
		return rfinish();
	}
	//crbegin func done// 
	const_reverse_iterator crbegin()noexcept {
		return crstart();
	}
	//crbegin func done// 
	const_reverse_iterator crbegin()const noexcept {
		return crstart();
	}
	//crend func done// 
	const_reverse_iterator crend()const noexcept {
		return crfinish();
	}
	//crend func done// 
	const_reverse_iterator crend() noexcept {
		return crfinish();
	}
	//unsafe_insert func done// 
	//use this func only for performance and when you 
	//know where the iterator points be very careful
	bool unsafe_insert(const_iterator pos, const _Ty& data) {
		//this is again an insert function which works pretty similar to 
		//to the insert after func but this func doesn't see if the pos you passed
		//is valid so only use this func if you know that the iterator that you passed 
		// points to the list that called the method and also points to an element of this list
		// not to nothing 
		//make sure pretty much that the iterator is valid or else the behavior is
		//undefined
		if (pos == cend()) {//no valid pos no insertion
			return false;
		}
		list_node* ptr{ new (std::nothrow)list_node{data} };
		if (ptr == nullptr)return false;
		//we insert the node after the position simple
		//doesn't matter where the pos is we insert it either somewhere in the middle
		//or at the end no difference this code handles both scenarios
		//if we are in middle we make the first if no need to change tail
		//if we are at the end we change tail simply 
		count++;
		ptr->next = pos.ptr->next;
		if (pos.ptr->next != nullptr) {
			pos.ptr->next->prev = ptr;
		}
		else {
			tail = ptr;
		}
		pos.ptr->next = ptr;
		ptr->prev = pos.ptr;
		return true;
	}
};
//default constructor done//
template<typename _Ty>
double_linked_list<_Ty>::double_linked_list()noexcept
	:head{}, tail{}, count{}
{
}
//push_back func done//
template<typename _Ty>
bool double_linked_list<_Ty>::push_back(const _Ty& data) {
	return push_back_node(data);
}
//push_back func done//
template<typename _Ty>
bool double_linked_list<_Ty>::push_back(_Ty&& data) {
	return push_back_node(std::move(data));
}
//show func done//
template<typename _Ty>
void double_linked_list<_Ty>::show()const {
	list_node* ptr{ head };
	while (ptr != nullptr) {
		std::cout << ptr->data << " ";
		ptr = ptr->next;
	}
	std::cout << "\n\n";
	ptr = tail;
	while (ptr != nullptr) {
		std::cout << ptr->data << " ";
		ptr = ptr->prev;
	}
	std::cout << "\n\n";
	return;
}
//push_front func done//
template<typename _Ty>
bool double_linked_list<_Ty>::push_front(const _Ty& data) {
	return push_front_node(data);
}
//push_front func done// 
template<typename _Ty>
bool double_linked_list<_Ty>::push_front(_Ty&& data) {
	return push_front_node(std::move(data));
}
//pop_front func done//
template<typename _Ty>
void double_linked_list<_Ty>::pop_front() {
	pop_front_node();
}
//pop_back func done//
template<typename _Ty>
void double_linked_list<_Ty>::pop_back() {
	pop_back_node();
}
//destructor func done// 
template<typename _Ty>
double_linked_list<_Ty>::~double_linked_list()noexcept {
	clear();
}
//reverse func done//
template<typename _Ty>
void double_linked_list<_Ty>::reverse()noexcept {
	reverse_double_linked_list();
}
//swap func done//
template<typename _Ty>
void double_linked_list<_Ty>::swap(double_linked_list<_Ty>& other)noexcept {
	//this justs swaps the contents of two double linked lists
	//the main thing about this class is the members head,tail,count
	//if we swap to ourselves nothing happens
	if (this != &other) {
		std::swap(head, other.head);
		std::swap(tail, other.tail);
		std::swap(count, other.count);
	}
}
//constructor with initializer_list done//
template<typename _Ty>
double_linked_list<_Ty>::double_linked_list(const std::initializer_list<_Ty>& other)
	:head{}, tail{}, count{}
{
	const _Ty* ptr{ other.begin() };
	for (std::size_t i = 0; i < other.size(); i++) {
		if (!push_back(*ptr)) {
			clear();
			break;
		}
		ptr++;
	}

}
//copy constructor done// 
template<typename _Ty>
double_linked_list<_Ty>::double_linked_list(const double_linked_list<_Ty>& other)
	:head{}, tail{}, count{}
{//this simply copies the contets of the other object
	//if this==&other nothing happens
	//if this!=&other then i other empty nothing happens
	//otherwise copy the contents of the other object
	list_node* curr{ other.head };
	while (curr != nullptr) {
		if (!push_back(curr->data)) {
			clear();
			break;
		}
		curr = curr->next;
	}
}
//move constructor done//
template<typename _Ty>
double_linked_list<_Ty>::double_linked_list(double_linked_list<_Ty>&& other)noexcept
	:head{}, tail{}, count{}
{//if this==&other then swaps nullptr's and 0's no problem 
	//if this !=&other if other is empty same as case as previous
	//if this!=&other and other not empty simply steal his contets
	//and giving him the default state 
	std::swap(head, other.head);
	std::swap(tail, other.tail);
	std::swap(count, other.count);
}
//emplace_back func done// 
template<typename _Ty>
template<class..._Valty>
bool double_linked_list<_Ty>::emplace_back(_Valty&&..._Val) {
	return emplace_back_node(std::forward<_Valty>(_Val)...);
}
//emplace_front func done// 
template<typename _Ty>
template<class..._Valty>
bool double_linked_list<_Ty>::emplace_front(_Valty&&..._Val) {
	return emplace_front_node(std::forward<_Valty>(_Val)...);
}
//move operator done//
template<typename _Ty>
double_linked_list<_Ty>& double_linked_list<_Ty>::operator =(double_linked_list<_Ty>&& other) & noexcept
{
	//we just swap the pointer pretty much we steal the data
	//attention if we move to ourselves we lose our data 
	clear();
	std::swap(head, other.head);
	std::swap(tail, other.tail);
	std::swap(count, other.count);
	return *this;
}
//insert_after func done// 
template<typename _Ty>
bool double_linked_list<_Ty>::insert_after(const_iterator pos, const _Ty& data) {
	return insert(pos, data);
}
//add_unique_after done//
template<typename _Ty>
bool double_linked_list<_Ty>::add_unique_after(const_iterator pos, const _Ty& data) {
	return add_unique(pos, data, std::equal_to<>{});
}
//add_unique_after done//
template<typename _Ty>
template<typename _Pred1>
bool double_linked_list<_Ty>::add_unique_after(const_iterator pos, const _Ty& data,
	_Pred1 _Pred) {
	return add_unique(pos, data, _Pred);
}
//remove func done//
template<typename _Ty>
void double_linked_list<_Ty>::remove(const _Ty& data) {
	erase_node_if([&](const _Ty& _Other) -> bool { return _Other == data; });
}
//remove_if func done//
template<typename _Ty>
template<typename _Pred1>
void double_linked_list<_Ty>::remove_if(_Pred1 _Pred) {
	erase_node_if(_Pred);
}
//unique func done//
template<typename _Ty>
void double_linked_list<_Ty>::unique() {
	delete_duplicates(std::equal_to<>{});
}
//unique func done//
template<typename _Ty>
template<typename _Pred1>
void double_linked_list<_Ty>::unique(_Pred1 _Pred) {
	delete_duplicates(_Pred);
}
//is_ascending func done//
template<typename _Ty>
bool double_linked_list<_Ty>::is_ascending()const {
	return is_ascending_(std::less_equal<>{});
}
//is_ascending func done// 
template<typename _Ty>
template<typename Compare>
bool double_linked_list<_Ty>::is_ascending(Compare comp)const {
	return is_ascending_(comp);
}
//is_descending func done// 
template<typename _Ty>
bool double_linked_list<_Ty>::is_descending()const {
	return is_descending_(std::greater_equal<>{});
}
//is_descending func done//
template<typename _Ty>
template<typename Compare>
bool double_linked_list<_Ty>::is_descending(Compare comp)const {
	return is_descending_(comp);
}
//is_sorted func done// 
template<typename _Ty>
bool double_linked_list<_Ty>::is_sorted()const {
	return is_sorted_(std::less_equal<>{}, std::greater_equal<>{});
}
//is_sorted func done// 
template<typename _Ty>
template<typename Compare1, typename Compare2>
bool double_linked_list<_Ty>::is_sorted(Compare1 comp1, Compare2 comp2)const {
	return is_sorted_(comp1, comp2);
}
//copy operator with initializer list func done// 
template<typename _Ty>
double_linked_list<_Ty>& double_linked_list<_Ty>::
operator=(const std::initializer_list<_Ty>& other)& {
	//thats the copy with initializer list it works with the method prev curr
	//in order to avoid unecessary allocations
	//there 5 scenarios
	// we are empty so nothing happens
	//one of the lists is empty 
	//if this empty prev1==nullptr and other.size()!=0 and we go first if
	//if the other one is empty prev2==nullptr &&curr1!=nuullptr then we must call the destructor in the
	// second if 
	//if both have elements equally nothing happens we just copy the elements
	//if size>other.size we have extra nodes we should delete them so curr1!=nullptr
	//and curr2==other.end() show we go in the last if 
	//if size<other.size we have to allocate some new nodes so
	//curr1==nullptr and curr2!=other.end() show we go to the first if 
	list_node* prev1{ nullptr };
	list_node* curr1{ head };
	static_assert(std::is_copy_assignable_v<_Ty>, "you must be able to do this:"
		"curr1->data=*curr2");
	static_assert(std::is_nothrow_destructible_v<_Ty>, "the type must be destructible without throwing");
	const _Ty* prev2{ nullptr };
	const _Ty* curr2{ other.begin() };
	while (curr1 != nullptr && curr2 != other.end()) {
		curr1->data = *curr2;
		prev1 = curr1;
		curr1 = curr1->next;
		prev2 = curr2;
		curr2++;
	}
	if (prev1 == nullptr && other.size() != 0 || curr1 == nullptr && curr2 != other.end()) {
		while (curr2 != other.end()) {
			if (!push_back(*curr2)) {
				clear();
				break;
			}
			curr2++;
		}
		return *this;
	}
	if (prev2 == nullptr && curr1 != nullptr) {
		clear();
		return *this;
	}
	if (curr1 != nullptr && curr2 == other.end()) {
		tail = prev1;//new tail deallocate the other nodes that are not needed
		prev1->next = nullptr;
		list_node* ptr{ };
		while (curr1 != nullptr) {
			ptr = curr1;
			curr1 = curr1->next;
			delete ptr;
			count--;
		}
		return *this;
	}
	return *this;
}
//copy operator func done// 
template<typename _Ty>
double_linked_list<_Ty>& double_linked_list<_Ty>::operator=(const
	double_linked_list<_Ty>& other)& {
	//thats the copy operator it works with the method prev curr
	//in order to avoid unecessary allocations
	//there 5 scenarios
	// we are empty so nothing happens
	//one of the lists is empty 
	//if this empty prev1==nullptr and curr2!=nullptr and we go first if
	//if the other one is empty prev2==nullptr and curr1 != nullptr 
	// then we must call the destructor in the
	// second if 
	//if both have elements equally nothing happens we just copy the elements
	//if size>other.size we have extra nodes we should delete them so curr1!=nullptr
	//and curr2==nullptr show we go in the last if 
	//if size<other.size we have to allocate some new nodes so
	//curr1==nullptr and curr2!=nullptr show we go to the first if 
	static_assert(std::is_copy_assignable_v<_Ty>, "you must be able to make this operation"
		"curr1->data=curr2->data");
	static_assert(std::is_nothrow_destructible_v<_Ty>, "the type must be destructible without throwing");
	if (this != &other) {
		list_node* prev1{ nullptr };
		list_node* curr1{ head };
		list_node* prev2{ nullptr };
		list_node* curr2{ other.head };
		while (curr1 != nullptr && curr2 != nullptr) {
			curr1->data = curr2->data;
			prev1 = curr1;
			prev2 = curr2;
			curr1 = curr1->next;
			curr2 = curr2->next;
		}
		if (prev1 == nullptr && curr2 != nullptr || curr2 != nullptr && curr1 == nullptr) {
			while (curr2 != nullptr) {
				if (!push_back(curr2->data)) {
					clear();
					break;
				}
				curr2 = curr2->next;
			}
			return *this;
		}
		if (prev2 == nullptr && curr1 != nullptr) {
			clear();
			return *this;
		}
		if (curr1 != nullptr && curr2 == nullptr) {
			tail = prev1;//new tail deallocate the other nodes that are not needed
			prev1->next = nullptr;
			while (curr1 != nullptr) {
				list_node* ptr{ curr1 };
				curr1 = curr1->next;
				delete ptr;
				count--;
			}
			return *this;
		}
	}
	return *this;
}
//merge func done// 
template<typename _Ty>
template<typename Compare>
void double_linked_list<_Ty>::merge(double_linked_list<_Ty>& other, Compare comp) {
	merge_lists(other, comp);
}
//merge func done// 
template<typename _Ty>
template<typename Compare>
void double_linked_list<_Ty>::merge(double_linked_list<_Ty>&& other, Compare comp) {
	merge_lists(other, comp);
}
//merge func done// 
template<typename _Ty>
void double_linked_list<_Ty>::merge(double_linked_list<_Ty>& other) {
	merge_lists(other, std::less_equal<>{});
}
//merge func done//
template<typename _Ty>
void double_linked_list<_Ty>::merge(double_linked_list<_Ty>&& other) {
	merge_lists(other, std::less_equal<>{});
}
//
_PANAGIOTIS_END
