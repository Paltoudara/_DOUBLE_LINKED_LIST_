# 📚WELCOME TO THE DOUBLE_LINKED_LIST API 🌐:
# 🧩 Interface:
```markdown
```cpp
template<typename _Ty>
class double_linked_list final {
public:
	using iterator = list_node_iterator<1>;

	using const_iterator = list_node_iterator<2>;

	using reverse_iterator = list_node_iterator<3>;

	using const_reverse_iterator = list_node_iterator<4>;

	static_assert(std::is_object_v<_Ty>, "The C++ Standard forbids container adaptors of non-object types "
		"because of [container.requirements].");

	static_assert(!std::is_reference_v<_Ty>, "no references allowed");

	static_assert(!std::is_const_v<_Ty>, "no const types are allowed");

	static_assert(!std::is_volatile_v<_Ty>, "no volatile types are allowed");

	double_linked_list()noexcept;

	double_linked_list(const std::initializer_list<_Ty>& other);

	double_linked_list(const double_linked_list<_Ty>& other);

	double_linked_list(double_linked_list<_Ty>&& other)noexcept;

	double_linked_list<_Ty>& operator =(double_linked_list<_Ty>&& other) & noexcept;

	double_linked_list<_Ty>& operator =(const std::initializer_list<_Ty>& other)&;

	double_linked_list<_Ty>& operator =(const double_linked_list<_Ty>& other)&;

	bool push_back(const _Ty& data);

	bool push_back(_Ty&& data);

	bool insert_after(const_iterator pos, const _Ty& data);

	bool add_unique_after(const_iterator pos, const _Ty& data);

	template<typename _Pred1>
	bool add_unique_after(const_iterator pos, const _Ty& data, _Pred1 _Pred);

	bool push_front(const _Ty& data);

	template<class..._Valty>
	bool emplace_back(_Valty&&..._Val);

	template<class..._Valty>
	bool emplace_front(_Valty&&..._Val);

	bool push_front(_Ty&& data);

	void pop_front();

	void pop_back();

	void show()const;

	void reverse()noexcept;

	void remove(const _Ty& data);

	template<typename _Pred1>
	void remove_if(_Pred1 _Pred);

	void unique();

	template<typename _Pred1>
	void unique(_Pred1 _Pred);

	void swap(double_linked_list<_Ty>& other)noexcept;

	bool is_ascending()const;

	template<typename Compare>
	bool is_ascending(Compare comp)const;

	bool is_descending()const;

	void merge(double_linked_list<_Ty>& other);

	void merge(double_linked_list<_Ty>&& other);

	template<typename Compare>
	void merge(double_linked_list<_Ty>& other, Compare comp);

	template<typename Compare>
	void merge(double_linked_list<_Ty>&& other, Compare comp);

	template<typename Compare>
	bool is_descending(Compare comp)const;

	bool is_sorted()const;

	template<typename Compare1, typename Compare2 >
	bool is_sorted(Compare1 comp1, Compare2 comp2)const;

	bool erase_after(const_iterator pos);

	~double_linked_list()noexcept;
	bool empty()const noexcept;

	std::size_t size()const noexcept ;

	_NODISCARD _Ty&& back()&& ;

	_NODISCARD const _Ty&& back()const&& ;

	_NODISCARD const _Ty& back()const& ;

	_NODISCARD _Ty& back()& ;

	_NODISCARD const _Ty& front()const& ;

	_NODISCARD _Ty& front()& ;

	_NODISCARD _Ty&& front()&& ;

	_NODISCARD const _Ty&& front()const&&;

	iterator begin() noexcept ;
 
	const_iterator begin()const noexcept ;

	iterator end() noexcept ;

	const_iterator end()const noexcept;

	const_iterator cbegin()const noexcept ;

	const_iterator cend()const noexcept;

	reverse_iterator rbegin()noexcept ;

	const_reverse_iterator rbegin()const noexcept ;

	reverse_iterator rend() noexcept ;

	const_reverse_iterator rend()const noexcept ;

	const_reverse_iterator crbegin()const noexcept ;

	const_reverse_iterator crend()const noexcept;

	bool unsafe_insert(const_iterator pos, const _Ty& data);
    
	bool unsafe_erase(const_iterator pos)noexcept ;

};
```
