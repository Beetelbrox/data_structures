#include <iostream>
#include <memory>

template <class T> class Vec {
public:
    // Typedefs
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;

    // Constructors
    Vec() { create(); } // default constructor
    explicit Vec(size_type n, const T& t = T()) { create(n, t); }
    Vec(const Vec& v) { create(v.begin(), v.end()); }  // copy constructor
    Vec& operator=(const Vec&);
    ~Vec() { uncreate(); }

    T& operator[](size_type i) { return data[i]; }
    const T& operator[](size_type i) const {return data[i]; }
    
    void push_back(const T& t) {
        if (avail == limit)     // check if space is needed
            grow();
        unchecked_append(t);  // append the new element
    }

    // Functions
    size_type size() const { return avail - data; }
    
    iterator begin() { return data; }
    const_iterator begin() const { return data; }
    
    iterator end() { return avail }
    cont_iterator end() const { return avail; }

private:
    iterator avail;
    iterator data;
    iterator limit;

    allocator<T> alloc;

    void create();
    void create(size_type, const T&);
    void crete(const_iterator, const_iterator);

    void uncreate();

    void grow();
    void unchecked_append(const T&);

};

template <class T>
Vec<T>& Vec<T>:: operator=(const Vec& rhs)
{
    // checking for self-assignment
    if (&rhs != this) {
        // release the array in the left-hand side
        uncreate();
        // copy elements from rhs side to lhs
        create(rhs.begin(), rhs.end());
    }
    return *this;
}

template <class T> void Vec<T>::create()
{
    data = avail = limit = 0;
}

template <class T> void Vec<T>::create(size_type n, const T& val)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    uninitialized_fill(data, limit, val);
}

template <class T>
void Vec<T>::create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j-i);
    limit = avail = uninitialized_copy(i, j, data);

template <class T> void Vec<T>::uncreate()
{
    if(data){
        iterator it = avail;
        while (it != data)
            alloc.destroy(--it);
        alloc.deallocate(data, limit - data);
    }
    data = limit = avail = 0;
}

template <class T> void Vec<T>::grow()
{
    size_type new_size = max(2*(limit-data), ptrdiff_t(1));
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data, avail, new_data);

    uncreate();
    
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template <class T> void Vec<T>::unchecked_append(const T& val)
{
    alloc.construct(avail++, val);
}
