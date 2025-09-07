# 📚WELCOME TO THE DOUBLE_LINKED_LIST API 🌐:
# 🧩 Interface:
```markdown
```cpp
template<typename _Ty>
class double_linked_list final {
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
	bool erase_after(const_iterator pos);
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
	//unsafe_erase func done//
	//use this func only for performance and when you 
	//know where the iterator points be very careful
	bool unsafe_erase(const_iterator pos)noexcept {
		//this function works pretty similar to the erase_after function 
		//the only difference is that this func doesn't see if the pos you passed
		//is valid so only use this func if you know that the iterator that you passed 
		// points to the list that called the method and also points to an element of this list
		// not to nothing 
		//make sure pretty much that the iterator is valid or else the behavior is
		//undefined
		static_assert(std::is_nothrow_destructible_v<_Ty>, "the type must be"
			"destructible without throwing");
		if (pos == cend())return false;
		count--;
		if (pos.ptr->next == nullptr)return false;
		list_node* ptr{ pos.ptr->next };
		pos.ptr->next = ptr->next;
		if (ptr->next == nullptr) {
			tail = pos.ptr;
		}
		else {
			ptr->next->prev = pos.ptr;
		}
		delete ptr;
		return true;
	}
};


```
