#ifndef ARRAY_H
#define ARRAY_H

#include <cstdlib>
#include <cstddef>
#include <iostream>

template <class T, size_t N>
class Array {
public:
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  Array();
  explicit Array(const_reference val);
  Array(const Array& array);  // Copy constructor

  // Iterators
  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();

  // Capacity
  size_type size();
  size_type max_size();
  bool empty();

private:
  T* it_begin;
  iterator it_end;

};

template <class T, size_t N>
Array<T, N>::Array(){
  it_begin = new value_type[N];
  it_end = it_begin + N;
}

// This blocks copy construction from happening when executing Array a = 0
template <class T, size_t N>
Array<T, N>::Array(const_reference val){
  it_begin = new value_type[N];
  it_end = it_begin + N;
  for(size_type i=0; i<N; ++i) {
    *(it_begin+i) = val;
  }
}

template <class T, size_t N>
typename Array<T, N>::iterator Array<T, N>::begin(){
  return it_begin;
}

template <class T, size_t N>
typename Array<T, N>::iterator Array<T, N>::end(){
  return it_end;
}

template <class T, size_t N>
typename Array<T, N>::const_iterator Array<T, N>::cbegin(){
  return it_begin;
}

template <class T, size_t N>
typename Array<T, N>::const_iterator Array<T, N>::cend(){
  return it_end;
}

// Capacity
template <class T, size_t N>
typename Array<T, N>::size_type Array<T, N>::size(){
  return it_end - it_begin;
}

template <class T, size_t N>
typename Array<T, N>::size_type Array<T, N>::max_size(){
  return it_end - it_begin;
}

template <class T, size_t N>
bool Array<T, N>::empty(){
  return it_begin != it_end;
}

#endif
