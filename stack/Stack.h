#ifndef GUARD_STACK_H
#define GUARD_STACK_H

#include <memory>

template <class T> class Stack {
public:

// Typedefs
    typedef T value_type;
    typedef T* ptr;
    typedef const T* const_ptr;
    typedef size_t size_type;
    
    // Constructors & Destructors
    Stack() { create(); }   // default constructor
    Stack(const Stack& s) { create(s.begin(), s.end()); }   // copy constructor
    ~Stack() { uncreate(); }    // destructor
    
    // Operators
    Stack& operator=(const Stack&);
    
    // Methods
    void push(const T&);
    T& pop();
    T& peek();
    size_type size() { return head - data; }

private:
    ptr data;  // pointer to the data structure 
    ptr head;  // pointer to the head of the stack
    ptr limit; // pointer to the end of the allocated data
    
    // Allocator object to manage memory allocation & release
    std::allocator<T> alloc;

    void create();
    void create(const_ptr, const_ptr);
    void uncreate();
    void grow();
    void unchecked_append(const T&);
};

template <class T>
Stack<T>& Stack<T>::operator=(const Stack& rhs)
{
    if(&rhs != this){
        uncreate();
        create(rhs.begin(), rhs.end());
    }
    return *this;
}

template <class T>
void Stack<T>::push(const T& t)
{
    if(head == limit)
        grow();
    unchecked_append(t);
}

template <class T>
T& Stack<T>::pop()
{
    return *(--head);
}

template <class T>
T& Stack<T>::peek()
{
    return *(head-1);
}

template <class T>
void Stack<T>::create()
{
    data = head = limit = 0;
}

template <class T>
void Stack<T>::create(const_ptr i, const_ptr j)
{
    data = alloc.allocate(j-i);
    limit = head = uninitialized_copy(i, j, data);
}

template <class T>
void Stack<T>::uncreate()
{
    if(data){
        ptr it = head;
        while(it != data)
            alloc.destroy(--it);
        alloc.deallocate(data, limit - data);
    }
    data = limit = head = 0;
}

template <class T>
void Stack<T>::grow()
{
    size_type new_size = std::max(2*(limit - data), ptrdiff_t(1));
    ptr new_data = alloc.allocate(new_size);
    ptr new_head = std::uninitialized_copy(data, head, new_data);

    uncreate();
    data = new_data;
    head = new_head;
    limit = data + new_size;
}

template <class T>
void Stack<T>::unchecked_append(const T& val)
{
    alloc.construct(head++, val);
}
#endif
