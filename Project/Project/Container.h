#pragma once

#include <iostream>
#include <stdexcept>

/**
* Class representing a container on circular buffer
* 
* Note: a gap-element after last element necessary to proper work of iterators
**/
template<class T>
class Container final {
public:
  Container();
  Container(const Container& other);
  ~Container();

  void PushFront(const T& value);
  void PushBack(const T& value);
  void PopFront();
  void PopBack();

  int Front() const;
  int Back() const;

  bool Full() const;
  bool Empty() const;
  int Size() const;
  int Capacity() const;

  void Swap(Container& other);
  void Reverse();

  void Clear();

  friend std::ostream& operator<<(std::ostream& os, const Container<T>& container) {
    for (int i = 0; i < container.m_capacity; ++i) {
      if (i == container.m_front)
        os << "(f)";
      if (i == container.m_rear)
        os << "(r)";
      os << container.m_data[i] << " ";
    }
    os << "\n";
    return os;
  };

public:
  struct Iterator;
  Iterator begin() { return Iterator(m_data, m_front, m_capacity); }
  Iterator end() { return Iterator(m_data, m_rear + 1, m_capacity); }

  struct ConstIterator;
  ConstIterator cbegin() const { return ConstIterator(m_data, m_front, m_capacity); }
  ConstIterator cend() const { return ConstIterator(m_data, m_rear + 1, m_capacity); }

private:
  void Resize();

 private:
  static const int DEFAULT_CAPACITY = 5;

  int m_size;
  int m_capacity;
  T* m_data;
  int m_front, m_rear;
};

template<class T>
inline Container<T>::Container() :
  m_size(0),
  m_capacity(DEFAULT_CAPACITY),
  m_data(new T[DEFAULT_CAPACITY]),
  m_front(-1),
  m_rear(-1)
{

}

template<class T>
inline Container<T>::Container(const Container& other) :
  m_size(other.m_size),
  m_capacity(other.m_capacity),
  m_data(new T[m_capacity]),
  m_front(-1),
  m_rear(-1)
{
  for (int i = 0; i < other.m_size; ++i) {
    m_data[i] = other.m_data[i];
  }
}

template<class T>
inline Container<T>::~Container()
{
  delete[] m_data;
}

template<class T>
void Container<T>::PushFront(const T& value)
{
  if (Full())
    Resize();
  if (m_front == -1 && m_rear == -1) {
    m_front = m_rear = 0;
    m_data[m_front] = value;
  }
  else if (m_front == 0) {
    m_front = m_capacity - 1;
    m_data[m_front] = value;
  }
  else {
    m_data[--m_front] = value;
  }
  ++m_size;
}

template<class T>
inline void Container<T>::PushBack(const T& value)
{
  if (Full())
    Resize();
  if (m_front == -1 && m_rear == -1) {
    m_front = m_rear = 0;
    m_data[m_rear] = value;
  }
  else if (m_rear == m_capacity - 1) {
    m_rear = 0;
    m_data[m_rear] = value;
  }
  else {
    m_data[++m_rear] = value;
  }
  ++m_size;
}

template<class T>
inline void Container<T>::PopFront()
{
  if (m_front == -1 && m_rear == -1)
    throw std::out_of_range("Cannot pop from empty container");
  else if (m_front == m_rear)
    m_front = m_rear = -1;
  else if (m_front == m_capacity - 1)
    m_front = 0;
  else
    ++m_front;
}

template<class T>
inline void Container<T>::PopBack()
{
  if (m_front == -1 && m_rear == -1)
    throw std::out_of_range("Cannot pop from empty container");
  else if (m_front == m_rear)
    m_front = m_rear = -1;
  else if (m_rear == 0)
    m_rear = m_capacity - 1;
  else
    --m_rear;
}

template<class T>
inline int Container<T>::Front() const
{
  if (m_front == -1 && m_rear == -1)
    throw std::out_of_range("Cannot get front from empty container");
  return m_data[m_front];
}

template<class T>
inline int Container<T>::Back() const
{
  if (m_front == -1 && m_rear == -1)
    throw std::out_of_range("Cannot get back from empty container");
  return m_data[m_rear];
}

template<class T>
inline bool Container<T>::Full() const
{
  // Store an empty gap-element to iterator correct processing
  return m_size == m_capacity - 1 || m_front == 0 && m_rear == m_capacity - 2 || m_front == m_rear + 2;
}

template<class T>
inline bool Container<T>::Empty() const
{
  return m_size == 0;
}

template<class T>
inline int Container<T>::Size() const
{
  return m_size;
}

template<class T>
inline int Container<T>::Capacity() const
{
  return m_capacity;
}

template<class T>
inline void Container<T>::Clear()
{
  delete[] m_data;
  m_size = 0;
  m_capacity = DEFAULT_CAPACITY;
  m_data = new T[DEFAULT_CAPACITY];
  m_front = m_rear = -1;
}

template<class T>
inline void Container<T>::Swap(Container& other)
{
  std::swap(m_size, other.m_size);
  std::swap(m_capacity, other.m_capacity);
  std::swap(m_data, other.m_data);
  std::swap(m_front, other.m_front);
  std::swap(m_rear, other.m_rear);
}

template<class T>
inline void Container<T>::Reverse()
{
  T* revData = new T[m_size];
  int i = 0;
  for (auto it = begin(); it != end(); ++it)
    revData[i++] = *it;
  for (auto it = begin(); it != end(); ++it)
    *it = revData[--i];
  delete[] revData;
}

template<class T>
inline void Container<T>::Resize()
{
  if (!Full())
    return;
  int newCapacity = m_capacity * 2;
  T* newData = new T[newCapacity];
  
  int iNew = 0;
  for (int i = m_front; i != m_rear + 1;) {
    newData[iNew++] = m_data[i];
    i = (i + 1) % m_capacity;
  }

  delete[] m_data;
  m_data = newData;
  m_front = 0;
  m_rear = m_capacity - 2;
  m_capacity = newCapacity;
}

template<class T>
struct Container<T>::Iterator
{
  using iterator_category = std::forward_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T*;
  using reference = T&;

  Iterator(pointer data, int idx, int size) : m_data(data), m_idx(idx), m_cap(size) {}

  reference operator*() const {
    return m_data[m_idx];
  }
  pointer operator->() {
    return &m_data[m_idx];
  }
  Iterator& operator++() {
    m_idx = (m_idx + 1) % m_cap;
    return *this;
  }
  Iterator operator++(int) {
    Iterator tmp = *this; ++(*this);
    return tmp;
  }
  friend bool operator== (const Iterator& a, const Iterator& b) {
    return a.m_data == b.m_data && a.m_idx == b.m_idx && a.m_cap == b.m_cap;
  };
  friend bool operator!= (const Iterator& a, const Iterator& b) {
    return !(a == b);
  };

private:
  pointer m_data;
  int m_idx;
  int m_cap;
};

template<class T>
struct Container<T>::ConstIterator
{
  using iterator_category = std::forward_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T*;
  using reference = T&;

  ConstIterator(pointer data, int idx, int size) : m_data(data), m_idx(idx), m_cap(size) {}

  const reference operator*() const {
    return m_data[m_idx];
  }
  pointer operator->() {
    return &m_data[m_idx];
  }
  ConstIterator& operator++() {
    m_idx = (m_idx + 1) % m_cap;
    return *this;
  }
  ConstIterator operator++(int) {
    ConstIterator tmp = *this; ++(*this);
    return tmp;
  }
  friend bool operator== (const ConstIterator& a, const ConstIterator& b) {
    return a.m_data == b.m_data && a.m_idx == b.m_idx && a.m_cap == b.m_cap;
  };
  friend bool operator!= (const ConstIterator& a, const ConstIterator& b) {
    return !(a == b);
  };

private:
  pointer m_data;
  int m_idx;
  int m_cap;
};