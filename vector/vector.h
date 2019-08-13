#ifndef GUARD_VEC_H
#define GUARD_VEC_H

template <class T> class Vector {
public:
    // Typedefs
    typedef size_t size_type;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* iterator;
    typedef const T* const_iterator;

    // Constructors
    Vector();// default constructor
    explicit Vector( size_type n, const T& t = T() );
    Vector( const Vec& v );  // copy constructor
    Vec& operator=( const Vector& );
    ~Vec();

    T& operator[](size_type i);
    const T& operator[](size_type i);

    void push_back(const T& t);

    // Functions
    size_type size() const;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

private:
  // Pointers to the data
  T* begin;    // Pointer to the beginning of the vector
  T* avail;   // Pointer to the first available slot in the vector
  T* end;   // Pointer to the first element outside the vector

    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    void uncreate();

    void grow();
    void unchecked_append(const T&);

};

// Default Constructor
template <class T>
Vector(): begin { 0 }, avail { 0 } end { 0 } {}

// Constant value initializer
template <class T>
explicit Vector( size_type n, const_reference t = T() ) {
  data = new value_type[n];
  avail = end = data + n;
  for ( int i=0; i < n; ++i ){
    *(data+i) = t;
  }
}

// Copy constructor
template <class T>
Vector( const_reference v ) {
  data = new value_type[v.end-v.begin];
  create( v );
}

Vec& operator=( const Vector& );
~Vec() { uncreate(); }

T& operator[](size_type i) { return data[i]; }
const T& operator[](size_type i) const { return data[i]; }

void push_back(const T& t)
{
    if (avail == limit)
        grow();
    unchecked_append(t);
}

// Functions
size_type size() const { return avail - data; }

iterator begin() { return data; }
const_iterator begin() const { return data; }

iterator end() { return avail; };http://localhost:8888/notebooks/S2-03-Supervised_Learning-Classification.ipynb
const_iterator end() const { return avail; };

template <class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
    // check for self-assignment
    if (&rhs != this) {
        uncreate();
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
}

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
    size_type new_size = std::max(2*(limit - data), ptrdiff_t(1));
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    uncreate();

    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template <class T>
void Vec<T>::unchecked_append(const T& val)
{
    alloc.construct(avail++, val);
}

#endif
