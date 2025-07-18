# _DOUBLE_LINKED_LIST_
# Simple DOUBLE LINKED LSIT header that i created using C++
🧱 AN entire _DOUBLE_LINKED_LIST_ with all the basic features:
</br>
1. an inside class of a simple list node that has pointers to previous and next with constructors<br>
~the default </br>
~with const element</br>
~with move element</br>
~and a private constructor used to craft the object in place (see implementation)
2. an inside class of a simple iterator (pretty much a wrapper around a pointer that points to a node or to nothing nullptr),
   with the iterator you have access to change the element or to see it and advance or go backwards
   operations supported: ++,!=,==,*,+=,->,+,--,-,-= and a couple of constructors and adestructor and acopy operator and a move operator
3. another inside class of a simple const iterator (pretty much a wrapper around a pointer that points to a node or to nothing nullptr),this kind of iterator works pretty similar to the iterator that we talked above the only difference is
   that this iterator is only used to see elements not to change them
4. another inside class of a simple reverse iterator (pretty much a wrapper around a pointer that points to a node or to nothing nullptr),this kind of iterator again is similar to the iterators talked above but this time the operations that
   are for advance make the iterator go backwards and the operations to go backwards this time make you go forward like : ++,+=,+ make you go backward in the list, and --,-=,- make you go forward in the list
5. another inside class of a simple const reverse iterator the differences with this and the reverse iterator is that now we can only see elements not change them
6. the private funcs start,finish,cstart,cfinish,rstart,rfinish,crstart,crfinish,
7. the private members head,tail,count in order to maintain and manipulate the list
8. push_back function which puts the element at  the end of the list
9. push_front function  which put the element at the start of the list
10. pop_front which delete the first element of the list
11. pop_back which delete the last element of the list
12. clear this function is used to deallocate the list
13. reverse this function just reverses the list nothing more
14. emplace_back this function is the same with push_back, the only difference is that the pointer is crafted differently from push_back, the object of the node is crafted in place
15. emplace_front this function is the same with push_front, the only difference is that the pointer is crafted differently from push_front, the object of the node is crafted in place
16. insert ,this function takes a const_iterator position and inserts the element after this position
17. add_unique pretty much is the same case with insert except that the only difference is that we search the list to find if the element exists if we find it we do not insert it
18. erase_node_if erases nodes of the list if a certain condition is met with the help of the passed function the argument _Pred
19. delete_duplicates,it just deletes the duplicates but we consider that the list is sorted if it is not we might want to use a hashset in order to keep track of the elements
20. is_ascending_ checks if the elements are in ascending order using a compare func
21. is_descending_ checks if the elements are in descending order using a compare func
22. is_sorted_ checks if the elements are either sorted in  ascending or descending order
23. merge_lists just combines two lists and leaves the other empty,in order for this func to work properly we consider that the two lists are sorted in ascending order and the other list is not empty else whats the point
    and also we must not try to merge a list into itselft simple enough
# 👥CONTRIBUTORS:

~The-Mastermind1
