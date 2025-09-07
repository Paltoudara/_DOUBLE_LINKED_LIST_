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
# 📝NOTE THAT:
THIS IS THE INTERFACE OF THE DOUBLE_LINKED_LIST ,WITH THIS INTERFACE YOU CAN MANIPULATE THE LIST.IF YOU WANT MORE DETAILS ABOUT THE IMPLEMENTATION JUST SEE THE List.h and Macros.h FOR HOW THINGS ARE DONE ALSO THIS DATA STRUCTURE ACCEPTS
ONLY ELEMENTS THAT ARE NOTHROW DESTRUCTIBLE

# ⚙️Member functions
1) default constructor, this function makes the list in the default state

2) constructor with initializer list,if the function fails then the list is left in the default state (strong exception guarantee) else we just copy the elements of intializer list (deep copy)

3) copy constructor is exactly the same as the previous constructor this time the other is a double_linked_list argument,if the function fails then the list is left in the default state (strong exception guarantee)

4) move constructor,it just steals the contents of the other list and leaves it in the default state ,if this==&other then the list is left in the default state

5) the destructor deallocates all the list that was allocated (if it was) and returns the list back to the default state ,if the list is empty this func doesn't do anything

6) push_back funtion,this function just creates a list node and pushes it by copy or move at the end of the list,if something goes wrong this function doesn't do anything(strong exception guarantee)

7) push_front, this function just creates a list node and pushes it by copy or move at the start of the list,if something goes wrong this function doesn't do anything (strong exception guarantee)

8) pop_front,this function just deletes the first node of the list and updates the list ,if there exists at least one node to delete,WARNING: calling this function while the list is empty will throw an pop_from_an_empty_list exception

9) pop_back,this function just deletes the last node of the list and updates the list ,if there exists at least one node to delete,WARNING: calling this function while the list is empty will throw an pop_from_an_empty_list exception

10) show,this function prints the list forward and backward so we know that the list is valid forward and backward,use this funtion only if the elements that the container holds are printable

11) reverse,this function just reverses the list in place,if the list is like 1 2 3 4 5 the result will be 5 4 3 2 1 the reverse proccess goes like this: 12345->21345->32145->43215->54321

12) swap,this function simply swaps the contents of two double linked lists ,if this==&other then nothing happens

13) emplace_back,this function works pretty similar to the push_back function but this time  we craft the element in place with the arguments passed and we create the list node

14) emplace_front,this fucntion works pretty similar to the push_front function but this time we craft the element in place with the arguments passed and we create the list node

15) move operator,deallocs our contents and steals the other's contents, WARNING: moving into ourselves will put the list in the default state so we will lose our resources

16) insert_after,

