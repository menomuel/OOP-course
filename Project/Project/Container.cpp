#include "Container.h"

//Container::Container() : 
//  m_size(0),
//  m_capacity(DEFAULT_CAPACITY),
//  m_data(new int[DEFAULT_CAPACITY]),
//  m_front(-1),
//  m_rear(-1)
//{
//}

//Container::Container(const Container& other) :
//  m_size(other.m_size),
//  m_capacity(other.m_capacity),
//  m_data(new int[m_capacity]),
//  m_front(-1),
//  m_rear(-1)
//{
//  for (int i = 0; i < other.m_size; ++i) {
//    m_data[i] = other.m_data[i];
//  }
//}

//
//Container::Container(Container&& other) noexcept:
//  m_size(other.m_size),
//  m_capacity(other.m_capacity),
//  m_data(other.m_data)
//{
//  other.m_size = 0;
//  other.m_capacity = 0;
//  other.m_data = nullptr;
//}

//Container::~Container()
//{
//  delete[] m_data;
//}

//void Container::PushFront(int value)
//{
//  if (Full())
//    Resize();
//  if (m_front == -1 && m_rear == -1) {
//    m_front = m_rear = 0;
//    m_data[m_front] = value;
//  }
//  else if (m_front == 0) {
//    m_front = m_capacity - 1;
//    m_data[m_front] = value;
//  }
//  else {
//    m_data[--m_front] = value;
//  }
//  ++m_size;
//}

//void Container::PushBack(int value) {
//  if (Full())
//    Resize();
//  if (m_front == -1 && m_rear == -1) {
//    m_front = m_rear = 0;
//    m_data[m_rear] = value;
//  }
//  else if (m_rear == m_capacity - 1) {
//    m_rear = 0;
//    m_data[m_rear] = value;
//  }
//  else {
//    m_data[++m_rear] = value;
//  }
//  ++m_size;
//}

//void Container::PopFront() {
//  if (m_front == -1 && m_rear == -1)
//    throw std::out_of_range("Cannot pop from empty container");
//  else if (m_front == m_rear)
//    m_front = m_rear = -1;
//  else if (m_front == m_capacity - 1)
//    m_front = 0;
//  else
//    ++m_front;
//}

//void Container::PopBack() {
//  if (m_front == -1 && m_rear == -1)
//    throw std::out_of_range("Cannot pop from empty container");
//  else if (m_front == m_rear)
//    m_front = m_rear = -1;
//  else if (m_rear == 0)
//    m_rear = m_capacity - 1;
//  else
//    --m_rear;
//}

//int Container::Front() const
//{
//  if (m_front == -1 && m_rear == -1)
//    throw std::out_of_range("Cannot get front from empty container");
//  return m_data[m_front];
//}

//int Container::Back() const
//{
//  if (m_front == -1 && m_rear == -1)
//    throw std::out_of_range("Cannot get back from empty container");
//  return m_data[m_rear];
//}

//bool Container::Full() const
//{
//  return m_size == m_capacity || m_front == 0 && m_rear == m_capacity - 1 || m_front == m_rear + 1;
//}
//
//bool Container::Empty() const
//{
//  return m_size == 0;
//}
//
//int Container::Size() const
//{
//  return m_size;
//}
//
//int Container::Capacity() const
//{
//  return m_capacity;
//}
//
//void Container::Clear()
//{
//  delete[] m_data;
//  m_size = 0;
//  m_capacity = DEFAULT_CAPACITY;
//  m_data = new int[DEFAULT_CAPACITY];
//  m_front = m_rear = -1;
//}

//void Container::Swap(Container& other)
//{
//  std::swap(m_size, other.m_size);
//  std::swap(m_capacity, other.m_capacity);
//  std::swap(m_data, other.m_data);
//  std::swap(m_front, other.m_front);
//  std::swap(m_rear, other.m_rear);
//}
//
//void Container::Resize()
//{
//  if (!Full())
//    return;
//  int newCapacity = m_capacity * 2;
//  int* newData = new int[newCapacity];
//  int iNew = 0;
//  for (int i = m_front; i != m_rear;) {
//    newData[iNew] = m_data[i];
//    ++iNew;
//    i = (i + 1) % m_capacity;
//  }
//  newData[iNew] = m_data[m_rear];
//
//  delete[] m_data;
//  m_data = newData;
//  m_front = 0;
//  m_rear = m_capacity - 1;
//  m_capacity = newCapacity;
//}

//std::ostream& operator<<(std::ostream& os, const Container& container)
//{
//  for (int i = 0; i < container.m_capacity; ++i) {
//    if (i == container.m_front)
//      os << "(f)";
//    if (i == container.m_rear)
//      os << "(r)";
//    os << container.m_data[i] << " ";
//  }
//  os << "\n";
//  return os;
//}
